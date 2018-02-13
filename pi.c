#include <stdio.h>
#include <time.h>
#include "mt19937.h"

int main(int argc, char* argv[])
{
	FILE *f = fopen("pi.txt", "w");
	if (f == NULL)
	{
		printf("Error opening file!\n");
		exit(1);
	}

	dsfmt_seed(time(NULL));
	int i, N, j, aantal, k;
	double x, y, pi, nhits;
	aantal = 20;
	N=10000;
	fprintf(f, "#Print pi voor verschillende N met random sampling.\n");
	fprintf(f, "pi\tN\n");
	for(k=10; k<=N; k=k*10)
	{
		printf("Voor N=%d:\n", k);
		for(j=0; j<aantal; j++)
		{
			nhits=0.;
			for(i=0; i<k; i++)
			{
				x = 1 - 2*dsfmt_genrand();
				y = 1 - 2*dsfmt_genrand();
				if(x*x + y*y < 1)
				{
					nhits++;
				}
			}
			pi = nhits/k*4.;
			fprintf(f, "%lf\t%d\n", pi, k);
			printf("%lf\n", pi);
		}
		
	}
	getchar();
	fclose(f);
	return 0;
}