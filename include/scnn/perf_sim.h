#ifndef SCNN_PERF_SIM_H_
#define SCNN_PERF_SIM_H_

#include "dlsim/common.h"
#include "dlsim/simulator.h"
#include "dlsim/tensor.h"
#include "dlsim/tensor_4d.h"
#include "dlsim/weight_4d.h"
#include "dlsim/fmap_4d.h"

#include "scnn/common.h"
#include "scnn/arch_config.h"
#include "scnn/layer_config.h"

#include "scnn/pe.h"
#include "scnn/loader.h"

namespace Scnn{

class PerfSim : public dlsim::Simulator{
public:
    PerfSim(Scnn::ArchConfig& arch_cfg);
    virtual ~PerfSim();
    
    virtual void run();                             // for dynamic binding
    virtual bool done();

    virtual void prepare_current_layer(
        dlsim::Tensor* IA,
        dlsim::Tensor* W,
        dlsim::Tensor* OA
        );
    virtual void cleanup_current_layer();
    virtual void collect_stats();

    void cycle();

    Scnn::PE** get_PE();

private:
	Scnn::ArchConfig    _arch_cfg;     // decided by user at the top file.
	Scnn::LayerConfig   _layer_cfg;

	Scnn::Loader*   _loader;
	Scnn::PE**       _pe;

    unsigned long long _cycle_network;  // counting model-wide cycle
    unsigned long long _cycle_layer;    // counting layer-wide cycle (e.g., cycle for each layer)
};

} // namespace Scnn

#endif //SCNN_PERF_SIM_H_
