/*
* Filename: data_element.cc
* File created by Jaduk Suh
* Date: January, 2023
*/

#include "scnn/data_element.h"

namespace Scnn 
{

/* TODO: Repeat for IA_element & OA_element */

/**********************************************************************/
// Constructors
W_element::W_element(
    bool valid,
    Weight_t data,
    tensor_4D_idx idx
) {
    this->_valid = valid;
    this->_data = data;
    this->_idx = idx;
}

/**********************************************************************/
// Destructors
W_element::~W_element() {}

/**********************************************************************/
// Member Functions

/* Prints all of the information of this weight element */
void W_element::print() {
    if(!this->_valid) {
        cout << "This weight element is not valid.\n";
        return;
    }
    else cout << "This weight element is valid.\n";
    cout << "The value of this weight is " << this->_data << endl;
    cout << "The index of this weight is [" << get<0>(this->_idx) 
    << ", " << get<1>(this->_idx) << ", " << get<2>(this->_idx) << ", "
    << get<3>(this->_idx) << "]" << endl;
}

/* Public getter method for _valid */
bool W_element::get_valid() {
    return this->_valid;
}

/* Public getter method for _data */
Weight_t W_element::get_data() {
    return this->_data;
}

/* Public getter method for _idx */
tensor_4D_idx W_element::get_idx() {
    return this->_idx;
}

/* Public setter method for _valid */
void W_element::set_valid(bool valid) {
    this->_valid = valid;
}

/* Public setter method for _valid */
void W_element::set_data(Weight_t data) {
    this->_data = data;
}

/* Public setter method for _valid */
void W_element::set_idx(tensor_4D_idx idx) {
    this->_idx = idx;
}

}