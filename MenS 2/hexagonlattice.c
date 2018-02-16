#include <stdio.h>
#include <time.h>
#include <math.h>
#include "mt19937.h"

#define PI 3.14159265

int main(int argc, char* argv[])
{
	FILE *f = fopen("xy_hexagon.dat", "w");
	if (f == NULL)
	{
		printf("Error opening file!\n");
		exit(1);
	}
	
	int Nx, Ny, N, i, j;
	Nx = 6;
	Ny = 6;
	N = Nx*Ny;
	
	double d, r, spacing, l, boxx, boxy, x, y;
	d = 1.;
	r = d/2;
	spacing = 0.;
	l = d+spacing;
	boxx = Nx*l+1/2;
	boxy = Ny*l*sqrt(3)/2;
		
	fprintf(f, "%lf\t%lf\n%d", boxx, boxy, N);
	
	for(j=0; j<Ny; j++)
	{
		for(i=0; i<Nx; i++)
		{
			if(j%2==0)
			{
				x = r+l*i;
				y = r+l*sqrt(3)/2*j;
			}
			else
			{
				x = r+l*i+l/2;
				y = r+l*sqrt(3)/2*j;
			}
			fprintf(f, "\n%lf\t%lf", x, y);
		}
		
	}
	
	return 0;
}