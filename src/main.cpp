//MINESWEEPER IN C++
//BY NAUT VAN DER WINDEN
//21-01-2026
//На заре небеса зовут меня
#include <iostream>
#include <cmath>
#include <vector>
#include <utility>
#include <cstdlib>

//Consts TODO move to seperate file??
const std::string SPLASH = "8b    d8  88  88b 88  888888  .dP\"Y8  88    88  888888  888888  88\"\"Yb  888888  88\"\"Yb\n88b  d88  88  88Yb88  88__    `Ybo.\"  88/pq\\88  88__    88__    88__dP  88__    88__dP\n88ybdP88  88  88 Y88  88\"\"    0.`Y8b  88p  q88  88\"\"    88\"\"    88\"\"    88\"\"    88\"Yb\n88 YY 88  88  88  Y8  888888  8bodP\'  8p    q8  888888  888888  88      888888  88  Yb";

//Struct defining a cell
struct cell{
	bool mine = false;
	bool flag = false;
	bool seen = true;
};

std::pair<int,int> offsets[8] = {
//	 x  y
	{-1,-1},//top left
	{ 0,-1},//top
	{ 1,-1},//top right
	{-1, 0},//left
	{ 1, 0},//right
	{-1, 1},//bottom left
	{ 0, 1},//bottom
	{ 1, 1} //bottom right
};

std::pair<int,int> index_to_coords(int i, int size){
	int y = i % size;
	int x = i - x * size;
	return {x,y};
}

int coords_to_index(std::pair<int,int> c, int size){
	return c.first + c.second * size;
}

void clear(){
	for(int i = 0; i < 500; i++){
		std::cout << std::endl;
	}
}

//function to check the amount of adjacent mines
int check_num_mines(std::vector<cell> b, int p){
	int mines = 0;
	for (std::pair<int,int> o_c : offsets){
		int o = coords_to_index(o_c,std::sqrt(b.size()));
		int c = p + o; //Cell to check (position + offset)
		//check if offset even is within array bounds
		if (c < 0 || c > b.size()-1){
			continue;
		}
		//std::cout << "Offset: " << std::to_string(o);
		//std::cout << " Coord: " << std::to_string(c);
		//std::cout << " Mine: " << ((b[c].mine) ? "t" : "f");
		//Should be safe, check the cell
		if (b[c].mine){
			mines++;
		}
	}
	return mines;
}

//function to display board
void display_board(std::vector<cell> b){
	int size = std::sqrt(b.size());
	//Top row of column numbers
	std::cout << "  ";
	for (int s = 0; s < size; s++){
		if(s < 9){
			std::cout << ' ';
		} else {
			std::cout << std::to_string(s + 1)[0];
		}
	}
	//Bottom row of column numbers
	std::cout << std::endl << "  ";
	for (int s = 0; s < size; s++){
		std::string c = std::to_string(s + 1);
		std::cout << c.substr(c.size()-1);
	}	
	std::cout << std::endl << " ┌";
	//DIV
	for (int i = 0; i < size; i++){
		std::cout << "─";
	}
	std::cout << "┐";
	//ROWS
	for (int row = 0; row < size; row ++){
		std::cout << std::endl <<  (char)('a' + row) << "│";
		for (int col = 0; col < size; col++){
			int index = coords_to_index({row,col},std::sqrt(b.size()));
			cell c = b[index];
			if (!c.seen){	//Tile hasnt been shown, either show undis. tile or a flag
				std::cout << ((c.flag) ? "┏" : "▒");
			} else if(c.mine){	//Tile has been seen, it either is a mine, or an empty space with a number
				std::cout << "╳";
			} else {		//Number
				//calculate amount of touching mines
				int m = check_num_mines(b,index);
				std::cout << std::to_string(m);
			}
		}
		std::cout << "│";
	}
	std::cout << std::endl << " └";
	for (int i = 0; i < size; i++){
		std::cout << "─";
	}
	std::cout << "┘" << std::endl;
}

std::vector<cell> generate_board(int size, int mines){
	srand(time(0));
	std::vector<cell> board;
	board.resize(size * size);
	int n_mines = 0;
	int i;
	while (n_mines < mines){
		i = rand() %(size * size);
		if (!board[i].mine){
			board[i].mine = true;
			board[i].seen = true;
			n_mines += 1;
		}
	}
	return board;
}

int main(int argc, char* argv[]){
	int size = 7, surface;
	float mines_p = .25;
	//VALIDATE ARGS
	if (argc > 1){	//size passed
		if (std::string(argv[1]) == "-h"){
			std::cout << "help msg" << std::endl;
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
	std::vector<cell> board = generate_board(size, size * size * mines_p);
	display_board(board);
	return 0;
}
