/*
* Filename: conv_layer.cc
* File created by Jaduk Suh
* Date: January, 2023
*/

#ifndef DLSIM_CONV_LAYER_CC_
#define DLSIM_CONV_LAYER_CC_

#include "dlsim/conv_layer.h"
#include "dlsim/tensor_4d.h"

namespace dlsim
{

ConvLayer::ConvLayer(const map<string,unsigned int>* cfg_curr_layer)
{
    // TODO:: Implement
    this->_IFmap = new Tensor4d<Fmap_t>(
        4, 
        cfg_curr_layer->at("N"), 
        cfg_curr_layer->at("C"), 
        cfg_curr_layer->at("H"), 
        cfg_curr_layer->at("W"),
        _IA_Tensor,
        cfg_curr_layer->at("IA_sparsity")
    );
    
    this->_W = new Tensor4d<Fmap_t>(
        4, 
        cfg_curr_layer->at("K"), 
        cfg_curr_layer->at("C"), 
        cfg_curr_layer->at("S"), 
        cfg_curr_layer->at("R"),
        _W_Tensor,
        cfg_curr_layer->at("W_sparsity")
    );

    this->_OFmap = new Tensor4d<Fmap_t>(
        4, 
        cfg_curr_layer->at("N"), 
        cfg_curr_layer->at("K"), 
        cfg_curr_layer->at("H"), 
        cfg_curr_layer->at("W"),
        _OA_Tensor,
        0
    );
}

ConvLayer::~ConvLayer() {
    delete _IFmap;
    delete _W;
    delete _OFmap;
}

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
    cout << "IFmap Tensor4d:: " << endl;
    this->_IFmap->print();
    cout << "W Tensor4d:: " << endl;
    this->_W->print();
    cout << "OFmap Tensor4d:: " << endl;
    this->_OFmap->print();
}

}

#endif