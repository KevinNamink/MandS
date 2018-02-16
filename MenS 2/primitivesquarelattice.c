#include <stdio.h>
#include <time.h>
#include <math.h>
#include "mt19937.h"

#define PI 3.14159265

int main(int argc, char* argv[])
{
	FILE *f = fopen("xyz_fcc.dat", "w");
	if (f == NULL)
	{
		printf("Error opening file!\n");
		exit(1);
	}
	
	int Nx, Ny, N, i, j, Nz, k;
	Nx = 4;
	Ny = 4;
	Nz = 4;
	N = Nx*Ny*Nz;
	
	double d, r, spacing, l, boxx, boxy, boxz, x, y, z;
	d = 1.;
	r = d/2;
	spacing = 0.;
	l = d+spacing;
	boxx = Nx*l;
	boxy = Ny*l;
	boxz = Nz*l;
	
	fprintf(f, "%lf\t%lf\t%lf\n%d", boxx, boxy, boxz, N);
	
	for(k=0; k<Nz; k++)
	{
		for(j=0; j<Ny; j++)
		{
			for(i=0; i<Nx; i++)
			{
				z = r+l*k;
				x = r+l*i;
				y = r+l*j;
			
				fprintf(f, "\n%lf\t%lf\t%lf", x, y, z);
			}
		}
	}
	
	return 0;
}