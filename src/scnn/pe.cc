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
    // _ppu          = new Scnn::PPU(arch_cfg);  

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
    // delete    _ppu;
}

void
PE::cycle(){

    //================================================================================
    // stats
    _cycle++;
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
    if(done()) {
        _c_cycle_waiting_at_barrier++;
        return;
    }
    if(idle()) {
        _mult_array->clear_both_WFIFO_and_IARAM();
        advance_layer();
        // Here, one should check for clearing OARAM
        if(_layer_idx % (layer_N * layer_C) == 0) _oa_banks->cycle(_xbar, _OA_full, true);
        unsigned chunk_id = _layer_idx / (layer_N * layer_C);
        unsigned N_id = (_layer_idx / layer_C) % layer_N;
        unsigned C_id = _layer_idx % layer_C;
        _mult_array->fill_WFIFO_and_IARAM(N_id, C_id, chunk_id);
        _c_cycle_active++;
        _oa_banks->cycle(_xbar, _OA_full, false);
        _xbar->cycle();
        _mult_array->cycle(_xbar);
    }
    else {
        _c_cycle_active++;
        _oa_banks->cycle(_xbar, _OA_full, false);
        _xbar->cycle();
        _mult_array->cycle(_xbar);
    }
}

bool
PE::idle(){
    // all component idle
    return (_mult_array->idle()==true)&&(_xbar->idle()==true)&&(_oa_banks->idle(_xbar)==true);
}

void
PE::advance_layer() {
    _layer_idx++;
}

bool
PE::end_of_layer() {
    return _layer_idx >= (max_chunk_id + 1) * layer_N * layer_C;
}

bool
PE::done() {
    return idle() && end_of_layer();
}

bool PE::finished_layer_exec() {
    throw runtime_error("SCNN::PE finished_layer_exec is not yet implemented");
}

void PE::prepare_current_layer(
    dlsim::Fmap4d_t* IA_full,
    dlsim::Fmap4d_t* OA_full,
    dlsim::Fmap4d_t* IA_slice,
    dlsim::Weight4d_t* W,
    Scnn::LayerConfig& layer_cfg
) {
    _IA_full = IA_full;
    _OA_full = OA_full;
    _IA_slice = IA_slice;
    _W = W;
    _layer_cfg = layer_cfg;
    
    _layer_idx = 0;
    max_chunk_id = layer_cfg.get_K()/layer_cfg.get_chunk_sz();
    layer_N = layer_cfg.get_N();
    layer_C = layer_cfg.get_C();
    _mult_array->fill_WFIFO_and_IARAM(0, 0, 0);
}

void PE::cleanup_current_layer() {
    _layer_idx = 0;
    _IA_full = NULL;
    _OA_full = NULL;
    _IA_slice = NULL;
    _W = NULL;

    _cycle = 0;
    _c_cycle_waiting_at_barrier         = 0;
    _c_cycle_active                     = 0;
    _c_cycle_finished_waiting_others    = 0;


    _mult_array->clean();
    _oa_banks->clean();
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

dlsim::Fmap4d_t* PE::get_IA_slice() {
    return this->_IA_slice;
}

dlsim::Weight4d_t* PE::get_W() {
    return this->_W;
}


} // namespace Scnn

#endif
