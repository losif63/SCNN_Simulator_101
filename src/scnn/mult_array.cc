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

MultArray::~MultArray() {
    delete _arch_cfg;
}


void MultArray::init(Scnn::LayerConfig& layer_cfg, dlsim::Tensor**, dlsim::Tensor* W) {
    throw runtime_error("SCNN::MultArray init is not yet implemented");
}

void MultArray::clean() {
    throw runtime_error("SCNN::MultArray clean is not yet implemented");
}

bool MultArray::fill_WFIFO_and_IARAM(dlsim::Fmap4d_t* IA_full, unsigned N_id, unsigned C_id, unsigned chunk_id) {
    throw runtime_error("SCNN::MultArray fill_WFIFO_and_IARAM is not yet implemented");
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
    throw runtime_error("SCNN::MultArray advance_WFIFO is not yet implemented");
}

void MultArray::advance_IARAM() {
    throw runtime_error("SCNN::MultArray advance_IARAM is not yet implemented");
}

void MultArray::advance_to_next_mul_op() {
    throw runtime_error("SCNN::MultArray advance_to_next_mul_op is not yet implemented");
}

void MultArray::clear_both_WFIFO_and_IARAM(){
    throw runtime_error("SCNN::MultArray clear_both_WFIFO_and_IARAM is not yet implemented");
}

// helper functions
bool MultArray::is_empty_WFIFO() {
    throw runtime_error("SCNN::MultArray is_empty_WFIFO is not yet implemented");
}

bool MultArray::is_empty_IARAM(){
    throw runtime_error("SCNN::MultArray is_empty_IARAM is not yet implemented");
}

// get
W_vec_entry MultArray::curr_WFIFO_entry() {
    throw runtime_error("SCNN::MultArray curr_WFIFO_entry is not yet implemented");
}

IA_vec_entry MultArray::curr_IARAM_entry() {
    throw runtime_error("SCNN::MultArray curr_IARAM_entry is not yet implemented");
}

bool MultArray::end_of_WFIFO() {
    throw runtime_error("SCNN::MultArray end_of_WFIFO is not yet implemented");
}

bool MultArray::end_of_IARAM() {
    throw runtime_error("SCNN::MultArray end_of_IARAM is not yet implemented");
}

}

#endif