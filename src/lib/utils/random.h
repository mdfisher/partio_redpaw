/*
PARTIO SOFTWARE
Copyright 2013 Disney Enterprises, Inc. All rights reserved

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are
met:

* Redistributions of source code must retain the above copyright
notice, this list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright
notice, this list of conditions and the following disclaimer in
the documentation and/or other materials provided with the
distribution.

* The names "Disney", "Walt Disney Pictures", "Walt Disney Animation
Studios" or the names of its contributors may NOT be used to
endorse or promote products derived from this software without
specific prior written permission from Walt Disney Pictures.

Disclaimer: THIS SOFTWARE IS PROVIDED BY WALT DISNEY PICTURES AND
CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING,
BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE, NONINFRINGEMENT AND TITLE ARE DISCLAIMED.
IN NO EVENT SHALL WALT DISNEY PICTURES, THE COPYRIGHT HOLDER OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND BASED ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
*/

#include <iostream>
#include "3rdParty/mtrand.h"

using namespace std;
namespace Partio {

// uses std:rand functions pretty weak sauce
double partioRand()
{
    return ((rand() / double(RAND_MAX))-.5)*2;
}

template <class T>
double partioRand(T a, T b)
{
    return (double)(b-a)*partioRand() + a;
}

template <class T>
long partioRand(T n)
{
    if (n < 0) n = -n;
    if (n==0) return 0;
    long guard = (long) (partioRand() * n) +1;
    return (guard > n)? n : guard;
}

void seed(uint seedVal)
{
    srand(seedVal);
}

// subclassing  Mersenne twister for better random functions
// generates double floating point numbers in the half-open interval [-1, 1)
class pioMTRand : public MTRand_int32 {
public:
    pioMTRand() : MTRand_int32() {}
    pioMTRand(unsigned long seed) : MTRand_int32(seed) {}
    pioMTRand(const unsigned long* seed, int size) : MTRand_int32(seed, size) {}
    ~pioMTRand() {}
    // Returns  between -1 and 1
    double operator()()
	{
        return static_cast<double>(((rand_int32()) * (1. / 4294967296.)-.5)*2);
    } // divided by 2^32
    // Returns within range
    double operator()(float min,float max)
	{
        return static_cast<double>((max-min)*(((rand_int32()) * (1. / 4294967296.)-.5)*2)+min);
    } // divided by 2^32
private:
    pioMTRand(const pioMTRand&); // copy constructor not defined
    void operator=(const pioMTRand&); // assignment operator not defined
};



}