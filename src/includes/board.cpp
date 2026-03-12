#include "board.h"

#include <vector>
#include <cmath>
#include <iostream>


namespace board{
	struct cell{
		bool mine = false;
		bool seen = false;
		bool flag = false;
	};

	int width;
	int height;	
	std::vector<cell> grid;
	std::pair<int,int> adjacent[8] = {
	//        x  y
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
	std::pair<int,int> Board::index_to_coords(int i){
		int x = i % width;
		int y = std::floor(i/width);
		return {x,y};
	}

	int Board::coords_to_index(std::pair<int,int> c){
		return c.first + c.second * width;
	}

	//function to check the amount of adjacent mines
	int Board::check_num_mines(int p, bool v){
		int mines = 0;
		for (std::pair<int,int> o_c : adjacent){
			std::pair<int,int> current_coords = index_to_coords(p);
			std::pair<int,int> check_coords = {current_coords.first + o_c.first,
							   current_coords.second + o_c.second};
			if (v){
				std::cout << "Coords: " << current_coords.first << ", " << current_coords.second;
				std::cout << " Offset: " << o_c.first << ", " << o_c.second;
				std::cout << " Checking: " << check_coords.first << ", " << check_coords.second << std::endl;
			}
			//Check if either coordinate is out of bounds
			if (check_coords.first < 0 || check_coords.first > width - 1 ||
			    check_coords.second < 0 || check_coords.second > height - 1){
				continue;
			}
			//Get index
			int c = coords_to_index(check_coords);
			
			//Should be safe, check the cell
			if (grid[c].mine){
				mines++;
			}
		}
		return mines;
	}

	Board::Board(int w,int h,float mines_p){
		width = w;
		height = h;
		grid.resize(w * h);
		int i;
		int mines = w * h * mines_p;
		int n_mines = 0;
		while (n_mines < mines){
			i = rand() % (w * h);
			if (!grid[i].mine){
				grid[i].mine = true;
				n_mines += 1;
			}
		}
	}
	
	//function to display board
	void Board::display(){
		//Top row of column numbers
		std::cout << "  ";
		for (int s = 0; s < width; s++){
			if(s < 9){
				std::cout << ' ';
			} else {
				std::cout << std::to_string(s + 1)[0];
			}
		}
		//Bottom row of column numbers
		std::cout << std::endl << "  ";
		for (int s = 0; s < width; s++){
			std::string c = std::to_string(s + 1);
			std::cout << c.substr(c.size()-1);
		}	
		std::cout << std::endl << " ┌";
		//DIV
		for (int i = 0; i < width; i++){
			std::cout << "─";
		}
		std::cout << "┐";
		//ROWS
		for (int row = 0; row < height; row ++){
			std::cout << std::endl <<  (char)('a' + row) << "│";
			for (int col = 0; col < width; col++){
				int index = coords_to_index({row,col});
				cell c = grid[index];
				if (!c.seen){	//Tile hasnt been shown, either show undis. tile or a flag
					std::cout << ((c.flag) ? "┏" : "▒");
				} else if(c.mine){	//Tile has been seen, it either is a mine, or an empty space with a number
					std::cout << "╳";
				} else {		//Number
					//calculate amount of touching mines
					int m = check_num_mines(index);
					std::cout << std::to_string(m);
				}
			}
			std::cout << "│";
		}
		std::cout << std::endl << " └";
		for (int i = 0; i < width; i++){
			std::cout << "─";
		}
		std::cout << "┘" << std::endl;
	}

	//MOVES
	//+===========+============+==============+===========+
	//| Code\Move |    flag    |    unflag    |    dig    |
	//+===========+============+==============+===========+
	//|     0     |   flagged  |   unflagged  |  no mine  |
	//|	1     | can't flag | can't unflag | can't dig |
	//|     2     |    none    |     none     |  hit mine |
	//+===========+============+==============+===========+
	
	int Board::flag(std::pair<int, int> coords){
		int index = coords_to_index(coords);
		//check cell
		if (grid[index].seen || grid[index].flag){return 1;}
		grid[index].flag = true;
		return 0;
	}

	int Board::unflag(std::pair<int, int> coords){
		int index = coords_to_index(coords);
		//check cell
		if (grid[index].seen || !grid[index].flag){return 1;}
		grid[index].flag = false;
		return 0;
	}
	
	int Board::dig(std::pair<int, int> coords){
		int index = coords_to_index(coords);
		//check cell
		if (grid[index].seen){return 1;}
		grid[index].seen = true;
		if (grid[index].mine){return 2;}
		if (check_num_mines(index) == 0){
			for (std::pair<int, int> offset : adjacent){
				std::pair<int, int> c = {coords.first + offset.first, coords.second + offset.second};
				if (c.first < 0 || c.second < 0 || 
				    c.first > width - 1 || 
				    c.second > height - 1 ){
					continue;
				}
				dig(c);
			}
		}
		return 0;
	}

	bool Board::won(){
		bool won = true;
		for (cell c : grid){
			if (!c.mine && !c.seen){ //Win when all non mine tiles are shown, so break when we encounter a non-visible, non-mined tile
				won = false;
				break;
			}
		}
		return won;
	}
}
