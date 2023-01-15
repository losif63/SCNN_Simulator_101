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
        float w_sparsity = (float)weight->sparsity()/100.0;
        float randProbability, randValue;
        default_random_engine gen;
        uniform_real_distribution<float> probGenerator(0.0, 1.0);
        uniform_real_distribution<float> valueGenerator(-3.0, 3.0);
        int max_k = weight->dim_sz('K');
        int max_c = weight->dim_sz('C');
        int max_s = weight->dim_sz('S');
        int max_r = weight->dim_sz('R');
        for(int k = 0; k < max_k; k++) {
            for(int c = 0; c < max_c; c++) {
                for(int s = 0; s < max_s; s++) {
                    for(int r = 0; r < max_r; r++) {
                        randProbability = probGenerator(gen);
                        randValue = valueGenerator(gen);
                        if(randProbability > w_sparsity)
                            weight->set_data(k, c, s, r, randValue);
                        else 
                            weight->set_data(k, c, s, r, 0.0);
                    }
                }
            }
        }
    
        /* If this is the first layer, generate new data as input */
        if(_curr_layer == NULL) {
            Fmap4d_t* input = ((Fmap4d_t *)temp_layer->IFmap());
            float ia_sparsity = (float)input->sparsity()/100.0;
            uniform_real_distribution<float> valueGenerator2(0.0, 10.0);
            int max_n = input->dim_sz('N');
            int max_c2 = input->dim_sz('C');
            int max_h = input->dim_sz('H');
            int max_w = input->dim_sz('W');
            for(int n = 0; n < max_n; n++) {
                for(int c = 0; c < max_c2; c++) {
                    for(int h = 0; h < max_h; h++) {
                        for(int w = 0; w < max_w; w++) {
                            randProbability = probGenerator(gen);
                            randValue = valueGenerator2(gen);
                            if(randProbability > ia_sparsity)
                                weight->set_data(n, c, h, w, randValue);
                            else 
                                weight->set_data(n, c, h, w, 0.0);
                        }
                    }
                }
            }
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
    /* Todo:: Initialize loader from filename stored in dnn_name */
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