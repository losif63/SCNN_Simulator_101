/*
* Filename: loader.cc
* File created by Jaduk Suh
* Date: January, 2023
*/

#ifndef DLSIM_LOADER_CC_
#define DLSIM_LOADER_CC_

#include "dlsim/loader.h"

namespace dlsim
{

Loader::Loader(string dnn_name) {
    /* For now, use temporary input data */
    /* TODO:: Load data from file using dnn_name */
    map<string, unsigned int> *layer1 = new map<string, unsigned int>;
    layer1->insert({"N", 1});
    layer1->insert({"C", 4});
    layer1->insert({"K", 4});
    layer1->insert({"H", 16});
    layer1->insert({"W", 16});
    layer1->insert({"R", 3});
    layer1->insert({"S", 3});
    // For the sparsity, the actual value is x/100
    layer1->insert({"IA_sparsity", 50});
    layer1->insert({"W_sparsity", 50});

    _cfg_network = new deque<map<string, unsigned int>*>;
    _cfg_network->push_front(layer1);

    _curr_layer = NULL;
}

Loader::~Loader() {
    while(_cfg_network->empty()) {
        delete _cfg_network->back();
        _cfg_network->pop_back();
    }
    delete _cfg_network;
}

unsigned Loader::num_layers() {
    return _cfg_network->size();
}

bool Loader::done() {
    /* For now, output done if all layers are processed & removed */
    if(_cfg_network->size() == 0) return true;
    else return false;
}

void Loader::print_layer() {
    cout << "Print all unprocessed layers & current layer";
    cout << "-------------------------------------------------\n";
    for(map<string, unsigned int>* layer : *_cfg_network) {
        for(auto i : *layer) {
            cout << '{' << i.first << ", " << i.second << "}\n";
        }
        cout << "-------------------------------------------------\n";
    }
    
}

void Loader::load_next_layer() {
    if(_curr_layer != NULL) delete _curr_layer;
    _curr_layer = NULL;

    if(_cfg_network->size() > 0) {
        _curr_layer = new ConvLayer(_cfg_network->back());
        _cfg_network->pop_back();
    }
}

void Loader::update_curr_layer_id(unsigned layer_id) {
    _curr_layer_id = layer_id;
}

ConvLayer* Loader::current_layer() {
    return _curr_layer;
}

unsigned Loader::curr_layer_id() {
    return _curr_layer_id;
}



}

#endif