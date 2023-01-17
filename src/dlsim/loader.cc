/*
* Filename: loader.cc
* File created by Jaduk Suh
* Date: January, 2023
*/

#ifndef DLSIM_LOADER_CC_
#define DLSIM_LOADER_CC_

#include <iostream>
#include <fstream>
#include "dlsim/loader.h"
#include "dlsim/tensor_4d.h"

namespace dlsim
{

Loader::Loader(string dnn_name) {
    /* For now, use temporary input data */
    /* TODO:: Load data from file using dnn_name */
    this->dnn_name = dnn_name;
    this->initialize();
    this->_curr_layer = NULL;
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

/* This function deletes the previous ConvLayer if it exists, 
   and creates a new ConvLayer object & loads it. */
void Loader::load_next_layer() {
    ConvLayer* temp_layer = NULL;
    if(_cfg_network->size() > 0) {
        /* Construct new ConvLayer object */
        temp_layer = new ConvLayer(_cfg_network->back());
        /* Generate random value for weight */
        Weight4d_t* weight = ((Weight4d_t *)temp_layer->W());
        weight->randInit();
        Fmap4d_t* output = ((Fmap4d_t*)temp_layer->OFmap());
        output->zeroInit();
        /* If this is the first layer, generate new data as input */
        if(_curr_layer == NULL) {
            Fmap4d_t* input = ((Fmap4d_t *)temp_layer->IFmap());
            input->randInit();
        }
        /* Otherwise, copy output data from previous layer */ 
        else {
            ((Fmap4d_t *)temp_layer->IFmap())->
                copy_data((Fmap4d_t *)_curr_layer->OFmap());
        }
    }

    if(_curr_layer != NULL) delete _curr_layer;
    _curr_layer = temp_layer;

    _curr_layer_id++;
}

/* Pops the latest entry in _cfg_network. */
void Loader::clear_current_layer() {
    _cfg_network->pop_back();
}

/* Apparently, this function updates current layer id and resets 
   everything. This function is used only when done() is true.*/
void Loader::reload(unsigned layer_id) {
    delete _cfg_network;
    this->initialize();
    this->_curr_layer_id = layer_id;
}

void Loader::initialize() {
    _cfg_network = new deque<map<string, unsigned int>*>;
    _curr_layer = NULL;
    _curr_layer_id = 0;

    string Text;
    ifstream ReadFile(dnn_name);
    if(!ReadFile) {
        cerr << "Cannot read file " << dnn_name << endl;
    }
    getline(ReadFile, Text);
    int num_layer = stoi(Text.substr(Text.find(" ")+1));
    for(int i = 0; i < num_layer; i++) {
        map<string, unsigned int> *layer = new map<string, unsigned int>;
        for(int j = 0; j < 9; j++) {
            getline(ReadFile, Text);
            layer->insert({Text.substr(0, Text.find(":")), stoi(Text.substr(Text.find(" ")+1))});
        }
        _cfg_network->push_front(layer);
        getline(ReadFile, Text);
    }
    ReadFile.close();
}

ConvLayer* Loader::current_layer() {
    return _curr_layer;
}

unsigned Loader::curr_layer_id() {
    return _curr_layer_id;
}



}

#endif