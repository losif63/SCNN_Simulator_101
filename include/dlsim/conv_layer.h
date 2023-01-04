#ifndef DLSIM_CONV_LAYER_H_
#define DLSIM_CONV_LAYER_H_

#include "dlsim/common.h"
#include "dlsim/layer.h"
#include "dlsim/fmap_4d.h"
#include "dlsim/weight_4d.h"

// This class gets cfg_layer as INPUT from dlsim::loader
namespace dlsim
{
class ConvLayer : public Layer
{
public:
    ConvLayer(const map<string,unsigned int>* cfg_curr_layer);
    virtual ~ConvLayer();

    virtual Tensor* IFmap();
    virtual Tensor* W();
    virtual Tensor* OFmap();

    virtual void print();

protected:
    unsigned        _name;

    Fmap4d_t*       _IFmap;
    Weight4d_t*     _W;
    Fmap4d_t*       _OFmap;

};

} // namespace dlsim


#endif