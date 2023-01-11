/*
* Filename: layer_config.cc
* File created by Jaduk Suh
* Date: January, 2023
*/

#include "scnn/layer_config.h"

namespace Scnn {

/**********************************************************************/
// Constructors
LayerConfig::LayerConfig() { // -1 means uninitilaized
    this->set_N(-1);
    this->set_C(-1);
    this->set_H(-1);
    this->set_W(-1);
    this->set_K(-1);
    this->set_R(-1);
    this->set_S(-1);
    this->set_chunk_sz(-1);

    this->set_H_per_PE(-1);
    this->set_W_per_PE(-1);
}

LayerConfig::LayerConfig(
    unsigned N,
    unsigned C,
    unsigned H,
    unsigned W,
    unsigned K,
    unsigned R,
    unsigned S,
    unsigned chunk_sz
) {
    this->set_N(N);
    this->set_C(C);
    this->set_H(H);
    this->set_W(W);
    this->set_K(K);
    this->set_R(R);
    this->set_S(S);
    this->set_chunk_sz(chunk_sz);
    
    this->set_H_per_PE(-1);  // Cannot determine value yet
    this->set_W_per_PE(-1);
}

/**********************************************************************/
// Destructors
LayerConfig::~LayerConfig() {}

/**********************************************************************/
// Public getter functions

/* Returns _N of current object */
unsigned LayerConfig::get_N() {
    return this->_N;
}

/* Returns _C of current object */
unsigned LayerConfig::get_C() {
    return this->_C;
}

/* Returns _H of current object */
unsigned LayerConfig::get_H() {
    return this->_H;
}

/* Returns _W of current object */
unsigned LayerConfig::get_W() {
    return this->_W;
}

/* Returns _K of current object */
unsigned LayerConfig::get_K() {
    return this->_K;
}

/* Returns _R of current object */
unsigned LayerConfig::get_R() {
    return this->_R;
}

/* Returns _S of current object */
unsigned LayerConfig::get_S() {
    return this->_S;
}

/* Returns _chunk_sz of current object */
unsigned LayerConfig::get_chunk_sz() {
    return this->_chunk_sz;
}

/* Returns _H_per_PE of current object */
unsigned LayerConfig::get_H_per_PE() {
    return this->_H_per_PE;
}

/* Returns _W_per_PE of current object */
unsigned LayerConfig::get_W_per_PE() {
    return this->_W_per_PE;
}

/**********************************************************************/
// Public setter functions

/* Updates _N and returns updated value */
unsigned LayerConfig::set_N(unsigned N) {
    this->_N = N;
    return this->_N;
}

/* Updates _C and returns updated value */
unsigned LayerConfig::set_C(unsigned C) {
    this->_C = C;
    return this->_C;
}

/* Updates _H and returns updated value */
unsigned LayerConfig::set_H(unsigned H) {
    this->_H = H;
    return this->_H;
}

/* Updates _W and returns updated value */
unsigned LayerConfig::set_W(unsigned W) {
    this->_W = W;
    return this->_W;
}

/* Updates _K and returns updated value */
unsigned LayerConfig::set_K(unsigned K) {
    this->_K = K;
    return this->_K;
}

/* Updates _R and returns updated value */
unsigned LayerConfig::set_R(unsigned R) {
    this->_R = R;
    return this->_R;
}

/* Updates _S and returns updated value */
unsigned LayerConfig::set_S(unsigned S) {
    this->_S = S;
    return this->_S;
}

/* Updates _chunk_sz and returns updated value */
unsigned LayerConfig::set_chunk_sz(unsigned chunk_sz) {
    this->_chunk_sz = chunk_sz;
    return this->_chunk_sz;
}

/* Updates _H_per_PE and returns updated value */
unsigned LayerConfig::set_H_per_PE(unsigned H_per_PE) {
    this->_H_per_PE = H_per_PE;
    return this->_W;
}

/* Updates _W_per_PE and returns updated value */
unsigned LayerConfig::set_W_per_PE(unsigned W_per_PE) {
    this->_W_per_PE = W_per_PE;
    return this->_W_per_PE;
}

/**********************************************************************/
}