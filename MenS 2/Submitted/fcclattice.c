#include <stdio.h>
#include <time.h>
#include <math.h>
#include "mt19937.h"

#define PI 3.14159265

int main(int argc, char* argv[])
{
	FILE *f = fopen("fcc_xyz.dat", "w");
	if (f == NULL)
	{
		printf("Error opening file!\n");
		exit(1);
	}
	
	/* We build the crystal per unit cell */
	int Nx, Ny, N, i, j, Nz, k;
	Nx = 8;
	Ny = 8;
	Nz = 5;
	N = Nx*Ny*Nz*4;
	
	double a, d, spacing, l, boxx, boxy, boxz, x, y, z;
	d = 1.;
	spacing = 0.;
	l = (d+spacing);
	a = sqrt(2*l*l);
	boxx = Nx*a;
	boxy = Ny*a;
	boxz = Nz*a;
	
	fprintf(f, "%d\n0\t%lf\n0\t%lf\n0\t%lf", N, boxx, boxy, boxz);
	
	/* For each unit cell: */
	for(k=0; k<Nz; k++)
	{
		for(j=0; j<Ny; j++)
		{
			for(i=0; i<Nx; i++)
			{
				
				/* Place spheres at the correct places */
				x = a*i;
				y = a*j;
				z = a*k;
				fprintf(f, "\n%lf\t%lf\t%lf\t%lf", x, y, z, d);
				
				x = a*i+a/2;
				y = a*j+a/2;
				z = a*k;
				fprintf(f, "\n%lf\t%lf\t%lf\t%lf", x, y, z, d);
				
				x = a*i+a/2;
				y = a*j;
				z = a*k+a/2;
				fprintf(f, "\n%lf\t%lf\t%lf\t%lf", x, y, z, d);
				
				x = a*i;
				y = a*j+a/2;
				z = a*k+a/2;
				fprintf(f, "\n%lf\t%lf\t%lf\t%lf", x, y, z, d);
			}
		}
	}
	
	return 0;
}