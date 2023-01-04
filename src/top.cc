#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <iostream>
#include <assert.h>

#include "dlsim/common.h"
#include "dlsim/loader.h"

#include "scnn/common.h"
#include "scnn/perf_sim.h"

using namespace std;

int main (int argc, char** argv){

    cout << "+++++++ SIMULATION START +++++++" << endl;

    // argc check
    if(argc != 2){
        cout << "[WARNING] Argument should be in the form of './scnn 0 model_name'" << endl;
    }
    assert(argc == 2);
    
    // loader - input is THE MODEL NAME
    dlsim::Loader dnn_loader(argv[1]);

    // simulator
    dlsim::Simulator* perf_sim = NULL;

    // SCNN arch config

    // pe & mult_array
    unsigned    mult_arr_M = 4;
    unsigned    mult_arr_W = 4;
        
    // x-bar
    unsigned    xbar_in = mult_arr_M * mult_arr_W; 
    unsigned    xbar_scale_out_ratio  = 1;
    unsigned    xbar_out  = xbar_in*(xbar_scale_out_ratio);
        
    // q
    unsigned    xbar_in_num_phy_ch_q  = xbar_out;
    unsigned    xbar_in_num_q_entries_per_phy_ch = 1;
    unsigned    xbar_out_num_phy_ch_q  = 1;
    unsigned    xbar_out_num_q_entries_per_phy_ch = 2;
        
    // sram size
    unsigned    chunk_sz_for_accum_bank_sizing = 2;
    unsigned    max_num_elem_per_bank = 0;

    unsigned    max_OA_H_per_PE = 0;
    unsigned    max_OA_W_per_PE = 0;
    unsigned    min_OA_H_per_PE = 1080;
    unsigned    min_OA_W_per_PE = 1080;

    cout << "\n+++++++ PREPROCESSING STEP START : DNN TOPOLOGY ANALYSIS +++++++" << endl;
    while(dnn_loader.done() == false){
        dnn_loader.load_next_layer();
        dnn_loader.print_layer();

        cout << "+++ NOW RUN FOR Layer # "<< dnn_loader.curr_layer_id() << endl;
        
        // IA & W info for this layer
        dlsim::Fmap4d_t*    IFmap = dynamic_cast<dlsim::Fmap4d_t*>(dnn_loader.current_layer()->IFmap());
        dlsim::Weight4d_t*  W     = dynamic_cast<dlsim::Weight4d_t*>(dnn_loader.current_layer()->W());

        unsigned  max_R     = W->dim_sz('R');
        unsigned  max_S     = W->dim_sz('S');
        unsigned  pad_H_sz  = (max_R-1)/2;
        unsigned  pad_W_sz  = (max_S-1)/2;
      
        unsigned  stride_R  = 1;
        unsigned  stride_S  = 1;
      
        unsigned  max_IA_H  = IFmap->dim_sz('H');
        unsigned  max_IA_W  = IFmap->dim_sz('W');
        unsigned  max_OA_H  = (max_IA_H - max_R + 2*pad_H_sz)/stride_R + 1;
        unsigned  max_OA_W  = (max_IA_W - max_S + 2*pad_W_sz)/stride_S + 1;

        unsigned  max_H_per_PE = max_OA_H;
        unsigned  max_W_per_PE = max_OA_W;
        
        // Sweeping all layer, determine the Max and min OA_H_per_PE
        // OA's max H per PE
        if(max_H_per_PE > max_OA_H_per_PE ) {
            max_OA_H_per_PE = max_H_per_PE;
        }
        // OA's max W per PE
        if(max_W_per_PE > max_OA_W_per_PE) {
            max_OA_W_per_PE = max_W_per_PE ;
        }
        // OA's min H per PE
        if(max_H_per_PE < min_OA_H_per_PE) {
            min_OA_H_per_PE = max_H_per_PE;
        }
        // OA's min W per PE
        if(max_W_per_PE < min_OA_W_per_PE) {
            min_OA_W_per_PE = max_W_per_PE;
        }

        // clean-up current layer and add 1 to layer id
        dnn_loader.clear_current_layer();
    }

    // SCNN uArch parameter
    max_num_elem_per_bank = (max_OA_H_per_PE * max_OA_W_per_PE * chunk_sz_for_accum_bank_sizing) / xbar_out;
    // sanity
    assert(((max_OA_H_per_PE * max_OA_W_per_PE * chunk_sz_for_accum_bank_sizing) % xbar_out)==0);

    cout << "+++++++ PREPROCESSING STEP END : DNN TOPOLOGY ANALYSIS +++++++" << endl;
    // make SCNN configuration
    Scnn::ArchConfig arch_config(
        // pe            
        mult_arr_M, 
        mult_arr_W, 

        //xbar
        xbar_in_num_phy_ch_q, 
        xbar_in_num_q_entries_per_phy_ch, 
        xbar_out_num_phy_ch_q, 
        xbar_out_num_q_entries_per_phy_ch, 
        xbar_scale_out_ratio, 
        xbar_in, 
        xbar_out, 

        //sram size
        chunk_sz_for_accum_bank_sizing, 
        max_num_elem_per_bank, 

        max_OA_H_per_PE, 
        max_OA_W_per_PE, 
        min_OA_H_per_PE, 
        min_OA_W_per_PE
    );

    perf_sim = new Scnn::PerfSim(arch_config);

    // initializing
    dnn_loader.update_curr_layer_id(0);

    // DO SIMULATION --- "a single layer for a loop"
    cout << "\n+++++++ PERFOMANCE SIMULATION STEP START +++++++" << endl;
    while(dnn_loader.done() == false){
        cout << "+++ NOW RUN FOR LAYER : Layer # "<< dnn_loader.curr_layer_id() << endl;
        // fetch next layer
        dnn_loader.load_next_layer();
        
        // DEBUG
        #ifdef DEBUG
        dnn_loader.print_layer();
        #endif
        // SEND A LAYER TO PERFORMANCE SIMULATOR
        perf_sim->prepare_current_layer(
            dnn_loader.current_layer()->IFmap(),
            dnn_loader.current_layer()->W(),
            dnn_loader.current_layer()->OFmap()
        );

        // DO PERFORMANCE SIMULATION
        unsigned cycle = 0;
        //cout << "+++ cycle = "  << cycle << endl;

        while(perf_sim->done() == 0){
            //cout << "\n+++ cycle = "  << cycle << endl;
            perf_sim->run();
            cycle++;
        }
        cout << "+++ Final cycle = "  << cycle << endl;

        // COLLECT STATS
        cout << "+++ COLLECTING STATS +++" << endl;
        perf_sim->collect_stats();

        cout << "+++ NOW DONE FOR LAYER : Layer # "<< dnn_loader.curr_layer_id() << endl;

        // CLEAR DNN LAYER
        perf_sim->cleanup_current_layer();
        dnn_loader.clear_current_layer();
    }

    // DONE
    cout << "[DONE]" << endl;
    delete perf_sim;
}
