//
//  cilindro.cpp
//  CG-FORMAS-PRIMARIAS
//
//  Created by Hélder José Alves Gonçalves on 27/02/14.
//  Copyright (c) 2014 Hélder José Alves Gonçalves. All rights reserved.
//

#include "cilindro.h"

void cilindro(float raio,int lados,float alt,int sep_cir,int sep_h){
    float angulo=(2*M_PI)/lados,x,y=0,l_aux,h_aux1,h_aux2=0;
    
    circulo(raio, lados, sep_cir, 0, 0);
    circulo(raio, lados, sep_cir, alt, 1);
    
    alt=alt/sep_h;
    glBegin(GL_TRIANGLES);
    for(;sep_h>0;sep_h--){
        h_aux1=h_aux2;
        h_aux2+=alt;
        y=0;

        for (l_aux=0; l_aux<=lados; l_aux++) {
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
    int i=0,v=0,j=0,avanco;
    
    altura/=camadas;
    raio=raio/aneis;
    r_aux=raio;
    int n_pontos=((1+fatias*aneis)*3) + (fatias*camadas*3) + ((aneis-1)*fatias+1)*3;
    n_indices=((fatias*(aneis-1)*2+fatias)*3)  + (fatias*camadas*3*2)  + (((aneis-1)*fatias*2+fatias)*3);
    
    
    indices=(unsigned short*)malloc(n_indices*sizeof(unsigned short));
    float *vertexB=(float*)malloc(n_pontos*sizeof(float));
    
    //Activar Buffers
    glEnableClientState(GL_VERTEX_ARRAY);
    
        //Circulo do topo
        vertexB[v++]=0;vertexB[v++]=alt_aux;vertexB[v++]=0;
        for(l_aux=0;l_aux<fatias;l_aux++){
            
            vertexB[v++]=r_aux*sin(y);vertexB[v++]=alt_aux;vertexB[v++]=r_aux*cos(y);
            
            indices[i++]=0;
            indices[i++]=l_aux+1;
            indices[i++]=l_aux+2;
            y+=angulo;
        }
        indices[i-1]=1;
        
        for(j++;j<aneis;j++){
            r_aux+=raio;
            y=0;
            for(l_aux=0;l_aux<fatias;l_aux++){
                avanco=j*fatias+1;
                
                vertexB[v++]=r_aux*sin(y); vertexB[v++]=alt_aux; vertexB[v++]=r_aux*cos(y);
                
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
    //Corpo
    for(;camadas>0;camadas--){
        y=0;
        alt_aux-=altura;
        for(l_aux=0;l_aux<fatias;l_aux++){
            avanco=j*fatias+1;
            
            vertexB[v++]=r_aux*sin(y); vertexB[v++]=alt_aux; vertexB[v++]=r_aux*cos(y);
            
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
        j++;
    }
    
        //Circulo da base
    
        for(;aneis>1;aneis--){
            r_aux-=raio;
            y=0;
            for(l_aux=0;l_aux<fatias;l_aux++){
                avanco=j*fatias+1;
                
                vertexB[v++]=r_aux*sin(y); vertexB[v++]=0; vertexB[v++]=r_aux*cos(y);
                
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
            j++;
        }
   
    vertexB[v++]=0;vertexB[v++]=0;vertexB[v++]=0;
    for(l_aux=0;l_aux<fatias;l_aux++){
        
        indices[i++]=avanco+fatias;
        indices[i++]=avanco+l_aux+1;
        indices[i++]=avanco+l_aux;
    }
    indices[i-2]=avanco;
    
    glGenBuffers(1, buffers);
    glBindBuffer(GL_ARRAY_BUFFER,buffers[0]);
    glBufferData(GL_ARRAY_BUFFER,n_pontos*sizeof(float), vertexB, GL_STATIC_DRAW);
    
    //printf("%d||%d -- %d||%d -- %d\n",n_indices,i,n_pontos,v,fatias);
    
    free(vertexB);

}

void Cilindro::desenha(){
    glBindBuffer(GL_ARRAY_BUFFER,buffers[0]);
    glVertexPointer(3,GL_FLOAT,0,0);
    glDrawElements(GL_TRIANGLES, n_indices ,GL_UNSIGNED_SHORT, indices);
}

