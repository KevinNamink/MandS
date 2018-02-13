#include <stdio.h>
#include <time.h>
#include "mt19937.h"

int main(int argc, char* argv[])
{
	FILE *f = fopen("pi_markov.txt", "w");
	if (f == NULL)
	{
		printf("Error opening file!\n");
		exit(1);
	}

	dsfmt_seed(time(NULL));
	int i, N, j, aantal, rejected;
	double x, y, pi, nhits, dx, dy, delta;
	aantal = 20;
	N=1000000;
	fprintf(f, "#Print pi voor verschillende delta met Markov-Chain Sampling. Aantal stappen = %d\n", N);
	fprintf(f, "pi\tdelta\trejects\n");
	for(delta=1./4; delta<6; delta+=1./2)
	{
		printf("Voor delta=%lf:\n", delta);
		for(j=0; j<aantal; j++)
		{
			nhits=0.;
			x = 0.;
			y = 0.;
			rejected = 0;
			for(i=0; i<N; i++)
			{
				dx = delta - delta*2*dsfmt_genrand();
				dy = delta - delta*2*dsfmt_genrand();
				if( (x+dx)*(x+dx) < 1 && (y+dy)*(y+dy) < 1 )
				{
					x = x + dx;
					y = y + dy;
				}
				else
				{
					rejected++;
				}
				if(x*x + y*y < 1)
				{
					nhits++;
				}
			}
			pi = nhits/N*4.;
			fprintf(f, "%lf\t%lf\t%d\n", pi, delta, rejected);
			printf("%lf\n", pi);
		}
		
	}
	getchar();
	fclose(f);
	return 0;
}