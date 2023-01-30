#ifndef SCNN_ACCUM_BANKS_H_
#define SCNN_ACCUM_BANKS_H_

#include "dlsim/common.h"
#include "dlsim/fmap_4d.h"

#include "scnn/common.h"
#include "scnn/arch_config.h"
#include "scnn/data_element.h"
#include "scnn/xbar.h"

// FOR DOUBLE BUFFERING
#define NUM_OA_ACCUM_BANK_SETS 2

namespace Scnn
{

class AccumulatorBanks
{
public:
    AccumulatorBanks(Scnn::ArchConfig&  arch_cfg);
    ~AccumulatorBanks();

	void							cycle(Scnn::Xbar* xbar, dlsim::Fmap4d_t* OA_full, bool flush);
    bool              			    idle(Scnn::Xbar* xbar);

    void							clean(unsigned set_id);
    void                            clean();

    // control
    unsigned                        ptr_idle_bank();
    void                            switch_active_bank();

    // get
    OA_element*                   banks();
    unsigned                        ptr_active_bank();
    unsigned                        num_banks();
    unsigned                        num_elem_per_bank();
    bool                            empty(unsigned set_id);

private:
    Scnn::ArchConfig*                _arch_cfg;

    unsigned                        _num_banks;
    unsigned                        _num_elem_per_bank;
    unsigned                        _ptr_active_bank;

    OA_element*                   _banks;

    /* Array of bool values, indicating emptiness of banks? */
    bool*                           _empty;
};
    
} // namespace Scnn

#endif