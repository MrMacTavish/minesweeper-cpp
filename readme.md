# Minesweeper in c++
## By Naut van der Winden

Minesweeper written in C++
## Project structure

```
minesweeper-cpp/  
	src/
		includes/
			board.cpp
			board.h
			helpmsg.cpp
			helpmsg.h
		main.cpp
	readme.md
	build.sh
```

## Build instructions

Run `./build.sh`, this will create a folder `bin` with the compiled program using G++. Otherwise manually compile the files in `src/` and `src/includes/`

## Usage
<pre>
<b>Usage:</b>
	minesweeper -h
	minesweeper [board_size] [mines]
<b>Parameters:</b>
	board_size	size of the board   (5-11, def:7)
	mines		percentage of mines (10-90, def:12)
</pre>

## Todo
- [ ] Support for non-square board sizes
- [x] First move should always be safe (move mine should the first move hit one)
- [ ] Better comments
