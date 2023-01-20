#ifndef SCNN_PE_H_
#define SCNN_PE_H_

#include "dlsim/common.h"

#include "scnn/common.h"
#include "scnn/arch_config.h"
#include "scnn/layer_config.h"

// HARDWARES
#include "scnn/mult_array.h"
#include "scnn/sequencer.h"
#include "scnn/xbar.h"
#include "scnn/accum_banks.h"
#include "scnn/ppu.h"

namespace Scnn
{
class PE {
public:
    PE(Scnn::ArchConfig& arch_cfg);
    ~PE();

	void    cycle();
    bool    finished_layer_exec();	
    bool    idle();
	void    prepare_current_layer(
                dlsim::Tensor* IA_full,
                dlsim::Tensor* OA_full,
                dlsim::Tensor* IA_slice,
                dlsim::Tensor* W,
                Scnn::LayerConfig& layer_cfg
                );
	void	cleanup_current_layer();
    void    find_work();

    // get
    bool                  sync_barrier();

    // set
    void                  setup_sync_barrier();
    void                  clear_sync_barrier();

    // stat
    unsigned              _c_cycle_active;
    unsigned              _c_cycle_waiting_at_barrier;
    unsigned              _c_cycle_finished_waiting_others;

    // get modules
    Scnn::MultArray*              get_mult();
	Scnn::PPU*	                  get_ppu();

    dlsim::Fmap4d_t*	          get_IA_slice();
    dlsim::Weight4d_t*            get_W();

private:
    // state
    bool                            _sync_barrier;
    unsigned long long              _cycle;

	// PE config
	Scnn::ArchConfig			      _arch_cfg;
    Scnn::LayerConfig                 _layer_cfg;

    // major modules
    Scnn::Sequencer*			    _sequencer;
    Scnn::MultArray*				_mult_array;
    Scnn::Xbar*						_xbar;
    Scnn::AccumulatorBanks*         _oa_banks;
    Scnn::PPU*                      _ppu;

    // IA/OA (the entire NCHW) -- used for sanity check
    dlsim::Fmap4d_t*            _IA_full;
    dlsim::Fmap4d_t*            _OA_full;

	// IA and W (for this PE)
	dlsim::Fmap4d_t*	                  _IA_slice;
	dlsim::Weight4d_t*			          _W;

    friend class PerfSim;
};

} // namespace Scnn
#endif