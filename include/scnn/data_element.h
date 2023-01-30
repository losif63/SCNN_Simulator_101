#ifndef SCNN_DATA_ELEMENT_H_
#define SCNN_DATA_ELEMENT_H_

#include "dlsim/common.h"

#include "scnn/common.h"

namespace Scnn
{

#define W_vec_entry     vector<W_element>
#define IA_vec_entry    vector<IA_element>

#define tensor_4D_idx   tuple<int, int, int, int>

class W_element{
public:
    W_element(
        bool valid,
        Weight_t data,
        tensor_4D_idx idx
        );
    ~W_element();
    
    void print();

    void set_valid(bool valid);
    void set_data(Weight_t data);
    void set_idx(tensor_4D_idx idx);

    bool            get_valid();
    Weight_t        get_data();
    tensor_4D_idx   get_idx();

private:
    bool            _valid;
    Weight_t        _data;
    tensor_4D_idx   _idx;
};

class IA_element {
public:
    IA_element(bool valid, Weight_t data, tensor_4D_idx idx);
    ~IA_element();

    void print();
    
    void set_valid(bool valid);
    void set_data(Fmap_t data);
    void set_idx(tensor_4D_idx idx);

    bool            get_valid();
    Fmap_t          get_data();
    tensor_4D_idx   get_idx();

private:
    bool            _valid;
    Fmap_t          _data;
    tensor_4D_idx   _idx;
};

class OA_element {
public:
    OA_element();
    OA_element(
        bool valid,
        Fmap_t data,
        tensor_4D_idx idx,
        unsigned bank_id,
        unsigned idx_in_bank
        );
    ~OA_element();

    //get
    bool            get_init();
    bool            get_valid();
    Fmap_t          get_data();
    tensor_4D_idx   get_idx();
    unsigned        get_bank_id();
    unsigned        get_idx_in_bank();
    void            print();

    // set
    void            write_init(bool initValue);
    void            write_data(Fmap_t new_data);
    void            write_bank_id(unsigned new_id);
    void            write_idx_in_bank(unsigned new_idx);
    void            accumulate(OA_element elem);

private:
    bool                    _init;
	bool					_valid;
	Fmap_t					_data;
    tensor_4D_idx           _idx;
    unsigned                _bank_id;
    unsigned                _idx_in_bank;
};

} // namespace Scnn

#endif