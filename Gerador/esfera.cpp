//
//  esfera.cpp
//  CG-FORMAS-PRIMARIAS
//
//  Created by Hélder José Alves Gonçalves on 27/02/14.
//  Copyright (c) 2014 Hélder José Alves Gonçalves. All rights reserved.
//

#include "esfera.h"

void esfera(float raio, int camadas, int fatias, FILE* f){
    float   angulo_cir=(2*M_PI)/fatias,
            angulo_h=(M_PI)/camadas,
            x,y,l_aux,lh_aux,h_aux1,h_aux2=M_PI_2;
    
    h_aux1=h_aux2;
    h_aux2+=angulo_h;
    y=0;
    
    fprintf(f,"%d\n",2*fatias*(camadas-1)*9);

    for (l_aux=0; l_aux<fatias; l_aux++) {
        x=y;
        y+=angulo_cir;
        fprintf(f,"%f %f %f\n",raio*sin(x)*cos(h_aux2), raio*sin(h_aux2), raio*cos(x)*cos(h_aux2));
        fprintf(f,"%f %f %f\n",raio*sin(y)*cos(h_aux2), raio*sin(h_aux2), raio*cos(y)*cos(h_aux2));
        fprintf(f,"%f %f %f\n",raio*sin(y)*cos(h_aux1), raio*sin(h_aux1), raio*cos(y)*cos(h_aux1));
    }
    
    for(lh_aux=1;lh_aux<camadas-1;lh_aux++){
        h_aux1=h_aux2;
        h_aux2+=angulo_h;
        y=0;
        
        for (l_aux=0; l_aux<fatias; l_aux++) {
            x=y;
            y+=angulo_cir;
            fprintf(f,"%f %f %f\n",raio*sin(x)*cos(h_aux1), raio*sin(h_aux1), raio*cos(x)*cos(h_aux1));
            fprintf(f,"%f %f %f\n",raio*sin(x)*cos(h_aux2), raio*sin(h_aux2), raio*cos(x)*cos(h_aux2));
            fprintf(f,"%f %f %f\n",raio*sin(y)*cos(h_aux1), raio*sin(h_aux1), raio*cos(y)*cos(h_aux1));

            fprintf(f,"%f %f %f\n",raio*sin(x)*cos(h_aux2), raio*sin(h_aux2), raio*cos(x)*cos(h_aux2));
            fprintf(f,"%f %f %f\n",raio*sin(y)*cos(h_aux2), raio*sin(h_aux2), raio*cos(y)*cos(h_aux2));
            fprintf(f,"%f %f %f\n",raio*sin(y)*cos(h_aux1), raio*sin(h_aux1), raio*cos(y)*cos(h_aux1));
        }
    }
    h_aux1=h_aux2;
    h_aux2+=angulo_h;
    y=0;
    
    for (l_aux=0; l_aux<fatias; l_aux++) {
        x=y;
        y+=angulo_cir;
        fprintf(f,"%f %f %f\n",raio*sin(x)*cos(h_aux1), raio*sin(h_aux1), raio*cos(x)*cos(h_aux1));
        fprintf(f,"%f %f %f\n",raio*sin(x)*cos(h_aux2), raio*sin(h_aux2), raio*cos(x)*cos(h_aux2));
        fprintf(f,"%f %f %f\n",raio*sin(y)*cos(h_aux1), raio*sin(h_aux1), raio*cos(y)*cos(h_aux1));
    }
   
}

void esferaVBO(float raio, int camadas, int fatias,FILE* f){
    float   angulo_cir=(2*M_PI)/fatias,
    angulo_h=(M_PI)/camadas,y=0,l_aux,h_aux=M_PI_2;
    
    int i=0,v=0,j,avanco;
    
    int n_pontos=(2+fatias*(camadas-1))*3;
    int n_indices=(fatias*(camadas-1)*2)*3;
    
    float *vertexB=(float*)malloc(n_pontos*sizeof(float));
    int *indices=(int*)malloc(n_indices*sizeof(int));

    h_aux+=angulo_h;
    
    vertexB[v++]=0;vertexB[v++]=raio;vertexB[v++]=0;
    for (l_aux=0; l_aux<fatias; l_aux++) {
        
        vertexB[v++]=raio*sin(y)*cos(h_aux);vertexB[v++]=raio*sin(h_aux);vertexB[v++]=raio*cos(y)*cos(h_aux);
        
        indices[i++]=0;
        indices[i++]=l_aux+1;
        indices[i++]=l_aux+2;
        
        y+=angulo_cir;
    }
    indices[i-1]=1;
    
    for(j=1;j<camadas-1;j++){
        h_aux+=angulo_h;
        y=0;
        for (l_aux=0; l_aux<fatias; l_aux++) {
            avanco=j*fatias+1;
            
            vertexB[v++]=raio*sin(y)*cos(h_aux);vertexB[v++]=raio*sin(h_aux);vertexB[v++]=raio*cos(y)*cos(h_aux);
            
            indices[i++]=avanco-fatias+l_aux;
            indices[i++]=avanco+l_aux;
            indices[i++]=avanco-fatias+l_aux+1;
            
            indices[i++]=avanco+l_aux;
            indices[i++]=avanco+l_aux+1;
            indices[i++]=avanco-fatias+l_aux+1;
           
            y+=angulo_cir;
        }
        indices[i-4]=avanco-fatias;
        indices[i-2]=avanco;
        indices[i-1]=avanco-fatias;
    }
    
    vertexB[v++]=0;vertexB[v++]=-raio;vertexB[v++]=0;
    for (l_aux=0; l_aux<fatias; l_aux++) {
        
        indices[i++]=avanco+l_aux;
        indices[i++]=avanco+fatias;
        indices[i++]=avanco+l_aux+1;
    }
    indices[i-1]=avanco;
 

    //Imprimir os vertices e indices
    fprintf(f, "%d\n",n_pontos);
    for(i=0;i<n_pontos;i+=3)
        fprintf(f, "%f %f %f\n",vertexB[i],vertexB[i+1],vertexB[i+2]);

    fprintf(f, "%d\n",n_indices);
    for(i=0;i<n_indices;i+=3)
        fprintf(f, "%d %d %d\n",indices[i],indices[i+1],indices[i+2]);   
}

