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

void Sequencer::init(Scnn::LayerConfig& layer_cfg, dlsim::Tensor** IA_slice, dlsim::Tensor* W) {
    throw runtime_error("SCNN::Sequencer init is not yet implemented");
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
    throw runtime_error("SCNN::Sequencer next_N_id is not yet implemented");
}

void Sequencer::next_C_id() {
    throw runtime_error("SCNN::Sequencer next_C_id is not yet implemented");
}

void Sequencer::next_chunk_id() {
    throw runtime_error("SCNN::Sequencer next_chunk_id is not yet implemented");
}

void Sequencer::rewind_C_id() {
    throw runtime_error("SCNN::Sequencer rewind_C_id is not yet implemented");
}

void Sequencer::rewind_chunk_id() {
    throw runtime_error("SCNN::Sequencer rewind_chunk_id is not yet implemented");
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