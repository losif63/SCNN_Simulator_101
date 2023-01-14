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
    this->dnn_name = dnn_name;
    this->initialize();
}

Loader::~Loader() {
    while(_cfg_network->empty()) {
        delete _cfg_network->back();
        _cfg_network->pop_back();
    }
    delete _cfg_network;
    _curr_layer_id = 0;
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

/* This function creates a new ConvLayer object & loads it. Deleting
   the previous layer is done by clear_current_layer() function. */
void Loader::load_next_layer() {
    if(_cfg_network->size() > 0) {
        _curr_layer = new ConvLayer(_cfg_network->back());
        _cfg_network->pop_back();
        _curr_layer_id++;
    }
}

/* This function only deletes current layer, and loading is done by 
   the load_next_layer() function. */
void Loader::clear_current_layer() {
    if(_curr_layer != NULL) delete _curr_layer;
    _curr_layer = NULL;
}

/* Apparently, this function updates current layer id and resets 
   everything. This function is used only when done() is true.*/
void Loader::update_curr_layer_id(unsigned layer_id) {
    delete _cfg_network;
    this->initialize();
}

void Loader::initialize() {
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
    _curr_layer_id = 0;
}

ConvLayer* Loader::current_layer() {
    return _curr_layer;
}

unsigned Loader::curr_layer_id() {
    return _curr_layer_id;
}



}

#endif