#include		<iostream>
#include		<string>
#include		"Windows\WinSocket.hpp"

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
	std::cout << "Nicolas est pas le plus beau" << std::endl;
	
	getchar();
	return (0);
}