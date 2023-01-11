/*
* Filename: vir_ch.cc
* File created by Jaduk Suh
* Date: January, 2023
*/

#include "scnn/vir_ch.h"

#ifndef SCNN_VIR_CH_CC_
#define SCNN_VIR_CH_CC_



namespace Scnn 
{

/**********************************************************************/
// Constructors
template <class T>
VirtualChannel<T>::VirtualChannel() {
    // Negative numbers mean not initialized yet
    this->_num_phy_ch_q = -1;
    this->_num_q_entries_per_phy_ch = -1;
}

/**********************************************************************/
// Destructors
template <class T>
VirtualChannel<T>::~VirtualChannel() {
    /* TODO: Free memory allocated to deque structure */
}

/**********************************************************************/
// Member functions

template <class T>
bool VirtualChannel<T>::isFullOnPhyCh(unsigned phy_id) {
    assert((_num_phy_ch_q > 0) && (phy_id >= 0)
    && (phy_id < _num_phy_ch_q));
    
    /* <WARNING> This part is susceptible to huge runtime errors */
    if(((deque<T>*)&_phy_ch_q[phy_id])->size() < 
    _num_q_entries_per_phy_ch) return false;
    else return true;
}

template <class T>
void VirtualChannel<T>::init(unsigned num_phy_ch_q, 
                        unsigned num_q_entries_per_phy_ch) {
    assert(num_phy_ch_q > 0);
    assert(num_q_entries_per_phy_ch > 0);   
    this->_num_phy_ch_q = num_phy_ch_q;
    this->_num_q_entries_per_phy_ch = num_q_entries_per_phy_ch;

    deque<T> queueList[num_phy_ch_q];
    _phy_ch_q = queueList;
}

/* My guess: If there are no elements in the channel, it is idle */
template <class T>
bool VirtualChannel<T>::idle() {
    assert((_num_phy_ch_q > 0) && (_num_q_entries_per_phy_ch) > 0);
    for(int i = 0; i < this->_num_phy_ch_q; i++) {
        // If any one of the channels has element, it is not idle
        if(canDrain(i)) return false;
    }
    return true;
}

template <class T>
bool VirtualChannel<T>::canReceive(unsigned phy_id) {
    return !this->isFullOnPhyCh(phy_id);
}

template <class T>
bool VirtualChannel<T>::canDrain(unsigned phy_id) {
    assert((_num_phy_ch_q > 0) && (phy_id >= 0)
    && (phy_id < _num_phy_ch_q));
    /* <WARNING> This part is susceptible to huge runtime errors */
    if(((deque<T>*)&_phy_ch_q[phy_id])->size() > 0) return true;
    else return false;
}

template <class T>
void VirtualChannel<T>::receive(T elem, unsigned phy_id) {
    assert(this->canReceive(phy_id));
    ((deque<T>)&_phy_ch_q[phy_id])->push_front(elem);
}

template <class T>
T VirtualChannel<T>::drain(unsigned phy_id) {
    assert(this->canDrain(phy_id));
    return ((deque<T>)&_phy_ch_q[phy_id])->pop_back();
}

template <class T>
T VirtualChannel<T>::next_elem_to_be_drained(unsigned phy_id) {
    assert(canDrain(phy_id));
    return ((deque<T>)&_phy_ch_q[phy_id])->back();
}

template <class T>
unsigned VirtualChannel<T>::num_phy_ch_q() {
    return this->_num_phy_ch_q;
}

template <class T>
unsigned VirtualChannel<T>::num_q_entries_per_phy_ch() {
    return this->_num_q_entries_per_phy_ch;
}

/**********************************************************************/
}

#endif