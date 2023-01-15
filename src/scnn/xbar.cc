/*
* Filename: xbar.cc
* File created by Jaduk Suh
* Date: January, 2023
*/

#ifndef SCNN_XBAR_CC_
#define SCNN_XBAR_CC_

#include "scnn/xbar.h"

namespace Scnn {

Xbar::Xbar(Scnn::ArchConfig& arch_cfg) {
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

Xbar::~Xbar() {
    delete _arch_cfg;
}

void Xbar::cycle() {
    throw runtime_error("SCNN::Xbar cycle is not yet implemented");
}

bool Xbar::idle() {
    throw runtime_error("SCNN::Xbar idle is not yet implemented");
}

void Xbar::clean() {
    throw runtime_error("SCNN::Xbar clean is not yet implemented");
}

int Xbar::arbitrate_port_in_to_drain_from(unsigned port_out_id) {
    throw runtime_error("SCNN::Xbar arbitrate_port_in_to_drain_from is not yet implemented");
}

int Xbar::ptr_drain_port_in_id(unsigned port_out_id) {
    throw runtime_error("SCNN::Xbar ptr_drain_port_in_id is not yet implemented");
}

Scnn::VirtualChannel<OA_element>* Xbar::port_in() {
    return _port_in;
}

Scnn::VirtualChannel<OA_element>* Xbar::port_out() {
    return _port_out;
}

unsigned Xbar::num_port_in() {
    return _num_port_in;
}

unsigned Xbar::num_port_out() {
    return _num_port_out;
}

}

#endif