// Imports
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

// Explains the correct use of the executable
void printHelp(char **argv){
	printf("Usage: %s <M> <N> <seed>\n",argv[0]);
	return;
}

// Generates the random numbers for each element in an arbitrary matrix
void generateMatrix(int **matrix, int x, int y){
	for (int i=0; i<x; i++){
		for (int j=0; j<y; j++){
			matrix[i][j] = rand() % (99 + 1 - 0) + 0;
		}
	}

	return;
}
// Displays the elements of an arbitrary matrix on the console
void printMatrix(int **matrix, int x, int y){
	for (int i=0; i<x; i++){
		for (int j=0; j<y; j++){
			printf("%d ",matrix[i][j]);
		}
		printf("\n");
	}

	return;
}

// Frees memory allocated to an arbitrary matrix with 'size' rows
void freeMatrix(int **matrix, int size){
	for (int i=0; i<size; i++)
		free(matrix[i]);
	free(matrix);
}

int** multiplyMatrices(int **resultMatrix, int **matrix1, int **matrix2, int x, int y){
	for (int i=0; i<x; i++){
		for (int j=0; j<x; j++){
			for (int k=0; k<y; k++){
				resultMatrix[i][j] = resultMatrix[i][j] + (matrix1[i][k] * matrix2[k][j]);
			}
		}
	}

	return resultMatrix;
}

// Main function which takes command line arguments
int main(int argc, char **argv){
	int m;
	int n;
	int seed;

	int **mat1;
	int **mat2;
	int **result;

	struct timeval start, stop, elapsed;

	if (argc != 4){
		printf("ERROR: incorrect number of arguments\n");
		printHelp(argv);
		return 0;
	}

	// Checks if M and N from CLA are integers and also not 0
	for (int i=1; i<3; i++){
		if (atoi(argv[i]) == 0){
			printf("ERROR: arguments are not integers\n");
			printHelp(argv);
			return 0;
		}
	}
	m = atoi(argv[1]);
	n = atoi(argv[2]);
	seed = atoi(argv[3]); // if CLA not an int, 0 works for seed

	// Initialises seed for random number generation
	srand(seed);

	// Generates matrix 1
	mat1 = malloc(m * sizeof(long unsigned int));
	if (mat1 == NULL)
		return -1;
	for (int i=0; i<m; i++){
		mat1[i] = malloc(n * sizeof(int));
		if (mat1[i] == NULL)
			return -1;
	}
	generateMatrix(mat1,m,n);
	printf("MATRIX 1:\n");
	printMatrix(mat1,m,n);

	// Generates matrix 2
	mat2 = malloc(n * sizeof(long unsigned int));
	if (mat2 == NULL)
		return -1;
	for (int i=0; i<n; i++){
		mat2[i] = malloc(m * sizeof(int));
		if (mat2[i] == NULL)
			return -1;
	}
	generateMatrix(mat2,n,m);
	printf("MATRIX 2:\n");
	printMatrix(mat2,n,m);

	// Creates empty result matrix
	result = malloc(m * sizeof(long unsigned int));
	if (result == NULL)
		return -1;
	for (int i=0; i<m; i++){
		result[i] = malloc(m * sizeof(int));
		if (result[i] == NULL)
			return -1;
	}

	// Multiplies both matrices and display result on console with time elapsed
	gettimeofday(&start, NULL);
	multiplyMatrices(result,mat1,mat2,m,n);
	gettimeofday(&stop, NULL);
	printf("RESULT:\n");
	printMatrix(result,m,m);
	timersub(&stop,&start,&elapsed);
	printf("EXECUTION TIME: %lu.%06lu seconds\n",elapsed.tv_sec,elapsed.tv_usec);

	// Frees both matrices
	freeMatrix(mat1,m);
	freeMatrix(mat2,n);

	return 0;
}