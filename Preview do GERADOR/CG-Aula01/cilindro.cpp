//
//  cilindro.cpp
//  CG-FORMAS-PRIMARIAS
//
//  Created by Hélder José Alves Gonçalves on 27/02/14.
//  Copyright (c) 2014 Hélder José Alves Gonçalves. All rights reserved.
//

#include "cilindro.h"

void cilindro(float raio,int fatias,float alt,int sep_cir,int sep_h){
    float angulo=(2*M_PI)/fatias,x,y=0,l_aux,h_aux1,h_aux2=0;
    
    circulo(raio, fatias, sep_cir, 0, 0);
    circulo(raio, fatias, sep_cir, alt, 1);
    
    alt=alt/sep_h;
    glBegin(GL_TRIANGLES);
    for(;sep_h>0;sep_h--){
        h_aux1=h_aux2;
        h_aux2+=alt;
        y=0;

        for (l_aux=0; l_aux<=fatias; l_aux++) {
            x=y;
            y+=angulo;
            
            glVertex3f(raio*sin(x), h_aux2, raio*cos(x));
            glVertex3f(raio*sin(x), h_aux1, raio*cos(x));
            glVertex3f(raio*sin(y), h_aux2, raio*cos(y));
            
            glVertex3f(raio*sin(x), h_aux1, raio*cos(x));
            glVertex3f(raio*sin(y), h_aux1, raio*cos(y));
            glVertex3f(raio*sin(y), h_aux2, raio*cos(y));
        }
    }
    glEnd();
}

Cilindro::Cilindro(float raio,int fatias,float altura,int aneis,int camadas){
    float angulo=(2*M_PI)/fatias,y=0,l_aux, r_aux,alt_aux=altura;
    int i=0,v=0,j,n=0,avanco=0;
    
    r_aux=raio;
    int n_pontos=(fatias*(camadas+1)*3) + (1+fatias*aneis)*6;
    n_indices= (fatias*camadas*3*2) + (fatias*(aneis-1)*2+fatias)*6;
    
    
    float *vertexB=(float*)malloc(n_pontos*sizeof(float)),
    *normalB=(float*)malloc(n_pontos*sizeof(float));
    indices=(unsigned short*)malloc(n_indices*sizeof(unsigned short));

    
    //Activar Buffers
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    
    
    //Corpo
    for(j=0;j<=camadas;j++){
        y=0;

        for(l_aux=0;l_aux<fatias;l_aux++){
            
            vertexB[v++]=r_aux*sin(y); vertexB[v++]=alt_aux; vertexB[v++]=r_aux*cos(y);
            normalB[n++]=sin(y);normalB[n++]=0;normalB[n++]=cos(y);
            
            if(j!=camadas){
                indices[i++]=avanco+l_aux;
                indices[i++]=avanco+fatias+l_aux;
                indices[i++]=avanco+l_aux+1;
                
                indices[i++]=avanco+fatias+l_aux;
                indices[i++]=avanco+fatias+l_aux+1;
                indices[i++]=avanco+l_aux+1;
            }
            y+=angulo;
        }
        if(j!=camadas){
            indices[i-4]=avanco;
            indices[i-2]=avanco+fatias;
            indices[i-1]=avanco;
        }
        avanco+=fatias;
        alt_aux-=altura/camadas;
    }
    
    //Circulo do topo
    r_aux=raio/aneis;
    
    vertexB[v++]=0;vertexB[v++]=altura;vertexB[v++]=0;
    normalB[n++]=0;normalB[n++]=1;normalB[n++]=0;

    for(l_aux=0;l_aux<fatias;l_aux++){
        
        vertexB[v++]=r_aux*sin(y);vertexB[v++]=altura;vertexB[v++]=r_aux*cos(y);
        normalB[n++]=0;normalB[n++]=1;normalB[n++]=0;
        
        indices[i++]=avanco;
        indices[i++]=avanco+l_aux+1;
        indices[i++]=avanco+l_aux+2;
        y+=angulo;
    }
    indices[i-1]=avanco+1;
    avanco+=fatias+1;
    
    
    for(j=1;j<aneis;j++){
        r_aux+=raio/aneis;
        y=0;
        for(l_aux=0;l_aux<fatias;l_aux++){
            
            vertexB[v++]=r_aux*sin(y); vertexB[v++]=altura; vertexB[v++]=r_aux*cos(y);
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
        avanco+=fatias;
    }
    
    //Circulo da base
    r_aux=raio/aneis;
    
    vertexB[v++]=0;vertexB[v++]=0;vertexB[v++]=0;
    normalB[n++]=0;normalB[n++]=-1;normalB[n++]=0;
    
    for(l_aux=0;l_aux<fatias;l_aux++){
        
        vertexB[v++]=r_aux*sin(y);vertexB[v++]=0;vertexB[v++]=r_aux*cos(y);
        normalB[n++]=0;normalB[n++]=-1;normalB[n++]=0;
        
        indices[i++]=avanco;
        indices[i++]=avanco+l_aux+2;
        indices[i++]=avanco+l_aux+1;
        y+=angulo;
    }
    indices[i-2]=avanco+1;
    avanco+=fatias+1;
    
    
    for(j=1;j<aneis;j++){
        r_aux+=raio/aneis;
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

    
    glGenBuffers(2, buffers);
    glBindBuffer(GL_ARRAY_BUFFER,buffers[0]);
    glBufferData(GL_ARRAY_BUFFER,n_pontos*sizeof(float), vertexB, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER,buffers[1]);
    glBufferData(GL_ARRAY_BUFFER,n_pontos*sizeof(float), normalB, GL_STATIC_DRAW);
    
    free(vertexB);
    free(normalB);

}

void Cilindro::desenha(){
    glBindBuffer(GL_ARRAY_BUFFER,buffers[0]);
    glVertexPointer(3,GL_FLOAT,0,0);
    glBindBuffer(GL_ARRAY_BUFFER,buffers[1]);
    glNormalPointer(GL_FLOAT,0,0);
    glDrawElements(GL_TRIANGLES, n_indices ,GL_UNSIGNED_SHORT, indices);
}

