//MINESWEEPER IN C++
//BY NAUT VAN DER WINDEN
//21-01-2026
//На заре небеса зовут меня
#include <iostream>
#include <cmath>
#include <vector>
#include <utility>
#include <cstdlib>

#include "includes/helpmsg.h"
#include "includes/board.h"
//Consts TODO move to seperate file??
const std::string SPLASH = "8b    d8  88  88b 88  888888  .dP\"Y8  88    88  888888  888888  88\"\"Yb  888888  88\"\"Yb\n88b  d88  88  88Yb88  88__    `Ybo.\"  88/pq\\88  88__    88__    88__dP  88__    88__dP\n88ybdP88  88  88 Y88  88\"\"    0.`Y8b  88p  q88  88\"\"    88\"\"    88\"\"    88\"\"    88\"Yb\n88 YY 88  88  88  Y8  888888  8bodP\'  8p    q8  888888  888888  88      888888  88  Yb";

void clear(){
	for(int i = 0; i < 500; i++){
		std::cout << std::endl;
	}
}

int main(int argc, char* argv[]){
	int size = 7, surface;
	float mines_p = .25;
	//VALIDATE ARGS
	if (argc > 1){	//size passed
		if (std::string(argv[1]) == "-h"){
			help::helpmsg();
			return 0;
		}
		try{
			size = std::stoi(argv[1]);
		}catch (int err){
			std::cout << "Invalid value for argument: size!" << std::endl;
			return 1;
		}
		if (size < 5 || size > 11){
			std::cout << "Invalid value for argument: size!" << std::endl;
			return 1;
		}
	}
	surface = size * size;
	if (argc > 2){	//mines_p passed
		try{
			mines_p = std::stoi(argv[1]);
		}catch (int err){
			std::cout << "Invalid value for argument: mines_p! Not an interger!" << std::endl;
			return 1;
		}
		if (mines_p < 10 || mines_p > 90){
			std::cout << "Invalid value for argument: mines_p! invalid bounds!" << std::endl;
			return 1;
		}
		mines_p /= 100;
	}
	//SPLASH SCREEN
	clear();
	std::cout << SPLASH << std::endl;
	std::cout << "By MrMacTavish (Naut van der Winden)" << std::endl;
	std::cout << "Press <RETURN> to start" << std::endl;
	while(std::cin.get() != '\n'){}
	//PARAMS
	clear();
	//PREGEN
	std::vector<board::cell> board = board::generate(size, size * size * mines_p);
	board::display(board);
	std::cout << board::check_num_mines(board,0,true) << std::endl;
	return 0;
}
