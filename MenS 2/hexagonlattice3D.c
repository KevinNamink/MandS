#include <stdio.h>
#include <time.h>
#include <math.h>
#include "mt19937.h"

#define PI 3.14159265

int main(int argc, char* argv[])
{
	FILE *f = fopen("xyz_hexagon.dat", "w");
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
	boxx = Nx*l+1/2;
	boxy = Ny*l*sqrt(3)/2;
	boxz = Nz*l*sqrt(3)/2;
		
	fprintf(f, "%lf\t%lf\t%lf\n%d", boxx, boxy, boxz, N);
	
	for(k=0; k<Nz; k++)
	{
		for(j=0; j<Ny; j++)
		{
			for(i=0; i<Nx; i++)
			{
				if(k%2==0)
				{
					if(j%2==0)
					{
						z = r+l*sqrt(3)/2*k;
						x = r+l*i;
						y = r+l*sqrt(3)/2*j;
					}
					else
					{
						z = r+l*sqrt(3)/2*k;
						x = r+l*i+l/2;
						y = r+l*sqrt(3)/2*j;
					}
				}
				else
				{
					if(j%2==0)
					{
						z = r+l*sqrt(3)/2*k;
						x = r+l*i+l*sqrt(3)/4;
						y = r+l*sqrt(3)/2*j+l*sqrt(3)/4;
					}
					else
					{
						z = r+l*sqrt(3)/2*k;
						x = r+l*i+l/2+l*sqrt(3)/4;
						y = r+l*sqrt(3)/2*j+l*sqrt(3)/4;
					}
				}
				fprintf(f, "\n%lf\t%lf\t%lf", x, y, z);
			}
		}
	}
	
	return 0;
}