#include "scnn/pe.h"

#ifndef SCNN_PE_CC_
#define SCNN_PE_CC_

namespace Scnn
{

PE::PE(
    Scnn::ArchConfig& arch_cfg
):
    _arch_cfg(arch_cfg),
    _sync_barrier(false)
{
    // modules for active banks
    _sequencer    = new Scnn::Sequencer;
    _mult_array   = new Scnn::MultArray(arch_cfg);
    _xbar         = new Scnn::Xbar(arch_cfg);
    _oa_banks     = new Scnn::AccumulatorBanks(arch_cfg);    
    _ppu          = new Scnn::PPU(arch_cfg);  

    _cycle        = 0;    

    // stat
    _c_cycle_waiting_at_barrier         = 0;
    _c_cycle_active                     = 0;
    _c_cycle_finished_waiting_others    = 0;
}

PE::~PE(){
    delete    _mult_array;
    delete    _oa_banks;
    delete    _xbar;
    delete    _sequencer;
    delete    _ppu;
}

void
PE::cycle(){

    //================================================================================
    // stats
    _cycle++;

    if(finished_layer_exec()==true) {
        _c_cycle_finished_waiting_others++;
    }
    else {
        if(sync_barrier()==true) {
            _c_cycle_waiting_at_barrier++;
        }
        else {
            _c_cycle_active++;
        }
    }
    //================================================================================

    //================================================================================
    // [step_5]: tick PPU, PPU's operation is de-coupled from the actions happening in the 'active' banks
    // [step_4]: drain xbar->port_out() elements into accumulator banks
    // [step_3]: drain results and forward it to accum_banks (if possible)
    // [step_2]: do work and generate results (if possible)
    // [step_1]: find work for multiplier-array
    //================================================================================
    // PE currently idle, but still has work to do for this chunk of weight sets
    // (all comp. idle) && (done all this layer) && (all idle)
    // then, IT SHOULD GET REST CHUNK OF WEIGHT SETS
    //================================================================================
}

bool
PE::idle(){
    // all component idle
    return (_mult_array->idle()==true)&&(_xbar->idle()==true)&&(_ppu->idle()==true)&&(_oa_banks->idle(_xbar)==true);
}

bool PE::finished_layer_exec() {
    throw runtime_error("SCNN::PE finished_layer_exec is not yet implemented");
}

void PE::prepare_current_layer(
    dlsim::Fmap4d_t* IA_full,
    dlsim::Fmap4d_t* OA_full,
    dlsim::Fmap4d_t** IA_slice,
    dlsim::Weight4d_t* W,
    Scnn::LayerConfig& layer_cfg
) {
    throw runtime_error("SCNN::PE prepare_current_layer is not yet implemented");
}

void PE::cleanup_current_layer() {
    throw runtime_error("SCNN::PE cleanup_current_layer is not yet implemented");
}

void PE::find_work() {
    throw runtime_error("SCNN::PE find_work is not yet implemented");
}

bool PE::sync_barrier() {
    throw runtime_error("SCNN::PE sync_barrier is not yet implemented");
}

void PE::setup_sync_barrier() {
    throw runtime_error("SCNN::PE setup_sync_barrier is not yet implemented");
}

void clear_sync_barrier() {
    throw runtime_error("SCNN::PE clear_sync_barrier is not yet implemented");
}

Scnn::MultArray* PE::get_mult() {
    return this->_mult_array;
}

Scnn::PPU* PE::get_ppu() {
    return this->_ppu;
}

dlsim::Fmap4d_t** PE::get_IA_slice() {
    return this->_IA_slice;
}

dlsim::Weight4d_t* PE::get_W() {
    return this->_W;
}


} // namespace Scnn

#endif
