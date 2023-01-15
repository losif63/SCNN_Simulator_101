/*
* Filename: simulator.cc
* File created by Jaduk Suh
* Date: January, 2023
*/

#ifndef DLSIM_SIMULATOR_CC_
#define DLSIM_SIMULATOR_CC_

#include "dlsim/simulator.h"

namespace dlsim {

Simulator::Simulator() {}

Simulator::~Simulator() {}

void Simulator::run() {}

bool Simulator::done() {
    throw runtime_error("DLSIM::Simulator done is not yet implemented");
}

}

#endif