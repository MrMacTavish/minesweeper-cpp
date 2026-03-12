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

bool lost = false;
bool first = true;

void clear(){
	for(int i = 0; i < 500; i++){
		std::cout << std::endl;
	}
}

std::pair<int,int> parse_coords(std::string i){
	char x = i[0];
	int y = 0;
	try{
		y = std::stoi(i.substr(1));		
	} catch (...) {
		return {-1,-1};
	}
	return {
		(int)(x - 'a'),
		y - 1  
	};
}

int main(int argc, char* argv[]){
	int size = 7, surface;
	float mines_p = .12;
	//VALIDATE ARGS
	if (argc > 1){	//size passed
		if (std::string(argv[1]) == "-h"){
			help::helpmsg();
			return 0;
		}
		try{
			size = std::stoi(argv[1]);
		}catch (...){
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
			mines_p = std::stoi(argv[2]);
		}catch (...){
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
	//PREGEN
	std::vector<board::cell> board = board::generate(size, size * size * mines_p);
	while (!lost){
		//check if won
		if (board::won(board)){
			clear();
			board::display(board);
			std::cout << " You won!" << std::endl;
			return 0;
		}
		//get move
		char move = ' ';
		while (move != 'q' && (move < '1' || move > '3')){	
			clear();
			board::display(board);
			std::cout <<	" Moves:"	<< std::endl <<
			 	   	"--------" 	<< std::endl <<
			    		"1) Dig"   	<< std::endl <<
			     		"2) Flag" 	<< std::endl <<
					"3) Unflag"	<< std::endl <<
					"q) Quit"	<< std::endl;
			move = std::cin.get();
		}
		if (move == 'q'){
			return 0;
		}
		//get pos
		std::string i;
		std::pair<int, int> pos = {-1, -1};
		while (pos.first < 0 || pos.second < 0 || pos.first >= size || pos.second >= size){
			clear();
			board::display(board);
			std::cout << "Enter coordinates (e.x. a3): " << std::flush;
			std::cin >> i;
			pos = parse_coords(i);
		}
		int res = -1;
		switch (move){
			case '1':
				res = board::dig(board,pos,first);
				first = false;
				if (res == 2){lost = true;}
				break;
			case '2':
				res = board::flag(board,pos);
				break;
			case '3':
				res = board::unflag(board,pos);
				break;
		}	
	}
	std::cout << "You lost!";
	return 0;
}
