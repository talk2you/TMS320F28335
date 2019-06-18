/*
 * fft.c
 *
 *  Created on: 2019. 6. 12.
 *      Author: JJang
 */


#include "fft.h"
#include "FPU.h"
#include "math.h"

#define	RFFT_STAGES	8
#define	RFFT_SIZE	(1 << RFFT_STAGES)

#pragma DATA_SECTION(RFFTin1Buff,"RFFTdata1");  //Buffer alignment for the input array,
float32 RFFTin1Buff[RFFT_SIZE];                 //RFFT_f32u(optional), RFFT_f32(required)
                                                //Output of FFT overwrites input if
                                                //RFFT_STAGES is ODD
#pragma DATA_SECTION(RFFToutBuff,"RFFTdata2");
float32 RFFToutBuff[RFFT_SIZE];                 //Output of FFT here if RFFT_STAGES is EVEN

#pragma DATA_SECTION(RFFTmagBuff,"RFFTdata3");
float32 RFFTmagBuff[RFFT_SIZE/2+1];             //Additional Buffer used in Magnitude calc

#pragma DATA_SECTION(RFFTF32Coef,"RFFTdata4");
float32 RFFTF32Coef[RFFT_SIZE];                 //Twiddle buffer

const float	RadStep = 0.1963495408494f;             // Step to generate test bench waveform
float		Rad = 0.0f;
char		freq_point[10] = {0,};

RFFT_F32_STRUCT rfft;

void FFT_init(void)
{
	rfft.FFTSize   = RFFT_SIZE;
	rfft.FFTStages = RFFT_STAGES;
	rfft.InBuf     = &RFFTin1Buff[0];  //Input buffer
	rfft.OutBuf    = &RFFToutBuff[0];  //Output buffer
	rfft.CosSinBuf = &RFFTF32Coef[0];  //Twiddle factor buffer
	rfft.MagBuf    = &RFFTmagBuff[0];  //Magnitude buffer

	RFFT_f32_sincostable(&rfft);       //Calculate twiddle factor
}

void FFTtest(int time)
{
	Uint16	i;

	// Generate sample waveforms:
	Rad = 0.0f;
	for(i=0; i < RFFT_SIZE; i++)
	{
		RFFTin1Buff[i]   = sin(Rad*0.1*time) + 0.1*cos(Rad*0.5) + 0.8*sin(Rad*3) + 0.5*cos(Rad*10); //Real input signal
		Rad = Rad + RadStep;
	}

	RFFT_f32(&rfft);				   //Calculate real FFT

	RFFT_f32_mag(&rfft);				//Calculate magnitude

	Analysis_freq();
}

void Analysis_freq(void)
{
	Uint16 i = 0,f = 0;

	for(i=0;i<10;i++)
		freq_point[i] = 0;

	for(i=2;i<128;i++)
	{
		if(RFFTmagBuff[i-1] > 5)
		{
			if(RFFTmagBuff[i-2] < RFFTmagBuff[i-1] && RFFTmagBuff[i-1] > RFFTmagBuff[i])
			{
				if(f < 10)
					freq_point[f++] = i-1;
				else
					break;
			}
		}
	}
}
