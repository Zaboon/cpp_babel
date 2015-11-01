#include	"SoundManager.hpp"

SoundManager::SounManager()
{
  _opus = new EncodeManager;
  _streamIn = NULL;
  _streamOut = NULL;
  for (int i = 0; i < FRAMES_PER_BUFFER; i++) _buff[i] = 0; /* memset */
  _run = true;
}

SoundManager::~SoundManager()
{
  if (_enc) delete _enc;
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
      errorAudio();
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
  _inParam.suggestedLatency = Pa_GetDeviceInfo(_inParam.device)->defaultHighInputLatency;
  _inParam.hostApiSpecificsStreamInfo = NULL;
}

void		SoundManager::initOutput()
{
  _outParam.device = Pa_GetDefaultOutputDevice();
  _outParam.channelCount = 1;
  _outParam.sampleFormat = PA_SAMPLE_TYPE;
  _outParam.suggestedLatency = Pa_GetDeviceInfo(_outParam.device)->defaultHighOutputLatency;
  _outParam.hostApiSpecificsStreamInfo = NULL;
}

int		