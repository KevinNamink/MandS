#include <stdio.h>
#include <time.h>
#include <math.h>
#include "mt19937.h"

#define PI 3.14159265

int main(int argc, char* argv[])
{
	FILE *f = fopen("xy_square.dat", "w");
	if (f == NULL)
	{
		printf("Error opening file!\n");
		exit(1);
	}
	
	int Nx, Ny, N, i, j;
	Nx = 5;
	Ny = 6;
	N = Nx*Ny;
	
	double d, r, spacing, l, boxx, boxy, x, y;
	d = 1.;
	r = d/2;
	spacing = 0.;
	l = d+spacing;
	boxx = Nx*l;
	boxy = Ny*l;
		
	fprintf(f, "%lf\t%lf\n%d", boxx, boxy, N);
	
	for(i=0; i<Nx; i++)
	{
		for(j=0; j<Ny; j++)
		{
			x = r+l*i;
			y = r+l*j;
			fprintf(f, "\n%lf\t%lf", x, y);
		}
		
	}
	
	return 0;
}