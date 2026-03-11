#include "helpmsg.h"
#include <iostream>

namespace help{
	void helpmsg(){
		std::cout << 
		"Usage: " << std::endl <<
		"\tmastermind [board_size] [mines]" << std::endl <<
		"Parameters: " << std::endl << 
		"\tboard_size\tsize of the board (5-11)" << std::endl <<
		"\tmines\t\tpercentage of mines (10-90)" << std::endl;
	
	}
}
