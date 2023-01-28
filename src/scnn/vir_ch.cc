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
    _phy_ch_q = NULL;
}

/**********************************************************************/
// Destructors
template <class T>
VirtualChannel<T>::~VirtualChannel() {
    /* TODO: Free memory allocated to deque structure */
    if(_phy_ch_q != NULL) delete _phy_ch_q;
}

/**********************************************************************/
// Member functions

template <class T>
void VirtualChannel<T>::init(unsigned num_phy_ch_q, 
                        unsigned num_q_entries_per_phy_ch) {
    assert(num_phy_ch_q > 0);
    assert(num_q_entries_per_phy_ch > 0);   
    this->_num_phy_ch_q = num_phy_ch_q;
    this->_num_q_entries_per_phy_ch = num_q_entries_per_phy_ch;
    _phy_ch_q = new deque<T>[num_phy_ch_q];
}

template <class T>
bool VirtualChannel<T>::isFullOnPhyCh(unsigned phy_id) {
    assert((_num_phy_ch_q > 0) && (phy_id >= 0)
    && (phy_id < _num_phy_ch_q));
    
    // cout << "current size: " << _phy_ch_q[phy_id].size() << endl;
    // cout << "limit: " << _num_q_entries_per_phy_ch << endl;
    if(_phy_ch_q[phy_id].size() < _num_q_entries_per_phy_ch)
        return false;
    else return true;
}

/* My guess: If there are no elements in the channel, it is idle */
template <class T>
bool VirtualChannel<T>::idle() {
    // Not initialized yet
    if((_num_phy_ch_q < 0) && (_num_q_entries_per_phy_ch) < 0)
        return true;
    
    for(int i = 0; i < _num_phy_ch_q; i++) {
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
    if(_phy_ch_q[phy_id].size() > 0) return true;
    else return false;
}

template <class T>
void VirtualChannel<T>::receive(T elem, unsigned phy_id) {
    assert(this->canReceive(phy_id));
    _phy_ch_q[phy_id].push_front(elem);
    // cout << "Just pushed an element!!\n";
    // cout << "Pushed element: " << _phy_ch_q[phy_id].front() << endl;
}

template <class T>
T VirtualChannel<T>::drain(unsigned phy_id) {
    assert(this->canDrain(phy_id));
    T temp = _phy_ch_q[phy_id].back();
    _phy_ch_q[phy_id].pop_back();
    return temp;
}

template <class T>
T VirtualChannel<T>::next_elem_to_be_drained(unsigned phy_id) {
    assert(canDrain(phy_id));
    return _phy_ch_q[phy_id].back();
}

template <class T>
unsigned VirtualChannel<T>::num_phy_ch_q() {
    return this->_num_phy_ch_q;
}

template <class T>
unsigned VirtualChannel<T>::num_q_entries_per_phy_ch() {
    return this->_num_q_entries_per_phy_ch;
}

template class VirtualChannel<int>;
template class VirtualChannel<float>;
template class VirtualChannel<OA_element>;

/**********************************************************************/
}

#endif