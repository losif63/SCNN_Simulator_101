#include <iostream>
#include <random>


#include "dlsim/common.h"
#include "dlsim/fmap_4d.h"


using namespace std;

int succ_count = 0;
int fail_count = 0;
int total_count = 0;

template <class T>
void test(T a, T b) {
    total_count++;
    cout << "Test # " << total_count << " ";
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
/*Fmap4d_t, Weight4d_t, Tensor4d_T*/
unsigned int randim1 = randGenerator(gen);
unsigned int randim2 = randGenerator(gen);
unsigned int randim3 = randGenerator(gen);
unsigned int randim4 = randGenerator(gen);
cout << randim1 << ", " << randim2 << ", " << randim3 << ", " << randim4 << endl;

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

/* Test Copying */
for(int i = 0; i < randim1; i++) {
    for(int j = 0; j < randim2; j++) {
        for(int k = 0; k < randim3; k++) {
            for(int l = 0; l < randim4; l++) {
                IA_map->set_data(i, j, k, l, randFloatGen(gen));
            }
        }
    }
}
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
/**********************************************************************/



/**********************************************************************/



/*********************************SCNN*********************************/







cout << fail_count << " out of " << total_count << " test cases failed." << endl;
cout << succ_count << " out of " << total_count << " test cases passed." << endl;
/**********************************************************************/
}