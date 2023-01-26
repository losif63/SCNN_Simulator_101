#ifndef SCNN_SEQUENCER_H_
#define SCNN_SEQUENCER_H_

#include "dlsim/common.h"
#include "dlsim/fmap_4d.h"
#include "dlsim/weight_4d.h"

#include "scnn/common.h"
#include "scnn/arch_config.h"
#include "scnn/layer_config.h"

namespace Scnn
{
class Sequencer
{
public:
    Sequencer();
    ~Sequencer();

    void                init(Scnn::LayerConfig& layer_cfg, dlsim::Fmap4d_t*, dlsim::Weight4d_t* W);
    void                clean();

    // indicator
    /* Working set probably refers to chunks */
    bool                advance_to_next_working_set();
    /* Layers deal with all variables - N, C, Kc, K/Kc */
    bool                done_with_layer();
    
    // dataflow control
    void                next_N_id();
    void                next_C_id();
    void                next_chunk_id();
    /* We must compute all possible combinations of vector F and I */
    void                rewind_N_id();
    void                rewind_C_id();
    void                rewind_chunk_id();

    bool                end_of_N_id();
    bool                end_of_C_id();
    bool                end_of_chunk_id();
    
    // get
    unsigned            curr_N_id();
    unsigned            curr_C_id();
    unsigned            curr_chunk_id();

private:
    unsigned						_curr_N_id;
    unsigned						_curr_C_id;
    unsigned						_curr_chunk_id;

	unsigned						_max_N_id;
	unsigned						_max_C_id;
	unsigned						_max_K_id;
	unsigned						_chunk_sz;
	unsigned						_max_chunk_id;

	bool						    _done_with_layer;

    // IA and W (for this PE)
    dlsim::Fmap4d_t*        _IA;
    dlsim::Fmap4d_t*       _IA_slice;
    dlsim::Weight4d_t*      _W;

};

} // namespace Scnn


#endif