//
//  plano.cpp
//  CG-FORMAS-PRIMARIAS
//
//  Created by Hélder José Alves Gonçalves on 28/02/14.
//  Copyright (c) 2014 Hélder José Alves Gonçalves. All rights reserved.
//

#include "plano.h"

/* Tipos de planos
 1 -> +XoY
 2 -> -XoY
 
 3 -> +ZoY
 4 -> -ZoY
 
 5 -> +ZoX
 6 -> -ZoX
 
*/

void plano(float altura, float lado, int camadas, int fatias, float z_index, int ori, FILE* f, int flag){
    int i;
    float l_const=lado/fatias, alt_const=altura/camadas,alt_ori=-altura/2,lado_ori=-lado/2;

    if (flag==1) fprintf(f,"%d\n",2*camadas*fatias*9);
    
    switch (ori) {
        case 1:
            for(altura=alt_ori;camadas>0;camadas--){
                i=0;
                for(lado=lado_ori;i<fatias;i++){
                    
                    fprintf(f,"%f %f %f\n",lado,altura, z_index);
                    fprintf(f,"%f %f %f\n",lado+l_const,altura, z_index);
                    fprintf(f,"%f %f %f\n",lado,altura+alt_const, z_index);
            
                    fprintf(f,"%f %f %f\n",lado+l_const,altura, z_index);
                    fprintf(f,"%f %f %f\n",lado+l_const,altura+alt_const, z_index);
                    fprintf(f,"%f %f %f\n",lado,altura+alt_const, z_index);
                    lado+=l_const;
                }
                altura+=alt_const;
            }
            break;
        case 2:
            for(altura=alt_ori;camadas>0;camadas--){
                i=0;
                for(lado=lado_ori;i<fatias;i++){
                    
                    fprintf(f,"%f %f %f\n",lado,altura, z_index);
                    fprintf(f,"%f %f %f\n",lado,altura+alt_const, z_index);
                    fprintf(f,"%f %f %f\n",lado+l_const,altura, z_index);
                    
                    fprintf(f,"%f %f %f\n",lado+l_const,altura, z_index);
                    fprintf(f,"%f %f %f\n",lado,altura+alt_const, z_index);
                    fprintf(f,"%f %f %f\n",lado+l_const,altura+alt_const, z_index);
                    lado+=l_const;
                }
                altura+=alt_const;
            }
            break;
        case 3:
            for(altura=alt_ori;camadas>0;camadas--){
                i=0;
                for(lado=lado_ori;i<fatias;i++){
                    
                    fprintf(f,"%f %f %f\n",z_index,altura, lado);
                    fprintf(f,"%f %f %f\n",z_index,altura+alt_const, lado);
                    fprintf(f,"%f %f %f\n",z_index,altura, lado+l_const);
                    
                    fprintf(f,"%f %f %f\n",z_index,altura, lado+l_const);
                    fprintf(f,"%f %f %f\n",z_index,altura+alt_const, lado);
                    fprintf(f,"%f %f %f\n",z_index,altura+alt_const, lado+l_const);
                    lado+=l_const;
                }
                altura+=alt_const;
            }
            break;
        case 4:
            for(altura=alt_ori;camadas>0;camadas--){
                i=0;
                for(lado=lado_ori;i<fatias;i++){
                    
                    fprintf(f,"%f %f %f\n",z_index,altura, lado);
                    fprintf(f,"%f %f %f\n",z_index,altura, lado+l_const);
                    fprintf(f,"%f %f %f\n",z_index,altura+alt_const, lado);
                    
                    fprintf(f,"%f %f %f\n",z_index,altura,lado+l_const);
                    fprintf(f,"%f %f %f\n",z_index,altura+alt_const, lado+l_const);
                    fprintf(f,"%f %f %f\n",z_index,altura+alt_const, lado);
                    lado+=l_const;
                }
                altura+=alt_const;
            }
            break;
        case 5:
            for(altura=alt_ori;camadas>0;camadas--){
                i=0;
                for(lado=lado_ori;i<fatias;i++){
                    
                    fprintf(f,"%f %f %f\n",altura,z_index, lado);
                    fprintf(f,"%f %f %f\n",altura,z_index, lado+l_const);
                    fprintf(f,"%f %f %f\n",altura+alt_const,z_index, lado);
                    
                    fprintf(f,"%f %f %f\n",altura,z_index,lado+l_const);
                    fprintf(f,"%f %f %f\n",altura+alt_const,z_index, lado+l_const);
                    fprintf(f,"%f %f %f\n",altura+alt_const,z_index, lado);
                    lado+=l_const;
                }
                altura+=alt_const;
            }
            break;
        case 6:
            for(altura=alt_ori;camadas>0;camadas--){
                i=0;
                for(lado=lado_ori;i<fatias;i++){
                    
                    fprintf(f,"%f %f %f\n",altura,z_index, lado);
                    fprintf(f,"%f %f %f\n",altura+alt_const,z_index, lado);
                    fprintf(f,"%f %f %f\n",altura,z_index, lado+l_const);
                    
                    fprintf(f,"%f %f %f\n",altura,z_index, lado+l_const);
                    fprintf(f,"%f %f %f\n",altura+alt_const,z_index, lado);
                    fprintf(f,"%f %f %f\n",altura+alt_const,z_index, lado+l_const);
                    lado+=l_const;
                }
                altura+=alt_const;
            }
            break;
            
        default:
            break;
    }
}


void planoVBO(float altura, float lado, int camadas, int fatias, float z_index, int ori, FILE *f){
    int k=0,j=0,v=0, i=0, avanco;
    float l_const=lado/fatias, alt_const=altura/camadas,alt_ori=-altura/2,lado_ori=-lado/2;
    
    
    int n_pontos=(fatias+1)*(camadas+1)*3;
    int n_indices=(2*fatias*camadas)*3;
    
    float *vertexB=(float*)malloc(n_pontos*sizeof(float));
    int* indices=(int*)malloc(n_indices*sizeof(int));
    
    switch (ori) {
        case 1:
            for(altura=alt_ori;j<=camadas;j++){
                k=0;
                avanco=j*(fatias+1);
                for(lado=lado_ori;k<=fatias;k++){
                    //Inserir Ponto
                    vertexB[v++]=lado;vertexB[v++]=altura;vertexB[v++]=z_index;
                    if(k!=fatias && j!=camadas){
                        indices[i++]=avanco+k;
                        indices[i++]=avanco+k+1;
                        indices[i++]=avanco+fatias+1+k;
                        
                        indices[i++]=avanco+k+1;
                        indices[i++]=avanco+fatias+1+k+1;
                        indices[i++]=avanco+fatias+1+k;
                    }
                    lado+=l_const;
                }
                altura+=alt_const;
            }
            break;
        case 2:
            for(altura=alt_ori;j<=camadas;j++){
                k=0;
                avanco=j*(fatias+1);
                for(lado=lado_ori;k<=fatias;k++){
                    //Inserir Ponto
                    vertexB[v++]=lado;vertexB[v++]=altura;vertexB[v++]=z_index;
                    if(k!=fatias && j!=camadas){
                        indices[i++]=avanco+k;
                        indices[i++]=avanco+fatias+1+k;
                        indices[i++]=avanco+k+1;
                        
                        indices[i++]=avanco+k+1;
                        indices[i++]=avanco+fatias+1+k;
                        indices[i++]=avanco+fatias+1+k+1;
                    }
                    lado+=l_const;
                }
                altura+=alt_const;
            }
            break;
        
        case 3:
            for(altura=alt_ori;j<=camadas;j++){
                k=0;
                avanco=j*(fatias+1);
                for(lado=lado_ori;k<=fatias;k++){
                    //Inserir Ponto
                    vertexB[v++]=z_index;vertexB[v++]=altura;vertexB[v++]=lado;
                    if(k!=fatias && j!=camadas){
                        indices[i++]=avanco+k;
                        indices[i++]=avanco+fatias+1+k;
                        indices[i++]=avanco+k+1;
                        
                        indices[i++]=avanco+k+1;
                        indices[i++]=avanco+fatias+1+k;
                        indices[i++]=avanco+fatias+1+k+1;
                    }
                    lado+=l_const;
                }
                altura+=alt_const;
            }
            break;
        case 4:
            for(altura=alt_ori;j<=camadas;j++){
                k=0;
                avanco=j*(fatias+1);
                for(lado=lado_ori;k<=fatias;k++){
                    //Inserir Ponto
                    vertexB[v++]=z_index;vertexB[v++]=altura;vertexB[v++]=lado;
                    if(k!=fatias && j!=camadas){
                        indices[i++]=avanco+k;
                        indices[i++]=avanco+k+1;
                        indices[i++]=avanco+fatias+1+k;
                        
                        indices[i++]=avanco+k+1;
                        indices[i++]=avanco+fatias+1+k+1;
                        indices[i++]=avanco+fatias+1+k;
                    }
                    lado+=l_const;
                }
                altura+=alt_const;
            }
            break;
        case 5:
            for(altura=alt_ori;j<=camadas;j++){
                k=0;
                avanco=j*(fatias+1);
                for(lado=lado_ori;k<=fatias;k++){
                    //Inserir Ponto
                    vertexB[v++]=altura;vertexB[v++]=z_index;vertexB[v++]=lado;
                    if(k!=fatias && j!=camadas){
                        indices[i++]=avanco+k;
                        indices[i++]=avanco+k+1;
                        indices[i++]=avanco+fatias+1+k;
                        
                        indices[i++]=avanco+k+1;
                        indices[i++]=avanco+fatias+1+k+1;
                        indices[i++]=avanco+fatias+1+k;
                    }
                    lado+=l_const;
                }
                altura+=alt_const;
            }
            break;
        case 6:
            for(altura=alt_ori;j<=camadas;j++){
                k=0;
                avanco=j*(fatias+1);
                for(lado=lado_ori;k<=fatias;k++){
                    //Inserir Ponto
                    vertexB[v++]=altura;vertexB[v++]=z_index;vertexB[v++]=lado;
                    if(k!=fatias && j!=camadas){
                        indices[i++]=avanco+k;
                        indices[i++]=avanco+fatias+1+k;
                        indices[i++]=avanco+k+1;
                        
                        indices[i++]=avanco+k+1;
                        indices[i++]=avanco+fatias+1+k;
                        indices[i++]=avanco+fatias+1+k+1;
                    }
                    lado+=l_const;
                }
                altura+=alt_const;
            }
            break;

        
    }
    
    //Imprimir os vertices e indices
    fprintf(f, "%d\n",n_pontos);
    for(i=0;i<n_pontos;i+=3)
        fprintf(f, "%f %f %f\n",vertexB[i],vertexB[i+1],vertexB[i+2]);

    fprintf(f, "%d\n",n_indices);
    for(i=0;i<n_indices;i+=3)
        fprintf(f, "%d %d %d\n",indices[i],indices[i+1],indices[i+2]); 

}


