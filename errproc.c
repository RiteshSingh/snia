#include <stdio.h>

#define NLIN 9387

int main(){
	FILE *fep,*fe1,*fe2;
	float f1,f2;
	int i;
	fep=fopen("errproc.txt","w");
	fe2=fopen("errraw.txt","r");
	fe1=fopen("errraw.txt","r");
	
	fscanf(fe2,"%f",&f2);
	
	for(i=0;i<NLIN;i++){
		fscanf(fe2,"%f",&f2);
		fscanf(fe1,"%f",&f1);
		if(f2) {
			fprintf(fep,"%f\n",f1);
		} else {
			fscanf(fe2,"%f",&f2);
			fscanf(fe1,"%f",&f1);
			i++;
		}
	}
	
	fclose(fep);
	fclose(fe1);
	fclose(fe2);
	return 0;
}
