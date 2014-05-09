//
//  cone.cpp
//  CG-FORMAS-PRIMARIAS
//
//  Created by Hélder José Alves Gonçalves on 10/03/14.
//  Copyright (c) 2014 Hélder José Alves Gonçalves. All rights reserved.
//

#include "cone.h"

Cone::Cone(float raio, float altura, int fatias, int aneis, int camadas){
    
    float angulo=(2*M_PI)/fatias,y=0,l_aux, r_aux,factor_h=(raio/camadas),alt_aux=0;
    int i=0,v=0,j=0,n=0,avanco=0;
    
    altura/=camadas;
    raio=raio/aneis;
    r_aux=raio;
    int n_pontos=((1+fatias*aneis)*3)  + ((camadas)*fatias+1)*3;
    n_indices=(fatias*(aneis-1)*2+fatias)*3  +(fatias*(camadas)*2+fatias)*3;
    
    
    indices=(unsigned short*)malloc(n_indices*sizeof(unsigned short));
    float *vertexB=(float*)malloc(n_pontos*sizeof(float)),
    *normalB=(float*)malloc(n_pontos*sizeof(float));
    
    //Activar Buffers
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);

    
    //Base do cone
    vertexB[v++]=0;vertexB[v++]=0;vertexB[v++]=0;
    normalB[n++]=0;normalB[n++]=-1;normalB[n++]=0;
    for(l_aux=0;l_aux<fatias;l_aux++){
        
        vertexB[v++]=r_aux*sin(y);vertexB[v++]=0;vertexB[v++]=r_aux*cos(y);
        normalB[n++]=0;normalB[n++]=-1;normalB[n++]=0;
        
        indices[i++]=0;
        indices[i++]=l_aux+2;
        indices[i++]=l_aux+1;
        y+=angulo;
    }
    indices[i-2]=1;
    avanco+=fatias+1;

    for(j=1;j<aneis;j++){
        r_aux+=raio;
        y=0;
        for(l_aux=0;l_aux<fatias;l_aux++){
            
            vertexB[v++]=r_aux*sin(y); vertexB[v++]=0; vertexB[v++]=r_aux*cos(y);
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
        avanco+=fatias;
    }
    //Corpo
    //raio*=factor_h;
    for(j=0;j<camadas;j++){

        y=0;
        for(l_aux=0;l_aux<fatias;l_aux++){
            
            vertexB[v++]=r_aux*sin(y); vertexB[v++]=alt_aux; vertexB[v++]=r_aux*cos(y);
            normalB[n++]=sin(y);normalB[n++]=1;normalB[n++]=cos(y);//Coordenada y está errada
            
            if(j!=camadas){
                indices[i++]=avanco-fatias+l_aux;
                indices[i++]=avanco-fatias+l_aux+1;
                indices[i++]=avanco+l_aux;
                
                indices[i++]=avanco+l_aux;
                indices[i++]=avanco-fatias+l_aux+1;
                indices[i++]=avanco+l_aux+1;
            }
            
            y+=angulo;
        }
        if(j!=camadas){
            indices[i-5]=avanco-fatias;
            indices[i-1]=avanco;
            indices[i-2]=avanco-fatias;
        }
        alt_aux+=altura;
        r_aux-=factor_h;
        avanco+=fatias;
    }
    
    vertexB[v++]=0;vertexB[v++]=alt_aux;vertexB[v++]=0;
    normalB[n++]=sin(y);normalB[n++]=1;normalB[n++]=cos(y);//Coordenada y está errada
    for(l_aux=0;l_aux<fatias;l_aux++){
        
        
        indices[i++]=avanco;
        indices[i++]=avanco-fatias+l_aux;
        indices[i++]=avanco-fatias+l_aux+1;
        y+=angulo;
    }
    indices[i-1]=avanco-fatias;
    
    

    
    glGenBuffers(1, buffers);
    glBindBuffer(GL_ARRAY_BUFFER,buffers[0]);
    glBufferData(GL_ARRAY_BUFFER,n_pontos*sizeof(float), vertexB, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER,buffers[1]);
    glBufferData(GL_ARRAY_BUFFER,n_pontos*sizeof(float), normalB, GL_STATIC_DRAW);
    
    printf("Indices: %d||%d --Pontos: %d||%d -- %d\n",n_indices,i,n_pontos,v,fatias);
    
    free(vertexB);
    free(normalB);
    
}

void Cone::desenha(){
    glBindBuffer(GL_ARRAY_BUFFER,buffers[0]);
    glVertexPointer(3,GL_FLOAT,0,0);
    glBindBuffer(GL_ARRAY_BUFFER,buffers[1]);
    glNormalPointer(GL_FLOAT,0,0);
    glDrawElements(GL_TRIANGLES, n_indices ,GL_UNSIGNED_SHORT, indices);

    
}


void cone(float raio_base, float altura, int lados, int sep_circulo, int sep_h){
    float angulo=(2*M_PI)/lados,x,y=0,l_aux,  alt_aux1,alt_aux2=0,r_aux1,r_aux2=raio_base;
    altura/=sep_h;
    
    float i=1,factor_h=(i/sep_h);
    
    circulo(raio_base, lados, sep_circulo, 0, 0);
    glBegin(GL_TRIANGLES);
    for(;sep_h>1;sep_h--){
        alt_aux1=alt_aux2;
        alt_aux2+=altura;
        y=0;
        i-=factor_h;
        r_aux1=r_aux2;
        r_aux2=raio_base *i;
        
        for (l_aux=0; l_aux<lados; l_aux++) {
            x=y;
            y+=angulo;
            
            glVertex3f(r_aux2*sin(x), alt_aux2, r_aux2*cos(x));
            glVertex3f(r_aux1*sin(x), alt_aux1, r_aux1*cos(x));
            glVertex3f(r_aux2*sin(y), alt_aux2, r_aux2*cos(y));

            glVertex3f(r_aux1*sin(x), alt_aux1, r_aux1*cos(x));
            glVertex3f(r_aux1*sin(y), alt_aux1, r_aux1*cos(y));
            glVertex3f(r_aux2*sin(y), alt_aux2, r_aux2*cos(y));
            
        }
    }
    
    alt_aux1=alt_aux2;
    alt_aux2+=altura;
    y=0;
    i-=factor_h;
    r_aux1=r_aux2;
    r_aux2=raio_base *i;
    
    for (l_aux=0; l_aux<lados; l_aux++) {
        x=y;
        y+=angulo;
        
                    
        glVertex3f(r_aux1*sin(x), alt_aux1, r_aux1*cos(x));
        glVertex3f(r_aux1*sin(y), alt_aux1, r_aux1*cos(y));
        glVertex3f(r_aux2*sin(y), alt_aux2, r_aux2*cos(y));
        
    }

    
    glEnd();
    
}