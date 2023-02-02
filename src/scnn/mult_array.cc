/*
* Filename: mult_array.cc
* File created by Jaduk Suh
* Date: January, 2023
*/

#ifndef SCNN_MULT_ARRAY_CC_
#define SCNN_MULT_ARRAY_CC_

#include "scnn/mult_array.h"

namespace Scnn {

MultArray::MultArray(Scnn::ArchConfig& arch_cfg) {
    _arch_cfg = new ArchConfig(
        arch_cfg.get_pe_arr_W(),
        arch_cfg.get_pe_arr_H(),
        arch_cfg.get_mult_arr_F(),
        arch_cfg.get_mult_arr_I(),

        arch_cfg.get_xbar_in_num_phy_ch_q(),
        arch_cfg.get_xbar_in_num_q_entries_per_phy_ch(),
        arch_cfg.get_xbar_out_num_phy_ch_q(),
        arch_cfg.get_xbar_out_num_q_entries_per_phy_ch(),

        arch_cfg.get_xbar_scale_out_ratio(),
        arch_cfg.get_xbar_in(),
        arch_cfg.get_xbar_out(),

        arch_cfg.get_chunk_sz_for_accum_bank_sizing(),
        arch_cfg.get_max_num_elem_per_bank(),

        arch_cfg.get_max_OA_H_per_PE(),
        arch_cfg.get_max_OA_W_per_PE(),
        arch_cfg.get_min_OA_H_per_PE(),
        arch_cfg.get_min_OA_W_per_PE()
    );
}

MultArray::~MultArray() {
    delete _arch_cfg;
}


void MultArray::init(Scnn::LayerConfig& layer_cfg, dlsim::Fmap4d_t* IA_slice, dlsim::Weight4d_t* W) {
    this->_layer_cfg = layer_cfg;
    this->_IA_slice = IA_slice;
    this->_W = W;
    
    _max_r = layer_cfg.get_R();
    _max_s = layer_cfg.get_S();
    _pad_h_sz = (layer_cfg.get_S() - 1)/2;
    _pad_w_sz = (layer_cfg.get_R() - 1)/2;
    _stride_r = 1;
    _stride_s = 1;
    _max_IA_h = layer_cfg.get_H();
    _max_IA_w = layer_cfg.get_W();
    _max_OA_h = _max_IA_h + (2 * _pad_h_sz) - _max_s + 1;
    _max_OA_w = _max_IA_w + (2 * _pad_w_sz) - _max_r + 1;
    _max_OA_H_per_PE = (int)ceil((float)_max_OA_h/(float)_arch_cfg->get_pe_arr_H());
    _max_OA_W_per_PE = (int)ceil((float)_max_OA_w/(float)_arch_cfg->get_pe_arr_W());
    _base_offset_h_in_OA = _max_OA_H_per_PE * _pe_arr_h_idx;
    _base_offset_w_in_OA = _max_OA_W_per_PE * _pe_arr_w_idx;
    _max_idx_h_in_OA = _max_OA_H_per_PE * (_pe_arr_h_idx + 1) - 1;
    _max_idx_w_in_OA = _max_OA_W_per_PE * (_pe_arr_w_idx + 1) - 1;
}

/* Empty WFIFO and IARAM */
void MultArray::clean() {
    clear_both_WFIFO_and_IARAM();
}

/* Some vectors will not be filled completely --> fill rest with invalid vectors */
/* During multiplication, only use valid entries!! */
void MultArray::fill_WFIFO_and_IARAM(unsigned N_id, unsigned C_id, unsigned chunk_id) {
    /* Fill WFIFO */
    /* K range: (chunk_id * chunk_sz) ~ (chunk_id * chunk_sz + chunk_sz-1) */
    int index = 0;
    int WFIFO_size = 0;
    int IARAM_size = 0;
    W_vec_entry* Wvec = new W_vec_entry;
    /* Buffer size: C * Kc * S * R, but C is determined */
    /* Therefore, must iterate through Kc * S * R */
    /* If Kc is not valid, then don't insert & continue */
    while(index < _layer_cfg.get_chunk_sz() * _layer_cfg.get_S() * _layer_cfg.get_R()) {
        int kIndex = (index / (_layer_cfg.get_S() * _layer_cfg.get_R())) + chunk_id * _layer_cfg.get_chunk_sz();
        int sIndex = (index % (_layer_cfg.get_S() * _layer_cfg.get_R())) / _layer_cfg.get_R();
        int rIndex = index % _layer_cfg.get_R();
        if(kIndex >= _layer_cfg.get_K()) {
            index++;
            continue;
        }
        if(_W->get_data(kIndex, C_id, sIndex, rIndex) != 0.0) {
            W_element w_elem(true, _W->get_data(kIndex, C_id, sIndex, rIndex), tuple<int, int, int, int>(kIndex, C_id, sIndex, rIndex));
            Wvec->push_back(w_elem);
            // cout << "[" << kIndex << ", " << C_id << ", " << sIndex << ", " << rIndex << "] inserted" << endl;
        }
        if(Wvec->size() == _arch_cfg->get_mult_arr_F()) {
            _WFIFO.push_back(Wvec);
            Wvec = new W_vec_entry;
            WFIFO_size++;
        }
        index++;
    }
    if(Wvec->size() != 0) {
        while(Wvec->size() < _arch_cfg->get_mult_arr_F()) {
            W_element dummy(false, 0.0, tuple<int, int, int, int>(-1, -1, -1, -1));
            Wvec->push_back(dummy);
        }
        _WFIFO.push_back(Wvec);
        WFIFO_size++;
    }

    /* Fill IARAM */
    index = 0;
    unsigned slice_H = (int)ceil(((float)_layer_cfg.get_H() / (float)_arch_cfg->get_pe_arr_H())) + _layer_cfg.get_S() - 1;
    unsigned slice_W = (int)ceil(((float)_layer_cfg.get_W() / (float)_arch_cfg->get_pe_arr_W())) + _layer_cfg.get_R() - 1;
    IA_vec_entry* IAvec = new IA_vec_entry;
    /* Buffer size: N * C * H * W, but N and C are determined */
    /* Therefore, must iterate through H * W */
    /* However, note that H and W are *tiled* for each PEs */
    while(index < slice_H * slice_W){
        int hIndex = index / slice_W;
        int wIndex = index % slice_W;
        int actualH = hIndex - _pad_h_sz + _base_offset_h_in_OA;
        int actualW = wIndex - _pad_w_sz + _base_offset_w_in_OA;
        if(_IA_slice->get_data(N_id, C_id, hIndex, wIndex) != 0.0) {
            IA_element ia_elem(true, _IA_slice->get_data(N_id, C_id, hIndex, wIndex), tuple<int, int, int, int>(N_id, C_id, actualH, actualW));
            IAvec->push_back(ia_elem);
            // DEBUG
            // cout << "[" << N_id << ", " << C_id << ", " << actualH << ", " << actualW << "] " << _IA_slice->get_data(N_id, C_id, hIndex, wIndex) << " inserted" << endl;
        }
        if(IAvec->size() == _arch_cfg->get_mult_arr_I()) {
            _IARAM.push_back(IAvec);
            IAvec = new IA_vec_entry;
            IARAM_size++;
        }
        index++;
    }
    if(IAvec->size() != 0) {
        while(IAvec->size() < _arch_cfg->get_mult_arr_I()) {
            IA_element dummy(false, 0.0, tuple<int, int, int, int>(-1, -1, -1, -1));
            IAvec->push_back(dummy);
        }
        _IARAM.push_back(IAvec);
        IARAM_size++;
    }

    // DEBUG
    // cout << "***WFIFO SIZE***: " << WFIFO_size << ", " << _WFIFO.size() << endl;
    // cout << "***IARAM SIZE***: " << IARAM_size << ", " << _IARAM.size() << endl;
    _curr_WFIFO_size = _WFIFO.size();
    _curr_IARAM_size = _IARAM.size();
    _c_WFIFO_advance = 1;
    _c_IARAM_advance = 1;
}

void MultArray::check_IA_slice_sanity(dlsim::Fmap4d_t* IA_full, unsigned N_id, unsigned C_id) {
    throw runtime_error("SCNN::MultArray check_IA_slice_sanity is not yet implemented");
}

// Here, we must check 2 things
// First, if xbar is not idle (input port not cleared) then stall (return)
// Second, if this multArray is currently idle, then return
void MultArray::cycle(Scnn::Xbar* xbar) {
    if(idle()) return;
    if(!xbar->idle()) return;
    compute_mul_array_output(xbar);
    advance_to_next_mul_op();

}

bool MultArray::idle() {
    return end_of_mult();
}

bool MultArray::compute_mul_array_output(Scnn::Xbar* xbar) {
    W_vec_entry* wvec = curr_WFIFO_entry();
    IA_vec_entry* iavec = curr_IARAM_entry();

    // DEBUG
    // cout << endl;
    // cout << "Current PE: " << _pe_arr_h_idx << ", " << _pe_arr_w_idx << endl;
    // cout << "Current WFIFO & entry size: " << _WFIFO.size() << ", " << wvec->size() << endl;
    // cout << "Current IARAM & entry size: " << _IARAM.size() << ", " << iavec->size() << endl;
    if((_IARAM.size() == 0) || (_WFIFO.size() == 0)) return true;
    for(int i = 0; i < wvec->size(); i++) {
        for(int j = 0; j < iavec->size(); j++) {
            /* If either one of WFIFO or IARAM is a dummy, then continue */
            if((*wvec)[i].get_valid() == false) {
                // DEBUG
                // cout << "Weight dummy" << endl;
                continue;
            }
            if((*iavec)[j].get_valid() == false) {
                // DEBUG
                // cout << "Input dummy" << endl;
                continue;
            }
            int y_displacement = (_layer_cfg.get_S()-1)/2 - get<2>((*wvec)[i].get_idx());
            int x_displacement = (_layer_cfg.get_R()-1)/2 - get<3>((*wvec)[i].get_idx());
            tuple<int, int, int, int> oa_idx = tuple<int, int, int, int>(
                get<0>((*iavec)[j].get_idx()),
                get<0>((*wvec)[i].get_idx()),
                get<2>((*iavec)[j].get_idx()) + y_displacement,
                get<3>((*iavec)[j].get_idx()) + x_displacement
            );
            /* If the resulting H and W values are not in range,
               Do not create an OA_element and just simply continue.
            */
           int max_h_idx = (_max_idx_h_in_OA < (_layer_cfg.get_H() - 1)) ? _max_idx_h_in_OA : _layer_cfg.get_H() - 1;
           int max_w_idx = (_max_idx_w_in_OA < (_layer_cfg.get_W() - 1)) ? _max_idx_w_in_OA : _layer_cfg.get_W() - 1;
            if((get<2>(oa_idx) < _base_offset_h_in_OA) || (get<2>(oa_idx) > max_h_idx)) {
                //DEBUG
                // cout << "Input [" << get<0>((*iavec)[j].get_idx()) << ", " << get<1>((*iavec)[j].get_idx()) << ", " << get<2>((*iavec)[j].get_idx()) << ", " << get<3>((*iavec)[j].get_idx()) << ", " << (*iavec)[j].get_data() << "] | ";
                // cout << "Weight [" << get<0>((*wvec)[i].get_idx()) << ", " << get<1>((*wvec)[i].get_idx()) << ", " << get<2>((*wvec)[i].get_idx()) << ", " << get<3>((*wvec)[i].get_idx()) << ", " << (*wvec)[i].get_data() << "] | ";
                // cout << "H not in range " << _base_offset_h_in_OA << " ~ " << max_h_idx << " [" << get<0>(oa_idx) << ", " << get<1>(oa_idx) << ", " << get<2>(oa_idx) << ", " << get<3>(oa_idx) << ", " << (*wvec)[i].get_data() * (*iavec)[j].get_data() << "]" << endl;
                continue;
            }
            if((get<3>(oa_idx) < _base_offset_w_in_OA) || (get<3>(oa_idx) > max_w_idx)) {
                // cout << "Input [" << get<0>((*iavec)[j].get_idx()) << ", " << get<1>((*iavec)[j].get_idx()) << ", " << get<2>((*iavec)[j].get_idx()) << ", " << get<3>((*iavec)[j].get_idx()) << ", " << (*iavec)[j].get_data() << "] | ";
                // cout << "Weight [" << get<0>((*wvec)[i].get_idx()) << ", " << get<1>((*wvec)[i].get_idx()) << ", " << get<2>((*wvec)[i].get_idx()) << ", " << get<3>((*wvec)[i].get_idx()) << ", " << (*wvec)[i].get_data() << "] | ";
                // cout << "W not in range " << _base_offset_w_in_OA << " ~ " << max_w_idx << " [" << get<0>(oa_idx) << ", " << get<1>(oa_idx) << ", " << get<2>(oa_idx) << ", " << get<3>(oa_idx) << ", " << (*wvec)[i].get_data() * (*iavec)[j].get_data() << "]" << endl;
                continue;
            }
            // DEBUG
            // cout << "Input [" << get<0>((*iavec)[j].get_idx()) << ", " << get<1>((*iavec)[j].get_idx()) << ", " << get<2>((*iavec)[j].get_idx()) << ", " << get<3>((*iavec)[j].get_idx()) << ", " << (*iavec)[j].get_data() << "] | ";
            // cout << "Weight [" << get<0>((*wvec)[i].get_idx()) << ", " << get<1>((*wvec)[i].get_idx()) << ", " << get<2>((*wvec)[i].get_idx()) << ", " << get<3>((*wvec)[i].get_idx()) << ", " << (*wvec)[i].get_data() << "] | ";
            // cout << "TEST:: Partial Sum [" << get<0>(oa_idx) << ", " << get<1>(oa_idx) << ", " << get<2>(oa_idx) << ", " << get<3>(oa_idx) << ", " << (*wvec)[i].get_data() * (*iavec)[j].get_data() << "]" << endl;
            OA_element oa_elem(
                (*wvec)[i].get_valid() && (*iavec)[j].get_valid(),
                (*wvec)[i].get_data() * (*iavec)[j].get_data(),
                oa_idx,
                get<0>(OA_idx_to_bank_addr(oa_idx)),
                get<1>(OA_idx_to_bank_addr(oa_idx))
            );
            // DEBUG
            // cout << "- - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
            // (*iavec)[j].print();
            // (*wvec)[i].print();
            // oa_elem.print();
            // cout << "- - - - - - - - - - - - - - - - - - - - - - - - -" << endl;

            int port_in_id = i * iavec->size() + j;
            xbar->port_in()->receive(oa_elem, port_in_id);
        }
    }
    return true;
}

/* Method that generates an "accumulator address" from output index */
int MultArray::accum_addr_in_1d(tensor_4D_idx oa_idx) {
    unsigned chunk_size = _layer_cfg.get_chunk_sz();
    unsigned pe_h = _IA_slice->dim_sz('H');
    unsigned pe_w = _IA_slice->dim_sz('W');

    unsigned hash_k = get<1>(oa_idx) % chunk_size;
    unsigned hash_h = get<2>(oa_idx) % pe_h;
    unsigned hash_w = get<3>(oa_idx) % pe_w;

    unsigned hash = 0;
    hash += get<0>(oa_idx) * chunk_size * pe_h * pe_w;
    hash += hash_k * pe_h * pe_w;
    hash += hash_h * pe_w;
    hash += hash_w;

    return hash;
}
/* Method that generates bank id from an "accumulator address" */
unsigned MultArray::accum_addr_to_bank_id(unsigned mode, int accum_addr, unsigned num_accum_banks) {
    return (accum_addr % num_accum_banks);
}

/* Method that generates bank index from an "accumulator address" */
unsigned MultArray::idx_in_bank(unsigned mode, int accum_addr, unsigned num_accum_banks) {
    return (accum_addr / num_accum_banks);
}

/* Method that geneartes bank id * index from output index */
tuple<unsigned,unsigned> MultArray::OA_idx_to_bank_addr(tensor_4D_idx oa_idx) {
    int accum_addr = accum_addr_in_1d(oa_idx);
    unsigned bank_id = accum_addr_to_bank_id(0, accum_addr, _arch_cfg->get_xbar_out());
    unsigned bank_idx = idx_in_bank(0, accum_addr, _arch_cfg->get_xbar_out());
    return tuple<unsigned, unsigned>(bank_id, bank_idx);
}

void MultArray::advance_WFIFO() {
    vector<Scnn::W_element>* wvec = _WFIFO.front();
    _WFIFO.pop_front();
    _WFIFO.push_back(wvec);
    _c_WFIFO_advance++;
}

void MultArray::advance_IARAM() {
    vector<Scnn::IA_element>* iavec = _IARAM.front();
    _IARAM.pop_front();
    _IARAM.push_back(iavec);
    _c_IARAM_advance++;
}


void MultArray::advance_to_next_mul_op() {
    /*
    * We need to multiply all IARAM vectors with all WFIFO vectors
    * To do so, we first advance IARAM only
    * After completing an IARAM cycle, advance WFIFO and repeat
    */
    if(end_of_IARAM()) {
        // DEBUG
        // cout << "Advance WFIFO & ";
        advance_WFIFO();
    }
    advance_IARAM();
    // DEBUG
    // cout << "Advance IARAM" << endl;
}

void MultArray::clear_both_WFIFO_and_IARAM(){
    while(!_WFIFO.empty()) {
        delete(_WFIFO.front());
        _WFIFO.pop_front();
    }
    while(!_IARAM.empty()) {
        delete(_IARAM.front());
        _IARAM.pop_front();
    }
    _curr_WFIFO_size = 0;
    _curr_IARAM_size = 0;
    _c_WFIFO_advance = 0;
    _c_IARAM_advance = 0;
}

// helper functions
bool MultArray::is_empty_WFIFO() {
    return _WFIFO.empty();
}

bool MultArray::is_empty_IARAM(){
    return _IARAM.empty();
}

// get
W_vec_entry* MultArray::curr_WFIFO_entry() {
    return _WFIFO.front();
}

IA_vec_entry* MultArray::curr_IARAM_entry() {
    return _IARAM.front();
}    

bool MultArray::end_of_WFIFO() {
    if(_curr_IARAM_size == 0) return true;
    return ((_c_WFIFO_advance % _curr_WFIFO_size) == 0);
}

bool MultArray::end_of_IARAM() {
    if(_curr_IARAM_size == 0) return true;
    return ((_c_IARAM_advance % _curr_IARAM_size) == 0);
}

bool MultArray::end_of_mult() {
    if((_curr_WFIFO_size == 0) || (_curr_IARAM_size == 0)) return true;
    return ((_c_IARAM_advance > 1) && (((_c_IARAM_advance - 1) % (_curr_WFIFO_size * _curr_IARAM_size)) == 0));
}

unsigned MultArray::size_WFIFO() {
    return _curr_WFIFO_size;
}

unsigned MultArray::size_IARAM() {
    return _curr_IARAM_size;
}

void MultArray::set_pe_arr_h_idx(int h) {
    _pe_arr_h_idx = h;
}

void MultArray::set_pe_arr_w_idx(int w) {
    _pe_arr_w_idx = w;
}

}

#endif