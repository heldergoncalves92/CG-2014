//
//  circulo.cpp
//  CG-FORMAS-PRIMARIAS
//
//  Created by Hélder José Alves Gonçalves on 27/02/14.
//  Copyright (c) 2014 Hélder José Alves Gonçalves. All rights reserved.
//

#include "circulo.h"

//ORI --- 1 -> BASE && 0 -> TOPO


void circulo(float raio, int lados,int aneis, float alt,int ori){
    float angulo=(2*M_PI)/lados,x,y=0,l_aux, r_aux1,r_aux2;
    raio=raio/aneis;
    if(ori){
        glBegin(GL_TRIANGLES);
        
        for(l_aux=0;l_aux<lados;l_aux++){
        	x=y;
            y+=angulo;
            glVertex3f(0, alt, 0);
            glVertex3f(raio*sin(x), alt, raio*cos(x));
            glVertex3f(raio*sin(y), alt, raio*cos(y));
        }
        r_aux2=raio;
        y=0;
        for(aneis--;aneis>0;aneis--){
            r_aux1=r_aux2;
            r_aux2+=raio;
            
            for(l_aux=0;l_aux<lados;l_aux++){
                x=y;
                y+=angulo;
                glVertex3f(r_aux1*sin(x), alt, r_aux1*cos(x));
                glVertex3f(r_aux2*sin(x), alt, r_aux2*cos(x));
                glVertex3f(r_aux1*sin(y), alt, r_aux1*cos(y));
                
                glVertex3f(r_aux1*sin(y), alt, r_aux1*cos(y));
                glVertex3f(r_aux2*sin(x), alt, r_aux2*cos(x));
                glVertex3f(r_aux2*sin(y), alt, r_aux2*cos(y));
            }
        }
        glEnd();
    }else{
        glBegin(GL_TRIANGLES);
        for(l_aux=0;l_aux<lados;l_aux++){
        	x=y;
            y+=angulo;
            glVertex3f(0, alt, 0);
            glVertex3f(raio*sin(y), alt, raio*cos(y));
            glVertex3f(raio*sin(x), alt, raio*cos(x));
        }
        r_aux2=raio;
        y=0;
        for(aneis--;aneis>0;aneis--){
            r_aux1=r_aux2;
            r_aux2+=raio;
            
            for(l_aux=0;l_aux<=lados;l_aux++){
                x=y;
                y+=angulo;
                glVertex3f(r_aux1*sin(x), alt, r_aux1*cos(x));
                glVertex3f(r_aux1*sin(y), alt, r_aux1*cos(y));
                glVertex3f(r_aux2*sin(x), alt, r_aux2*cos(x));
                
                glVertex3f(r_aux1*sin(y), alt, r_aux1*cos(y));
                glVertex3f(r_aux2*sin(y), alt, r_aux2*cos(y));
                glVertex3f(r_aux2*sin(x), alt, r_aux2*cos(x));
            }
        }
        glEnd();
    }
}

Circulo::Circulo(float raio, int lados,int aneis, float alt,int ori){
    
    float angulo=(2*M_PI)/lados,y=0,l_aux, r_aux;
    int i=0,v=0,j=0,avanco;
    
    raio=raio/aneis;
    r_aux=raio;
    int n_pontos=(1+lados*aneis)*3;
    n_indices=(lados*(aneis-1)*2+lados)*3;
    
    
    indices=(unsigned short*)malloc(n_indices*sizeof(unsigned short));
    float *vertexB=(float*)malloc(n_pontos*sizeof(float));
    
    //Activar Buffers
    glEnableClientState(GL_VERTEX_ARRAY);
    
    if(ori){
        vertexB[v++]=0;vertexB[v++]=alt;vertexB[v++]=0;
        for(l_aux=0;l_aux<lados;l_aux++){
            
            vertexB[v++]=r_aux*sin(y);vertexB[v++]=alt;vertexB[v++]=r_aux*cos(y);
            
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
                
                vertexB[v++]=r_aux*sin(y); vertexB[v++]=alt; vertexB[v++]=r_aux*cos(y);
                
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
        vertexB[v++]=0;vertexB[v++]=alt;vertexB[v++]=0;
        for(l_aux=0;l_aux<lados;l_aux++){
            
            vertexB[v++]=r_aux*sin(y);vertexB[v++]=alt;vertexB[v++]=r_aux*cos(y);
            
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
                
                vertexB[v++]=r_aux*sin(y); vertexB[v++]=alt; vertexB[v++]=r_aux*cos(y);
                
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
    
    
    glGenBuffers(1, buffers);
    glBindBuffer(GL_ARRAY_BUFFER,buffers[0]);
    glBufferData(GL_ARRAY_BUFFER,n_pontos*sizeof(float), vertexB, GL_STATIC_DRAW);
    
    //printf("%d||%d -- %d||%d -- %d\n",n_indices,i,n_pontos,v,lados);
    
    free(vertexB);
}

void Circulo::desenha(){
    
    glBindBuffer(GL_ARRAY_BUFFER,buffers[0]);
    glVertexPointer(3,GL_FLOAT,0,0);
    glDrawElements(GL_TRIANGLES, n_indices ,GL_UNSIGNED_SHORT, indices);
    
    
}







