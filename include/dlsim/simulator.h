#ifndef DLSIM_SIMULATOR_H
#define DLSIM_SIMULATOR_H

#include "dlsim/common.h"
#include "dlsim/tensor.h"
namespace dlsim
{
class Simulator{

public:
    Simulator();
    virtual ~Simulator();

    virtual void run();
    virtual bool done();
    virtual void prepare_current_layer(Tensor* IA, Tensor* W, Tensor* OA) = 0;
    virtual void cleanup_current_layer() = 0;
    virtual void collect_stats() = 0;

    };

} // namespace dlsim

#endif