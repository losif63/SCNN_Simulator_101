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
    _max_OA_H_per_PE = _max_OA_h/_arch_cfg->get_pe_arr_H();
    _max_OA_W_per_PE = _max_OA_w/_arch_cfg->get_pe_arr_W();
    _base_offset_h_in_OA = _max_OA_H_per_PE * _pe_arr_h_idx;
    _base_offset_w_in_OA = _max_OA_W_per_PE * _pe_arr_w_idx;
    _max_idx_h_in_OA = _max_OA_H_per_PE * (_pe_arr_h_idx + 1) - 1;
    _max_idx_w_in_OA = _max_OA_W_per_PE * (_pe_arr_w_idx + 1) - 1;
}

/* Empty WFIFO and IARAM */
void MultArray::clean() {

}

/* Some vectors will not be filled completely --> fill rest with invalid vectors */
/* During multiplication, only use valid entries!! */
void MultArray::fill_WFIFO_and_IARAM(unsigned N_id, unsigned C_id, unsigned chunk_id) {
    /* Fill WFIFO */
    /* K range: (chunk_id * chunk_sz) ~ (chunk_id * chunk_sz + chunk_sz-1) */
    int index = 0;
    W_vec_entry* Wvec = new W_vec_entry;
    /* Buffer size: C * Kc * S * R, but C is determined */
    /* Therefore, must iterate through Kc * S * R */
    while(index < _layer_cfg.get_chunk_sz() * _layer_cfg.get_S() * _layer_cfg.get_R()) {
        int kIndex = (index / (_layer_cfg.get_S() * _layer_cfg.get_R())) + chunk_id * _layer_cfg.get_chunk_sz();
        int sIndex = (index % (_layer_cfg.get_S() * _layer_cfg.get_R())) / _layer_cfg.get_R();
        int rIndex = index % _layer_cfg.get_R();
        if(_W->get_data(kIndex, C_id, sIndex, rIndex) != 0.0) {
            W_element w_elem(true, _W->get_data(kIndex, C_id, sIndex, rIndex), tuple<int, int, int, int>(kIndex, C_id, sIndex, rIndex));
            Wvec->push_back(w_elem);
            // cout << "[" << kIndex << ", " << C_id << ", " << sIndex << ", " << rIndex << "] inserted" << endl;
        }
        if(Wvec->size() == _arch_cfg->get_mult_arr_F()) {
            _WFIFO.push_back(Wvec);
            Wvec = new W_vec_entry;
        }
        index++;
    }
    if(Wvec->size() != 0) {
        while(Wvec->size() < _arch_cfg->get_mult_arr_F()) {
            W_element dummy(false, 0.0, tuple<int, int, int, int>(-1, -1, -1, -1));
            Wvec->push_back(dummy);
        }
        _WFIFO.push_back(Wvec);
    }

    /* Fill IARAM */
    index = 0;
    unsigned slice_H = (_layer_cfg.get_H()/_arch_cfg->get_pe_arr_H()) + _layer_cfg.get_S() - 1;
    unsigned slice_W = (_layer_cfg.get_W()/_arch_cfg->get_pe_arr_W()) + _layer_cfg.get_R() - 1;
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
            // cout << "[" << N_id << ", " << C_id << ", " << actualH << ", " << actualW << "] " << _IA_slice->get_data(N_id, C_id, hIndex, wIndex) << " inserted" << endl;
        }
        if(IAvec->size() == _arch_cfg->get_mult_arr_I()) {
            _IARAM.push_back(IAvec);
            IAvec = new IA_vec_entry;
        }
        index++;
    }
    if(IAvec->size() != 0) {
        while(IAvec->size() < _arch_cfg->get_mult_arr_I()) {
            IA_element dummy(false, 0.0, tuple<int, int, int, int>(-1, -1, -1, -1));
            IAvec->push_back(dummy);
        }
        _IARAM.push_back(IAvec);
    }
}

void MultArray::check_IA_slice_sanity(dlsim::Fmap4d_t* IA_full, unsigned N_id, unsigned C_id) {
    throw runtime_error("SCNN::MultArray check_IA_slice_sanity is not yet implemented");
}

// Xbar contains channels of OA_element
void MultArray::cycle(Scnn::Xbar* xbar) {
    throw runtime_error("SCNN::MultArray cycle is not yet implemented");
}

bool MultArray::idle() {
    throw runtime_error("SCNN::MultArray idle is not yet implemented");
}

bool MultArray::compute_mul_array_output(Scnn::Xbar* xbar) {
    throw runtime_error("SCNN::MultArray compute_mul_array_output is not yet implemented");
}

int MultArray::accum_addr_in_1d(tensor_4D_idx oa_idx) {
    throw runtime_error("SCNN::MultArray accum_addr_in_1d is not yet implemented");
}

unsigned MultArray::accum_addr_to_bank_id(unsigned mode, int accum_addr, unsigned num_accum_banks) {
    throw runtime_error("SCNN::MultArray accum_addr_to_bank_id is not yet implemented");
}

unsigned MultArray::idx_in_bank(unsigned mode, int accum_addr, unsigned num_accum_banks) {
    throw runtime_error("SCNN::MultArray idx_in_bank is not yet implemented");
}

tuple<unsigned,unsigned> MultArray::OA_idx_to_bank_addr(tensor_4D_idx oa_idx) {
    throw runtime_error("SCNN::MultArray OA_idx_to_bank_addr is not yet implemented");
}

void MultArray::advance_WFIFO() {
    vector<Scnn::W_element>* wvec = _WFIFO.front();
    _WFIFO.pop_front();
    _WFIFO.push_back(wvec);
}

void MultArray::advance_IARAM() {
    vector<Scnn::IA_element>* iavec = _IARAM.front();
    _IARAM.pop_front();
    _IARAM.push_back(iavec);
}

void MultArray::advance_to_next_mul_op() {
    throw runtime_error("SCNN::MultArray advance_to_next_mul_op is not yet implemented");
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
    throw runtime_error("SCNN::MultArray end_of_WFIFO is not yet implemented");
}

bool MultArray::end_of_IARAM() {
    throw runtime_error("SCNN::MultArray end_of_IARAM is not yet implemented");
}

unsigned MultArray::size_WFIFO() {
    return _WFIFO.size();
}

unsigned MultArray::size_IARAM() {
    return _IARAM.size();
}

void MultArray::set_pe_arr_h_idx(int h) {
    _pe_arr_h_idx = h;
}

void MultArray::set_pe_arr_w_idx(int w) {
    _pe_arr_w_idx = w;
}

}

#endif