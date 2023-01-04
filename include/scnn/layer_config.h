#ifndef SCNN_LAYER_CONFIG_H_
#define SCNN_LAYER_CONFIG_H_

#include "scnn/common.h"

namespace Scnn
{
class LayerConfig
{
public:
    LayerConfig();
    LayerConfig(
        unsigned N,
        unsigned C,
        unsigned H,
        unsigned W,
        unsigned K,
        unsigned R,
        unsigned S,
        unsigned chunk_sz
    );
    ~LayerConfig();

    // get
    unsigned get_N();
    unsigned get_C();
    unsigned get_H();
    unsigned get_W();
    unsigned get_K();
    unsigned get_R();
    unsigned get_S();
    unsigned get_chunk_sz();

    unsigned get_H_per_PE();
    unsigned get_W_per_PE();

    // set
    unsigned set_N(unsigned N);
    unsigned set_C(unsigned C);
    unsigned set_H(unsigned H);
    unsigned set_W(unsigned W);
    unsigned set_K(unsigned K);
    unsigned set_R(unsigned R);
    unsigned set_S(unsigned S);
    unsigned set_chunk_sz(unsigned chunk_sz);

    unsigned set_H_per_PE(unsigned H_per_PE);   
    unsigned set_W_per_PE(unsigned W_per_PE);   

private:
    unsigned _N;
    unsigned _C;
    unsigned _H;
    unsigned _W;
    unsigned _K;
    unsigned _R;
    unsigned _S;
    unsigned _chunk_sz;  // kernel wide

    unsigned _H_per_PE;
    unsigned _W_per_PE;
};

} // namespace Scnn

#endif