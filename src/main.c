/* main.c */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include "portaudio.h"
#include "fir.h"

#define SAMPLE_RATE 48000


int main(int argc, char *argv[])
{   
	//   PaStream *stream;
	//   PaError err;

	if(argc != 3)
	{
		fprintf(stderr, "Usage: <in> <out>\n");
		return -1;
	}
	char *fileIn  = argv[1];
	char *fileOut = argv[2];

	clock_t start, finish;
	double  duration;
	int count;

	FILE *inFp  = fopen(fileIn,"r");
	FILE *outFp = fopen(fileOut,"w");
	if(inFp == NULL || outFp == NULL)
	{   
		fprintf(stderr, "failed to open pcm\n");
		return -1;
	}

	int tempSize = 160;
	short *in  = (short*)calloc(tempSize, sizeof(short));
	short *out = (short*)calloc(tempSize, sizeof(short));
	int pcmLen = tempSize;

	fir_init();

	start = clock();

	while(pcmLen > 0)
	{
		pcmLen = fread(in, sizeof(short), tempSize, inFp);
		fir_process(in,out,pcmLen,0);
		pcmLen = fwrite(out, sizeof(short), pcmLen, outFp);
	}

	fir_destroy();

	return 0;    
}
