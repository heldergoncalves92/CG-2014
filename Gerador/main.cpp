#include <string.h>
#include <stdlib.h>

#include "esfera.h"
#include "cilindro.h"
#include "plano.h"
#include "cone.h"

int main(int argc, char *argv[]){
	int i1,i2,i3;
	float p1,p2,p3;
	char* op=argv[1];
	FILE* f=NULL;

	if(strcmp(op,"esfera")==0){
		if(argc==6){

			if(sscanf(argv[2],"%f",&p1)&&sscanf(argv[3],"%d",&i1)&&sscanf(argv[4],"%d",&i2)){
				f=fopen(argv[5],"w");
				esfera(p1,i1,i2,f);
				fclose(f);

			}else
				printf("ERRO!! Parametros não estão correctos!\n");
		}
		else
			printf("ERRO!! Número de argumentos errado\n");
	}
	else
		if(strcmp(op,"cilindro")==0){
			if(argc==8){

				if(sscanf(argv[2],"%f",&p1)&&sscanf(argv[3],"%f",&p2)&&sscanf(argv[4],"%f",&p3)&&sscanf(argv[5],"%d",&i1)&&sscanf(argv[6],"%d",&i2)){
					f=fopen(argv[7],"w");
					cilindro(p1,p2,p3,i1,i2,f);
					fclose(f);

				}else
					printf("ERRO!! Parametros não estão correctos!\n");
			}
			else
				printf("ERRO!! Número de argumentos errado\n");
		}else
			if(strcmp(op,"circulo")==0){
				if(argc==6){

					if(sscanf(argv[2],"%f",&p1)&&sscanf(argv[3],"%d",&i1)&&sscanf(argv[4],"%d",&i2)&&sscanf(argv[5],"%d",&i3)){
						f=fopen(argv[5],"w");
						circulo(p1,i1,i2,0,i3,f);
						fclose(f);

					}else
						printf("ERRO!! Parametros não estão correctos!\n");
				}
				else
					printf("ERRO!! Número de argumentos errado\n");
			}else
				if(strcmp(op,"plano")==0){
					if(argc==8){

						if(sscanf(argv[2],"%f",&p1)&&sscanf(argv[3],"%f",&p2)&&sscanf(argv[4],"%d",&i1)&&sscanf(argv[5],"%d",&i2)&&sscanf(argv[6],"%d",&i3)){
							f=fopen(argv[7],"w");
							plano(p1,p2,i1,i2,0,i3,f);
							fclose(f);

						}else
							printf("ERRO!! Parametros não estão correctos!\n");
					}
					else
						printf("ERRO!! Número de argumentos errado\n");
				}
				else
					if(strcmp(op,"paralelepipedo")==0){
						if(argc==8){

							if(sscanf(argv[2],"%f",&p1)&&sscanf(argv[3],"%f",&p2)&&sscanf(argv[4],"%f",&p3)&&sscanf(argv[5],"%d",&i1)&&sscanf(argv[6],"%d",&i2)){
								f=fopen(argv[7],"w");
								plano(p1,p2,i1,i2,0,i3,f);
								fclose(f);

							}else
								printf("ERRO!! Parametros não estão correctos!\n");
						}
						else
							printf("ERRO!! Número de argumentos errado\n");
					}
					else
						if(strcmp(op,"cone")==0){
							if(argc==8){

								if(sscanf(argv[2],"%f",&p1) && sscanf(argv[3],"%f",&p2) && sscanf(argv[4],"%d",&i1) && sscanf(argv[5],"%d",&i2) && sscanf(argv[6],"%d",&i3)){
									f=fopen(argv[7],"w");
									cone(p1,p2,i1,i2,i3,f);
									fclose(f);

								}else
									printf("ERRO!! Parametros não estão correctos!\n");
							}
							else
								printf("ERRO!! Número de argumentos errado\n");
						}
		

}