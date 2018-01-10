#include <cstdio>
#include "speex_resampler.h"

int main()
{
	int err = -1;
	SpeexResamplerState* state = speex_resampler_init(2, //spx_uint32_t nb_channels,
		44100, //spx_uint32_t in_rate,
		48000, //spx_uint32_t out_rate,
		5,     //int quality,
		&err    //int *err
		);


	printf("init returns:%d\n", err);


	if (!state){
		printf("state is null!\n");
	}


	return 0;
}