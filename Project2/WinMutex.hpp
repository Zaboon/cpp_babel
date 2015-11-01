#ifndef WINMUTEX_H_
# define WINMUTEX_H_

# include				<winnt.h>
# include				<intsafe.h>
# include				<WinBase.h>
# include				<processthreadsapi.h>
# include				"IMutex.hpp"

class WinMutex :		public IMutex
{
public:
	WinMutex()
	{}
};

#endif /* !WINMUTEX_H_ */