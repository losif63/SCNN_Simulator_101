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
        unsigned    N,
        unsigned    C,
        unsigned    H,
        unsigned    W,
        char*       type,
        int         sparsity
    );
    virtual ~Tensor4d();

    virtual unsigned				dim_sz(char key);
    virtual unsigned				size();
    virtual void					print();

    T**** data() const;

    void set_data(
        unsigned    N,
        unsigned    C,
        unsigned    H,
        unsigned    W,
        T           init_value
        );

private:
    
protected:
    T**** _data;

};

}

#endif