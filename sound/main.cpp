#include "SoundManager.hpp"

int	main(int ac, char **av)
{
	IAudio	*a = new SoundManager;

	a->initAudio();
	a->startStream();
	a->stopStream();
	delete a;
	return (0);
}
