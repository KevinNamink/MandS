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
	boxx = Nx*l*sqrt(2);
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
						z = r+l*k*sqrt(3)/2;
						x = r+l*i*sqrt(2);
						y = r+l*j*sqrt(3)/2;
					}
					else
					{
						z = r+l*k*sqrt(3)/2;
						x = r+l*(i+0.5)*sqrt(2);
						y = r+l*j*sqrt(3)/2;
					}
				}
				else
				{
					if(j%2==0)
					{
						z = r+l*k*sqrt(3)/2;
						x = r+l*(i+0.5)*sqrt(2);
						y = r+l*j*sqrt(3)/2;
					}
					else
					{
						z = r+l*k*sqrt(3)/2;
						x = r+l*i*sqrt(2);
						y = r+l*j*sqrt(3)/2;
					}
				}
				
				
				fprintf(f, "\n%lf\t%lf\t%lf", x, y, z);
			}
		}
	}
	
	return 0;
}