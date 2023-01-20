/*
* Filename: loader.cc
* File created by Jaduk Suh
* Date: January, 2023
*/

#ifndef SCNN_LOADER_CC_
#define SCNN_LOADER_CC_

#include "scnn/loader.h"

namespace Scnn {

Loader::Loader(ArchConfig& arch_cfg) {
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


Loader::~Loader() {
    delete _arch_cfg;
}

void Loader::setup_IA_W_and_OA(dlsim::Tensor* IA, dlsim::Tensor* W, dlsim::Tensor* OA) {
    this->_IA = (dlsim::Fmap4d_t*)IA;
    this->_W = (dlsim::Weight4d_t*)W;
    this->_OA = (dlsim::Fmap4d_t*)OA;
}

void Loader::distribute_IA_across_spatial_PEs(Scnn::LayerConfig& layer_cfg) {
    

}

void Loader::clear_IA_slice_and_W() {
    throw runtime_error("SCNN::Loader method clear_IA_slice_and_W is not yet implemented");
}


void Loader::check_IA_W_density() {
    throw runtime_error("SCNN::Loader method check_IA_W_density is not yet implemented");
}

dlsim::Fmap4d_t* Loader::IA_slice() {
    return _IA_slice;
}

dlsim::Fmap4d_t* Loader::IA() {
    return _IA;
}

dlsim::Weight4d_t* Loader::W() {
    return _W;
}

dlsim::Fmap4d_t* Loader::OA() {
    return _OA;
}

}

#endif