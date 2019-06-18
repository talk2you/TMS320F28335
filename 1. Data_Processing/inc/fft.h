/*
 * fft.h
 *
 *  Created on: 2019. 6. 12.
 *      Author: JJang
 */

#ifndef INC_FFT_H_
#define INC_FFT_H_

#include "def.h"

void FFT_init(void);
void FFTtest(int time);
void Analysis_freq(void);

extern char freq_point[10];

#endif /* INC_FFT_H_ */
