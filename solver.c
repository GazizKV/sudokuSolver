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

bool haveItSolve(int x, int y, char **sudoku, char *arrayOf123456789) {
	bool fit = false;
	int fittable_counter = 0;
	int inerCounter = 0;

	for (int i=0;i<9;i++) {
		fittable_counter=0;
		fittable_counter += chek_horisontal(arrayOf123456789[i], sudoku, x);
		fittable_counter += chek_vertikal(arrayOf123456789[i], sudoku, y);
		fittable_counter += chek_square(arrayOf123456789[i], sudoku, x, y);
		if(fittable_counter==0)
			inerCounter++;
	}
	if(inerCounter==1)
		fit = true;
	return fit;
}

char *getValueOfFit(int x, int y, char **sudoku, char *arrayOf123456789) {
	int fittable_counter = 0;
	char *result;

	result = "-";
	for (int i=0;i<9;i++) {
		fittable_counter=0;
		fittable_counter += chek_horisontal(arrayOf123456789[i], sudoku, x);
		fittable_counter += chek_vertikal(arrayOf123456789[i], sudoku, y);
		fittable_counter += chek_square(arrayOf123456789[i], sudoku, x, y);
		if(fittable_counter==0) {
			result = &arrayOf123456789[i];
			break;
		}
	}
	return result;
}

char *get_suit_valu(int x, int y, char **sudoku) {
	char *arrayOf123456789 = "123456789";
	int i, j;
	char *result = "-";
	char *arrayOfFitable;

	int fittable_counter = 0;
	arrayOfFitable = calloc(9, sizeof(char*));
	if(haveItSolve(x, y, sudoku, arrayOf123456789)) {
		result = getValueOfFit(x, y, sudoku, arrayOf123456789);
	} else {
		result = "-";
	}

	free(arrayOfFitable);
	return result;
	
}

void solve(char **sudoku) {
	int j;
	int trigger = 0;

	for(int i=0;i<9;i++) {
		j=0;
		for(j=0;j<9;j++) {
			if (sudoku[i][j] != 45)
				continue;
			sudoku[i][j] = *get_suit_valu(i, j, sudoku);
		}
		puts("\n");
	}
}

void freeing_memory(char **sudoku) {
	for(int i=0;i<9;i++)
		free(sudoku[i]);
	free(sudoku);
	puts("Memory for char  **sudoku freed && end the programm");
}

int trigger(char **sudoku) {
	int result;

	result = 1;
	for(int i=0;i<9;i++) {
		for(int j=0;j<9;j++) {
			if(sudoku[i][j] == 45)
				result = 0;
		}
	}
	return result;
}

void writeSudokuToFile(char **sudoku) {
	FILE* fd_write = fopen("sudoku", "a");
	assert(fd_write);
	putc(sudoku[0][9], fd_write);
	for(int i=0;i<9;i++) {
		for(int j=0;j<9;j++) {
			putc(32, fd_write);
			putc(sudoku[i][j], fd_write);
			if(j==2 || j==5)
				putc(124, fd_write);
			if(j==8)
				putc(10, fd_write);
		}
		if(i==2 || i==5) {
			for(int f=0;f<20;f++)
				fputc(45, fd_write);
			fputc(10, fd_write);
		}
	}
	fclose(fd_write);
}

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
