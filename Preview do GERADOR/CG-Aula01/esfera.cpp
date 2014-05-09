//
//  esfera.cpp
//  CG-FORMAS-PRIMARIAS
//
//  Created by Hélder José Alves Gonçalves on 27/02/14.
//  Copyright (c) 2014 Hélder José Alves Gonçalves. All rights reserved.
//

#include "esfera.h"



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


Esfera::Esfera(float raio, int camadas, int fatias){
    float   angulo_cir=(2*M_PI)/fatias,
    angulo_h=(M_PI)/camadas,y=0,l_aux,h_aux=M_PI_2;
    
    int i=0,v=0,j,n=0,avanco;
    
    //Activar Buffers
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    
    int n_pontos=(2+fatias*(camadas-1))*3;
    n_indices=(fatias*(camadas-1)*2)*3;
    
    float *vertexB=(float*)malloc(n_pontos*sizeof(float)),
    *normalB=(float*)malloc(n_pontos*sizeof(float));
    indices=(unsigned int*)malloc(n_indices*sizeof(unsigned int));

    h_aux+=angulo_h;
    
    vertexB[v++]=0;vertexB[v++]=raio;vertexB[v++]=0;
    normalB[n++]=0;normalB[n++]=1;normalB[n++]=0;
    for (l_aux=0; l_aux<fatias; l_aux++) {
        
        vertexB[v++]=raio*sin(y)*cos(h_aux);vertexB[v++]=raio*sin(h_aux);vertexB[v++]=raio*cos(y)*cos(h_aux);
        normalB[n++]=sin(y)*cos(h_aux);normalB[n++]=sin(h_aux);normalB[n++]=cos(y)*cos(h_aux);
        
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
            normalB[n++]=sin(y)*cos(h_aux);normalB[n++]=sin(h_aux);normalB[n++]=cos(y)*cos(h_aux);
            
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
    normalB[n++]=0;normalB[n++]=-1;normalB[n++]=0;
    for (l_aux=0; l_aux<fatias; l_aux++) {
        
        indices[i++]=avanco+l_aux;
        indices[i++]=avanco+fatias;
        indices[i++]=avanco+l_aux+1;
    }
    indices[i-1]=avanco;
    
    glGenBuffers(1, buffers);
    glBindBuffer(GL_ARRAY_BUFFER,buffers[0]);
    glBufferData(GL_ARRAY_BUFFER,n_pontos*sizeof(float), vertexB, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER,buffers[1]);
    glBufferData(GL_ARRAY_BUFFER,n_pontos*sizeof(float), normalB, GL_STATIC_DRAW);
    
//    printf("%d||%d -- %d||%d -- %d\n",n_indices,i,n_pontos,v,fatias);
    
    free(vertexB);
    free(normalB);
}

void Esfera::desenha(){
    
    glBindBuffer(GL_ARRAY_BUFFER,buffers[0]);
    glVertexPointer(3,GL_FLOAT,0,0);
    glBindBuffer(GL_ARRAY_BUFFER,buffers[1]);
    glNormalPointer(GL_FLOAT,0,0);
    glDrawElements(GL_TRIANGLES, n_indices ,GL_UNSIGNED_INT, indices);
}

