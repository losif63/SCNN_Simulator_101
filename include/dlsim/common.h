#ifndef DLSIM_COMMOM_H_
#define DLSIM_COMMOM_H_

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <cstdio>
#include <cstdlib>

#include <map>
#include <deque>
#include <vector>
#include <tuple>
#include <string>
#include <random>
#include <cassert>

//#define DEBUG
//#define give_sparsity

// type of variables
#ifdef _GOLD_
#define Weight_t		signed long
#define Fmap_t			signed long

#else
#define Weight_t		float
#define Fmap_t			float

#endif

namespace dlsim{
    using namespace std;   
}

#endif