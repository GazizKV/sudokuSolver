#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

void print_sudoku(char **sudoku) {
	for(int i=0;i<9;i++) {
		printf("%s", sudoku[i]);
	}
}

char** allocating_memory(FILE *fd_sudoku) {
	char **sudoku = calloc(9, sizeof(char*));
	for(int i=0;i<9;i++)
	{
		sudoku[i] = calloc(11, sizeof(char));
		printf("%ls", &i);
	}
	if ( sudoku==NULL) {
		printf("Can not allocating memory\n");
		exit (1);
	}
	printf("Memory allocating\n");
	return sudoku;
}

FILE *open_pruv_file(char *file_name) {
	FILE *fd_sudoku;
	fd_sudoku=fopen(file_name, "r");
	if (fd_sudoku == 0) {
		printf("Cannot open file\n");
		exit(1);
	}
	puts("File open by file stream name fd_sudoku\n");
	return fd_sudoku;
}

char **read_file_to_sudoku(char **sudoku, FILE *fd_sudoku) {
	int i;

	i = 0;
	while (fgets(*sudoku, 11, fd_sudoku) != NULL) {
		printf("%s", *sudoku++);
	}
	puts("\n");
	if (feof(fd_sudoku))
		puts("End of file reached");
	printf("File readed to char **sudoku\n\n");
	fclose(fd_sudoku);
	return sudoku;
}

int chek_horisontal(char digit, char **sudoku, int x) {
	int result = 0;
	for(int i=0;i<9;i++) {
		if(digit==sudoku[x][i]) result=1;
	}
	return result;
}

int chek_vertikal(char digit, char **sudoku, int y) {
	int result = 0;
	for(int i=0;i<9;i++) {
		if(digit==sudoku[i][y]) result=1;
	}
	return result;
}

int chek_square(char digit, char **sudoku, int x, int y) {
	int result = 0;
	int fromX = x/3*3;
	int fromY = y/3*3;

	for(int i=fromX;i<fromX+3;i++) {
		for(int j=fromY;j<fromY+3;j++) {
			if(digit==sudoku[i][j])
				result=1;
		}
	}
	return result;
}

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
	printf("%d-%d ", fit, inerCounter);
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
	char *hephen = "-";

	for(int i=0;i<9;i++) {
		j=0;
		for(j=0;j<9;j++) {
			if (sudoku[i][j] != *hephen)
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

int main(int argc, char* argv[]){
	FILE *fd_sudoku;
	char **sudoku;
	int trigger;

	sudoku = allocating_memory(fd_sudoku);
	fd_sudoku = open_pruv_file("sudoku");
	read_file_to_sudoku(sudoku, fd_sudoku);
	while(true) {
		print_sudoku(sudoku);
		solve(sudoku);
		scanf("%d", &trigger);
		if(trigger)
			break;

	}
	freeing_memory(sudoku);

	return 0;
}
