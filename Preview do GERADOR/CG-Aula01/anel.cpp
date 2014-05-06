//
//  anel.cpp
//  CG-TESTES
//
//  Created by Hélder José Alves Gonçalves on 07/04/14.
//  Copyright (c) 2014 Hélder José Alves Gonçalves. All rights reserved.
//

#include "anel.h"



//ORI --- 1 -> BASE && 0 -> TOPO

Anel::Anel(float raio_fora, float raio_dentro, int fatias, int aneis, int ori){
    
    float angulo=(2*M_PI)/fatias,y=0,l_aux,raio=(raio_fora-raio_dentro)/aneis;
    int i=0,v=0,j,avanco;
    

    int n_pontos=(fatias*(aneis+1))*3;
    n_indices=6*fatias*aneis;
    
    
    indices=(unsigned short*)malloc(n_indices*sizeof(unsigned short));
    float *vertexB=(float*)malloc(n_pontos*sizeof(float));
    
    //Activar Buffers
    glEnableClientState(GL_VERTEX_ARRAY);

    
    if(ori){
        
        for (j=0; j<fatias; j++) {
            vertexB[v++]=raio_dentro*sin(y); vertexB[v++]=0; vertexB[v++]=raio_dentro*cos(y);
            y+=angulo;
        }
        
        for(j=1;j<=aneis;j++){
            raio_dentro+=raio;
            y=0;
            for(l_aux=0;l_aux<fatias;l_aux++){
                avanco=j*fatias;
                
                vertexB[v++]=raio_dentro*sin(y); vertexB[v++]=0; vertexB[v++]=raio_dentro*cos(y);
                
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
        for (j=0; j<fatias; j++) {
            vertexB[v++]=raio_dentro*sin(y); vertexB[v++]=0; vertexB[v++]=raio_dentro*cos(y);
            y+=angulo;
        }
        
        for(j=1;j<=aneis;j++){
            raio_dentro+=raio;
            y=0;
            for(l_aux=0;l_aux<fatias;l_aux++){
                avanco=j*fatias;
                
                vertexB[v++]=raio_dentro*sin(y); vertexB[v++]=0; vertexB[v++]=raio_dentro*cos(y);
                
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
    
    glGenBuffers(1, buffers);
    glBindBuffer(GL_ARRAY_BUFFER,buffers[0]);
    glBufferData(GL_ARRAY_BUFFER,n_pontos*sizeof(float), vertexB, GL_STATIC_DRAW);
    
   // printf("Indices: %d||%d --Pontos: %d||%d -- %d\n",n_indices,i,n_pontos,v,fatias);
    
    free(vertexB);
    
}

void Anel::desenha(){
    glBindBuffer(GL_ARRAY_BUFFER,buffers[0]);
    glVertexPointer(3,GL_FLOAT,0,0);
    glDrawElements(GL_TRIANGLES, n_indices ,GL_UNSIGNED_SHORT, indices);

}

void anel(float raio_fora, float raio_dentro,int fatias, int aneis, int ori){
    float angulo=(2*M_PI)/fatias,x,y=0,l_aux,raio=(raio_fora-raio_dentro)/aneis;
    raio_fora=raio_dentro;
    glBegin(GL_TRIANGLES);
    if(ori){
        for(;aneis>0;aneis--){
            raio_dentro=raio_fora;
            raio_fora+=raio;
            
            for(l_aux=0;l_aux<=fatias;l_aux++){
                x=y;
                y+=angulo;
                glVertex3f(raio_dentro*sin(x), 0, raio_dentro*cos(x));
                glVertex3f(raio_fora*sin(x), 0, raio_fora*cos(x));
                glVertex3f(raio_dentro*sin(y), 0, raio_dentro*cos(y));
                
                glVertex3f(raio_dentro*sin(y), 0, raio_dentro*cos(y));
                glVertex3f(raio_fora*sin(x), 0, raio_fora*cos(x));
                glVertex3f(raio_fora*sin(y), 0, raio_fora*cos(y));
            }
        }
        
    }else{
        for(;aneis>0;aneis--){
            raio_dentro=raio_fora;
            raio_fora+=raio;
            
            for(l_aux=0;l_aux<fatias;l_aux++){
                x=y;
                y+=angulo;
                glVertex3f(raio_dentro*sin(x), 0, raio_dentro*cos(x));
                glVertex3f(raio_dentro*sin(y), 0, raio_dentro*cos(y));
                glVertex3f(raio_fora*sin(x), 0, raio_fora*cos(x));
                
                glVertex3f(raio_dentro*sin(y), 0, raio_dentro*cos(y));
                glVertex3f(raio_fora*sin(y), 0, raio_fora*cos(y));
                glVertex3f(raio_fora*sin(x), 0, raio_fora*cos(x));
            }
        }
    }
    glEnd();
}

