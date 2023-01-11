/*
* Filename: tensor.cc
* File created by Jaduk Suh
* Date: January, 2023
*/

#include "dlsim/tensor_4d.h"

#ifndef DLSIM_TENSOR_4D_CC_
#define DLSIM_TENSOR_4D_CC_

namespace dlsim {

/**********************************************************************/
// Constructors
template <class T>
Tensor4d<T>::Tensor4d() {
    this->_ndim = 4;
    this->_dim_key = "NCHW";
    this->_dim_sz.insert({'N', 0});
    this->_dim_sz.insert({'C', 0});
    this->_dim_sz.insert({'H', 0});
    this->_dim_sz.insert({'W', 0});
}

template <class T>
Tensor4d<T>::Tensor4d(
    unsigned    ndim,
    unsigned    N,
    unsigned    C,
    unsigned    H,
    unsigned    W,
    char*       type,
    int         sparsity
) {
    this->_ndim = ndim;
    this->_dim_key = "NCHW";
    this->_dim_sz.insert({'N', N});
    this->_dim_sz.insert({'C', C});
    this->_dim_sz.insert({'H', H});
    this->_dim_sz.insert({'W', W});
}

/**********************************************************************/
// Destructors
template <class T>
Tensor4d<T>::~Tensor4d() {}

/**********************************************************************/
// Member Functions

/* Returns the dimension size of the corresponding key */
template <class T>
unsigned Tensor4d<T>::dim_sz(char key) {
    return this->_dim_sz[key];
}

/* Returns the entire size of this tensor */
template <class T>
unsigned Tensor4d<T>::size() {
    return this->dim_sz['N'] * this->dim_sz['C'] * this->dim_sz['H'] 
    * this->dim_sz['W'];
}

/* Prints out the specifications of this tensor */
template <class T>
void Tensor4d<T>::print() {
    cout << "Number of Dimensions: " << this->_ndim << endl;
    cout << "Dimension Sizes: " << endl;
    for (auto i: this->_dim_sz) {
        cout << i.first << " " << i.second << endl << endl;
    }
    /* **TODO**: Print out data */
}

/* Returns the entire data of tensor */
template <class T>
T**** Tensor4d<T>::data() const {
    return this->_data;
};

/* Initializes data of tensor */
template <class T>
void Tensor4d<T>::set_data(
    unsigned    N,
    unsigned    C,
    unsigned    H,
    unsigned    W,
    T           init_value
) {
    this->_dim_sz['N'] = N;
    this->_dim_sz['C'] = C;
    this->_dim_sz['H'] = H;
    this->_dim_sz['W'] = W;
    // this->data = &&&&T;
}


}

#endif