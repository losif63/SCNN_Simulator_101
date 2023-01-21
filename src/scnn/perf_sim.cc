#include "scnn/perf_sim.h"

#ifndef SCNN_PERF_SIM_CC_
#define SCNN_PERF_SIM_CC_

#include <stdexcept>

namespace Scnn{

using namespace std;

PerfSim::PerfSim(Scnn::ArchConfig& arch_cfg)
:_arch_cfg(arch_cfg)
{
    // initialize PE and LOADER
    _pe = new Scnn::PE(_arch_cfg);
    _loader = new Scnn::Loader(_arch_cfg);

    // initialize cycles
    _cycle_layer = 0;
    _cycle_network = 0;
}

PerfSim::~PerfSim(){
    delete _pe;
    delete _loader;
};

void
PerfSim::run(){
    PerfSim::cycle();
};

bool
PerfSim::done() {
    throw runtime_error("Scnn::PerfSim done() is not yet implemented");
}

void
PerfSim::prepare_current_layer(dlsim::Tensor* IA, dlsim::Tensor* W, dlsim::Tensor* OA){

    // this function gets all IA, W, and OA for the whole single layer.
    _cycle_layer = 0;

    // whole IA and W for this layer
    dlsim::Fmap4d_t*    this_IA = dynamic_cast<dlsim::Fmap4d_t*>(IA);
    dlsim::Weight4d_t*  this_W  = dynamic_cast<dlsim::Weight4d_t*>(W);

    // get local values for layer parameters
    unsigned  max_R     = this_W->dim_sz('R');
    unsigned  max_S     = this_W->dim_sz('S');
    unsigned  pad_H_sz  = (max_R-1)/2;
    unsigned  pad_W_sz  = (max_S-1)/2;
    unsigned  stride_R  = 1;
    unsigned  stride_S  = 1;
    unsigned  max_IA_H  = this_IA->dim_sz('H');
    unsigned  max_IA_W  = this_IA->dim_sz('W');
    unsigned  max_OA_H  = (max_IA_H - max_R + 2*pad_H_sz)/stride_R + 1;
    unsigned  max_OA_W  = (max_IA_W - max_S + 2*pad_W_sz)/stride_S + 1;

    unsigned  max_H_per_PE = max_OA_H;
    unsigned  max_W_per_PE = max_OA_W;
        
    // find largest chunk_sz possible for this layer
    float max_num_elem_per_bank_with_base_chunk_sz = ((float)(max_H_per_PE * max_W_per_PE * _arch_cfg.get_chunk_sz_for_accum_bank_sizing())) / (float)_arch_cfg.get_xbar_out();
    if(max_num_elem_per_bank_with_base_chunk_sz<1.0) {
        max_num_elem_per_bank_with_base_chunk_sz  = 1.0;
    }

    // sanity  == should be lower than max
    assert(max_num_elem_per_bank_with_base_chunk_sz <= _arch_cfg.get_max_num_elem_per_bank());
    assert(max_num_elem_per_bank_with_base_chunk_sz > 0);

    // chunk_sz has to be pow(2)
    unsigned chunk_sz_for_this_layer  = _arch_cfg.get_chunk_sz_for_accum_bank_sizing();
        
    while(max_num_elem_per_bank_with_base_chunk_sz < _arch_cfg.get_max_num_elem_per_bank()){
        max_num_elem_per_bank_with_base_chunk_sz  *= 2;
        chunk_sz_for_this_layer                   *= 2;
    }
    if(max_num_elem_per_bank_with_base_chunk_sz > _arch_cfg.get_max_num_elem_per_bank()) {
        max_num_elem_per_bank_with_base_chunk_sz  /= 2;
        chunk_sz_for_this_layer                   /= 2;
    }
    // sanity
    assert(max_num_elem_per_bank_with_base_chunk_sz<=_arch_cfg.get_max_num_elem_per_bank());

    //DEBUG
    #ifdef DEBUG
    cout << "chunk_sz_for_this_layer = " << chunk_sz_for_this_layer << endl;
    cout << "max_num_elem_per_bank_with_base_chunk_sz = " << max_num_elem_per_bank_with_base_chunk_sz << endl;
    #endif
    
    Scnn::LayerConfig layer_cfg(
        (dynamic_cast<dlsim::Fmap4d_t*>(IA))->dim_sz('N'),
        (dynamic_cast<dlsim::Fmap4d_t*>(IA))->dim_sz('C'),
        (dynamic_cast<dlsim::Fmap4d_t*>(IA))->dim_sz('H'),
        (dynamic_cast<dlsim::Fmap4d_t*>(IA))->dim_sz('W'),
        (dynamic_cast<dlsim::Weight4d_t*>(W))->dim_sz('K'),
        (dynamic_cast<dlsim::Weight4d_t*>(W))->dim_sz('R'),
        (dynamic_cast<dlsim::Weight4d_t*>(W))->dim_sz('S'),
        chunk_sz_for_this_layer
    );

    // give loader pointers and distribute data across PE as IA_SLICE
    _loader->setup_IA_W_and_OA(IA, W, OA);
    _loader->distribute_IA_across_spatial_PEs(layer_cfg, this->_arch_cfg);
        
    // copy final layer-specific config to member var
    _layer_cfg = layer_cfg;

    // setup PE's initial status to get ready for current layer's execution 
    _pe->prepare_current_layer(_loader->IA(), _loader->OA(), _loader->IA_slice(), _loader->W(), _layer_cfg);
};

void
PerfSim::cleanup_current_layer() {
    throw runtime_error("Scnn::PerfSim cleanup_current_layer() is not yet implemented");
}

void
PerfSim::collect_stats() {
    throw runtime_error("Scnn::PerfSim collect_stats() is not yet implemented");
}


void
PerfSim::cycle(){
    // update clk cycle
    _cycle_network++; 
    _cycle_layer++;

    // tick PE
    _pe->cycle();
};

PE* PerfSim::get_PE() {
    return _pe;
}

}

#endif