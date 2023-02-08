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
#include "scnn/xbar.h"
#include "scnn/accum_banks.h"

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
unsigned    pe_arr_W = 8;
unsigned    pe_arr_H = 8;

// pe & mult_array -> Multiplier Array
unsigned    mult_arr_F = 13;
unsigned    mult_arr_I = 7;
    
// x-bar -> crossbar
unsigned    xbar_in = mult_arr_F * mult_arr_I; 
unsigned    xbar_scale_out_ratio = 2;
unsigned    xbar_out  = xbar_in*(xbar_scale_out_ratio);
    
// q --> queue?
unsigned    xbar_in_num_phy_ch_q  = xbar_out;
unsigned    xbar_in_num_q_entries_per_phy_ch = 1;
unsigned    xbar_out_num_phy_ch_q  = 1;
unsigned    xbar_out_num_q_entries_per_phy_ch = 2;
    
// sram size
unsigned    chunk_sz_for_accum_bank_sizing = 2;
unsigned    max_num_elem_per_bank = 2048;

unsigned    max_OA_H_per_PE = 0;
unsigned    max_OA_W_per_PE = 0;
unsigned    min_OA_H_per_PE = 1080;
unsigned    min_OA_W_per_PE = 1080;

Scnn::ArchConfig arch_config(
    // pe
    pe_arr_W,
    pe_arr_H,

    // mult array            
    mult_arr_F, 
    mult_arr_I, 

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

Scnn::LayerConfig layerConfig1(
    loader->current_layer()->IFmap()->dim_sz('N'),
    loader->current_layer()->IFmap()->dim_sz('C'),
    loader->current_layer()->IFmap()->dim_sz('H'),
    loader->current_layer()->IFmap()->dim_sz('W'),
    loader->current_layer()->W()->dim_sz('K'),
    loader->current_layer()->W()->dim_sz('R'),
    loader->current_layer()->W()->dim_sz('S'),
    arch_config.get_chunk_sz_for_accum_bank_sizing()
);

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
        for(int n = 0; n < slice->dim_sz('N'); n++) {
            for(int c = 0; c < slice->dim_sz('C'); c++) {
                #ifdef INPUT_HALO_
                for(int h = 0; h < slice->dim_sz('H'); h++) {
                    for(int w = 0; w < slice->dim_sz('W'); w++) {
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
                #endif
                #ifdef OUTPUT_HALO_
                for(int h = 0; h < slice->dim_sz('H'); h++) {
                    for(int w = 0; w < slice->dim_sz('W'); w++) {
                        // cout << "Current nchw:" << n << " " << c << " " << h << " " << w << endl;
                        int actual_H = i * new_H + h - ((layerConfig1.get_S() - 1) / 2);
                        int actual_W = j * new_W + w - ((layerConfig1.get_R() - 1) / 2);
                        if((h < ((layerConfig1.get_S() - 1) / 2)) || (h >= ((layerConfig1.get_S() - 1) / 2) + new_H) || (w < ((layerConfig1.get_R() - 1) / 2)) || (w >= ((layerConfig1.get_R() - 1) / 2) + new_W)) {
                            if(slice->get_data(n, c, h, w) != 0.0) {
                            allClear = false;
                            cout << "ERROR CODE 1013: " << slice->get_data(n, c, h, w) << endl;
                        }
                        }
                        else if(slice->get_data(n, c, h, w) != loader->current_layer()->IFmap()->get_data(n, c, actual_H, actual_W)) {
                            allClear = false;
                            cout << "ERROR CODE 1012: " << slice->get_data(n, c, h, w) << ", " << loader->current_layer()->IFmap()->get_data(n, c, actual_H, actual_W) << endl;
                            cout << "(" << i << ", " << j << "), " << n << ", " << c << ", " << h << ", " << w << "|| " << actual_H << ", " << actual_W << endl; 
                        }
                    }
                }
                #endif
            }
        }
        test<bool>(allClear, true);
    }
}

/**********************************************************************/
/* Xbar */
cout << "-----------------------------------------------------------\n";
cout << "Testing Scnn::Xbar class:" << endl; 

Scnn::Xbar xbar(arch_config);


/**********************************************************************/
/* AccumulatorBanks */
cout << "-----------------------------------------------------------\n";
cout << "Testing Scnn::AccumulatorBanks class:" << endl; 

Scnn::AccumulatorBanks accum_bank(arch_config);



/**********************************************************************/
/* MultArray */
cout << "-----------------------------------------------------------\n";
cout << "Testing Scnn::MultArray class:" << endl; 
// loader_scnn->IA()->print();
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
        int slice_id = pe_h * arch_config.get_pe_arr_W() + pe_w;
        // mult.init(layerConfig1, loader_scnn->IA_slice()[slice_id], loader_scnn->W());
        // loader_scnn->IA_slice()[slice_id]->print();
        for(unsigned N_id = 0; N_id < layerConfig1.get_N(); N_id++) {
            for(unsigned C_id = 0; C_id < layerConfig1.get_C(); C_id++) {
                mult.fill_WFIFO_and_IARAM(N_id, C_id, 0);
                int size = mult.size_IARAM();
                for(int temp = 0; temp < size; temp++) {
                    for(int i = 0; i < mult.curr_IARAM_entry()->size(); i++) {
                        if((*mult.curr_IARAM_entry())[i].get_valid() == false) continue;
                        tuple<int, int, int, int> idx = (*mult.curr_IARAM_entry())[i].get_idx();
                        // (*mult.curr_IARAM_entry())[i].print();
                        if((*mult.curr_IARAM_entry())[i].get_data() != loader_scnn->IA()->get_data(get<0>(idx), get<1>(idx), get<2>(idx), get<3>(idx))) {
                            IARAM_pass = false;
                            (*mult.curr_IARAM_entry())[i].print();
                            cout << "ERROR DETECTED IN IARAM!!!!" << endl;
                        }
                    }
                    mult.advance_IARAM();
                }
                mult.clear_both_WFIFO_and_IARAM();
            }
        }  
        test<bool>(true, IARAM_pass);
        for(unsigned chunk_id = 0; chunk_id <= layerConfig1.get_K()/layerConfig1.get_chunk_sz(); chunk_id++) {
            for(unsigned N_id = 0; N_id < layerConfig1.get_N(); N_id++) {
                for(unsigned C_id = 0; C_id < layerConfig1.get_C(); C_id++) {
                    // for(unsigned chunk_id = 0; chunk_id < layerConfig1.get_K()/layerConfig1.get_chunk_sz(); chunk_id++) {
                        // cout << "Testing for N_id, C_id, chunk_id: " << N_id << ", " << C_id << ", " << chunk_id << endl;
                        mult.fill_WFIFO_and_IARAM(N_id, C_id, chunk_id);
                        while((mult.idle() == false) || (xbar.idle() == false) || (accum_bank.idle(&xbar) == false)) {
                            accum_bank.cycle(&xbar, loader->current_layer()->OFmap(), false);
                            xbar.cycle();
                            mult.cycle(&xbar);
                        }
                        mult.clear_both_WFIFO_and_IARAM();
                    // }
                }
            }
            accum_bank.cycle(&xbar, loader->current_layer()->OFmap(), true);
        }
        // loader->current_layer()->OFmap()->print();
    }
}

dlsim::Fmap4d_t golden_output(4, layerConfig1.get_N(), layerConfig1.get_K(), layerConfig1.get_H(), layerConfig1.get_W(), _OA_Tensor, 0);
golden_output.zeroInit();
for(int n= 0; n < layerConfig1.get_N(); n++) {
    for(int k = 0; k < layerConfig1.get_K(); k++) {
        for(int c = 0; c < layerConfig1.get_C(); c++) {
            for(int w = 0; w < layerConfig1.get_W(); w++) {
                for(int h = 0; h < layerConfig1.get_H(); h++) {
                    for(int s = 0; s < layerConfig1.get_S(); s++) {
                        for(int r = 0; r < layerConfig1.get_R(); r++) {
                            float currValue = golden_output.get_data(n, k, h, w);
                            int inputH = h + s - (layerConfig1.get_S()-1)/2;
                            int inputW = w + r - (layerConfig1.get_R()-1)/2;
                            if((inputH < 0) || (inputH >= layerConfig1.get_H())) continue;
                            if((inputW < 0) || (inputW >= layerConfig1.get_W())) continue;
                            float inputValue = loader->current_layer()->IFmap()->get_data(n, c, inputH, inputW);
                            float weightValue = loader->current_layer()->W()->get_data(k, c, s, r);
                            float valueToAdd = inputValue * weightValue;
                            golden_output.set_data(n, k, h, w, currValue + valueToAdd);
                            // DEBUG
                            // cout << "Input [" << n << ", " << c << ", " << inputH << ", " << inputW << ", " << inputValue << "] | ";
                            // cout << "Weight [" << k << ", " << c << ", " << s << ", " << r << ", " << weightValue << "] | ";
                            // cout << "GOLDEN:: Partial Sum [" << n << ", " << k << ", " << h << ", " << w << ", " << valueToAdd << "]" << endl;
                        }
                    }
                }
            }
        }
    }
}
// loader->current_layer()->IFmap()->print();
// loader->current_layer()->W()->print();
// golden_output.print();
// loader->current_layer()->OFmap()->print();
bool accuracyTest = true;
for(int n= 0; n < layerConfig1.get_N(); n++) {
    for(int k = 0; k < layerConfig1.get_K(); k++) {
        for(int w = 0; w < layerConfig1.get_W(); w++) {
            for(int h = 0; h < layerConfig1.get_H(); h++) {
                float goldValue = golden_output.get_data(n, k, h, w);
                float calValue = loader->current_layer()->OFmap()->get_data(n, k, h, w);
                float error = calValue - goldValue;
                accuracyTest = accuracyTest && (fabs(error) < 0.001);
                cout << error << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
    cout << endl;
}
test<bool>(accuracyTest, true);
cout << endl;
if(accuracyTest) {
    cout << "SCNN simulator output is correct!!" << endl << endl;
} else {
    cout << "ERROR: SCNN simulator output incorrect!!" << endl << endl;
}
/* TODO: Test multiplication after implementing Xbar */


/**********************************************************************/
cout << fail_count << " out of " << total_count << " test cases failed." << endl;
cout << succ_count << " out of " << total_count << " test cases passed." << endl;
/**********************************************************************/
}