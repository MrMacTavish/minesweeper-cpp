#include "board.h"

#include <vector>
#include <cmath>
#include <iostream>


namespace board{

       std::pair<int,int> adjacent[8] = {
        //       x  y
                {-1,-1},//top left
                { 0,-1},//top
                { 1,-1},//top right
                {-1, 0},//left
                { 1, 0},//right
                {-1, 1},//bottom left
                { 0, 1},//bottom
                { 1, 1} //bottom right
        };


	//Functions to calculate index in the vector from 2 dimensional coords and vice-versa
	std::pair<int,int> index_to_coords(int i, int size){
		int x = i % size;
		int y = std::floor(i/size);
		return {x,y};
	}

	int coords_to_index(std::pair<int,int> c, int size){
		return c.first + c.second * size;
	}

	//function to check the amount of adjacent mines
	int check_num_mines(std::vector<cell> b, int p, bool v){
		int mines = 0;
		int size = std::sqrt(b.size());
		for (std::pair<int,int> o_c : adjacent){
			std::pair<int,int> current_coords = index_to_coords(p, size);
			std::pair<int,int> check_coords = {current_coords.first + o_c.first,
							   current_coords.second + o_c.second};
			if (v){
				std::cout << "Coords: " << current_coords.first << ", " << current_coords.second;
				std::cout << " Offset: " << o_c.first << ", " << o_c.second;
				std::cout << " Checking: " << check_coords.first << ", " << check_coords.second << std::endl;
			}
			//Check if either coordinate is out of bounds
			if (check_coords.first < 0 || check_coords.first > size - 1 ||
			    check_coords.second < 0 || check_coords.second > size - 1){
				continue;
			}
			//Get index
			int c = coords_to_index(check_coords, size);
			
			//Should be safe, check the cell
			if (b[c].mine){
				mines++;
			}
		}
		return mines;
	}

	//function to display board
	void display(std::vector<cell> b){
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

	std::vector<cell> generate(int size, int mines){
		srand(time(0));
		std::vector<cell> board;
		board.resize(size * size);
		int n_mines = 0;
		int i;
		while (n_mines < mines){
			i = rand() %(size * size);
			if (!board[i].mine){
				board[i].mine = true;
				n_mines += 1;
			}
		}
		return board;
	}
	//MOVES
	//+===========+============+==============+===========+
	//| Code\Move |    flag    |    unflag    |    dig    |
	//+===========+============+==============+===========+
	//|     0     |   flagged  |   unflagged  |  no mine  |
	//|	1     | can't flag | can't unflag | can't dig |
	//|     2     |    none    |     none     |  hit mine |
	//+===========+============+==============+===========+
	
	int flag(std::vector<cell>& board, std::pair<int, int> coords){
		int index = coords_to_index(coords, std::sqrt(board.size()));
		//check cell
		if (board[index].seen || board[index].flag){return 1;}
		board[index].flag = true;
		return 0;
	}

	int unflag(std::vector<cell>& board, std::pair<int, int> coords){
		int index = coords_to_index(coords, std::sqrt(board.size()));
		//check cell
		if (board[index].seen || !board[index].flag){return 1;}
		board[index].flag = false;
		return 0;
	}
	
	int dig(std::vector<cell>& board, std::pair<int, int> coords){
		int index = coords_to_index(coords, std::sqrt(board.size()));
		//check cell
		if (board[index].seen){return 1;}
		board[index].seen = true;
		if (board[index].mine){return 2;}
		if (check_num_mines(board, index) == 0){
			for (std::pair<int, int> offset : adjacent){
				std::pair<int, int> c = {coords.first + offset.first, coords.second + offset.second};
				if (c.first < 0 || c.second < 0 || 
				    c.first > std::sqrt(board.size()) - 1 || 
				    c.second > std::sqrt(board.size()) - 1 ){
					continue;
				}
				dig(board, c);
			}
		}
		return 0;
	}

	bool won(std::vector<cell> board){
		bool won = true;
		for (cell c : board){
			if (!c.mine && !c.seen){ //Win when all non mine tiles are shown, so break when we encounter a non-visible, non-mined tile
				won = false;
				break;
			}
		}
		return won;
	}
}
