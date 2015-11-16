#include "SoundManager.hpp"

int	main(int ac, char **av)
{
	IAudio	*a = new SoundManager;
	IAudio	*b = new SoundManager;

	Pa_Initialize();
	a->initInput();
	b->initOutput();
	a->setupStream();
	b->setupStream();
	// a->initAudio();
	// a->startStream();
	// a->stopStream();
	delete a;
	return (0);
}
