#include <stdlib.h>
#include <stdio.h>
#include <math.h>


int argc;
char **argv;

int main (int argc, char **argv) {
char filename1[255], firstletter[256];
FILE * fid;

/*This reads "masses.txt" and calculates angluar momentum*/

if (argc !=2) {
	printf("Usage: angular_momentum filename\n");
	exit(0);
	}


sprintf(filename1, "%s", argv[1]);

printf("input filename=%s\n", filename1);

fid=fopen(filename1, "r+w");


if (fid == NULL){
	printf("(Input file not found):\n");
	printf("%s\n", filename1);
	exit(0);
	}

rewind(fid);

float target_radius, impactor_radius;

fgets(firstletter, 255, fid);  /* "TARGET" */
/*fgets(firstletter, 255, fid); */ /* "rgstable xxx, xxx, xxx, xxx */
fgets(firstletter, 255, fid); /* "rgstable xxx, xxx, xxx, xxx */
sscanf(firstletter, "%*47c%e", &target_radius);

fgets(firstletter, 255, fid);  /* "input filename = obj.0000000.txt " */

float target_y, target_vx, target_mass;
float impactor_y, impactor_vx, impactor_mass;

fgets(firstletter, 255, fid);
sscanf(firstletter, "%e", &target_mass);

fgets(firstletter, 255, fid);
sscanf(firstletter, "%*48c\t%*2c%e", &target_y);
/*want the absolute value of y*/
target_y=sqrt(target_y*target_y);

fgets(firstletter, 255, fid);
sscanf(firstletter, "%*32c%e", &target_vx);
target_vx=1.0e5*target_vx;
/*want the absolute value of vx*/
target_vx=sqrt(target_vx*target_vx);

fgets(firstletter, 255, fid);  /* "IMPACTOR" */
/*fgets(firstletter, 255, fid);*/  /* "rgstable xxx, xxx, xxx, xxx */
fgets(firstletter, 255, fid); /* "rgstable xxx, xxx, xxx, xxx */
sscanf(firstletter, "%*47c%e", &impactor_radius);

fgets(firstletter, 255, fid);  /* "input filename = obj.0000000.txt " */

fgets(firstletter, 255, fid);
sscanf(firstletter, "%e", &impactor_mass);

fgets(firstletter, 255, fid);
sscanf(firstletter, "%*48c\t%*2c%e", &impactor_y);
/*want the absolute value of y*/
impactor_y=sqrt(impactor_y*impactor_y);

fgets(firstletter, 255, fid);
sscanf(firstletter, "%*32c%e", &impactor_vx);
impactor_vx=1.0e5*impactor_vx;
/*want the absolute value of vx*/
impactor_vx=sqrt(impactor_vx*impactor_vx);

fprintf(stderr, "target mass	: %e (grams)\n", target_mass);
fprintf(stderr, "target y loc	: %e (cm) \n", target_y);
fprintf(stderr, "target vx	: %e (cm/s)\n", target_vx);
fprintf(stderr, ".........................................\n");
fprintf(stderr, "impactor mass    : %e (grams)\n", impactor_mass);
fprintf(stderr, "impactor y loc   : %e (cm) \n", impactor_y);
fprintf(stderr, "impactor vx      : %e (cm/s)\n", impactor_vx);
fprintf(stderr, ".........................................\n");

fprintf(stderr, "Total mass	: %e (grams)\n", target_mass+impactor_mass);
fprintf(stderr, "Mass imapctor  : %e (grams)\n", impactor_mass);
fprintf(stderr, "Radius impactor: %.3f (km)\n", impactor_radius/1.0e5);
fprintf(stderr, "Dens. impactor : %.3f (g/cc)\n", impactor_mass/((4.0/3.0)*3.1415926*pow(impactor_radius, 3.0)));
fprintf(stderr, "Mass target    : %e (grams)\n", target_mass);
fprintf(stderr, "Radius target  : %.3f (km)\n", target_radius/1.0e5);
fprintf(stderr, "Dens. target   : %.3f (g/cc)\n", target_mass/((4.0/3.0)*3.1415926*pow(target_radius, 3.0)));
fprintf(stderr, "Gamma		: %e \n", impactor_mass/(target_mass+impactor_mass));

double L;

L=((target_mass/1.0e27)*(target_y/1.0e8)*(target_vx/1.0e5)) + ((impactor_mass/1.0e27)*(impactor_y/1.0e8)*(impactor_vx/1.0e5));

fprintf(stderr, "Angular momentum : %.5lf x10^41 (cgs)\n", L/10.0);
fprintf(stderr, "Angular momentum : %e (LEM)\n", L/3.5e1);

fprintf(fid, "Output from angular_momentum.c................\n");
fprintf(fid, "Total mass     : %e (grams)\n", target_mass+impactor_mass);
fprintf(fid, "Mass imapctor  : %e (grams)\n", impactor_mass);
fprintf(fid, "Radius impactor: %.3f (km)\n", impactor_radius/1.0e5);
fprintf(fid, "Dens. impactor : %.3f (g/cc)\n", impactor_mass/((4.0/3.0)*3.1415926*pow(impactor_radius, 3.0)));
fprintf(fid, "Mass target    : %e (grams)\n", target_mass);
fprintf(fid, "Radius target  : %.3f (km)\n", target_radius/1.0e5);
fprintf(fid, "Dens. target   : %.3f (g/cc)\n", target_mass/((4.0/3.0)*3.1415926*pow(target_radius, 3.0)));
fprintf(fid, "Gamma          : %e \n", impactor_mass/(target_mass+impactor_mass));
fprintf(fid, ".........................................\n");
fprintf(fid, "Angular momentum : %.5lf x10^41 (cgs)\n", L/10);
fprintf(fid, "Angular momentum : %e (LEM)\n", L/3.5e1);


fclose(fid);



return(0);
}

