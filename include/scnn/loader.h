#ifndef SCNN_LOADER_H_
#define SCNN_LOADER_H_

#include "dlsim/common.h"
#include "dlsim/tensor.h"
#include "dlsim/tensor_4d.h"
#include "dlsim/fmap_4d.h"
#include "dlsim/weight_4d.h"

#include "scnn/common.h"
#include "scnn/arch_config.h"
#include "scnn/layer_config.h"

namespace Scnn
{

class Loader
{
public:
    Loader(ArchConfig& arch_cfg);
    ~Loader();

    /* Method that brings in the IA, W, OA tensors */
  	void setup_IA_W_and_OA(dlsim::Tensor* IA, dlsim::Tensor* W, dlsim::Tensor* OA);
    /* Method that splits the IA tensor into smaller slices & stores them */
	void distribute_IA_across_spatial_PEs(Scnn::LayerConfig& layer_cfg, Scnn::ArchConfig& arch_cfg);
  	void clear_IA_slice_and_W();
	void check_IA_W_density();

	dlsim::Fmap4d_t** IA_slice();              // Array of Tensor4d objects
    dlsim::Fmap4d_t* IA();
	dlsim::Weight4d_t* W();
    dlsim::Fmap4d_t* OA();

private:
    // SCNN arch
    ArchConfig* _arch_cfg;

    // current layer config
    dlsim::Fmap4d_t*   _IA;
    dlsim::Weight4d_t* _W;
    dlsim::Fmap4d_t*   _OA;
    
    // IA parameters
    tuple<int, int, int, int>* _IA_shape_per_PE; // N C H W
    dlsim::Fmap4d_t** _IA_slice;
};

} // namespace Scnn

#endif