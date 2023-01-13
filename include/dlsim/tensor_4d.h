#ifndef DLSIM_TENSOR_4D_H_
#define DLSIM_TENSOR_4D_H_

#include "dlsim/common.h"
#include "dlsim/tensor.h"

#include "scnn/common.h"

namespace dlsim {

using namespace std;

template<class T>
class Tensor4d : public Tensor {
public:
    Tensor4d();
    Tensor4d(
        unsigned    ndim,
        unsigned    dim1,
        unsigned    dim2,
        unsigned    dim3,
        unsigned    dim4,
        TensorType  type,
        int         sparsity
    );
    virtual ~Tensor4d();

    virtual unsigned				dim_sz(char key);
    virtual unsigned				size();
    virtual void					print();

    T* data() const;

    void set_data(
        unsigned    dim1,
        unsigned    dim2,
        unsigned    dim3,
        unsigned    dim4,
        T           init_value
    );

private:
    
protected:
    // We will use 1D array as 4D array
    T* _data;

};

}

#endif