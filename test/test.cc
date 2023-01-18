#include <iostream>
#include <random>


#include "dlsim/common.h"
#include "dlsim/fmap_4d.h"
#include "dlsim/conv_layer.h"
#include "dlsim/loader.h"
#include "scnn/common.h"
#include "scnn/vir_ch.h"


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
test<unsigned>(loader->num_layers(), 3);
// loader->print_layer();



/**********************************************************************/

/*********************************SCNN*********************************/


/**********************************************************************/
/* VirtualChannel */
cout << "-----------------------------------------------------------\n";
cout << "Testing VirtualChannel class:" << endl; 
Scnn::VirtualChannel<int>* channel1 = new Scnn::VirtualChannel<int>;
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


cout << fail_count << " out of " << total_count << " test cases failed." << endl;
cout << succ_count << " out of " << total_count << " test cases passed." << endl;
/**********************************************************************/
}