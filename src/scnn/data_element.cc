/*
* Filename: data_element.cc
* File created by Jaduk Suh
* Date: January, 2023
*/

#include "scnn/data_element.h"

#ifndef SCNN_DATA_ELEMENT_CC_
#define SCNN_DATA_ELEMENT_CC_

namespace Scnn 
{

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

IA_element::IA_element(
    bool valid,
    Weight_t data,
    tensor_4D_idx idx
) {
    this->_valid = valid;
    this->_data = data;
    this->_idx = idx;
}

OA_element::OA_element() {}

OA_element::OA_element(
    bool valid,
    Fmap_t data,
    tensor_4D_idx idx,
    unsigned bank_id,
    unsigned idx_in_bank
) {
    this->_valid = valid;
    this->_data = data;
    this->_idx = idx;
    this->_bank_id = bank_id;
    this->_idx_in_bank = idx_in_bank;
}

/**********************************************************************/
// Destructors
W_element::~W_element() {}

IA_element::~IA_element() {}

OA_element::~OA_element() {}

/**********************************************************************/
// Member Functions

/* Prints all of the information of this weight element */
void W_element::print() {
    if(!this->_valid) {
        cout << "Invalid-----------------------\n";
        return;
    }
    else cout << "Valid----";
    cout << "[" << get<0>(this->_idx) 
    << ", " << get<1>(this->_idx) << ", " << get<2>(this->_idx) << ", "
    << get<3>(this->_idx) << "]" << " ";
    cout << this->_data << endl;
}

/* Prints all of the information of this IA element */
void IA_element::print() {
    if(!this->_valid) {
        cout << "Invalid-----------------------\n";
        return;
    }
    else cout << "Valid----";
    cout << "[" << get<0>(this->_idx) 
    << ", " << get<1>(this->_idx) << ", " << get<2>(this->_idx) << ", "
    << get<3>(this->_idx) << "]" << " ";
    cout << this->_data << endl;
}

/* Prints all of the information of this OA element */
void OA_element::print() {
    if(!this->_valid) {
        cout << "This OA element is not valid.\n";
        return;
    }
    else cout << "This OA element is valid.\n";
    cout << "The value of this OA element is " << this->_data << endl;
    cout << "The index of this OA element is [" << get<0>(this->_idx) 
    << ", " << get<1>(this->_idx) << ", " << get<2>(this->_idx) << ", "
    << get<3>(this->_idx) << "]" << endl;
    cout << "The bank ID of this OA element is " << this->_bank_id 
    << endl;
    cout << "The index ID in the bank of this OA element is " 
    << this->_idx_in_bank << endl;
}

/* Public getter method for _valid of W_element */
bool W_element::get_valid() {
    return this->_valid;
}

/* Public getter method for _data of W_element */
Weight_t W_element::get_data() {
    return this->_data;
}

/* Public getter method for _idx of W_element */
tensor_4D_idx W_element::get_idx() {
    return this->_idx;
}

/* Public getter method for _valid of IA_element */
bool IA_element::get_valid() {
    return this->_valid;
}

/* Public getter method for _data of IA_element */
Fmap_t IA_element::get_data() {
    return this->_data;
}

/* Public getter method for _idx of IA_element */
tensor_4D_idx IA_element::get_idx() {
    return this->_idx;
}

/* Public getter method for _valid of OA_element */
bool OA_element::get_valid() {
    return this->_valid;
}

/* Public getter method for _data of OA_element */
Fmap_t OA_element::get_data() {
    return this->_data;
}

/* Public getter method for _idx of OA_element */
tensor_4D_idx OA_element::get_idx() {
    return this->_idx;
}

/* Public getter method for _bank_id of OA_element */
unsigned OA_element::get_bank_id() {
    return this->_bank_id;
}

/* Public getter method for _idx_in_bank of OA_element */
unsigned OA_element::get_idx_in_bank() {
    return this->_idx_in_bank;
}

/* Public setter method for _valid of W_element */
void W_element::set_valid(bool valid) {
    this->_valid = valid;
}

/* Public setter method for _valid of W_element */
void W_element::set_data(Weight_t data) {
    this->_data = data;
}

/* Public setter method for _valid of W_element */
void W_element::set_idx(tensor_4D_idx idx) {
    this->_idx = idx;
}

/* Public setter method for _valid of IA_element */
void IA_element::set_valid(bool valid) {
    this->_valid = valid;
}

/* Public setter method for _valid of IA_element */
void IA_element::set_data(Fmap_t data) {
    this->_data = data;
}

/* Public setter method for _valid of IA_element */
void IA_element::set_idx(tensor_4D_idx idx) {
    this->_idx = idx;
}

/* Public setter method for _data of OA_element */
void OA_element::write_data(Fmap_t new_data) {
    this->_data = new_data;
}

/* Public setter method for _bank_id of OA_element */
void OA_element::write_bank_id(unsigned new_id) {
    this->_bank_id = new_id;
}

/* Public setter method for _idx_in_bank of OA_element */
void OA_element::write_idx_in_bank(unsigned new_idx) {
    this->_idx_in_bank = new_idx;
}

}

#endif