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
        arch_cfg.get_mult_arr_M(),
        arch_cfg.get_mult_arr_W(),

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

AccumulatorBanks::~AccumulatorBanks() {
    delete _arch_cfg;
}

void AccumulatorBanks::cycle(Scnn::Xbar* xbar, dlsim::Fmap4d_t* OA_full) {
    throw runtime_error("SCNN::AccumulatorBanks cycle is not yet implemented");
}

bool AccumulatorBanks::idle(Scnn::Xbar* xbar) {
    throw runtime_error("SCNN::AccumulatorBanks idle is not yet implemented");
}

void AccumulatorBanks::clean(unsigned set_id) {
    throw runtime_error("SCNN::AccumulatorBanks clean(unsigned set_id) is not yet implemented");
}

void AccumulatorBanks::clean() {
    throw runtime_error("SCNN::AccumulatorBanks clean() is not yet implemented");
}

unsigned AccumulatorBanks::ptr_idle_bank() {
    throw runtime_error("SCNN::AccumulatorBanks ptr_idle_bank is not yet implemented");
}

void AccumulatorBanks::switch_active_bank() {
    throw runtime_error("SCNN::AccumulatorBanks switch_active_bank is not yet implemented");
}

OA_element*** AccumulatorBanks::banks() {
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