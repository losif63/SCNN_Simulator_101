#ifndef SCNN_MULT_ARRAY_H_
#define SCNN_MULT_ARRAY_H_

#include "dlsim/common.h"
#include "dlsim/tensor_4d.h"
#include "dlsim/fmap_4d.h"
#include "dlsim/weight_4d.h"

#include "scnn/common.h"
#include "scnn/data_element.h"
#include "scnn/arch_config.h"
#include "scnn/layer_config.h"
#include "scnn/vir_ch.h"
#include "scnn/xbar.h"

#define NUM_ACCUM_HAZARD_BINS 9 
#define NUM_ACCUM_BANKS_BINS  32

namespace Scnn{

class MultArray{
public:
    MultArray(Scnn::ArchConfig& arch_cfg);
    ~MultArray();
    
    // fill
    // In the init stage, one should fill the WFIFO and IARAM
    void init(
        Scnn::LayerConfig& layer_cfg,
        dlsim::Tensor* IA_slice,
        dlsim::Tensor* W);
    void clean();
    bool fill_WFIFO_and_IARAM(
        dlsim::Fmap4d_t* IA_full,
        unsigned N_id, unsigned C_id,
        unsigned chunk_id);

    void                      check_IA_slice_sanity(dlsim::Fmap4d_t* IA_full, unsigned N_id, unsigned C_id);

    // Xbar contains channels of OA_element
	void                      cycle(Scnn::Xbar* xbar);
    bool                      idle();

    bool                      compute_mul_array_output(Scnn::Xbar* xbar);

    int                       accum_addr_in_1d(tensor_4D_idx oa_idx);
    unsigned                  accum_addr_to_bank_id(unsigned mode, int accum_addr, unsigned num_accum_banks);
    unsigned                  idx_in_bank(unsigned mode, int accum_addr, unsigned num_accum_banks);

    tuple<unsigned,unsigned>  OA_idx_to_bank_addr(tensor_4D_idx oa_idx);

    // control
    // advance --> bring in next vectors
    void                      advance_WFIFO();
    void                      advance_IARAM();
    void                      advance_to_next_mul_op();
    void                      clear_both_WFIFO_and_IARAM();

    // helper functions
    bool                      is_empty_WFIFO();
    bool                      is_empty_IARAM();

    // get
    W_vec_entry               curr_WFIFO_entry();
    IA_vec_entry              curr_IARAM_entry();
    bool                      end_of_WFIFO();
    bool                      end_of_IARAM();

    // stats
    unsigned                _c_num_of_nz_act;
    unsigned                _c_num_of_nz_w;
    unsigned                _c_multiply_ops_completed;
	unsigned				_c_cycles_drained_mularray_output;
	unsigned				_c_cycles_stalled_due_to_xbar_in_full;

    unsigned                _c_num_output_accumu_hazards[NUM_ACCUM_HAZARD_BINS];
    unsigned                _c_num_output_accumu_to_same_bank[NUM_ACCUM_BANKS_BINS];

private:
    // configurations
    Scnn::ArchConfig     _arch_cfg;
    Scnn::LayerConfig    _layer_cfg;

    deque<W_vec_entry>   _WFIFO;       
    deque<IA_vec_entry>  _IARAM;       
    
    // ptr to currently active WFIFO entry
    int   _ptr_WFIFO;

    // ENTIRE VALUE MAP
    dlsim::Fmap4d_t*    _IA;
    dlsim::Weight4d_t*  _W;

    // layer-specific info
    int                     _max_r;
    int                     _max_s;
    int                     _pad_h_sz;
    int                     _pad_w_sz;
    int                     _stride_r;
    int                     _stride_s;
    int                     _max_IA_h;
    int                     _max_IA_w;
    int                     _max_OA_h;
    int                     _max_OA_w;
    int                     _max_OA_H_per_PE;
    int                     _max_OA_W_per_PE;
    int                     _base_offset_h_in_OA;
    int                     _base_offset_w_in_OA;
    int                     _max_idx_h_in_OA;
    int                     _max_idx_w_in_OA;
};

} // namespace Scnn

#endif