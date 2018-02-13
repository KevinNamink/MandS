#include <stdio.h>
#include <time.h>
#include "mt19937.h"

int main(int argc, char* argv[])
{
	printf("Enter just a number and then hit enter, any other input, like a backspace, is registered and makes it crash.\nSize of desired matrix:\n");
	int myInt;
	scanf("%d", &myInt);
		
	FILE *f = fopen("transformation_matrix.txt", "w");
	if (f == NULL)
	{
		printf("Error opening file!\n");
		exit(1);
	}

	int N, i, j, NN;
	N = myInt;
	NN = N*N;
	float matrix[NN][NN];
	for(i=0; i<NN; i++)
	{
		for(j=0; j<NN; j++)
		{
			matrix[i][j] = 0.;
		}
	}
	
	for(i=0; i<N; i++)
	{
		for(j=0; j<N; j++)
		{
			if(i+N*j-N < 0) matrix[i+N*j][i+N*j] += 1./4;
			else matrix[i-N+N*j][i+N*j] += 1./4;
		
			if(i+N*j+N >= NN) matrix[i+N*j][i+N*j] += 1./4;
			else matrix[i+N+N*j][i+N*j] += 1./4;
			
			if(i-1 < 0) matrix[i+N*j][i+N*j] += 1./4;
			else matrix[i-1+N*j][i+N*j] += 1./4;
			
			if(i+1 >= N) matrix[i+N*j][i+N*j] += 1./4;
			else matrix[i+1+N*j][i+N*j] += 1./4;
		}
	}
	
	for(i=0; i<NN; i++)
	{
		fprintf(f, "%lf", matrix[i][0]);
		for(j=1; j<NN; j++)
		{
			fprintf(f, "\t%lf", matrix[i][j]);
		}
		fprintf(f, "\n");
	}
	
	fclose(f);
	return 0;
}