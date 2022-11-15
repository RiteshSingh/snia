#include <stdio.h>

struct valerrstruct{
	float val;
	float err;
};

typedef struct valerrstruct valerr;

int main() {
	FILE *f,*fwf,*fe;
	int sr0,sr,c,i,j,n,totc,totpair=0,ngalmultiple,flag,res[1000];//,d=0;
	valerr a[1000];
	float sum,diff,totsum=0,toterr;
	
	f=fopen("ned.txt","r");
	//fw=fopen("res.txt","w");
	fwf=fopen("finalres.txt","a");
	fe=fopen("errraw.txt","w");
	
	fscanf(f,"%d",&sr);
	c=1;
	fscanf(f,"%f%f",&a[0].val,&a[0].err);
	sr0=sr;
	
	toterr=a[0].err/a[0].val;
	totc=1;
	
	fprintf(fe,"%f\n",toterr);
	
	//ngal=1;
	ngalmultiple=0;
	flag=1;
	
	for(i=0;i<1000;i++) res[i]=0;
	
	while(sr0<147440) {
		fscanf(f,"%d",&sr);
		if(sr==sr0) {
			c++;
			fscanf(f,"%f%f",&a[c-1].val,&a[c-1].err);
			
			totc++;
			toterr+=a[c-1].err/a[0].val;
			
			//err=a[c-1].err/a[0].val;
			fprintf(fe,"%f\n",a[c-1].err/a[0].val);
			
			if(flag) {
				ngalmultiple++;
				flag=0;
			}
		} else {			
			for(i=0,sum=0,n=0;i<c-1;i++)
				for(j=i+1;j<c;j++) {
					diff = a[i].val-a[j].val;
					if(diff) {
						if(diff<0) diff=-1*diff;
						sum+=diff/a[j].err+diff/a[i].err;
						n+=2;
						res[(int)(diff/a[j].err)]++;
						res[(int)(diff/a[i].err)]++;
					} //else d++;
				}
					
			if(n) {
				totpair+=n;
				totsum+=sum;
			}
			
			sr0=sr;
			
			if(c==1){
				totc--;
				toterr-=a[c-1].err/a[0].val;
				
				fprintf(fe,"0\n",a[c-1].err/a[0].val);
			}
			
			if(sr<147440){			
				//ngal++;
				flag=1;	
				
				c=1;
				fscanf(f,"%f%f",&a[0].val,&a[0].err);
				totc++;
				toterr+=a[c-1].err/a[0].val;
				
				fprintf(fe,"%f\n",a[c-1].err/a[0].val);
			}
		}
	}
	
	//for(i=0;i<1000;i++) fprintf(fw,"%d\n",res[i]);
	
	//printf("NUM OF GALAXIES: %d\n",ngal);
	
	if(totc) printf("ERR: %f\n",(toterr/totc)*100);
	
	printf("NUMVAL: %d\n",totc);
	
	if(totpair) printf("AVG: %f\nPAIRS: %d\n",totsum/totpair,totpair);
	
	printf("NUMGAL: %d\n",ngalmultiple);
	
	printf("%f\n%f\n%f\n",res[0]*100.0/totpair,res[1]*100.0/totpair,100-res[0]*100.0/totpair-res[1]*100.0/totpair);
	
	fprintf(fwf,"%f\t%d\t%f\t%d\t%d\t%f\t%f\t%f\n",(toterr/totc)*100,totc,totsum/totpair,totpair,ngalmultiple,res[0]*100.0/totpair,res[1]*100.0/totpair,100-res[0]*100.0/totpair-res[1]*100.0/totpair);
	
	//printf("\nd=%d\n",d);
	
	//fclose(fw);
	fclose(f);
	fclose(fwf);
	fclose(fe);
}
