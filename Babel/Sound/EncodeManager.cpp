#include	"EncodeManager.hpp"

EncodeManager::EncodeManager()
{
  _enc = opus_encoder_create(SAMPLE_RATE, 2, OPUS_APPLICATION_VOIP, &_err);
  _dec = opus_decoder_create(SAMPLE_RATE, 2, &_err);
  opus_encoder_ctl(this->_enc, OPUS_GET_BANDWIDTH(&this->_len));
  this->_len = FRAMES_PER_BUFFER;
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
  if (opus_decode_float(_dec, data, enc_ret, out, FRAMES_PER_BUFFER, 0) < 0)
    std::cerr << "Error decoding" << std::endl;
}
