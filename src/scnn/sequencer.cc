/*
* Filename: sequencer.cc
* File created by Jaduk Suh
* Date: January, 2023
*/

#ifndef SCNN_SEQUENCER_CC_
#define SCNN_SEQUENCER_CC_

#include "scnn/sequencer.h"

namespace Scnn
{

Sequencer::Sequencer() {}

Sequencer::~Sequencer() {}

void Sequencer::init(Scnn::LayerConfig& layer_cfg, dlsim::Fmap4d_t* IA_slice, dlsim::Weight4d_t* W) {
    _curr_N_id = 0;
    _curr_C_id = 0;
    _curr_chunk_id = 0;

    _max_N_id = layer_cfg.get_N() - 1;
    _max_C_id = layer_cfg.get_C() - 1;
    _max_chunk_id = layer_cfg.get_K()/layer_cfg.get_chunk_sz() - 1;
    _max_K_id = layer_cfg.get_K() - 1;
    _chunk_sz = layer_cfg.get_chunk_sz();

    this->_IA_slice = IA_slice;
    this->_W = W;
}

void Sequencer::clean() {
    throw runtime_error("SCNN::Sequencer clean is not yet implemented");
}

bool Sequencer::advance_to_next_working_set() {
    throw runtime_error("SCNN::Sequencer advance_to_next_working_set is not yet implemented");
}

bool Sequencer::done_with_layer() {
    throw runtime_error("SCNN::Sequencer done_with_layer is not yet implemented");
}

// // dataflow control
void Sequencer::next_N_id() {
    _curr_N_id++;
}

void Sequencer::next_C_id() {
    _curr_C_id++;
}

void Sequencer::next_chunk_id() {
    _curr_chunk_id++;
}

void Sequencer::rewind_N_id() {
    _curr_N_id = 0;
}

void Sequencer::rewind_C_id() {
    _curr_C_id = 0;
}

void Sequencer::rewind_chunk_id() {
    _curr_chunk_id = 0;
}

bool Sequencer::end_of_N_id() {
    return _curr_N_id == _max_N_id;
}

bool Sequencer::end_of_C_id() {
    return _curr_C_id == _max_C_id;
}

bool Sequencer::end_of_chunk_id() {
    return _curr_chunk_id == _max_chunk_id;
}

unsigned Sequencer::curr_N_id() {
    return _curr_N_id;
}

unsigned Sequencer::curr_C_id() {
    return _curr_C_id;
}

unsigned Sequencer::curr_chunk_id() {
    return _curr_chunk_id;
}

}


#endif