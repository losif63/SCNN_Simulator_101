#ifndef DLSIM_TENSOR_H_
#define DLSIM_TENSOR_H_

#include "dlsim/common.h"

namespace dlsim{

class Tensor {
public:
    Tensor();
    virtual ~Tensor();
    virtual void    print() = 0;

protected:
    unsigned						_ndim;
	char*							_dim_key;
    map<char, unsigned>			    _dim_sz;
};

}

#endif