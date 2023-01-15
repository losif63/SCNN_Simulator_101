#ifndef DLSIM_FMAP_4D_CC_
#define DLSIM_FMAP_4D_CC_

#include "dlsim/fmap_4d.h"

namespace dlsim {

// /* Method used for generating weight tensor of arbitrary sparsity. 
//    This method should be only used when putting in the input data
//    for the first layer. */
// void Fmap4d_t::init() {
//     float sparsity = (Fmap_t)this->_sparsity/100.0;
//     float randProbability, randValue;
//     default_random_engine gen;
//     uniform_real_distribution<float> probGenerator(0.0, 1.0);
//     uniform_real_distribution<float> valueGenerator(-5.0, 5.0);
//     unsigned dim1, dim2, dim3, dim4;
//     for(int i = 0; i < this->size(); i++) {
//         randProbability = probGenerator(gen);
//         randValue = valueGenerator(gen);
//         if(randProbability > sparsity) _data[i] = 0.0;
//         else _data[i] = randValue;
//     }
// }

}

#endif