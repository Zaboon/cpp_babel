#include	"SoundManager.hpp"

SoundManager::SoundManager()
{
  _opus = new EncodeManager;
  _streamIn = NULL;
  _streamOut = NULL;
  _run = true;
}

SoundManager::~SoundManager()
{
  if (_opus) delete _opus;
  if (_data) delete _data;
  if (_streamIn) Pa_CloseStream(_streamIn);
  if (_streamOut) Pa_CloseStream(_streamOut);
  Pa_Terminate();
}

int		SoundManager::initAudio()
{
  _err = Pa_Initialize();
  if (_err != paNoError)
    {
      this->errorAudio();
      return 0;
    }
  initInput();
  initOutput();
  setupStream();
  return 1;
}

void		SoundManager::errorAudio()
{
  if (_err != paNoError)
    {
      _run = false;
      if (_streamIn)
	Pa_CloseStream(_streamIn);
      if (_streamOut)
	Pa_CloseStream(_streamOut);
      Pa_Terminate();
      std::cerr << "An error occured while using the portaudio stream" << std::endl;
      std::cerr << "Error number: " << _err << std::endl;
      std::cerr << "Error message: " << Pa_GetErrorText(_err) << std::endl;
    }
}

void		SoundManager::initInput()
{
  _inParam.device = Pa_GetDefaultInputDevice();
  _inParam.channelCount = 1;
  _inParam.sampleFormat = PA_SAMPLE_TYPE;
  _inParam.suggestedLatency = Pa_GetDeviceInfo(_inParam.device)->defaultLowInputLatency;
  _inParam.hostApiSpecificStreamInfo = NULL;
}

void		SoundManager::initOutput()
{
  _outParam.device = Pa_GetDefaultOutputDevice();
  _outParam.channelCount = 1;
  _outParam.sampleFormat = PA_SAMPLE_TYPE;
  _outParam.suggestedLatency = Pa_GetDeviceInfo(_outParam.device)->defaultLowOutputLatency;
  _outParam.hostApiSpecificStreamInfo = NULL;
}


int recordCallback(const void *input, void *output,
		  unsigned long framesPerBuffer,
		  const PaStreamCallbackTimeInfo* timeInfo,
		  PaStreamCallbackFlags statusFlags,
		  void *userData)
{
  SoundManager *dis = (SoundManager*)userData;
  const SAMPLE *in = (const SAMPLE *)input;
  int retenc(0);
  (void)timeInfo;
  (void)statusFlags;
  (void)output;


  dis->setData(dis->getEnc()->encodeAudio(in, &retenc));
  dis->setRetenc(retenc);
  return paContinue;
}

int playCallback(const void *input, void *output,
		unsigned long framesPerBuffer,
		const PaStreamCallbackTimeInfo* timeInfo,
		PaStreamCallbackFlags statusFlags,
		void *userData)
{
  SoundManager *dis = (SoundManager*)userData;
  SAMPLE*out = (SAMPLE *)output;
  (void)timeInfo;
  (void)statusFlags;
  (void)input;

  dis->getEnc()->decodeAudio(dis->getData().first, out, dis->getData().second);
  return paContinue;
}

int                     SoundManager::setupStream()
{
  this->_err = Pa_OpenStream(
			     &this->_streamIn,
			     &this->_inParam,
			     NULL,
			     SAMPLE_RATE,
			     FRAMES_PER_BUFFER,
			     paClipOff,
			     recordCallback,
			     this);
  if (this->_err != paNoError)
    {
      this->errorAudio();
      return (0);
    }
  this->_err = Pa_OpenStream(
			     &this->_streamOut,
			     NULL,
			     &this->_outParam,
			     SAMPLE_RATE,
			     FRAMES_PER_BUFFER,
			     paClipOff,
			     playCallback,
			     this);
  if (this->_err != paNoError)
    {
      this->errorAudio();
      return (0);
    }
  return (1);
}

int     SoundManager::startStream()
{
  this->_err = Pa_StartStream(this->_streamIn);
  if (this->_err != paNoError)
    {
      this->errorAudio();
      return (0);
    }
  this->_err = Pa_StartStream(this->_streamOut);
  if (this->_err != paNoError)
    {
      this->errorAudio();
      return (0);
    }
  std::cout << "Stream started..." << std::endl;
  while (this->_run)
    {
      std::cout << "Hit ENTER to quit..." << std::endl;
      if (std::cin.get() == '\n')
	this->_run = false;
    }
  return (1);
}


int                     SoundManager::stopStream()
{
  if (this->_streamIn)
    {
      this->_err = Pa_StopStream(this->_streamIn);
      if (this->_err != paNoError)
	{
	  this->errorAudio();
	  return (0);
	}
    }
  if (this->_streamOut)
    {
      this->_err = Pa_StopStream(this->_streamOut);
      if (this->_err != paNoError)
	{
	  this->errorAudio();
	  return (0);
	}
    }
  return (1);
}

IEncode       *SoundManager::getEnc()
{
  return (this->_opus);
}

const std::pair<const unsigned char *, const int>       SoundManager::getData() const
{
  return (std::make_pair(this->_data, this->_enc_ret));
}

void            SoundManager::setData(unsigned char *data)
{
  this->_data = data;
}

const int                       SoundManager::getRetenc() const
{
  return (this->_enc_ret);
}

void            SoundManager::setRetenc(int retenc)
{
  this->_enc_ret = retenc;
}

