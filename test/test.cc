#include <iostream>
#include <random>
#include <math.h>

#include "dlsim/common.h"
#include "dlsim/fmap_4d.h"
#include "dlsim/conv_layer.h"
#include "dlsim/loader.h"
#include "scnn/common.h"
#include "scnn/vir_ch.h"
#include "scnn/loader.h"
#include "scnn/mult_array.h"

using namespace std;

int succ_count = 0;
int fail_count = 0;
int total_count = 0;

template <class T>
void test(T a, T b) {
    total_count++;
    cout << "Test case # " << total_count << " ";
    if(a == b) {
        succ_count++;
        cout << "PASSED" << endl;
    }
    else {
        fail_count++;
        cout << "FAILED" << endl;
        cout << a << " should be " << b << endl;
    }
}

int main(void) {
    cout << "This is a test module, built for testing out the various ";
    cout << "sub-modules of this scnn simulator." << endl;
    default_random_engine gen;
    uniform_int_distribution<int> randGenerator(2, 10);
    uniform_real_distribution<float> randFloatGen(0.0, 5.0);
/********************************DLSIM*********************************/

/**********************************************************************/
cout << "-----------------------------------------------------------\n";
cout << "Testing Tensor4d classes:" << endl; 

/*Fmap4d_t, Weight4d_t, Tensor4d_T*/
unsigned int randim1 = randGenerator(gen);
unsigned int randim2 = randGenerator(gen);
unsigned int randim3 = randGenerator(gen);
unsigned int randim4 = randGenerator(gen);

dlsim::Fmap4d_t* IA_map = new dlsim::Fmap4d_t(4, randim1, randim2, randim3, randim4, _IA_Tensor, 50);
dlsim::Fmap4d_t* W_map = new dlsim::Fmap4d_t(4, randim1, randim2, randim3, randim4, _W_Tensor, 50);
test<unsigned>(IA_map->dim_sz('N'), randim1);
test<unsigned>(IA_map->dim_sz('C'), randim2);
test<unsigned>(IA_map->dim_sz('H'), randim3);
test<unsigned>(IA_map->dim_sz('W'), randim4);
test<unsigned>(IA_map->size(), randim1 * randim2 * randim3 * randim4);
test<unsigned>(W_map->dim_sz('K'), randim1);
test<unsigned>(W_map->dim_sz('C'), randim2);
test<unsigned>(W_map->dim_sz('S'), randim3);
test<unsigned>(W_map->dim_sz('R'), randim4);
test<unsigned>(W_map->size(), randim1 * randim2 * randim3 * randim4);

IA_map->randInit();
W_map->copy_data(IA_map);
bool valid_copy = true;
for(int i = 0; i < randim1; i++) {
    for(int j = 0; j < randim2; j++) {
        for(int k = 0; k < randim3; k++) {
            for(int l = 0; l < randim4; l++) {
                if(IA_map->get_data(i, j, k, l) != W_map->get_data(i, j, k, l)) valid_copy = false;
            }
        }
    }
}
test<bool>(valid_copy, true);
delete IA_map;
delete W_map;
/**********************************************************************/
/* ConvLayer */
cout << "-----------------------------------------------------------\n";
cout << "Testing ConvLayer class:" << endl; 
map<string, unsigned int> *layer1 = new map<string, unsigned int>;
layer1->insert({"N", randGenerator(gen)});
layer1->insert({"C", randGenerator(gen)});
layer1->insert({"K", randGenerator(gen)});
layer1->insert({"H", randGenerator(gen)});
layer1->insert({"W", randGenerator(gen)});
layer1->insert({"R", randGenerator(gen)});
layer1->insert({"S", randGenerator(gen)});
// For the sparsity, the actual value is x/100
layer1->insert({"IA_sparsity", 100});
layer1->insert({"W_sparsity", 50});

dlsim::ConvLayer* conv = new dlsim::ConvLayer(layer1);
((dlsim::Fmap4d_t*)conv->IFmap())->randInit();
((dlsim::Fmap4d_t*)conv->W())->randInit();
((dlsim::Fmap4d_t*)conv->OFmap())->randInit();

test<float>(((dlsim::Fmap4d_t*)conv->IFmap())->data()[0], 0.0);
test<float>(((dlsim::Fmap4d_t*)conv->IFmap())->data()[((dlsim::Fmap4d_t*)conv->IFmap())->size()-1], 0.0);
bool allZero = true;
for(int i = 0; i < ((dlsim::Fmap4d_t*)conv->IFmap())->size(); i++) {
    if(((dlsim::Fmap4d_t*)conv->IFmap())->data()[i] != 0.0) allZero = false;
}
test<bool>(allZero, true);
delete conv;
/**********************************************************************/
/* DLSIM::Loader */
cout << "-----------------------------------------------------------\n";
cout << "Testing DLSIM::Loader class:" << endl; 
dlsim::Loader* loader = new dlsim::Loader("config/examplenet");
test<unsigned>(loader->num_layers(), 3);
loader->load_next_layer();
// loader->current_layer()->print();
loader->clear_current_layer();
test<unsigned>(loader->num_layers(), 2);
loader->load_next_layer();
// loader->current_layer()->print();
loader->clear_current_layer();
test<unsigned>(loader->num_layers(), 1);
loader->load_next_layer();
// loader->current_layer()->print();
loader->clear_current_layer();
test<unsigned>(loader->num_layers(), 0);
loader->reload(0);
loader->load_next_layer();
test<unsigned>(loader->num_layers(), 3);
// loader->print_layer();

/*********************************SCNN*********************************/


/**********************************************************************/
/* VirtualChannel */
cout << "-----------------------------------------------------------\n";
cout << "Testing VirtualChannel class:" << endl; 
Scnn::VirtualChannel<int>* channel1 = new Scnn::VirtualChannel<int>;
randGenerator(gen);
randGenerator(gen);
randGenerator(gen);
randGenerator(gen);
unsigned channelNumber = randGenerator(gen);
unsigned entryNumber = randGenerator(gen);
channel1->init(channelNumber, entryNumber);
cout << "Testing VirtualChannel initialization:" << endl;
test<unsigned>(channel1->num_phy_ch_q(), channelNumber);
test<unsigned>(channel1->num_q_entries_per_phy_ch(), entryNumber);

cout << "Testing canDrain and canReceive for " << channelNumber << " channels:" << endl;
for(int i = 0; i < channelNumber; i++) {
    test<bool>(channel1->canDrain(i), false);
    test<bool>(channel1->canReceive(i), true);
}
unsigned randomChannel1 = randGenerator(gen) % channelNumber;
cout << "Testing channel filling on channel number " << randomChannel1 << ":" << endl;
test<bool>(channel1->isFullOnPhyCh(randomChannel1), false);
for(int i = 0; i < entryNumber; i++) {
    channel1->receive(randomChannel1, randomChannel1);
}
test<bool>(channel1->isFullOnPhyCh(randomChannel1), true);
test<bool>(channel1->canDrain(randomChannel1), true);
test<bool>(channel1->canReceive(randomChannel1), false);

test<int>(channel1->next_elem_to_be_drained(randomChannel1), randomChannel1);
test<int>(channel1->drain(randomChannel1), randomChannel1);


/**********************************************************************/
/* Scnn::Loader */
cout << "-----------------------------------------------------------\n";
cout << "Testing Scnn::Loader class:" << endl; 

// pe array
unsigned    pe_arr_W = 4;
unsigned    pe_arr_H = 4;

// pe & mult_array -> Multiplier Array
unsigned    mult_arr_M = 4;
unsigned    mult_arr_W = 4;
    
// x-bar -> crossbar
unsigned    xbar_in = mult_arr_M * mult_arr_W; 
unsigned    xbar_scale_out_ratio  = 1;
unsigned    xbar_out  = xbar_in*(xbar_scale_out_ratio);
    
// q --> queue?
unsigned    xbar_in_num_phy_ch_q  = xbar_out;
unsigned    xbar_in_num_q_entries_per_phy_ch = 1;
unsigned    xbar_out_num_phy_ch_q  = 1;
unsigned    xbar_out_num_q_entries_per_phy_ch = 2;
    
// sram size
unsigned    chunk_sz_for_accum_bank_sizing = 2;
unsigned    max_num_elem_per_bank = 0;

unsigned    max_OA_H_per_PE = 0;
unsigned    max_OA_W_per_PE = 0;
unsigned    min_OA_H_per_PE = 1080;
unsigned    min_OA_W_per_PE = 1080;

Scnn::ArchConfig arch_config(
    // pe
    pe_arr_W,
    pe_arr_H,

    // mult array            
    mult_arr_M, 
    mult_arr_W, 

    //xbar
    xbar_in_num_phy_ch_q, 
    xbar_in_num_q_entries_per_phy_ch, 
    xbar_out_num_phy_ch_q, 
    xbar_out_num_q_entries_per_phy_ch, 
    xbar_scale_out_ratio, 
    xbar_in, 
    xbar_out, 

    //sram size
    chunk_sz_for_accum_bank_sizing, 
    max_num_elem_per_bank, 

    max_OA_H_per_PE, 
    max_OA_W_per_PE, 
    min_OA_H_per_PE, 
    min_OA_W_per_PE
);

Scnn::LayerConfig layerConfig1(1, 4, 16, 16, 4, 3, 3, 2);

Scnn::Loader* loader_scnn = new Scnn::Loader(arch_config);
loader_scnn->setup_IA_W_and_OA(loader->current_layer()->IFmap(),
    loader->current_layer()->W(), loader->current_layer()->OFmap());
loader_scnn->distribute_IA_across_spatial_PEs(layerConfig1);
/* Check for all values whether tiling of input was correctly performed. */
/* If all values are correctly tiled, then test passed. */
int new_H = (int)ceil(((float)layerConfig1.get_H() / (float)arch_config.get_pe_arr_H()));
int new_W = (int)ceil(((float)layerConfig1.get_W() / (float)arch_config.get_pe_arr_W()));
for(int i = 0; i < arch_config.get_pe_arr_H(); i++) {
    for(int j = 0; j < arch_config.get_pe_arr_W(); j++) {
        bool allClear = true;
        // cout << "current i, j: " << i << " " << j << endl;
        dlsim::Fmap4d_t* slice = loader_scnn->IA_slice()[i * arch_config.get_pe_arr_W() + j];
        // cout << "current i, j: " << i << " " << j << endl;
        for(int n = 0; n < slice->dim_sz(slice->key()[0]); n++) {
            for(int c = 0; c < slice->dim_sz(slice->key()[1]); c++) {
                for(int h = 0; h < slice->dim_sz(slice->key()[2]); h++) {
                    for(int w = 0; w < slice->dim_sz(slice->key()[3]); w++) {
                        // cout << "Current nchw:" << n << " " << c << " " << h << " " << w << endl;
                        int actual_H = i * new_H + h - ((layerConfig1.get_S() - 1) / 2);
                        int actual_W = j * new_W + w - ((layerConfig1.get_R() - 1) / 2);
                        if((actual_H >= 0) && (actual_H < layerConfig1.get_H()) && (actual_W >= 0) && (actual_W < layerConfig1.get_W())) {
                            if(slice->get_data(n, c, h, w) != loader->current_layer()->IFmap()->get_data(n, c, actual_H, actual_W)) {
                                allClear = false;
                                cout << "ERROR CODE 1012: " << slice->get_data(n, c, h, w) << ", " << loader->current_layer()->IFmap()->get_data(n, c, actual_H, actual_W) << endl;
                            }
                        }
                        else {
                            if(slice->get_data(n, c, h, w) != 0.0) {
                                allClear = false;
                                cout << "ERROR CODE 1013: " << slice->get_data(n, c, h, w) << endl;
                            }
                            allClear = (allClear && (slice->get_data(n, c, h, w) == 0.0));
                        }
                    }
                }
            }
        }
        test<bool>(allClear, true);
    }
}

/**********************************************************************/
/* MultArray */
cout << "-----------------------------------------------------------\n";
cout << "Testing Scnn::MultArray class:" << endl; 

/* Check whether the indices in the WFIFO and IARAM are correctly set */
for(int pe_h = 0; pe_h < arch_config.get_pe_arr_H(); pe_h++) {
    for(int pe_w = 0; pe_w < arch_config.get_pe_arr_W(); pe_w++) {
        // cout << "PE Number: (h, w) = " << pe_h << ", " << pe_w << endl;
        Scnn::MultArray mult(arch_config);
        mult.set_pe_arr_h_idx(pe_h);
        mult.set_pe_arr_w_idx(pe_w);
        /* Test WFIFO */
        mult.init(layerConfig1, loader_scnn->IA_slice()[pe_h * arch_config.get_pe_arr_W() + pe_w], loader_scnn->W());
        // loader_scnn->W()->print();
        bool WFIFO_pass = true;

        for(unsigned C_id = 0; C_id < layerConfig1.get_C(); C_id++) {
            for(unsigned chunk_id = 0; chunk_id < layerConfig1.get_K()/layerConfig1.get_chunk_sz(); chunk_id++) {
                mult.fill_WFIFO_and_IARAM(0, C_id, chunk_id);
                int size = mult.size_WFIFO();
                for(int temp = 0; temp < size; temp++) {
                    for(int i = 0; i < mult.curr_WFIFO_entry()->size(); i++) {
                        // (*mult.curr_WFIFO_entry())[i].print();
                        if((*mult.curr_WFIFO_entry())[i].get_valid() == false) continue;
                        tuple<int, int, int, int> idx = (*mult.curr_WFIFO_entry())[i].get_idx();
                        if((*mult.curr_WFIFO_entry())[i].get_data() != loader_scnn->W()->get_data(get<0>(idx), get<1>(idx), get<2>(idx), get<3>(idx))) {
                            WFIFO_pass = false;
                            cout << "ERROR DETECTED IN WFIFO!!!!" << endl;
                        }
                            
                    }
                    mult.advance_WFIFO();
                }
                mult.clear_both_WFIFO_and_IARAM();
            }
        }
        test<bool>(true, WFIFO_pass);
        /* Test IARAM */
        bool IARAM_pass = true;
        // loader_scnn->IA()->print();
        int slice_id = pe_h * arch_config.get_pe_arr_W() + pe_w;
        mult.init(layerConfig1, loader_scnn->IA_slice()[slice_id], loader_scnn->W());
        // loader_scnn->IA_slice()[slice_id]->print();
        for(unsigned N_id = 0; N_id < layerConfig1.get_N(); N_id++) {
            for(unsigned C_id = 0; C_id < layerConfig1.get_C(); C_id++) {
                mult.fill_WFIFO_and_IARAM(N_id, C_id, 0);
                int size = mult.size_IARAM();
                for(int temp = 0; temp < size; temp++) {
                    for(int i = 0; i < mult.curr_IARAM_entry()->size(); i++) {
                        // (*mult.curr_IARAM_entry())[i].print();
                        if((*mult.curr_IARAM_entry())[i].get_valid() == false) continue;
                        tuple<int, int, int, int> idx = (*mult.curr_IARAM_entry())[i].get_idx();
                        if((*mult.curr_IARAM_entry())[i].get_data() != loader_scnn->IA()->get_data(get<0>(idx), get<1>(idx), get<2>(idx), get<3>(idx))) {
                            IARAM_pass = false;
                            cout << "ERROR DETECTED IN IARAM!!!!" << endl;
                        }
                    }
                    mult.advance_IARAM();
                }
                mult.clear_both_WFIFO_and_IARAM();
            }
        }  
        test<bool>(true, IARAM_pass);
    }
}

/* TODO: Test multiplication after implementing Xbar */

/**********************************************************************/
/* Xbar */
cout << "-----------------------------------------------------------\n";
cout << "Testing Scnn::Xbar class:" << endl; 



/**********************************************************************/
cout << fail_count << " out of " << total_count << " test cases failed." << endl;
cout << succ_count << " out of " << total_count << " test cases passed." << endl;
/**********************************************************************/
}