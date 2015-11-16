#ifndef	__IAUDIO__
#define __IAUDIO__

#include <iostream>
#include <fstream>
#include <iterator>
#include <utility>
#include <cstring>
#include "IEncode.hpp"

struct SoundPacket
{
    int                         retenc;
    unsigned char               *data;
};

class	        IAudio
{
public:
  virtual	~IAudio() {}

  virtual int	initAudio() = 0;
  virtual void	errorAudio() = 0;
  virtual void	initInput() = 0;
  virtual void	initOutput() = 0;
  virtual int	setupStream() = 0;
  virtual int	startStream() = 0;
  virtual int	stopStream() = 0;
  virtual IEncode*	getEnc() = 0;
  virtual void	setData(unsigned char *) = 0;
  virtual const int	getRetenc() const = 0;
  virtual void	setRetenc(int) = 0;
  virtual unsigned char* getData() const = 0;
  virtual SoundPacket*	getStruct() = 0;
};

#endif /* __IAUDUI__ */
