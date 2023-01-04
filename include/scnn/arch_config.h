#ifndef SCNN_ARCH_CONFIG_H_
#define SCNN_ARCH_CONFIG_H_

#include "dlsim/common.h"

#include "scnn/common.h"
namespace Scnn{

class ArchConfig{

public:
    ArchConfig(
        unsigned    _mult_arr_M,
        unsigned    _mult_arr_W,
 
        // xbar io-ports 
        unsigned      xbar_in_num_phy_ch_q,
        unsigned      xbar_in_num_q_entries_per_phy_ch,
        unsigned      xbar_out_num_phy_ch_q,
        unsigned      xbar_out_num_q_entries_per_phy_ch,

        unsigned      xbar_scale_out_ratio,
        unsigned      xbar_in,
        unsigned      xbar_out,

        unsigned      chunk_sz_for_accum_bank_sizing,
        unsigned      max_num_elem_per_bank,

        unsigned      max_OA_H_per_PE,
        unsigned      max_OA_W_per_PE,
        unsigned      min_OA_H_per_PE,
        unsigned      min_OA_W_per_PE
    );

    ~ArchConfig();

    //get
    unsigned get_mult_arr_M();
    unsigned get_mult_arr_W();

    unsigned get_xbar_in_num_phy_ch_q();                
    unsigned get_xbar_in_num_q_entries_per_phy_ch();    
    unsigned get_xbar_out_num_phy_ch_q();               
    unsigned get_xbar_out_num_q_entries_per_phy_ch();   

    unsigned get_xbar_scale_out_ratio();
    unsigned get_xbar_in();
    unsigned get_xbar_out();
    unsigned get_chunk_sz_for_accum_bank_sizing();
    unsigned get_max_num_elem_per_bank();

    unsigned get_max_OA_H_per_PE();
    unsigned get_max_OA_W_per_PE();
    unsigned get_min_OA_H_per_PE();
    unsigned get_min_OA_W_per_PE();

private:
    // multiplier array
    unsigned    _mult_arr_M;
    unsigned    _mult_arr_W;
    
    // xbar io-ports 
    unsigned    _xbar_in_num_phy_ch_q;
    unsigned    _xbar_in_num_q_entries_per_phy_ch;
    unsigned    _xbar_out_num_phy_ch_q;
    unsigned    _xbar_out_num_q_entries_per_phy_ch;
    
    // xbar
    unsigned    _xbar_scale_out_ratio;
    unsigned    _xbar_in;
    unsigned    _xbar_out;
    
    // sram size
    unsigned    _chunk_sz_for_accum_bank_sizing;    // Chanel size for accumm bank
    unsigned    _max_num_elem_per_bank;             // max number of element for a single bank 
    
    unsigned    _max_OA_H_per_PE;
    unsigned    _max_OA_W_per_PE;
    unsigned    _min_OA_H_per_PE;
    unsigned    _min_OA_W_per_PE;
};

}

#endif