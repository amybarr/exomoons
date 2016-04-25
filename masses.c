#include <stdlib.h>
#include <stdio.h>
#include <math.h>


int argc;
char **argv;

int main (int argc, char **argv) {
int nel, ntot;
char filename1[255], firstletter[256];
FILE * fid;
float mt, miron, mdunite;

if (argc !=2) {
	printf("Usage: masses filename\n");
	exit(0);
	}


sprintf(filename1, "%s", argv[1]);

printf("input filename=%s\n", filename1);

fid=fopen(filename1, "r");


if (fid == NULL){
	printf("(Input file not found):\n");
	printf("%s\n", filename1);
	exit(0);
	}

rewind(fid);

fgets(firstletter, 255, fid);

float xloc, yloc, zloc, vx, vy, vz, p, dens, tk, m1, m2, m3, m4, v1, v2, v3, v4;

nel=0;
ntot=0;
mt=0.0;
miron=0.0;
mdunite=0.0;


while(feof(fid) == 0) {

fgets(firstletter, 255, fid);
sscanf(firstletter, "%e%e%e%e%e%e%e%e%e%e%e%e%e%e%e%e%e", &xloc, &yloc, &zloc, &vx, &vy, &vz, &p, &dens, &tk, &m1, &m2, &m3, &m4, &v1, &v2, &v3, &v4);

mt=mt+(m1+m2+m3+m4);
miron=miron+(m2+m4);
mdunite=mdunite+(m1+m3);
}
fclose(fid);

printf("%e,%e,%e,%e\n", mt, miron, mdunite, miron/mt);


return(0);
}

