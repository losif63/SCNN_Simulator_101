#ifndef DLSIM_LOADER_H_
#define DLSIM_LOADER_H_

#include "dlsim/common.h"
#include "dlsim/layer.h"
#include "dlsim/conv_layer.h"

namespace dlsim
{

using namespace std;

class Loader {
public:
	Loader(string dnn_name);		// layer configuration only
	~Loader();

	// status 
	unsigned	num_layers();		
	bool 		done();				// when all layers are processed, out done.
	void 		print_layer();		// print layer data -> using Layer::print()

	// update
	void load_next_layer();
	void clear_current_layer();
	void update_curr_layer_id(unsigned layer_id);
	void initialize();

	// get
	ConvLayer* current_layer();
	unsigned curr_layer_id();
	string get_name();
	
private:
	/* The map designates the values of the parameters of the layer
	   Deque of maps means multiple such layers
	*/
	deque<map<string,unsigned int>*> *_cfg_network;

	// layer-wide info (for currently active layer)
	// Apparently, each layer keeps an id
   	unsigned int            _curr_layer_id;
   	ConvLayer*              _curr_layer;
	string					dnn_name;

};

} // namespace dlsim

#endif