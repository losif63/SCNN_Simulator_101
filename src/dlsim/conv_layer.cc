/*
* Filename: conv_layer.cc
* File created by Jaduk Suh
* Date: January, 2023
*/

#ifndef DLSIM_CONV_LAYER_CC_
#define DLSIM_CONV_LAYER_CC_

#include "dlsim/conv_layer.h"

namespace dlsim
{

ConvLayer::ConvLayer(const map<string,unsigned int>* cfg_curr_layer)
{
    // TODO:: Implement
}

ConvLayer::~ConvLayer() {}

Tensor* ConvLayer::IFmap() {
    return this->_IFmap;
}

Tensor* ConvLayer::W() {
    return this->_W;
}

Tensor* ConvLayer::OFmap() {
    return this->_OFmap;
}

void ConvLayer::print() {
    // TODO:: Implement
    cout << "The print function for ConvLayer is yet to be ";
    cout << "implemented." << endl;
}

}

#endif