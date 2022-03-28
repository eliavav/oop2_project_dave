#include <SFML/Graphics.hpp>

#include "Controller.h"
#include <exception> 


int main() try {

	Controller c1;
	c1.run();
	return EXIT_SUCCESS;
}
	catch (std::exception& e)
	{
		std::cout << e.what();
	}

