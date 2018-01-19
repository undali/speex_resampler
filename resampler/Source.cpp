#include <cstdio>
#include "speex_resampler.h"

//ffplay -f s16le -ar 44.1k -ac 2 out.pcm

int main()
{
	FILE *in = nullptr, *out = nullptr;
	int err = -1;
	SpeexResamplerState* state = speex_resampler_init(2, //spx_uint32_t nb_channels,
		48000, //spx_uint32_t in_rate,
		44100, //spx_uint32_t out_rate,
		3,     //int quality,
		&err    //int *err
		);

	printf("init returns:%d\n", err);

	if (!state) {
		printf("state is null!\n");
	}

	in = fopen("in_48000.pcm", "rb");
	out = fopen("out.pcm", "wb");
	if (!in) {
		printf("wtf..\n");
		return 02;
	}
	unsigned int readlen, pLen, oldval;
	short inBuffer[5000], outBuffer[5000];
	const int iLen = 800;
	readlen = iLen;
	while ((readlen = fread(inBuffer, 4, readlen, in)) != 0) { // unit is 4 here. because 2 channel * 2 bytes
		oldval = readlen;
		int ret =  speex_resampler_process_interleaved_int(state, inBuffer, &readlen, outBuffer, &pLen);
		printf("processed ret:%d readlen:%u writelen:%u\n", ret, readlen, pLen);
		fwrite(outBuffer, 4, pLen, out);

		fseek(in, ((readlen - oldval) * 2), SEEK_CUR);

		readlen = iLen;
	}


	fclose(in);
	fclose(out);

	return 0;
}