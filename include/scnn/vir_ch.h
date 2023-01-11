// *** APROVED *** //

/*
* Filename: vir_ch.h
* File created by VIALAB
* File documentation (comments) by Jaduk Suh
* Date: January, 2023
*/

#ifndef _SCNN_VIR_CH_H_
#define _SCNN_VIR_CH_H_

#include "dlsim/common.h"

#include "scnn/common.h"

namespace Scnn
{

/* Class VirtualChannel */
/* This class is meant to model the crossbar interconnection.
*  Crossbars have many input channels & output channels,
*  and every combination of input and output channels are connected.
*  The Xbar class consists of two VirtualChannel objects - 1 for input,
*  and 1 for output.
*  Thus, this VirtualChannel class connects many physical channels with 
*  1 channel.
*/
template<class T>
class VirtualChannel{
public:
    VirtualChannel();
    ~VirtualChannel();

	// done
    /* Returns whether channel number phy_id is full */
	bool			    isFullOnPhyCh(unsigned phy_id);
    /* Initializes the VirtualChannel object */
    void                init(unsigned num_phy_ch_q, 
                            unsigned num_q_entries_per_phy_ch);
    /* Returns whether this VirtualChannel is busy or not */
    bool                idle();

    /* Returns whether channel number phy_id has empty slots */
	bool				canReceive(unsigned phy_id);
    /* Returns whether channel number phy_id has elements to drain */
	bool				canDrain(unsigned phy_id);
    /* Insert element T into channel number phy_id */
	void				receive(T elem, unsigned phy_id);
    /* Remove element T from channel number phy_id and return element */
	T                   drain(unsigned phy_id);
    /* Return the next element to be removed from channel phy_id */
	T                   next_elem_to_be_drained(unsigned phy_id);

    // get
    /* Public getter method for the number of channels */
    unsigned            num_phy_ch_q();
    /* Public getter method for the number of entries per channel */
    unsigned            num_q_entries_per_phy_ch();

private:
    // # of physical channels in this virtual channel
    unsigned            _num_phy_ch_q;
    // # of Q_entries per physical channel
    unsigned            _num_q_entries_per_phy_ch;

    // queues
    /* Array of physical channels of this VirtualChannel */
    /* Indexed by 0 ~ _num_phy_ch_q-1 */
	deque<T>*			_phy_ch_q;
};

} // namespace Scnn

#endif