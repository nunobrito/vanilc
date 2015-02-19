// Copyright (c) 2015 Siemens AG, Author: Andreas Weinlich
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#pragma once

#include <opencv2/opencv.hpp>
#include <iostream>
#include <deque>

#include "vanilcEntropyCoder.h"

namespace vanilc {

using namespace std;
using namespace cv;

const double STRETCHMAPPING = 0.5104610121262;
const double SQUAREDSTRETCHMAPPING = 0.260570444900904;
const double MAGICFACTOR = 0.980258143468547;
const double VARFORPROBZEROTOOLARGE = 1.04068449050280;
const double MINUSONEDIVSQRT2 = -0.707106781186547;

class RiceGolombCoder : public EntropyCoder {
public:
	RiceGolombCoder(const EntropyCoder::bitqueue& bitstream = EntropyCoder::bitqueue()) : EntropyCoder(bitstream), runlength(0) {};
	void setParameters(double mean, double variance) { this->mean = mean; this->variance = variance; };
	void finalize();
	double costs(unsigned int symbol);
	void encode(unsigned int symbol);
	unsigned int decode();
	#ifdef WIN32
		double log2(double n) { return log(n) / log(2.0); };
	#endif

private:
	void encodeGolomb(unsigned int symbol, unsigned int m);
	unsigned int decodeGolomb(unsigned int m);

	double mean;
	double variance;
	unsigned int runlength;
	unsigned int runM;
};

} // end namespace vanilc

