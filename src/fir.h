/* fir.h */
#ifndef __FIR_FILT_H__
#define __FIR_FILT_H__

void fir_init();
void fir_destroy();
void fir_convolve(double *p_coeffs, int p_coeffs_n, short *p_in, short *p_out, int n);
void fir_aconvolve(short *Signal,float *Filter, int FilterLength, short *Output, int OutputLength);
int fir_process(
    const void* input,
    void *output,
    unsigned long numFrames,
    unsigned int filter);

#endif
