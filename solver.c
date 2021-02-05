#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "print_sudoku"
#include "allocating_memory"
#include "open_pruv_file"
#include "read_file_to_sudoku"
#include "chek_horisontal"
#include "chek_vertikal"
#include "chek_square"
#include "haveItSolve"
#include "getValueOfFit"
#include "get_suit_valu"
#include "solve"
#include "freeing_memory"
#include "trigger"
#include "writeSudokuToFile"


int main(int argc, char* argv[]){
	FILE *fd_sudoku;
	char **sudoku;

	sudoku = allocating_memory(fd_sudoku);
	fd_sudoku = open_pruv_file("sudoku.txt");
	read_file_to_sudoku(sudoku, fd_sudoku);
	while(true) {
		print_sudoku(sudoku);
		solve(sudoku);
		if(trigger(sudoku))
			break;
	}
	writeSudokuToFile(sudoku);
	print_sudoku(sudoku);
	freeing_memory(sudoku);
	return 0;
}
