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
    
    _num_port_in = arch_cfg.get_xbar_in();
    _num_port_out = arch_cfg.get_xbar_out();
    _c_inputs_fwded_to_output = 0;
    _c_cycles_active = 0;

    _port_in = new VirtualChannel<OA_element>;
    _port_out = new VirtualChannel<OA_element>;
    
    _port_in->init(_num_port_in, 1);
    _port_out->init(_num_port_out, 100);
    
}

Xbar::~Xbar() {
    delete _arch_cfg;
    // delete _port_in;
    // delete _port_out;
}

void Xbar::cycle() {
    if(idle()) return;
    for(int i = 0; i < _num_port_in; i++) {
        if(_port_in->canDrain(i)) {
            OA_element elem = _port_in->next_elem_to_be_drained(i);
            if(elem.get_valid() == false) {
                _port_in->drain(i);
                continue;
            }
            if(_port_out->canReceive(elem.get_bank_id())) {
                _port_in->drain(i);
                _port_out->receive(elem, elem.get_bank_id());
                // cout << "Xbar processed the following element: ";
                // elem.print();
            }
        }
    }
}

/* Returns if this Xbar has no OA_elements stuck in input port */
bool Xbar::idle() {
    bool isIdle = true;
    for(int i = 0; i < _num_port_in; i++) {
        isIdle = isIdle && _port_in->canReceive(i);
    }
    return isIdle;
}

void Xbar::clean() {
    for(int i = 0; i < _num_port_in; i++) {
        while(_port_in->canDrain(i)) _port_in->drain(i);
    }

    for(int i = 0; i < _num_port_out; i++) {
        while(_port_out->canDrain(i)) _port_out->drain(i);
    }
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