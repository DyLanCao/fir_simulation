/* fir.c */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "fir.h"

#define NUM_TAPS 63
#define BUF_SIZE 2

static short insamp[BUF_SIZE];
/* coefficients stored in taps.c */
extern const float lowpass[NUM_TAPS];
extern const float bandpass[NUM_TAPS];
extern const float highpass[NUM_TAPS];
extern const float test_lowpass[NUM_TAPS];
extern const float test_highpass[NUM_TAPS];
extern const int fixed_highpass[NUM_TAPS];

void fir_init()
{
	memset(&insamp[0], 0.0f, sizeof(float) * BUF_SIZE);
}

int fir_process(const void* input, void *output, unsigned long numFrames, unsigned int filter)
{
	float acc; // accumulator for MACs
	const float *coeffp; // pointer to coefficients
	const short *in = (short*)input;
	short *out = (short *)output;
	unsigned int n;
	unsigned int k;

	// put the new samples at the high end of the buffer
	memcpy(&insamp[NUM_TAPS - 1], input, sizeof(short) * numFrames);

	// convolve input samples with filter taps
	for (n = 0; n < numFrames; ++n) {
		switch(filter)
		{
			case 0:
				coeffp = &test_lowpass[0];
				break;
			case 1:
				coeffp = &highpass[0];
				break;
			case 2:
				coeffp = &test_highpass[0];
				break;
			default:
				break;
		}

		in = &insamp[NUM_TAPS - 1 + n];
		acc = 0;

		for (k = 0; k < NUM_TAPS; ++k) {
			acc += (*coeffp++) * (*in--);
		}

		*out++ = acc;
	}

	// shift input samples back in time for next time
	memmove(&insamp[0], &insamp[numFrames], sizeof(short) * (NUM_TAPS - 1));

	return 0;
} 

int fir_process_fixed(const void* input, void *output, unsigned long numFrames, unsigned int filter)
{
	float acc; // accumulator for MACs
	const int *coeffp; // pointer to coefficients
	const short *in = (short*)input;
	short *out = (short *)output;
	unsigned int n;
	unsigned int k;

	// put the new samples at the high end of the buffer
	memcpy(&insamp[NUM_TAPS - 1], input, sizeof(short) * numFrames);

	// convolve input samples with filter taps
	for (n = 0; n < numFrames; ++n) {
		switch(filter)
		{
			case 0:
				coeffp = &test_lowpass[0];
				break;
			case 1:
				coeffp = &test_highpass[0];
				break;
			case 2:
				coeffp = &fixed_highpass[0];
				break;
			default:
				break;
		}

		in = &insamp[NUM_TAPS - 1 + n];
		acc = 0;

		for (k = 0; k < NUM_TAPS; ++k) {
			acc += (*coeffp++) * (*in--);
		}

		acc = acc/10000;

		*out++ = acc;
	}

	// shift input samples back in time for next time
	memmove(&insamp[0], &insamp[numFrames], sizeof(short) * (NUM_TAPS - 1));

	return 0;
} 

void fir_convolve(double *p_coeffs, int p_coeffs_n, short *p_in, short *p_out, int n)
{
	int i, j, k;
	double tmp;

	for (k = 0; k < n; k++)  //  position in output
	{
		tmp = 0;

		for (i = 0; i < p_coeffs_n; i++)  //  position in coefficients array
		{
			j = k - i;  //  position in input

			if (j >= 0)  //  bounds check for input buffer
			{
				tmp += p_coeffs [i] * p_in [j];
			}
		}

		p_out [k] = (short)tmp;
	}
}

void fir_aconvolve(short *Signal,float *Filter, int FilterLength, short *Output, int OutputLength)
{
	for (int i = 0; i < OutputLength; ++i)
	{
		double sum = 0;
		for (int j = 0; j < FilterLength; ++j)
		  sum += Signal[i+j] * Filter[FilterLength - 1 - j];
		Output[i] = sum;
	}
}

void fir_destroy()
{
	/* No mallocs yet */
	return;
}
