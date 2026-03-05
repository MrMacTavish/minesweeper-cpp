//MINESWEEPER IN C++
//BY NAUT VAN DER WINDEN
//21-01-2026
//На заре небеса зовут меня
#include <iostream>
#include <cmath>
#include <array>
#include <utility>

//Consts TODO move to seperate file??
const int size = 3; //Size of the board
const int mines = (int)(std::pow(size, 2)*.25) ; //Amount of mines (set to 25%)

const int surface = (int)std::pow(size,2);
//Struct defining a cell
struct cell{
	bool mine = false;
	bool flag = false;
	bool seen = false;
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

std::pair<int,int> index_to_coords(int i){
	int y = i % size;
	int x = i - x * size;
	return {x,y};
}

int coords_to_index(std::pair<int,int> c){
	return c.first + c.second * size;
}

//function to check the amount of adjacent mines
int check_num_mines(std::array<cell,surface> b, int p){
	int mines = 0;
	for (std::pair<int,int> o_c : offsets){
		int o = coords_to_index(o_c);
		int c = p + o; //Cell to check (position + offset)
		//check if offset even is within array bounds
		if (c < 0 || c > surface-1){
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
void display_board(std::array<cell,surface> b){
	std::cout << ' ';
	for (int s = 0; s < size; s++){
		std::cout << std::to_string(s + 1);
	}
	for (int row = 0; row < size; row ++){
		std::cout << std::endl <<  (char)('a' + row);
		for (int col = 0; col < size; col++){
			int index = coords_to_index({row,col});
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
	}
	std::cout << std::endl;
}

//Board
std::array<cell,surface> board;

int main(){
	for (std::pair<int,int> o : offsets){
		std::cout << coords_to_index(o) << std::endl;
	}
	for (int i = 0; i < surface; i++){
		if (i == 4){
			board[i].seen = true;
		} else {
			board[i].seen = true;
			board[i].mine = true;
		}
	}
	//std::cout << std::to_string(check_num_mines(board,4));
	display_board(board);
	return 0;
}
