#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <cmath>
#include <iostream>

namespace board{
	class board;
}

class board::board{
	private:
		struct cell{
			bool mine = false;
			bool flag = false;
			bool seen = false;
		};
		std::pair<int,int> index_to_coords(int i);
		int coords_to_index(std::pair<int, int> c);
		int check_num_mines(int p, bool v = false);
		void display(std::vector<cell> b);
		std::vector<cell> generate(int size, int mines);
		int flag(std::vector<cell>& board, std::pair<int, int> coords);
		int unflag(std::vector<cell>& board, std::pair<int, int> coords);
		int dig(std::vector<cell>& board, std::pair<int, int> coords);
		bool won(std::vector<cell> board);
}
#endif
