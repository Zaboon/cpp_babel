#include		<iostream>
#include		<string>
#include		"Windows/WinThread.hpp"

void			superFunction()
{
	int			i = 42;

	while (--i > 0)
	{
		std::cout << "salut" << std::endl;
	}
}

int				main()
{
	std::cout << "Nicolas est le plus beau" << std::endl;
	
	getchar();
	return (0);
}