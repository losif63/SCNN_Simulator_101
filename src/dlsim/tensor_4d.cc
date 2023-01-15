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
    this->_ndim = 0;
    this->_dim_key = NULL;
    this->data = NULL;
    this->_sparsity = 0;
}

/* Initializes the tensor based on the given dimensionalities 
   and TensorType. Allocates an array of elements to the tensor 
   using the sizes of the dimensionalities. */
template <class T>
Tensor4d<T>::Tensor4d(
    unsigned    ndim,
    unsigned    dim1,
    unsigned    dim2,
    unsigned    dim3,
    unsigned    dim4,
    TensorType  type,
    int         sparsity
) {
    this->_ndim = ndim; // This should be 4 no matter what
    this->_data = new T[dim1 * dim2 * dim3 * dim4];
    this->_sparsity = sparsity;
    switch(type) {
        case _IA_Tensor:
            this->_dim_key = {'N', 'C', 'H', 'W'};
            this->_dim_sz.insert({'N', dim1});
            this->_dim_sz.insert({'C', dim2});
            this->_dim_sz.insert({'H', dim3});
            this->_dim_sz.insert({'W', dim4});
            // this->init();
            break;
        case _W_Tensor:
            this->_dim_key = {'K', 'C', 'S', 'R'};
            this->_dim_sz.insert({'K', dim1});
            this->_dim_sz.insert({'C', dim2});
            this->_dim_sz.insert({'S', dim3});
            this->_dim_sz.insert({'R', dim4});
            /* Weight should always be generated */
            float sparsity = (Fmap_t)this->_sparsity/100.0;
            float randProbability, randValue;
            default_random_engine gen;
            uniform_real_distribution<float> probGenerator(0.0, 1.0);
            uniform_real_distribution<float> valueGenerator(-5.0, 5.0);
            unsigned size = dim1 * dim2 * dim3 * dim4;
            for(int i = 0; i < size; i++) {
                randProbability = probGenerator(gen);
                randValue = valueGenerator(gen);
                if(randProbability > sparsity) _data[i] = 0.0;
                else _data[i] = randValue;
            }
            // this->init();
            break;
        case _OA_Tensor:
            this->_dim_key = {'N', 'K', 'H', 'W'};
            this->_dim_sz.insert({'N', dim1});
            this->_dim_sz.insert({'K', dim2});
            this->_dim_sz.insert({'H', dim3});
            this->_dim_sz.insert({'W', dim4});
            break;
    }
}

/**********************************************************************/
// Destructors
template <class T>
Tensor4d<T>::~Tensor4d() {
    delete this->_data;
}

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
    return this->dim_sz[_dim_key[0]] * this->dim_sz[_dim_key[0]] * 
    this->dim_sz[_dim_key[2]] * this->dim_sz[_dim_key[3]];
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
T* Tensor4d<T>::data() const {
    return this->_data;
};

/* Returns the sparsity tensor */
template <class T>
unsigned Tensor4d<T>::sparsity() {
    return this->_sparsity;
};

/* Initializes data of tensor at given index */
template <class T>
void Tensor4d<T>::set_data(
    unsigned    dim1,
    unsigned    dim2,
    unsigned    dim3,
    unsigned    dim4,
    T           init_value
) {
    unsigned stride[4];
    stride[0] = dim2 * dim3 * dim4;
    stride[1] = dim3 * dim4;
    stride[2] = dim4;
    stride[3] = 1;
    TENSOR_4D_INDEX_AT(_data, stride, dim1, dim2, dim3, dim4) 
        = init_value;
}

template <class T>
void Tensor4d<T>::copy_data(Tensor4d* tensor) {
    unsigned size = this->size();
    for(unsigned i = 0; i < size; i++)
        this->_data[i] = tensor->data()[i];
}


}

#endif