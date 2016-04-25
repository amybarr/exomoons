#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define Mearth 5.98e27


int argc;
char **argv;

int main (int argc, char **argv) {
int nel, ntot;

char filename1[255], filenameout[255], firstletter[400];
/*char crap[400];*/
FILE * fid;
FILE * fidout;
float totalvolfrac;

if (argc !=2) {
	printf("Usage: discard_empty input_filename\n");
	exit(0);
	}


sprintf(filename1, "%s", argv[1]);
sprintf(filenameout, "%s.no_empties.txt", argv[1]);

printf("input filename=%s\n", filename1);
printf("output filename=%s\n", filenameout);

fid=fopen(filename1, "r");
fidout=fopen(filenameout, "w");


if (fid == NULL){
	printf("(Input file not found):\n");
	printf("%s\n", filename1);
	exit(0);
	}

if (fidout == NULL) {
	printf("(Invalid output file name):\n");
	printf("%s\n", filenameout);
	exit(0);
	}


rewind(fid);
rewind(fidout);

fgets(firstletter, 400, fid);
/*fprintf(stderr, "firstletter=%s\n", firstletter);*/

float xloc, yloc, zloc, vx, vy, vz, dx, dy, dz, p, dens, tk, m1, m2, m3, m4, v1, v2, v3, v4;

float mt;

nel=0;
ntot=0;
mt=0.0;

fprintf(fidout, "                              \n");

while(feof(fid) == 0) {

/********** DEBUG ************/
/*while(ntot < 1){ */
/********** DEBUG ************/

totalvolfrac=0.0;

fgets(firstletter, 400, fid);

/********** DEBUG ************/
/*fprintf(stderr, "first line of numerical data=%s\n", firstletter); */
/********** DEBUG ************/

sscanf(firstletter, "%e%e%e%e%e%e%e%e%e%e%e%e%e%e%e%e%e%e%e%e", &xloc, &yloc, &zloc, &dx, &dy, &dz, &vx, &vy, &vz, &p, &dens, &tk, &m1, &m2, &m3, &m4, &v1, &v2, &v3, &v4);

/********** DEBUG ************/
/*fprintf(stderr, "xloc=%e, yloc=%e, zloc=%e\n", xloc, yloc, zloc);
fprintf(stderr, "dx=%e, dy=%e, dz=%e\n", dx, dy, dz);
fprintf(stderr, "vz=%e, p=%e, dens=%e, tk=%e, m1=%e, m2=%e\n", vz, p, dens, tk, m1, m2);
fprintf(stderr, "m3=%e, m4=%e, v1=%e, v2=%e, v3=%e, v4=%e\n", m3, m4, v1, v2, v3, v4);*/
/********** DEBUG ************/


totalvolfrac=v1+v2+v3+v4;

if(dens > 5.0e-6)  /*If there's stuff in this cell (above Robin's density cutoff -- ACB modified 6.14.10)... write to output file*/
{
fprintf(fidout, "%e,%e,%e,%e,%e,%e,%e,%e,%e,%e,%e,%e,%e,%e,%e,%e,%e, %e\n", xloc, yloc, zloc, vx, vy, vz, p, dens, tk, m1, m2, m3, m4, v1, v2, v3, v4, totalvolfrac);
nel=nel+1;
mt=mt+(m1+m2+m3+m4);
}
 ntot=ntot+1;


}

fprintf(stderr, "number of cells written=%d\n", nel);
fprintf(stderr, "percent kept=%e\n", (nel/(1.0*ntot))*100.0);

rewind(fidout);
fprintf(fidout, "%d", nel);


fclose(fidout);
fclose(fid);

fprintf(stderr, "total mass in domain=%e (grams), total mass in domain=%e (earth masses)\n", mt, mt/Mearth);


return(0);
}

