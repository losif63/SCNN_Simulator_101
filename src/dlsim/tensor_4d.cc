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
    this->_data = NULL;
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
    this->_size = dim1 * dim2 * dim3 * dim4;
    this->_sparsity = sparsity;
    switch(type) {
        case _IA_Tensor: {
            this->_dim_key = "NCHW";
            this->_dim_sz.insert({'N', dim1});
            this->_dim_sz.insert({'C', dim2});
            this->_dim_sz.insert({'H', dim3});
            this->_dim_sz.insert({'W', dim4});
            // this->init();
            break;
        }
            
        case _W_Tensor: {
            this->_dim_key = "KCSR";
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
            for(unsigned i = 0; i < size; i++) {
                randProbability = probGenerator(gen);
                randValue = valueGenerator(gen);
                if(randProbability > sparsity) _data[i] = 0.0;
                else _data[i] = randValue;
            }
            // this->init();
            break;
        }
        case _OA_Tensor: {
            this->_dim_key = "NKHW";
            this->_dim_sz.insert({'N', dim1});
            this->_dim_sz.insert({'K', dim2});
            this->_dim_sz.insert({'H', dim3});
            this->_dim_sz.insert({'W', dim4});
            break;
        }
    }
}

/**********************************************************************/
// Destructors
template <class T>
Tensor4d<T>::~Tensor4d() {
    if(this->_data != NULL) delete[] this->_data;
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
    return this->dim_sz(_dim_key[0]) * this->dim_sz(_dim_key[1]) * 
    this->dim_sz(_dim_key[2]) * this->dim_sz(_dim_key[3]);
}

template <class T>
void Tensor4d<T>::randInit() {
    default_random_engine gen;
    uniform_real_distribution<float> randProbGen(0.0, 1.0);
    uniform_real_distribution<float> randFloatGen(0.0, 5.0);
    for(int i = 0; i < dim_sz(_dim_key[0]); i++) {
        for(int j = 0; j < dim_sz(_dim_key[1]); j++) {
            for(int k = 0; k < dim_sz(_dim_key[2]); k++) {
                for(int l = 0; l < dim_sz(_dim_key[3]); l++) {
                    if(randProbGen(gen) < (float)sparsity()/100.0)
                        this->set_data(i, j, k, l, (T)0.0);
                    else 
                        this->set_data(i, j, k, l, (T)randFloatGen(gen));
                }
            }
        }
    }
}

template <class T>
void Tensor4d<T>::zeroInit() {
    for(int i = 0; i < dim_sz(_dim_key[0]); i++) {
        for(int j = 0; j < dim_sz(_dim_key[1]); j++) {
            for(int k = 0; k < dim_sz(_dim_key[2]); k++) {
                for(int l = 0; l < dim_sz(_dim_key[3]); l++) {
                    this->set_data(i, j, k, l, (T)0.0);
                }
            }
        }
    }
}

/* Prints out the specifications of this tensor */
template <class T>
void Tensor4d<T>::print() {
    cout << "Number of Dimensions: " << this->_ndim << endl;
    cout << "Dimension Sizes: " << endl;
    for(int i = 0; i < 4; i++) {
        cout << _dim_key[i] << " " << dim_sz(_dim_key[i]) << endl;
    }
    /* **TODO**: Print out data */
    for(int i = 0; i < dim_sz(_dim_key[0]); i++) {
        for(int j = 0; j < dim_sz(_dim_key[1]); j++) {
            for(int k = 0; k < dim_sz(_dim_key[2]); k++) {
                for(int l = 0; l < dim_sz(_dim_key[3]); l++) {
                    cout << get_data(i, j, k, l) << " ";
                }
                cout << endl;
            }
            cout << endl;
        }
        cout << "-------------------------" << endl;
    }
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
    stride[0] = dim_sz(_dim_key[1]) * dim_sz(_dim_key[2]) * dim_sz(_dim_key[3]);
    stride[1] = dim_sz(_dim_key[2]) * dim_sz(_dim_key[3]);
    stride[2] = dim_sz(_dim_key[3]);
    stride[3] = 1;
    // cout << "Write Limit: " << this->_size-1 << endl;
    // cout << "Calculated index: " << dim1 * stride[0] + dim2 * stride[1] + dim3 * stride[2] + dim4 * stride[3] << endl;
    TENSOR_4D_INDEX_AT(_data, stride, dim1, dim2, dim3, dim4) 
        = init_value;
    // cout << "Setting data successful" << endl;
}

/* Adds data of tensor at given index */
template <class T>
void Tensor4d<T>::add_data(
    unsigned    dim1,
    unsigned    dim2,
    unsigned    dim3,
    unsigned    dim4,
    T           init_value
) {
    unsigned stride[4];
    stride[0] = dim_sz(_dim_key[1]) * dim_sz(_dim_key[2]) * dim_sz(_dim_key[3]);
    stride[1] = dim_sz(_dim_key[2]) * dim_sz(_dim_key[3]);
    stride[2] = dim_sz(_dim_key[3]);
    stride[3] = 1;
    // cout << "Write Limit: " << this->_size-1 << endl;
    // cout << "Calculated index: " << dim1 * stride[0] + dim2 * stride[1] + dim3 * stride[2] + dim4 * stride[3] << endl;
    TENSOR_4D_INDEX_AT(_data, stride, dim1, dim2, dim3, dim4) 
        += init_value;
    // cout << "Adding data successful" << endl;
}

template <class T>
T Tensor4d<T>::get_data(
    unsigned    dim1,
    unsigned    dim2,
    unsigned    dim3,
    unsigned    dim4
) {
    unsigned stride[4];
    stride[0] = dim_sz(_dim_key[1]) * dim_sz(_dim_key[2]) * dim_sz(_dim_key[3]);
    stride[1] = dim_sz(_dim_key[2]) * dim_sz(_dim_key[3]);
    stride[2] = dim_sz(_dim_key[3]);
    stride[3] = 1;
    // cout << "Read Limit: " << this->_size-1 << endl;
    // cout << "Calculated index: " << dim1 * stride[0] + dim2 * stride[1] + dim3 * stride[2] + dim4 * stride[3] << endl;
    return TENSOR_4D_INDEX_AT(_data, stride, dim1, dim2, dim3, dim4);
}

template <class T>
void Tensor4d<T>::copy_data(Tensor4d* tensor) {
    unsigned size = this->size();
    for(unsigned i = 0; i < size; i++)
        this->_data[i] = tensor->data()[i];
}

template class Tensor4d<float>;

}

#endif