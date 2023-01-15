#ifndef SCNN_PPU_H_
#define SCNN_PPU_H_

#include "dlsim/common.h"
#include "dlsim/fmap_4d.h"

#include "scnn/common.h"
#include "scnn/arch_config.h"
#include "scnn/vir_ch.h"
#include "scnn/data_element.h"
#include "scnn/accum_banks.h"

#define   PPU_NUM_PORT_IN   8
#define   PPU_NUM_PORT_OUT  8

namespace Scnn
{

class PPU
{
public:
    PPU(ArchConfig& arch_cfg);
    ~PPU();

	void        cycle(Scnn::AccumulatorBanks* oa_banks);
    bool        idle();

	void        clean();

	Scnn::VirtualChannel<OA_element>*	port_in();
	unsigned							num_port_in();
	Scnn::VirtualChannel<OA_element>*	port_out();
	unsigned							num_port_out();	

private:
	// PostProcessingUnit config
    Scnn::ArchConfig*        		_arch_cfg;

    // i/o ports
    Scnn::VirtualChannel<OA_element>*   _port_in;
    unsigned                            _num_port_in;

    Scnn::VirtualChannel<OA_element>*   _port_out;
    unsigned                            _num_port_out;

    unsigned*                           _ptr_idx_relu;
    unsigned                            _num_elem_per_bank;
};

} // namespace Scnn

#endif