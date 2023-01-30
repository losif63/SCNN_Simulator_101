#ifndef SCNN_XBAR_H_
#define SCNN_XBAR_H_

#include "dlsim/common.h"

#include "scnn/common.h"
#include "scnn/arch_config.h"
#include "scnn/layer_config.h"
#include "scnn/data_element.h"
#include "scnn/vir_ch.h"

namespace Scnn
{

class Xbar
{
public:
    Xbar(Scnn::ArchConfig& arch_cfg);
    ~Xbar();

	void    cycle();
    bool    idle();
	void    clean();

    int arbitrate_port_in_to_drain_from(unsigned port_out_id);

    // get
    int ptr_drain_port_in_id(unsigned port_out_id);

    Scnn::VirtualChannel<OA_element>*	port_in();
	Scnn::VirtualChannel<OA_element>*	port_out();
	unsigned    num_port_in();
	unsigned    num_port_out();

    // stats
    unsigned    _c_inputs_fwded_to_output;
    unsigned    _c_cycles_active;

private:
	// Xbar config
    Scnn::ArchConfig*  				_arch_cfg;

    // i/o ports
    Scnn::VirtualChannel<OA_element>*  _port_in;
    unsigned                        _num_port_in;

    Scnn::VirtualChannel<OA_element>*  _port_out;
    unsigned                        _num_port_out;

    int*                            _ptr_drain_port_in_id;
};

} // namespace Scnn

#endif