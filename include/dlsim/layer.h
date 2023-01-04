#ifndef DLSIM_LAYER_H_
#define DLSIM_LAYER_H_

#include "dlsim/common.h"
#include "dlsim/tensor.h"

namespace dlsim
{

class Layer
{
public:
    Layer(/* args */);
    virtual ~Layer();

    virtual Tensor* IFmap()       =0;
    virtual Tensor* W()           =0;
    virtual Tensor* OFmap()       =0;

    virtual void print()          =0;
};


} // namespace dlsim

#endif