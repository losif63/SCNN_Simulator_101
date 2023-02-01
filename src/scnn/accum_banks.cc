/*
* Filename: accum_banks.cc
* File created by Jaduk Suh
* Date: January, 2023
*/

#ifndef SCNN_ACCUM_BANKS_CC_
#define SCNN_ACCUM_BANKS_CC_

#include "scnn/accum_banks.h"

namespace Scnn
{

AccumulatorBanks::AccumulatorBanks(Scnn::ArchConfig& arch_cfg) {
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

    _num_banks = arch_cfg.get_xbar_out();
    _num_elem_per_bank = arch_cfg.get_max_num_elem_per_bank();

    _banks = new OA_element[_num_banks * _num_elem_per_bank];
}

AccumulatorBanks::~AccumulatorBanks() {
    delete _arch_cfg;
    // delete _banks;
}

void AccumulatorBanks::cycle(Scnn::Xbar* xbar, dlsim::Fmap4d_t* OA_full, bool flush) {
    // cout << "Accumulator cycle called" << endl;
    if(flush == true) {
        // cout << "Flush called: " << endl;
        for(int i = 0; i < _num_banks * _num_elem_per_bank; i++) {
            OA_element elem = _banks[i];
            if(elem.get_init() == false) continue;
            else {
                tuple<int, int, int, int> idx = elem.get_idx();
                OA_full->set_data(get<0>(idx), get<1>(idx), get<2>(idx), get<3>(idx), elem.get_data());
                // DEBUG
                // cout << "Flushed to OA layer----";
                // cout << "[" << get<0>(idx) 
                // << ", " << get<1>(idx) << ", " << get<2>(idx) << ", "
                // << get<3>(idx) << "]" << " ";
                // cout << OA_full->get_data(get<0>(idx), get<1>(idx), get<2>(idx), get<3>(idx)) << " ------ " << endl;
            }
        }
        clean();
        // cout << endl << "AccumulatorBanks cleaned" << endl << endl;
    } 
    else {
        // cout << "No flush called: " << xbar->num_port_out() << endl;
        for(int i = 0; i < xbar->num_port_out(); i++) {
            if(xbar->port_out()->canDrain(i)) {
                OA_element elem = xbar->port_out()->next_elem_to_be_drained(i);
                // DEBUG
                // cout << "Before: ";
                // ACCUM_2D_INDEX_AT(_banks, _num_elem_per_bank, elem.get_bank_id(), elem.get_idx_in_bank()).print();
                
                // DEBUG
                // cout << "Accumulator accumulated: ";
                // elem.print();
                ACCUM_2D_INDEX_AT(_banks, _num_elem_per_bank, elem.get_bank_id(), elem.get_idx_in_bank()).accumulate(elem);
                
                // DEBUG
                // cout << "After: ";
                // ACCUM_2D_INDEX_AT(_banks, _num_elem_per_bank, elem.get_bank_id(), elem.get_idx_in_bank()).print();

                xbar->port_out()->drain(i);
            }
        }
    }
}

bool AccumulatorBanks::idle(Scnn::Xbar* xbar) {
    bool isIdle = true;
    for(int i = 0; i < xbar->num_port_out(); i++) {
        isIdle = isIdle && !xbar->port_out()->canDrain(i);
    }
    return isIdle;
}

void AccumulatorBanks::clean(unsigned set_id) {
    throw runtime_error("SCNN::AccumulatorBanks clean(unsigned set_id) is not yet implemented");
}

void AccumulatorBanks::clean() {
    for(int i = 0; i < _num_banks * _num_elem_per_bank; i++) {
        _banks[i].write_init(false);
    }
}

unsigned AccumulatorBanks::ptr_idle_bank() {
    throw runtime_error("SCNN::AccumulatorBanks ptr_idle_bank is not yet implemented");
}

void AccumulatorBanks::switch_active_bank() {
    throw runtime_error("SCNN::AccumulatorBanks switch_active_bank is not yet implemented");
}

OA_element* AccumulatorBanks::banks() {
    return _banks;
}

unsigned AccumulatorBanks::ptr_active_bank() {
    return _ptr_active_bank;
}

unsigned AccumulatorBanks::num_banks() {
    return _num_banks;
}

unsigned AccumulatorBanks::num_elem_per_bank() {
    return _num_elem_per_bank;
}

bool AccumulatorBanks::empty(unsigned set_id) {
    throw runtime_error("SCNN::AccumulatorBanks empty is not yet implemented");
}

}


#endif