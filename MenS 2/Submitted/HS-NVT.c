#include <stdio.h>
#include <time.h>
#include <assert.h>
#include <math.h>
#include "mt19937.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define NDIM 3
#define N 1280

/* Initialization variables */
const int mc_steps = 100000;
const int output_steps = 1000;
double packing_fraction = 0.4;  /* We change the packing fraction and delta with the input to not have to edit the program every time. */
const double diameter = 1.0;
double delta = 0.05;
const char* init_filename = "fcc_xyz.dat";

/* Simulation variables */
int n_particles = 0;
double radius;
double particle_volume;
double r[N][NDIM];
double box[NDIM];


/* Functions */

/* Question 5: */
void read_data(void)
{
	int i;
	double diameterthathasnorealuseappearantly;
	int intinput;
	double lfinp0, lfinp1, lfinp2; 
	
	printf("Enter just a number and then hit enter, any other input, like a backspace, is registered and makes it crash.\nSize of packing fraction:\n");
	scanf("%lf", &lfinp0);
	packing_fraction = lfinp0;
	printf("Size of delta: \n");
	scanf("%lf", &lfinp0);
	delta = lfinp0;
	printf("Now using packingfraction of: %lf \nand delta of:%lf\nEnter any number to start...\n", packing_fraction, delta);
	scanf("%lf", &lfinp0);
	
	
	
	FILE *fp = fopen(init_filename, "r");
	
	/* Take the values from the data, putting the data in temporary variables to get around (for us) difficult pointer issues. */
    fscanf(fp, "%d\n0\t%lf\n0\t%lf\n0\t%lf", &intinput, &lfinp0, &lfinp1, &lfinp2);
	n_particles = intinput;
	box[0] = lfinp0;
	box[1] = lfinp1;
	box[2] = lfinp2;
	
	
	for(i=0; i<n_particles; i++)
	{
		/* Same as before. */
		fscanf(fp, "\n%lf\t%lf\t%lf\t%lf", &lfinp0, &lfinp1, &lfinp2, &diameterthathasnorealuseappearantly);
		r[i][0] = lfinp0;
		r[i][1] = lfinp1;
		r[i][2] = lfinp2;
	}
	radius = diameterthathasnorealuseappearantly/2;
	particle_volume = 4/3*M_PI*radius*radius*radius;
	
}

/* Question 6: */
int OLD_move_particle(void)
{
	int rndmparticle;
	double xnew, ynew, znew, dx, dy, dz;
	
	/* Select a random particle */
    rndmparticle = (int)(n_particles*dsfmt_genrand());
	
	/* Select a random displacement */
	dx = 2*dsfmt_genrand()-1*delta;
	dy = 2*dsfmt_genrand()-1*delta;
	dz = 2*dsfmt_genrand()-1*delta;
	
	/* Account for the periodic boundary conditions. */
	if(r[rndmparticle][0]+dx<0)
		xnew = r[rndmparticle][0]+dx+box[0];
	else if(r[rndmparticle][0]+dx>=box[0])
		xnew = r[rndmparticle][0]+dx-box[0];
	else 
		xnew = r[rndmparticle][0]+dx;
	
	if(r[rndmparticle][1]+dy<0)
		ynew = r[rndmparticle][1]+dy+box[1];
	else if(r[rndmparticle][1]+dy>=box[1])
		ynew = r[rndmparticle][1]+dy-box[1];
	else 
		ynew = r[rndmparticle][1]+dy;
	
	if(r[rndmparticle][2]+dz<0)
		znew = r[rndmparticle][2]+dz+box[2];
	else if(r[rndmparticle][2]+dz>=box[2])
		znew = r[rndmparticle][2]+dz-box[2];
	else 
		znew = r[rndmparticle][2]+dz;
	
	/* Give the particle it's new position */
	r[rndmparticle][0] = xnew;
	r[rndmparticle][1] = ynew;
	r[rndmparticle][2] = znew;
	return 1;
    
}

/* Question 7: */
int move_particle(void)
{
	int rndmparticle, i;
	double xnew, ynew, znew, dx, dy, dz, chex, chey, chez;
	
    rndmparticle = (int)(n_particles*dsfmt_genrand());
	
	dx = 2*dsfmt_genrand()-1*delta;
	dy = 2*dsfmt_genrand()-1*delta;
	dz = 2*dsfmt_genrand()-1*delta;
	
	if(r[rndmparticle][0]+dx<0)
		xnew = r[rndmparticle][0]+dx+box[0];
	else if(r[rndmparticle][0]+dx>=box[0])
		xnew = r[rndmparticle][0]+dx-box[0];
	else 
		xnew = r[rndmparticle][0]+dx;
	
	if(r[rndmparticle][1]+dy<0)
		ynew = r[rndmparticle][1]+dy+box[1];
	else if(r[rndmparticle][1]+dy>=box[1])
		ynew = r[rndmparticle][1]+dy-box[1];
	else 
		ynew = r[rndmparticle][1]+dy;
	
	if(r[rndmparticle][2]+dz<0)
		znew = r[rndmparticle][2]+dz+box[2];
	else if(r[rndmparticle][2]+dz>=box[2])
		znew = r[rndmparticle][2]+dz-box[2];
	else 
		znew = r[rndmparticle][2]+dz;
	
	/* Until here the code is the same as in question 6. */
	
	/* For each particle */
	for(i=0; i<n_particles; i++)
	{
		
		/* Check if it is potentially an overlap with the periodic boundary in mind and save a value 
		   for the coordinate of the particle to use in checking range later for each direction */		
		if((r[i][0]-xnew)*(r[i][0]-xnew)>(r[i][0]-xnew+box[0])*(r[i][0]-xnew+box[0]))
			chex = r[i][0]+box[0];
		else if((r[i][0]-xnew)*(r[i][0]-xnew)>(r[i][0]-xnew-box[0])*(r[i][0]-xnew-box[0]))
			chex = r[i][0]-box[0];
		else 
			chex = r[i][0];
		
		if((r[i][1]-ynew)*(r[i][1]-ynew)>(r[i][1]-ynew+box[1])*(r[i][1]-ynew+box[1]))
			chey = r[i][1]+box[1];
		else if((r[i][1]-ynew)*(r[i][1]-ynew)>(r[i][1]-ynew-box[1])*(r[i][1]-ynew-box[1]))
			chey = r[i][1]-box[1];
		else 
			chey = r[i][1];
		
		if((r[i][2]-znew)*(r[i][2]-znew)>(r[i][2]-znew+box[2])*(r[i][2]-znew+box[2]))
			chez = r[i][2]+box[2];
		else if((r[i][2]-znew)*(r[i][2]-znew)>(r[i][2]-znew-box[2])*(r[i][2]-znew-box[2]))
			chez = r[i][2]-box[2];
		else 
			chez = r[i][2]; 
		
		
		if((chex-xnew)*(chex-xnew)		/* Check if it is in range. */
				+(chey-ynew)*(chey-ynew)
				+(chez-znew)*(chez-znew)
				<=(2*radius)*(2*radius))
		{
			if(i!=rndmparticle) 				/* Check if its not itself. */
				return 0; /* If it overlaps and is not itself: the move is invalid, 0 is returned and the function ended. */
		}				
	}
	
	
	/* Do the move, it is valid if this code is reached. */
	r[rndmparticle][0] = xnew;
	r[rndmparticle][1] = ynew;
	r[rndmparticle][2] = znew;
	return 1;
    
}

void write_data(int step){
    char buffer[128];
    sprintf(buffer, "coords_step%07d.dat", step);
    FILE* fp = fopen(buffer, "w");
    int d, n;
    fprintf(fp, "%d\n", n_particles);
    for(d = 0; d < NDIM; ++d){
        fprintf(fp, "%lf %lf\n",0.0,box[d]);
    }
    for(n = 0; n < n_particles; ++n){
        for(d = 0; d < NDIM; ++d) fprintf(fp, "%f\t", r[n][d]);
        fprintf(fp, "%lf\n", diameter);
    }
    fclose(fp);
}

void set_packing_fraction(void){
    double volume = 1.0;
    int d, n;
    for(d = 0; d < NDIM; ++d) volume *= box[d];
	
    double target_volume = (n_particles * particle_volume) / packing_fraction;
    double scale_factor = pow(target_volume / volume, 1.0 / NDIM);

    for(n = 0; n < n_particles; ++n){
        for(d = 0; d < NDIM; ++d) r[n][d] *= scale_factor;
    }
    for(d = 0; d < NDIM; ++d) box[d] *= scale_factor;
}

int main(int argc, char* argv[]){

    assert(packing_fraction > 0.0 && packing_fraction < 1.0);
    assert(diameter > 0.0);
    assert(delta > 0.0);

    radius = 0.5 * diameter;

    if(NDIM == 3) particle_volume = M_PI * pow(diameter, 3.0) / 6.0;
    else if(NDIM == 2) particle_volume = M_PI * pow(radius, 2.0);
    else{
        printf("Number of dimensions NDIM = %d, not supported.", NDIM);
        return 0;
    }

    read_data();

    if(n_particles == 0){
        printf("Error: Number of particles, n_particles = 0.\n");
        return 0;
    }

    set_packing_fraction();

    dsfmt_seed(time(NULL));

    int accepted = 0;
    int step, n;
    for(step = 0; step < mc_steps; ++step){
        for(n = 0; n < n_particles; ++n){
            accepted += move_particle();
        }

        if(step % output_steps == 0){
            printf("Step %d. Move acceptance: %lf.\n", step, (double)accepted / (n_particles * output_steps));
            accepted = 0;
            write_data(step);
        }
    }

    return 0;
}