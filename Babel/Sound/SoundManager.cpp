#include "SoundManager.hpp"

#ifdef _WIN32
	#include <Windows.h>
#endif

SoundManager::SoundManager(){
	this->_enc = new EncodeManager;
	this->_streamin = NULL;
	this->_streamout = NULL;
	this->_run = true;
	_data = new unsigned char[480]();
}

SoundManager::~SoundManager(){
	if (this->_enc)
		delete this->_enc;
	if (this->_data)
		delete this->_data;
	if (this->_streamin)
		Pa_CloseStream(this->_streamin);
	if (this->_streamout)
		Pa_CloseStream(this->_streamout);
	Pa_Terminate();
}

int			SoundManager::initAudio()
{
	this->_err = Pa_Initialize();
	if (this->_err != paNoError)
	{
		this->errorAudio();
		return (0);
	}
	this->initInput();
	this->initOutput();
	this->setupStream();
	return (1);
}

void		SoundManager::errorAudio()
{
	if (this->_err != paNoError)
	{
		this->_run = false;
		if (this->_streamin)
		{
			Pa_AbortStream(this->_streamin);
			Pa_CloseStream(this->_streamin);
		}
		if (this->_streamout)
		{
			Pa_AbortStream(this->_streamout);
			Pa_CloseStream(this->_streamout);
		}
		Pa_Terminate();
		std::cerr << "Error !" << std::endl;
		std::cerr << "Error number : " << this->_err << std::endl;
		std::cerr << "Error message : " << Pa_GetErrorText(this->_err) << std::endl;
	}
}

void		SoundManager::initInput()
{
	this->_inputParam.device = Pa_GetDefaultInputDevice();
	this->_inputParam.channelCount = 2;
	this->_inputParam.sampleFormat = PA_SAMPLE_TYPE;
	this->_inputParam.suggestedLatency = Pa_GetDeviceInfo(this->_inputParam.device)->defaultLowInputLatency;
	this->_inputParam.hostApiSpecificStreamInfo = NULL;
}

void		SoundManager::initOutput()
{
	this->_outputParam.device = Pa_GetDefaultOutputDevice();
	this->_outputParam.channelCount = 2;
	this->_outputParam.sampleFormat = PA_SAMPLE_TYPE;
	this->_outputParam.suggestedLatency = Pa_GetDeviceInfo(this->_outputParam.device)->defaultLowOutputLatency;
	this->_outputParam.hostApiSpecificStreamInfo = NULL;
}

int			recordCallback(const void *input, void *output,
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

int			playCallback(const void *input, void *output,
						unsigned long framesPerBuffer,
						const PaStreamCallbackTimeInfo* timeInfo,
						PaStreamCallbackFlags statusFlags,
						void *userData)
{
	SoundManager *dis = (SoundManager*)userData;
	SAMPLE	*out = (SAMPLE *)output;
	(void)timeInfo;
	(void)statusFlags;
	(void)input;

	//dis->getEnc()->decodeAudio(dis->getData().first, out, dis->getData().second);
	//dis->getEnc()->decodeAudio(dis->getData(), out, dis->getRetenc());
	dis->getEnc()->decodeAudio(dis->getReceivedData(), out, dis->getReceivedRetenc());
	return paContinue;
}

int			SoundManager::setupStream()
{
	this->_err = Pa_OpenStream(
		&this->_streamin,
		&this->_inputParam,
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
		&this->_streamout,
		NULL,
		&this->_outputParam,
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

int	SoundManager::startStream()
{
	this->_err = Pa_StartStream(this->_streamin);
	if (this->_err != paNoError)
	{
		this->errorAudio();
		return (0);
	}
	this->_err = Pa_StartStream(this->_streamout);
	if (this->_err != paNoError)
	{
		this->errorAudio();
		return (0);
	}
	std::cout << "Stream started..." << std::endl;
	/*while (this->_run)
	{
		std::cout << "Hit ENTER to quit..." << std::endl;
		if (std::cin.get() == '\n')
			this->_run = false;
	}*/
	return (1);
}

int			SoundManager::stopStream()
{
	if (this->_streamin)
	{
		this->_err = Pa_StopStream(this->_streamin);
		if (this->_err != paNoError)
		{
			this->errorAudio();
			return (0);
		}
	}
	if (this->_streamout)
	{
		this->_err = Pa_StopStream(this->_streamout);
		if (this->_err != paNoError)
		{
			this->errorAudio();
			return (0);
		}
	}
	return (1);
}

IEncode	*SoundManager::getEnc()
{
	return (this->_enc);
}

void		SoundManager::setData(unsigned char *data)
{
	this->_data = data;
}

const int			SoundManager::getRetenc() const
{
	return (this->_retenc);
}

void		SoundManager::setRetenc(int retenc)
{
	this->_retenc = retenc;
}

unsigned char		*SoundManager::getData() const
{
	return (_data);
}

void				SoundManager::setReceivedData(unsigned char *data)
{
	this->_receivedData = data;
}

unsigned char		*SoundManager::getReceivedData() const
{
	return _receivedData;
}

void					SoundManager::setReceivedRetenc(int retenc)
{
	this->_receivedRetenc = retenc;
}

int						SoundManager::getReceivedRetenc() const
{
	return _receivedRetenc;
}

SoundPacket       *SoundManager::getStruct()
{
	SoundPacket* sp= NULL;

	if (sp == NULL) {
		sp = new SoundPacket;
		sp->data = new unsigned char[480]();
	}
//	std::cout << "OK" << std::endl;
	sp->retenc = this->getRetenc();
//	std::cout << "OK" << std::endl;
	for (int i = 0; i < FRAMES_PER_BUFFER; i++)
	{
//		std::cout << i << std::endl;
		sp->data[i] = _data[i];
	}
//	std::cout << "OK" << std::endl;
	return sp;
}