//
//  circulo.cpp
//  CG-FORMAS-PRIMARIAS
//
//  Created by Hélder José Alves Gonçalves on 27/02/14.
//  Copyright (c) 2014 Hélder José Alves Gonçalves. All rights reserved.
//

#include "circulo.h"

//ORI --- 1 -> BASE && 0 -> TOPO


void circulo(float raio, int fatias,int aneis, float altura,int ori, FILE* f){
    float angulo=(2*M_PI)/fatias,x,y=0,l_aux, r_aux1,r_aux2;

    fprintf(f,"%d\n",(2*fatias*(aneis-1)+fatias)*9);
    raio=raio/aneis;
    if(ori){
        for(l_aux=0;l_aux<fatias;l_aux++){
        	x=y;
            y+=angulo;
            fprintf(f,"%d %f %d\n",0, altura, 0);
            fprintf(f,"%f %f %f\n",raio*sin(x), altura, raio*cos(x));
            fprintf(f,"%f %f %f\n",raio*sin(y), altura, raio*cos(y));
        }
        r_aux2=raio;
        y=0;
        for(aneis--;aneis>0;aneis--){
            r_aux1=r_aux2;
            r_aux2+=raio;
        
           for(l_aux=0;l_aux<fatias;l_aux++){
               x=y;
               y+=angulo;
                fprintf(f,"%f %f %f\n",r_aux1*sin(x), altura, r_aux1*cos(x));
                fprintf(f,"%f %f %f\n",r_aux2*sin(x), altura, r_aux2*cos(x));
                fprintf(f,"%f %f %f\n",r_aux1*sin(y), altura, r_aux1*cos(y));
               
                fprintf(f,"%f %f %f\n",r_aux1*sin(y), altura, r_aux1*cos(y));
                fprintf(f,"%f %f %f\n",r_aux2*sin(x), altura, r_aux2*cos(x));
                fprintf(f,"%f %f %f\n",r_aux2*sin(y), altura, r_aux2*cos(y));
            }
        }
    }else{
        for(l_aux=0;l_aux<fatias;l_aux++){
        	x=y;
            y+=angulo;
            fprintf(f,"%d %f %d\n",0, altura, 0);
            fprintf(f,"%f %f %f\n",raio*sin(y), altura, raio*cos(y));
            fprintf(f,"%f %f %f\n",raio*sin(x), altura, raio*cos(x));
        }
        r_aux2=raio;
        y=0;
        for(aneis--;aneis>0;aneis--){
            r_aux1=r_aux2;
            r_aux2+=raio;
            
            for(l_aux=0;l_aux<fatias;l_aux++){
                x=y;
                y+=angulo;
                fprintf(f,"%f %f %f\n",r_aux1*sin(x), altura, r_aux1*cos(x));
                fprintf(f,"%f %f %f\n",r_aux1*sin(y), altura, r_aux1*cos(y));
                fprintf(f,"%f %f %f\n",r_aux2*sin(x), altura, r_aux2*cos(x));
                
                fprintf(f,"%f %f %f\n",r_aux1*sin(y), altura, r_aux1*cos(y));
                fprintf(f,"%f %f %f\n",r_aux2*sin(y), altura, r_aux2*cos(y));
                fprintf(f,"%f %f %f\n",r_aux2*sin(x), altura, r_aux2*cos(x));
            }
        }
    }
}


void circuloVBO(float raio, int lados,int aneis, float altura,int ori, FILE *f){
    
    float angulo=(2*M_PI)/lados,y=0,l_aux, r_aux;
    int i=0,v=0,j=0,avanco;
    
    raio=raio/aneis;
    r_aux=raio;
    int n_pontos=(1+lados*aneis)*3;
    int n_indices=(lados*(aneis-1)*2+lados)*3;
    
    int *indices=(int*)malloc(n_indices*sizeof(int));
    float *vertexB=(float*)malloc(n_pontos*sizeof(float));

    if(ori){
        vertexB[v++]=0;vertexB[v++]=altura;vertexB[v++]=0;
        for(l_aux=0;l_aux<lados;l_aux++){
            
            vertexB[v++]=r_aux*sin(y);vertexB[v++]=altura;vertexB[v++]=r_aux*cos(y);
            
            indices[i++]=0;
            indices[i++]=l_aux+1;
            indices[i++]=l_aux+2;
            y+=angulo;
        }
        indices[i-1]=1;
        
        for(j++;j<aneis;j++){
            r_aux+=raio;
            y=0;
            for(l_aux=0;l_aux<lados;l_aux++){
                avanco=j*lados+1;
                
                vertexB[v++]=r_aux*sin(y); vertexB[v++]=altura; vertexB[v++]=r_aux*cos(y);
                
                indices[i++]=avanco-lados+l_aux;
                indices[i++]=avanco+l_aux;
                indices[i++]=avanco-lados+l_aux+1;

                indices[i++]=avanco+l_aux;
                indices[i++]=avanco+l_aux+1;
                indices[i++]=avanco-lados+l_aux+1;

                y+=angulo;
            }
            indices[i-4]=avanco-lados;
            indices[i-2]=avanco;
            indices[i-1]=avanco-lados;
        }
    }else{
        vertexB[v++]=0;vertexB[v++]=altura;vertexB[v++]=0;
        for(l_aux=0;l_aux<lados;l_aux++){
            
            vertexB[v++]=r_aux*sin(y);vertexB[v++]=altura;vertexB[v++]=r_aux*cos(y);
            
            indices[i++]=0;
            indices[i++]=l_aux+2;
            indices[i++]=l_aux+1;
            y+=angulo;
        }
        indices[i-2]=1;
        
        for(j++;j<aneis;j++){
            r_aux+=raio;
            y=0;
            for(l_aux=0;l_aux<lados;l_aux++){
                avanco=j*lados+1;
                
                vertexB[v++]=r_aux*sin(y); vertexB[v++]=altura; vertexB[v++]=r_aux*cos(y);
                
                indices[i++]=avanco-lados+l_aux;
                indices[i++]=avanco-lados+l_aux+1;
                indices[i++]=avanco+l_aux;
                
                indices[i++]=avanco+l_aux;
                indices[i++]=avanco-lados+l_aux+1;
                indices[i++]=avanco+l_aux+1;
                
                y+=angulo;
            }
            indices[i-5]=avanco-lados;
            indices[i-1]=avanco;
            indices[i-2]=avanco-lados;
        }
        
    }
    
    //Imprimir os vertices e indices
    fprintf(f, "%d\n",n_pontos);
    for(i=0;i<n_pontos;i+=3)
        fprintf(f, "%f %f %f\n",vertexB[i],vertexB[i+1],vertexB[i+2]);

    fprintf(f, "%d\n",n_indices);
    for(i=0;i<n_indices;i+=3)
        fprintf(f, "%d %d %d\n",indices[i],indices[i+1],indices[i+2]);
}

