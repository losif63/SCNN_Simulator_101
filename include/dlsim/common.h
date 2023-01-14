#ifndef DLSIM_COMMOM_H_
#define DLSIM_COMMOM_H_

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <cstdio>
#include <cstdlib>

#include <map>
#include <deque>
#include <vector>
#include <tuple>
#include <string>
#include <random>
#include <cassert>

//#define DEBUG
//#define give_sparsity

/*
* Let the dimensions be A * B * C * D
* stride[0] = sizeof(float) * B * C * D
* stride[1] = sizeof(float) * C * D
* stride[2] = sizeof(float) * D
* stride[3] = sizeof(float)
*/
#define TENSOR_4D_INDEX_AT(ptr, stride, i, j, k, l) ptr[i*stride[0]+j*stride[1]+k*stride[2]+l*stride[3]]
enum TensorType {
    _IA_Tensor, _W_Tensor, _OA_Tensor
};


// type of variables
#ifdef _GOLD_
#define Weight_t		signed long
#define Fmap_t			signed long

#else
#define Weight_t		float
#define Fmap_t			float

#endif

namespace dlsim{
    using namespace std;   
}

#endif