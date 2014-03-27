//
//  esfera.cpp
//  CG-FORMAS-PRIMARIAS
//
//  Created by Hélder José Alves Gonçalves on 27/02/14.
//  Copyright (c) 2014 Hélder José Alves Gonçalves. All rights reserved.
//

#include "esfera.h"


GLuint buffer_esf[1];
unsigned int  *indices_esf;
int n_indices_esf,n_pontos_esf;
float *vertexB_esf;

void esfera(float raio, int camadas, int fatias){
    float   angulo_cir=(2*M_PI)/fatias,
            angulo_h=(M_PI)/camadas,
            x,y,l_aux,lh_aux,h_aux1,h_aux2=M_PI_2;
    
    glBegin(GL_TRIANGLES);
    
    h_aux1=h_aux2;
    h_aux2+=angulo_h;
    y=0;
    
    for (l_aux=0; l_aux<=fatias; l_aux++) {
        x=y;
        y+=angulo_cir;
        glVertex3f(sin(x)*cos(h_aux2), sin(h_aux2), cos(x)*cos(h_aux2));
        glVertex3f(sin(y)*cos(h_aux2), sin(h_aux2), cos(y)*cos(h_aux2));
        glVertex3f(sin(y)*cos(h_aux1), sin(h_aux1), cos(y)*cos(h_aux1));
    }
    
        for(lh_aux=1;lh_aux<camadas-1;lh_aux++){
            h_aux1=h_aux2;
            h_aux2+=angulo_h;
            y=0;
            
            for (l_aux=0; l_aux<=fatias; l_aux++) {
                x=y;
                y+=angulo_cir;
                glVertex3f(sin(x)*cos(h_aux1), sin(h_aux1), cos(x)*cos(h_aux1));
                glVertex3f(sin(x)*cos(h_aux2), sin(h_aux2), cos(x)*cos(h_aux2));
                glVertex3f(sin(y)*cos(h_aux1), sin(h_aux1), cos(y)*cos(h_aux1));

                glVertex3f(sin(x)*cos(h_aux2), sin(h_aux2), cos(x)*cos(h_aux2));
                glVertex3f(sin(y)*cos(h_aux2), sin(h_aux2), cos(y)*cos(h_aux2));
                glVertex3f(sin(y)*cos(h_aux1), sin(h_aux1), cos(y)*cos(h_aux1));
            }
        }
    h_aux1=h_aux2;
    h_aux2+=angulo_h;
    y=0;
    
    for (l_aux=0; l_aux<=fatias; l_aux++) {
        x=y;
        y+=angulo_cir;
        glVertex3f(sin(x)*cos(h_aux1), sin(h_aux1), cos(x)*cos(h_aux1));
        glVertex3f(sin(x)*cos(h_aux2), sin(h_aux2), cos(x)*cos(h_aux2));
        glVertex3f(sin(y)*cos(h_aux1), sin(h_aux1), cos(y)*cos(h_aux1));
    }

    glEnd();
    
}


void esferaVBO(float raio, int camadas, int fatias){
    float   angulo_cir=(2*M_PI)/fatias,
    angulo_h=(M_PI)/camadas,y=0,l_aux,h_aux=M_PI_2;
    
    int i=0,v=0,j,avanco;
    
    //Activar Buffers
    glEnableClientState(GL_VERTEX_ARRAY);
    
    n_pontos_esf=(2+fatias*(camadas-1))*3;
    n_indices_esf=(fatias*(camadas-1)*2)*3;
    
    vertexB_esf=(float*)malloc(n_pontos_esf*sizeof(float));
    indices_esf=(unsigned int*)malloc(n_indices_esf*sizeof(unsigned int));

    h_aux+=angulo_h;
    
    vertexB_esf[v++]=0;vertexB_esf[v++]=raio;vertexB_esf[v++]=0;
    for (l_aux=0; l_aux<fatias; l_aux++) {
        
        vertexB_esf[v++]=raio*sin(y)*cos(h_aux);vertexB_esf[v++]=raio*sin(h_aux);vertexB_esf[v++]=raio*cos(y)*cos(h_aux);
        
        indices_esf[i++]=0;
        indices_esf[i++]=l_aux+1;
        indices_esf[i++]=l_aux+2;
        
        y+=angulo_cir;
    }
    indices_esf[i-1]=1;
    
    for(j=1;j<camadas-1;j++){
        h_aux+=angulo_h;
        y=0;
        for (l_aux=0; l_aux<fatias; l_aux++) {
            avanco=j*fatias+1;
            
            vertexB_esf[v++]=raio*sin(y)*cos(h_aux);vertexB_esf[v++]=raio*sin(h_aux);vertexB_esf[v++]=raio*cos(y)*cos(h_aux);
            
            indices_esf[i++]=avanco-fatias+l_aux;
            indices_esf[i++]=avanco+l_aux;
            indices_esf[i++]=avanco-fatias+l_aux+1;
            
            indices_esf[i++]=avanco+l_aux;
            indices_esf[i++]=avanco+l_aux+1;
            indices_esf[i++]=avanco-fatias+l_aux+1;
           
            y+=angulo_cir;
        }
        indices_esf[i-4]=avanco-fatias;
        indices_esf[i-2]=avanco;
        indices_esf[i-1]=avanco-fatias;
    }
    
    vertexB_esf[v++]=0;vertexB_esf[v++]=-raio;vertexB_esf[v++]=0;
    for (l_aux=0; l_aux<fatias; l_aux++) {
        
        indices_esf[i++]=avanco+l_aux;
        indices_esf[i++]=avanco+fatias;
        indices_esf[i++]=avanco+l_aux+1;
    }
    indices_esf[i-1]=avanco;
    
    glGenBuffers(1, buffer_esf);
    glBindBuffer(GL_ARRAY_BUFFER,buffer_esf[0]);
    glBufferData(GL_ARRAY_BUFFER,n_pontos_esf*sizeof(float), vertexB_esf, GL_STATIC_DRAW);
    
//    printf("%d||%d -- %d||%d -- %d\n",n_indices_esf,i,n_pontos_esf,v,fatias);
    
    free(vertexB_esf);
}

void drawEsfera(){
    
    glBindBuffer(GL_ARRAY_BUFFER,buffer_esf[0]);
    glVertexPointer(3,GL_FLOAT,0,0);
    glDrawElements(GL_TRIANGLES, n_indices_esf ,GL_UNSIGNED_INT, indices_esf);
}

