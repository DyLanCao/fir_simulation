/* fir.h */
#ifndef __FIR_FILT_H__
#define __FIR_FILT_H__

typedef signed char		int8_t;
typedef short int		int16_t;
typedef int			int32_t;

void fir_init();
void fir_destroy();
int fir_process(
    const void* input,
    void *output,
    unsigned long numFrames,
    unsigned int filter);

#endif
