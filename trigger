int trigger(char **sudoku);

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

