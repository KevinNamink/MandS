#include <stdio.h>
#include <time.h>
#include "mt19937.h"

int main(int argc, char* argv[])
{
	FILE *f = fopen("discrete_lattice_markov.txt", "w");
	if (f == NULL)
	{
		printf("Error opening file!\n");
		exit(1);
	}

	dsfmt_seed(time(NULL));
	
	
	int N, M, n, m, dx, dy, steps, site, i, j;
	double rnd;
	N = 4;
	M = 5;
	steps = 100000000;

	fprintf(f, "#For a run with steps = %d\n", steps);
	fprintf(f, "#On a lattice with width = %d\n", N);
	fprintf(f, "#and height = %d\n", M);
	fprintf(f, "lattice site\ttimes visited\n");
	
	int matrix[N][M];
	site = 0;
	for(i=0; i<N; i++)
	{
		for(j=0; j<M; j++)
		{
			matrix[i][j] = site;
			site++;
		}
	}
	
	n = 0;
	m = 0;
	
	int visits[site];
	for(i=0; i<site; i++) visits[i] = 0;
	
	for(i=0; i<steps; i++)
	{
		rnd = 4*dsfmt_genrand();
		if(rnd<1)
		{
			dx = 1;
			dy = 0;
		} 
		else if(rnd<2)
		{
			dx = 0;
			dy = 1;
		} 
		else if(rnd<3)
		{
			dx = -1;
			dy = 0;
		} 
		else
		{
			dx = 0;
			dy = -1;
		} 
		
		if( (n+dx != -1) && (n+dx != N) && (m+dy != -1) && (m+dy != M) )
		{
			n = n+dx;
			m = m+dy;
		}
		visits[matrix[n][m]] += 1;
		
	}
	
	for(i=0; i<site; i++)
	{
		fprintf(f, "%d\t%d\n", i, visits[i]);
	}
	
	fclose(f);
	return 0;
}