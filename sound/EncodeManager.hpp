#pragma once

#include	<iostream>
#include	"IEncode.hpp"
#include	"opus.h"

class		EncodeManager : public IEncode
{
private:
  OpusEncoder*	_enc;
  OpusDecoder*	_dec;
  opus_int32	_len;
  int		_err;

public:
  EncodeManager();
  virtual ~EncodeManager();

  virtual unsigned char*	encodeAudio(const SAMPLE* frame, int* enc_ret);
  virtual void			decodeAudio(const unsignedchar* data, SAMPLE* out, int enc_ret);
}
