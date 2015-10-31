#pragma once

#include "IAudio.hpp"
#include "EncodeManager.hpp"
#include "portaudio.h"
#include "audiosettings.h"

class SoundManager : public IAudio
{
private:
  PaStream*		_streamIn;
  PaStream*		_streamOut;
  PaError		_err;
  PaStreamParameters	_inParam;
  PaStreamParameters	_outParam;
  AbsEncode*		_opus;
  SAMPLE		_buff[FRAMES_PER_BUFFER];
  bool			_run;
  unsigned char*	_data;
  int			_enc_ret;

public:
  SoundManager();
  virtual ~SoundManager();

  virtual int		initAudio();
  virtual void		initInput();
  virtual void		initOutput();
  virtual int		setupStream();

  virtual void		errorAudio(int);
  virtual int		startStream();
  virtual int		stopStream();
  virtual AbsEncode*	getEnc();
  virtual const std::pair<const unsigned char *, const int> getData() const;
  virtual void		setData(unsigned char *);
  virtual const int	getRetenc() const;
  virtual void		setRetenc(int);
};
