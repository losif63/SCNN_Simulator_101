/*
* Filename: loader.cc
* File created by Jaduk Suh
* Date: January, 2023
*/

#ifndef SCNN_LOADER_CC_
#define SCNN_LOADER_CC_

#include "scnn/loader.h"
#include <math.h>

namespace Scnn {

Loader::Loader(ArchConfig& arch_cfg) {
    _arch_cfg = new ArchConfig(
        arch_cfg.get_pe_arr_W(),
        arch_cfg.get_pe_arr_H(),
        arch_cfg.get_mult_arr_F(),
        arch_cfg.get_mult_arr_I(),

        arch_cfg.get_xbar_in_num_phy_ch_q(),
        arch_cfg.get_xbar_in_num_q_entries_per_phy_ch(),
        arch_cfg.get_xbar_out_num_phy_ch_q(),
        arch_cfg.get_xbar_out_num_q_entries_per_phy_ch(),

        arch_cfg.get_xbar_scale_out_ratio(),
        arch_cfg.get_xbar_in(),
        arch_cfg.get_xbar_out(),

        arch_cfg.get_chunk_sz_for_accum_bank_sizing(),
        arch_cfg.get_max_num_elem_per_bank(),

        arch_cfg.get_max_OA_H_per_PE(),
        arch_cfg.get_max_OA_W_per_PE(),
        arch_cfg.get_min_OA_H_per_PE(),
        arch_cfg.get_min_OA_W_per_PE()
    );
    _IA_slice = NULL;
}


Loader::~Loader() {
    if(_IA_slice != NULL) {
        int size = _arch_cfg->get_pe_arr_H() * _arch_cfg->get_pe_arr_W();
        for(int i = 0; i < size; i++) {
            delete _IA_slice[i];
        }
        delete _IA_slice;
    }
    delete _arch_cfg;
}

void Loader::setup_IA_W_and_OA(dlsim::Tensor* IA, dlsim::Tensor* W, dlsim::Tensor* OA) {
    this->_IA = (dlsim::Fmap4d_t*)IA;
    this->_W = (dlsim::Weight4d_t*)W;
    this->_OA = (dlsim::Fmap4d_t*)OA;
}

void Loader::distribute_IA_across_spatial_PEs(Scnn::LayerConfig& layer_cfg) {
    // For now, we'll be doing input halo
    int new_H = (int)ceil(((float)layer_cfg.get_H() / (float)_arch_cfg->get_pe_arr_H()));
    int new_W = (int)ceil(((float)layer_cfg.get_W() / (float)_arch_cfg->get_pe_arr_W()));
    // int new_H = ((layer_cfg.get_H() + layer_cfg.get_S() - 1) / _arch_cfg->get_pe_arr_H()) + 1;
    // int new_W = ((layer_cfg.get_W() + layer_cfg.get_R() - 1) / _arch_cfg->get_pe_arr_W()) + 1;
    unsigned H_per_PE = new_H + layer_cfg.get_S() - 1;
    unsigned W_per_PE = new_W + layer_cfg.get_R() - 1;

    _IA_slice = new dlsim::Fmap4d_t*[_arch_cfg->get_pe_arr_W() * _arch_cfg->get_pe_arr_H()];
    for(int i = 0; i < _arch_cfg->get_pe_arr_H(); i++) {
        for(int j = 0; j < _arch_cfg->get_pe_arr_W(); j++) {
            int currIndex = i * _arch_cfg->get_pe_arr_W() + j;
            _IA_slice[currIndex] = new dlsim::Fmap4d_t(
                4, 
                layer_cfg.get_N(), 
                layer_cfg.get_C(), 
                H_per_PE, 
                W_per_PE, 
                _IA_Tensor, 
                0
            );
            _IA_slice[currIndex]->zeroInit();
            // _IA_slice[currIndex]->print();
            for(int k = 0; k < H_per_PE; k++) {
                for(int l = 0; l < W_per_PE; l++) {
                    int actual_H = i * new_H + k - ((layer_cfg.get_S() - 1) / 2);
                    int actual_W = j * new_W + l - ((layer_cfg.get_R() - 1) / 2);
                    // cout << "(k, l): ("<< k << ", " << l;
                    // cout << ") | (actual_H, actual_W): ("<< actual_H << ", " << actual_W << ")" << endl;
                    // check if (actual_H, actual_W is in actual range)
                    for(int i2 = 0; i2 < layer_cfg.get_N(); i2++) {
                        for(int j2 = 0; j2 < layer_cfg.get_C(); j2++) {
                            if(((actual_H >= 0) && (actual_H < layer_cfg.get_H())) && ((actual_W >= 0) && (actual_W < layer_cfg.get_W()))) {
                                _IA_slice[currIndex]->set_data(
                                    i2, 
                                    j2, 
                                    k, 
                                    l,
                                    _IA->get_data(
                                        i2, 
                                        j2, 
                                        actual_H, 
                                        actual_W
                                    )
                                );
                            }
                            else {
                                _IA_slice[currIndex]->set_data(
                                    i2, 
                                    j2, 
                                    k, 
                                    l, 
                                    0.0
                                );
                            }
                        }
                    }
                }
            }
            // _IA_slice[currIndex]->print();
        }
    }



}

void Loader::clear_IA_slice_and_W() {
    throw runtime_error("SCNN::Loader method clear_IA_slice_and_W is not yet implemented");
}


void Loader::check_IA_W_density() {
    throw runtime_error("SCNN::Loader method check_IA_W_density is not yet implemented");
}

dlsim::Fmap4d_t** Loader::IA_slice() {
    return _IA_slice;
}

dlsim::Fmap4d_t* Loader::IA() {
    return _IA;
}

dlsim::Weight4d_t* Loader::W() {
    return _W;
}

dlsim::Fmap4d_t* Loader::OA() {
    return _OA;
}

}

#endif