// *** APROVED *** //

#ifndef _SCNN_VIR_CH_H_
#define _SCNN_VIR_CH_H_

#include "dlsim/common.h"

#include "scnn/common.h"

namespace Scnn
{

template<class T>
class VirtualChannel{
public:
    VirtualChannel();
    ~VirtualChannel();

	// done
	bool			    isFullOnPhyCh(unsigned phy_id);
    void                init(unsigned num_phy_ch_q, unsigned num_q_entries_per_phy_ch);
    bool                idle();

	bool				canReceive(unsigned phy_id);
	bool				canDrain(unsigned phy_id);
	void				receive(T elem, unsigned phy_id);
	T                   drain(unsigned phy_id);
	T                   next_elem_to_be_drained(unsigned phy_id);

    // get
    unsigned            num_phy_ch_q();
    unsigned            num_q_entries_per_phy_ch();

private:
    unsigned            _num_phy_ch_q;              // # of physical channels in this virtual channel
    unsigned            _num_q_entries_per_phy_ch;  // # of Q_entries per physical channel

    // queues
	deque<T>*			_phy_ch_q;
};

} // namespace Scnn

#endif