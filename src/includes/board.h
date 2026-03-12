#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <cmath>
#include <iostream>

namespace board{
	class Board{
		private:
			std::pair<int,int> index_to_coords(int i);
			int coords_to_index(std::pair<int, int> c);
			int check_num_mines(int p, bool v = false);
		public:
			Board(int w, int h, float mines);
			void display();
			int flag(std::pair<int, int> coords);
			int unflag(std::pair<int, int> coords);
			int dig(std::pair<int, int> coords);
			bool won();
	};
}
#endif
