#include	"EncodeManager.hpp"

EncodeManager::EncodeManager()
{
  _enc = opus_encoder_create(SAMPLE_RATE, 1, OPUS_APPLICATION_VOIP, &_err);
  _dev = opus_decoder_create(SAMPLE_RATE, 1, &_err);
}

EncodeManager::~EncodeManager()
{
  opus_encoder_destroy(_enc);
  opus_decoder_destroy(_dec);
}

unsigned char*	EncodeManager::encodeAudio(const float* frame, int* enc_ret)
{
  unsigned char* data = new (unsigned char[_len]);

  *enc_ret = opus_encode_float(_enc, frame, FRAMES_PER_BUFFER, data, _len);
  return data;
}

void		EncodeManager::decodeAudio(const unsigned char* data, SAMPLE* out, int enc_ret)
{
  if (opus_decode_float(_dec, data, retenc, out, FRAMES_PER_BUFFER, 0) != OPUS_OK)
    std::cerr << "Error decoding" << std::endl;
}
