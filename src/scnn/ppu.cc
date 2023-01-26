/*
* Filename: ppu.cc
* File created by Jaduk Suh
* Date: January, 2023
*/

#ifndef SCNN_PPU_CC_
#define SCNN_PPU_CC_

#include "scnn/ppu.h"

namespace Scnn
{

PPU::PPU(ArchConfig& arch_cfg) {
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

PPU::~PPU() {
    delete _arch_cfg;
}

void PPU::cycle(Scnn::AccumulatorBanks* oa_banks) {
    throw runtime_error("SCNN::PPU cycle is not yet implemented");
}

bool PPU::idle() {
    throw runtime_error("SCNN::PPU idle is not yet implemented");
}

void PPU::clean() {
    throw runtime_error("SCNN::PPU clean is not yet implemented");
}

Scnn::VirtualChannel<OA_element>* PPU::port_in() {
    return this->_port_in;
}
unsigned PPU::num_port_in() {
    throw runtime_error("SCNN::PPU num_port_in is not yet implemented");
}

Scnn::VirtualChannel<OA_element>* PPU::port_out() {
    return this->_port_out;
}

unsigned PPU::num_port_out() {
    throw runtime_error("SCNN::PPU num_port_out is not yet implemented");
}	

}

#endif