#include "scnn/pe.h"

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

} // namespace Scnn
