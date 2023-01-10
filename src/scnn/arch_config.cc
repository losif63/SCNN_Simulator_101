#include "scnn/arch_config.h"

namespace Scnn
{

ArchConfig::ArchConfig(
    unsigned    _mult_arr_M,
    unsigned    _mult_arr_W,

    // xbar io-ports 
    unsigned      xbar_in_num_phy_ch_q,
    unsigned      xbar_in_num_q_entries_per_phy_ch,
    unsigned      xbar_out_num_phy_ch_q,
    unsigned      xbar_out_num_q_entries_per_phy_ch,

    unsigned      xbar_scale_out_ratio,
    unsigned      xbar_in,
    unsigned      xbar_out,

    unsigned      chunk_sz_for_accum_bank_sizing,
    unsigned      max_num_elem_per_bank,

    unsigned      max_OA_H_per_PE,
    unsigned      max_OA_W_per_PE,
    unsigned      min_OA_H_per_PE,
    unsigned      min_OA_W_per_PE
) {
    this->_mult_arr_M = _mult_arr_M;
    this->_mult_arr_W = _mult_arr_W;
 
    this->_xbar_in_num_phy_ch_q = xbar_in_num_phy_ch_q;
    this->_xbar_in_num_q_entries_per_phy_ch = xbar_in_num_q_entries_per_phy_ch;
    this->_xbar_out_num_phy_ch_q = xbar_out_num_phy_ch_q;
    this->_xbar_out_num_q_entries_per_phy_ch = xbar_out_num_q_entries_per_phy_ch;

    this->_xbar_scale_out_ratio = xbar_scale_out_ratio;
    this->_xbar_in = xbar_in;
    this->_xbar_out = xbar_out;

    this->_chunk_sz_for_accum_bank_sizing = chunk_sz_for_accum_bank_sizing;
    this->_max_num_elem_per_bank = max_num_elem_per_bank;

    this->_max_OA_H_per_PE = max_OA_H_per_PE;
    this->_max_OA_W_per_PE = max_OA_W_per_PE;
    this->_min_OA_H_per_PE = min_OA_H_per_PE;
    this->_min_OA_W_per_PE = min_OA_W_per_PE;
}

ArchConfig::~ArchConfig() {}

unsigned ArchConfig::get_mult_arr_M() {
    return this->_mult_arr_M;
}

unsigned ArchConfig::get_mult_arr_W() {
    return this->_mult_arr_W;
}

unsigned ArchConfig::get_xbar_in_num_phy_ch_q() {
    return this->_xbar_in_num_phy_ch_q;
}                
unsigned ArchConfig::get_xbar_in_num_q_entries_per_phy_ch() {
    return this->_xbar_in_num_q_entries_per_phy_ch;
}    
unsigned ArchConfig::get_xbar_out_num_phy_ch_q() {
    return this->_xbar_out_num_phy_ch_q;
}

unsigned ArchConfig::get_xbar_out_num_q_entries_per_phy_ch() {
    return this->_xbar_out_num_q_entries_per_phy_ch;
}  

unsigned ArchConfig::get_xbar_scale_out_ratio() {
    return this->_xbar_scale_out_ratio;
}

unsigned ArchConfig::get_xbar_in() {
    return this->_xbar_in;
}

unsigned ArchConfig::get_xbar_out() {
    return this->_xbar_out;
}

unsigned ArchConfig::get_chunk_sz_for_accum_bank_sizing() {
    return this->_chunk_sz_for_accum_bank_sizing;
}

unsigned ArchConfig::get_max_num_elem_per_bank() {
    return this->_max_num_elem_per_bank;
}


unsigned ArchConfig::get_max_OA_H_per_PE() {
    return this->_max_OA_H_per_PE;
}

unsigned ArchConfig::get_max_OA_W_per_PE() {
    return this->_max_OA_W_per_PE;
}

unsigned ArchConfig::get_min_OA_H_per_PE() {
    return this->_min_OA_H_per_PE;
}

unsigned ArchConfig::get_min_OA_W_per_PE() {
    return this->_min_OA_W_per_PE;
}

}