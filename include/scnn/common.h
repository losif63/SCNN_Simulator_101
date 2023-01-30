#ifndef SCNN_COMMON_H_
#define SCNN_COMMON_H_

#define INPUT_HALO_
#ifndef INPUT_HALO_
#define OUTPUT_HALO_
#endif

#include <iomanip>
#include <deque>
#include <vector>
#include <tuple>
#include <string>
#include <set>
#include <map>

#define ACCUM_2D_INDEX_AT(ptr, num_elem, i, j) ptr[i * num_elem + j]

namespace Scnn {
    using namespace std;
}

#endif