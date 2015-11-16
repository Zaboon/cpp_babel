#pragma once

#include <iostream>
#include <fstream>

typedef float		SAMPLE;
#define SAMPLE_RATE	(24000)
#define FRAMES_PER_BUFFER (480)
#define PA_SAMPLE_TYPE	paFloat32

class			IEncode
{
public:
 virtual		~IEncode() {}

 virtual unsigned char*	encodeAudio(const SAMPLE *frame, int *retenc) = 0;
 virtual void		decodeAudio(const unsigned char *data, SAMPLE *out, int retenc) = 0;
};
