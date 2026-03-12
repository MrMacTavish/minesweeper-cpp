//MINESWEEPER IN C++
//BY NAUT VAN DER WINDEN
//21-01-2026
//На заре небеса зовут меня
#include <iostream>
#include <cmath>
#include <vector>
#include <utility>
#include <cstdlib>

#include "includes/conior.h"
#include "includes/helpmsg.h"
#include "includes/board.h"
//Consts TODO move to seperate file??
const std::string SPLASH = "8b    d8  88  88b 88  888888  .dP\"Y8  88    88  888888  888888  88\"\"Yb  888888  88\"\"Yb\n88b  d88  88  88Yb88  88__    `Ybo.\"  88/pq\\88  88__    88__    88__dP  88__    88__dP\n88ybdP88  88  88 Y88  88\"\"    0.`Y8b  88p  q88  88\"\"    88\"\"    88\"\"    88\"\"    88\"Yb\n88 YY 88  88  88  Y8  888888  8bodP\'  8p    q8  888888  888888  88      888888  88  Yb";

bool lost = false;

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
	int width = 7, height = 7;
	float mines_p = .12;
	//VALIDATE ARGS
	if (argc > 1){	//width or help passed
		if (std::string(argv[1]) == "-h"){
			help::helpmsg();
			return 0;
		}
		try{
			width = std::stoi(argv[1]);
		}catch (...){
			std::cout << "Invalid value for argument width: Not an integer!" << std::endl;
			return 1;
		}
		if (width < 5 || width > 20){
			std::cout << "Invalid value for argument width: Out of bounds (5-20)!" << std::endl;
			return 1;
		}
	}
	height = width; //If height isn't specified, default to a square board
	if (argc > 2){	//height passed
		try{
			height = std::stoi(argv[2]);
		}catch (...){
			std::cout << "Invalid value for argument height: Not an interger!" << std::endl;
			return 1;
		}
		if (height < 5 || height > 20){
			std::cout << "Invalid value for argument height: Out of bounds (5-20)!" << std::endl;
			return 1;
		}
	}
	if (argc > 3){ //mines_p passed
		try{
			mines_p = std::stoi(argv[3]);
		}catch (...){
			std::cout << "Invalid value for argument mines_p: Not an integer!" << std::endl;
			return 1;
		}
		if (mines_p < 10 || mines_p > 90){
			std::cout << "Invalid value for argument mines_p: Out of bounds (10-0-)!" << std::endl;
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
	board::Board board(width,height,mines_p);
	while (!lost){
		//check if won
		if (board.won()){
			clear();
			board.display();
			std::cout << " You won!" << std::endl;
			return 0;
		}
		//get move
		char move = ' ';
		while (move != 'q' && (move < '1' || move > '3')){	
			clear();
			board.display();
			std::cout <<	"1) Dig  2) Flag  3) Unflag  q) Quit" << std::endl;
			move = getch();//std::cin.get();
		}
		if (move == 'q'){
			return 0;
		}
		//get pos
		std::string i;
		std::pair<int, int> pos = {-1, -1};
		while (pos.first < 0 || pos.second < 0 ||
		       pos.first >= width || pos.second >= height){
			clear();
			board.display();
			std::cout << "Enter coordinates (e.x. a3): " << std::flush;
			std::cin >> i;
			pos = parse_coords(i);
		}
		int res = -1;
		switch (move){
			case '1':
				res = board.dig(pos);
				if (res == 2){lost = true;}
				break;
			case '2':
				res = board.flag(pos);
				break;
			case '3':
				res = board.unflag(pos);
				break;
		}	
	}
	std::cout << " You lost!" << std::endl;
	return 0;
}
