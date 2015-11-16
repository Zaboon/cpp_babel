#pragma once

#include "IAudio.hpp"
#include "EncodeManager.hpp"
#include "portaudio.h"

class	SoundManager : public IAudio
{
private:
	PaStream							*_streamin;
	PaStream							*_streamout;
	PaError								_err;
	PaStreamParameters					_inputParam;
	PaStreamParameters					_outputParam;
	IEncode								*_enc;
	bool								_run;
	unsigned char						*_data;
	unsigned char						*_receivedData;
	int									_retenc;
	int									_receivedRetenc;

public:
	SoundManager();
	virtual ~SoundManager();

	virtual int						initAudio();
	virtual void					errorAudio();
	virtual void					initInput();
	virtual void					initOutput();
	virtual int						setupStream();
	virtual int						startStream();
	virtual int						stopStream();
	virtual IEncode *				getEnc();
	virtual void					setData(unsigned char *);
	virtual const int				getRetenc() const;
	virtual void					setRetenc(int);
	virtual unsigned char*			getData() const;
	virtual	void					setReceivedData(unsigned char *);
	virtual	unsigned char			*getReceivedData() const;
	virtual	void					setReceivedRetenc(int);
	virtual	int						getReceivedRetenc() const;
	virtual SoundPacket*			getStruct();

};