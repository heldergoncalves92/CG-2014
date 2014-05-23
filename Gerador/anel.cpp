//
//  anel.cpp
//  CG-FORMAS-PRIMARIAS
//
//  Created by Hélder José Alves Gonçalves on 23/04/14.
//  Copyright (c) 2014 Hélder José Alves Gonçalves. All rights reserved.
//

#include "anel.h"

//ORI --- 1 -> BASE && 0 -> TOPO

// Anel para o modo imediato
void anel(float raio_fora, float raio_dentro,int fatias, int aneis, int ori, FILE* f){
    float angulo=(2*M_PI)/fatias,x,y=0,l_aux,raio=(raio_fora-raio_dentro)/aneis,alt=0;
    
    //Imprime o número de pontos que vão ser utilizados
    fprintf(f,"%d\n",2*fatias*(aneis)*9);
    raio_fora=raio_dentro;
    if(ori){
        for(;aneis>0;aneis--){
            raio_dentro=raio_fora;
            raio_fora+=raio;
            
            for(l_aux=0;l_aux<fatias;l_aux++){
                x=y;
                y+=angulo;
                fprintf(f,"%f %f %f\n",raio_dentro*sin(x), alt, raio_dentro*cos(x));
                fprintf(f,"%f %f %f\n",raio_fora*sin(x), alt, raio_fora*cos(x));
                fprintf(f,"%f %f %f\n",raio_dentro*sin(y), alt, raio_dentro*cos(y));
                
                fprintf(f,"%f %f %f\n",raio_dentro*sin(y), alt, raio_dentro*cos(y));
                fprintf(f,"%f %f %f\n",raio_fora*sin(x), alt, raio_fora*cos(x));
                fprintf(f,"%f %f %f\n",raio_fora*sin(y), alt, raio_fora*cos(y));
            }
        }
    }else{
        for(;aneis>0;aneis--){
            raio_dentro=raio_fora;
            raio_fora+=raio;
            
            for(l_aux=0;l_aux<fatias;l_aux++){
                x=y;
                y+=angulo;
                fprintf(f,"%f %f %f\n",raio_dentro*sin(x), alt, raio_dentro*cos(x));
                fprintf(f,"%f %f %f\n",raio_dentro*sin(y), alt, raio_dentro*cos(y));
                fprintf(f,"%f %f %f\n",raio_fora*sin(x), alt, raio_fora*cos(x));
                
                fprintf(f,"%f %f %f\n",raio_dentro*sin(y), alt, raio_dentro*cos(y));
                fprintf(f,"%f %f %f\n",raio_fora*sin(y), alt, raio_fora*cos(y));
                fprintf(f,"%f %f %f\n",raio_fora*sin(x), alt, raio_fora*cos(x));
            }
        }
    }
}

// Anel para as vbo's
void anelVBO(float raio_fora, float raio_dentro, int fatias, int aneis, int ori, FILE* f){
    
    float angulo=(2*M_PI)/fatias,y=0,l_aux,raio=(raio_fora-raio_dentro)/aneis;
    int i=0,v=0,n=0,j,avanco;
    
    int n_pontos=(fatias*(aneis+1))*3;
    int n_indices=6*fatias*aneis;
    
    //Alocação de memória para os respectivos arrays
    int *indices=(int*)malloc(n_indices*sizeof(int));
    float   *vertexB=(float*)malloc(n_pontos*sizeof(float)),
            *normalB=(float*)malloc(n_pontos*sizeof(float));
    
    
    if(ori){
        //Pontos interiores
        for (j=0; j<fatias; j++) {
            vertexB[v++]=raio_dentro*sin(y); vertexB[v++]=0; vertexB[v++]=raio_dentro*cos(y);
            normalB[n++]=0;normalB[n++]=1;normalB[n++]=0;
            y+=angulo;
        }
        
        //Pontos dos aneis exteriores
        for(j=1;j<=aneis;j++){
            raio_dentro+=raio;
            y=0;
            for(l_aux=0;l_aux<fatias;l_aux++){
                avanco=j*fatias;
                
                vertexB[v++]=raio_dentro*sin(y); vertexB[v++]=0; vertexB[v++]=raio_dentro*cos(y);
                normalB[n++]=0;normalB[n++]=1;normalB[n++]=0;

                indices[i++]=avanco-fatias+l_aux;
                indices[i++]=avanco+l_aux;
                indices[i++]=avanco-fatias+l_aux+1;
                
                indices[i++]=avanco+l_aux;
                indices[i++]=avanco+l_aux+1;
                indices[i++]=avanco-fatias+l_aux+1;
                
                y+=angulo;
            }
            indices[i-4]=avanco-fatias;
            indices[i-2]=avanco;
            indices[i-1]=avanco-fatias;
        }
    }else{
        //Pontos interiores
        for (j=0; j<fatias; j++) {
            vertexB[v++]=raio_dentro*sin(y); vertexB[v++]=0; vertexB[v++]=raio_dentro*cos(y);
            normalB[n++]=0;normalB[n++]=-1;normalB[n++]=0;
            y+=angulo;
        }
        
        //Pontos dos aneis exteriores
        for(j=1;j<=aneis;j++){
            raio_dentro+=raio;
            y=0;
            for(l_aux=0;l_aux<fatias;l_aux++){
                avanco=j*fatias;
                
                vertexB[v++]=raio_dentro*sin(y); vertexB[v++]=0; vertexB[v++]=raio_dentro*cos(y);
                normalB[n++]=0;normalB[n++]=-1;normalB[n++]=0;
                
                indices[i++]=avanco-fatias+l_aux;
                indices[i++]=avanco-fatias+l_aux+1;
                indices[i++]=avanco+l_aux;
                
                indices[i++]=avanco+l_aux;
                indices[i++]=avanco-fatias+l_aux+1;
                indices[i++]=avanco+l_aux+1;
                
                y+=angulo;
            }
            indices[i-5]=avanco-fatias;
            indices[i-1]=avanco;
            indices[i-2]=avanco-fatias;
        }
    }
 
   //Imprimir os vertices, indices e normais
    fprintf(f, "%d\n",n_pontos);
    for(i=0;i<n_pontos;i+=3)
        fprintf(f, "%f %f %f\n",vertexB[i],vertexB[i+1],vertexB[i+2]);

    fprintf(f, "%d\n",n_indices);
    for(i=0;i<n_indices;i+=3)
        fprintf(f, "%d %d %d\n",indices[i],indices[i+1],indices[i+2]);   

    for(i=0;i<n_pontos;i+=3)
        fprintf(f, "%f %f %f\n",normalB[i],normalB[i+1],normalB[i+2]);

}



