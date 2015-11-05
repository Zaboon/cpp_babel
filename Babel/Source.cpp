#include		<iostream>
#include		<string>

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
	std::cout << "ip" << std::endl;
	
	getchar();
	return (0);
}