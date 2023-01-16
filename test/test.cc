#include <iostream>

#include "dlsim/common.h"
#include "dlsim/fmap_4d.h"


using namespace std;

int main(void) {
    cout << "This is a test module, built for testing out the various ";
    cout << "sub-modules of this scnn simulator." << endl;

/********************************DLSIM*********************************/


dlsim::Fmap4d_t* fmap = new dlsim::Fmap4d_t(4, 4, 4, 4, 4, _IA_Tensor, 50);
fmap->print();


/*********************************SCNN*********************************/







/**********************************************************************/
}