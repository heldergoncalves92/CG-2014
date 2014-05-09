//
//  plano.cpp
//  CG-FORMAS-PRIMARIAS
//
//  Created by Hélder José Alves Gonçalves on 28/02/14.
//  Copyright (c) 2014 Hélder José Alves Gonçalves. All rights reserved.
//

#include "plano.h"
#include <stdio.h>

/* Tipos de planos
 1 -> +XoY
 2 -> -XoY
 
 3 -> +ZoY
 4 -> -ZoY
 
 5 -> +ZoX
 6 -> -ZoX
 
*/

void plano(float altura, float lado, int sep_h, int sep_v, float z_index, int ori){
    int i;
    float l_const=lado/sep_v, alt_const=altura/sep_h,alt_ori=-altura/2,lado_ori=-lado/2;
    
    glBegin(GL_TRIANGLES);
    switch (ori) {
        case 1:
            for(altura=alt_ori;sep_h>0;sep_h--){
                i=0;
                for(lado=lado_ori;i<sep_v;i++){
                    glColor3f(1, 0, 0);
                    glVertex3f(lado,altura, z_index);
                    glVertex3f(lado+l_const,altura, z_index);
                    glVertex3f(lado,altura+alt_const, z_index);
            
                    glVertex3f(lado+l_const,altura, z_index);
                    glVertex3f(lado+l_const,altura+alt_const, z_index);
                    glVertex3f(lado,altura+alt_const, z_index);
                    lado+=l_const;
                }
                altura+=alt_const;
            }
            break;
        case 2:
            for(altura=alt_ori;sep_h>0;sep_h--){
                i=0;
                for(lado=lado_ori;i<sep_v;i++){
                                        glColor3f(1, 0.5, 0);
                    glVertex3f(lado,altura, z_index);
                    glVertex3f(lado,altura+alt_const, z_index);
                    glVertex3f(lado+l_const,altura, z_index);
                    
                    glVertex3f(lado+l_const,altura, z_index);
                    glVertex3f(lado,altura+alt_const, z_index);
                    glVertex3f(lado+l_const,altura+alt_const, z_index);
                    lado+=l_const;
                }
                altura+=alt_const;
            }
            break;
        case 3:
            for(altura=alt_ori;sep_h>0;sep_h--){
                i=0;
                for(lado=lado_ori;i<sep_v;i++){
                                        glColor3f(1, 1, 0);
                    glVertex3f(z_index,altura, lado);
                    glVertex3f(z_index,altura+alt_const, lado);
                    glVertex3f(z_index,altura, lado+l_const);
                    
                    glVertex3f(z_index,altura, lado+l_const);
                    glVertex3f(z_index,altura+alt_const, lado);
                    glVertex3f(z_index,altura+alt_const, lado+l_const);
                    lado+=l_const;
                }
                altura+=alt_const;
            }
            break;
        case 4:
            for(altura=alt_ori;sep_h>0;sep_h--){
                i=0;
                for(lado=lado_ori;i<sep_v;i++){
                                        glColor3f(0, 0, 1);
                    glVertex3f(z_index,altura, lado);
                    glVertex3f(z_index,altura, lado+l_const);
                    glVertex3f(z_index,altura+alt_const, lado);
                    
                    glVertex3f(z_index,altura,lado+l_const);
                    glVertex3f(z_index,altura+alt_const, lado+l_const);
                    glVertex3f(z_index,altura+alt_const, lado);
                    lado+=l_const;
                }
                altura+=alt_const;
            }
            break;
        case 5:
            for(altura=alt_ori;sep_h>0;sep_h--){
                i=0;
                for(lado=lado_ori;i<sep_v;i++){
                                        glColor3f(1, 0, 1);
                    glVertex3f(altura,z_index, lado);
                    glVertex3f(altura,z_index, lado+l_const);
                    glVertex3f(altura+alt_const,z_index, lado);
                    
                    glVertex3f(altura,z_index,lado+l_const);
                    glVertex3f(altura+alt_const,z_index, lado+l_const);
                    glVertex3f(altura+alt_const,z_index, lado);
                    lado+=l_const;
                }
                altura+=alt_const;
            }
            break;
        case 6:
            for(altura=alt_ori;sep_h>0;sep_h--){
                i=0;
                for(lado=lado_ori;i<sep_v;i++){
                                        glColor3f(0, 1, 0);
                    glVertex3f(altura,z_index, lado);
                    glVertex3f(altura+alt_const,z_index, lado);
                    glVertex3f(altura,z_index, lado+l_const);
                    
                    glVertex3f(altura,z_index, lado+l_const);
                    glVertex3f(altura+alt_const,z_index, lado);
                    glVertex3f(altura+alt_const,z_index, lado+l_const);
                    lado+=l_const;
                }
                altura+=alt_const;
            }
            break;
            
        default:
            break;
    }
    glEnd();
}


Plano::Plano(float altura, float lado, int camadas, int fatias, float z_index, int ori){
    int k=0,j=0,v=0, i=0, avanco,n=0;
    float l_const=lado/fatias, alt_const=altura/camadas,alt_ori=-altura/2,lado_ori=-lado/2;
    
    //Activar Buffers
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    
    int n_pontos=(fatias+1)*(camadas+1)*3;
    n_indices=(2*fatias*camadas)*3;
    
    float *vertexB=(float*)malloc(n_pontos*sizeof(float)),
    *normalB=(float*)malloc(n_pontos*sizeof(float));

    indices=(unsigned int*)malloc(n_indices*sizeof(unsigned int));
    
    switch (ori) {
        case 1:
            for(altura=alt_ori;j<=camadas;j++){
                k=0;
                avanco=j*(fatias+1);
                for(lado=lado_ori;k<=fatias;k++){
                    //Inserir Ponto
                    vertexB[v++]=lado;vertexB[v++]=altura;vertexB[v++]=z_index;
                    normalB[n++]=0;normalB[n++]=0;normalB[n++]=1;
                    if(k!=fatias && j!=camadas){
                        indices[i++]=avanco+k;
                        indices[i++]=avanco+k+1;
                        indices[i++]=avanco+fatias+1+k;
                        
                        indices[i++]=avanco+k+1;
                        indices[i++]=avanco+fatias+1+k+1;
                        indices[i++]=avanco+fatias+1+k;
                        

                    }
                    lado+=l_const;
                }
                altura+=alt_const;
            }
            break;
        case 2:
            for(altura=alt_ori;j<=camadas;j++){
                k=0;
                avanco=j*(fatias+1);
                for(lado=lado_ori;k<=fatias;k++){
                    //Inserir Ponto
                    vertexB[v++]=lado;vertexB[v++]=altura;vertexB[v++]=z_index;
                    normalB[n++]=0;normalB[n++]=0;normalB[n++]=-1;
                    if(k!=fatias && j!=camadas){
                        indices[i++]=avanco+k;
                        indices[i++]=avanco+fatias+1+k;
                        indices[i++]=avanco+k+1;
                        
                        indices[i++]=avanco+k+1;
                        indices[i++]=avanco+fatias+1+k;
                        indices[i++]=avanco+fatias+1+k+1;
                    }
                    lado+=l_const;
                }
                altura+=alt_const;
            }
            break;
        
        case 3:
            for(altura=alt_ori;j<=camadas;j++){
                k=0;
                avanco=j*(fatias+1);
                for(lado=lado_ori;k<=fatias;k++){
                    //Inserir Ponto
                    vertexB[v++]=z_index;vertexB[v++]=altura;vertexB[v++]=lado;
                    normalB[n++]=1;normalB[n++]=0;normalB[n++]=0;
                    if(k!=fatias && j!=camadas){
                        indices[i++]=avanco+k;
                        indices[i++]=avanco+fatias+1+k;
                        indices[i++]=avanco+k+1;
                        
                        indices[i++]=avanco+k+1;
                        indices[i++]=avanco+fatias+1+k;
                        indices[i++]=avanco+fatias+1+k+1;
                    }
                    lado+=l_const;
                }
                altura+=alt_const;
            }
            break;
        case 4:
            for(altura=alt_ori;j<=camadas;j++){
                k=0;
                avanco=j*(fatias+1);
                for(lado=lado_ori;k<=fatias;k++){
                    //Inserir Ponto
                    vertexB[v++]=z_index;vertexB[v++]=altura;vertexB[v++]=lado;
                    normalB[n++]=-1;normalB[n++]=0;normalB[n++]=0;
                    if(k!=fatias && j!=camadas){
                        indices[i++]=avanco+k;
                        indices[i++]=avanco+k+1;
                        indices[i++]=avanco+fatias+1+k;
                        
                        indices[i++]=avanco+k+1;
                        indices[i++]=avanco+fatias+1+k+1;
                        indices[i++]=avanco+fatias+1+k;
                    }
                    lado+=l_const;
                }
                altura+=alt_const;
            }
            break;
        case 5:
            for(altura=alt_ori;j<=camadas;j++){
                k=0;
                avanco=j*(fatias+1);
                for(lado=lado_ori;k<=fatias;k++){
                    //Inserir Ponto
                    vertexB[v++]=altura;vertexB[v++]=z_index;vertexB[v++]=lado;
                    normalB[n++]=0;normalB[n++]=1;normalB[n++]=0;
                    if(k!=fatias && j!=camadas){
                        indices[i++]=avanco+k;
                        indices[i++]=avanco+k+1;
                        indices[i++]=avanco+fatias+1+k;
                        
                        indices[i++]=avanco+k+1;
                        indices[i++]=avanco+fatias+1+k+1;
                        indices[i++]=avanco+fatias+1+k;
                    }
                    lado+=l_const;
                }
                altura+=alt_const;
            }
            break;
        case 6:
            for(altura=alt_ori;j<=camadas;j++){
                k=0;
                avanco=j*(fatias+1);
                for(lado=lado_ori;k<=fatias;k++){
                    //Inserir Ponto
                    vertexB[v++]=altura;vertexB[v++]=z_index;vertexB[v++]=lado;
                    normalB[n++]=0;normalB[n++]=-1;normalB[n++]=0;
                    if(k!=fatias && j!=camadas){
                        indices[i++]=avanco+k;
                        indices[i++]=avanco+fatias+1+k;
                        indices[i++]=avanco+k+1;
                        
                        indices[i++]=avanco+k+1;
                        indices[i++]=avanco+fatias+1+k;
                        indices[i++]=avanco+fatias+1+k+1;
                    }
                    lado+=l_const;
                }
                altura+=alt_const;
            }
            break;

        
    }
    
    glGenBuffers(2, buffers);
    glBindBuffer(GL_ARRAY_BUFFER,buffers[0]);
    glBufferData(GL_ARRAY_BUFFER,n_pontos*sizeof(float), vertexB, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ARRAY_BUFFER,buffers[1]);
    glBufferData(GL_ARRAY_BUFFER, n_pontos*sizeof(float), normalB,GL_STATIC_DRAW);
    
}

void paralelepipedo(float altura, float lado_x, float lado_z, int sep_h, int sep_v){
    
    plano(altura, lado_x, sep_h, sep_v, lado_z/2, 1);
    plano(altura, lado_x, sep_h, sep_v, -lado_z/2, 2);
    
    plano(altura, lado_z, sep_h, sep_v, lado_x/2, 3);
    plano(altura, lado_z, sep_h, sep_v, -lado_x/2, 4);
    
    plano(lado_x, lado_z, sep_h, sep_v, altura/2, 5);
    plano(lado_x, lado_z, sep_h, sep_v, -altura/2, 6);
}

Paralelepipedo::Paralelepipedo(float lado_y, float lado_x, float lado_z, int camadas, int fatias_x, int fatias_z){
    int     k=0,j=0,v=0, i=0, avanco=0,n=0;
    float   change_x=lado_x/fatias_x,
            change_z=lado_z/fatias_z,
            change_y=lado_y/camadas,
            begin_y=-lado_y/2,
            begin_x=-lado_x/2,
            begin_z=-lado_z/2,
            altura_aux,lado_aux;
    
    //Activar Buffers
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    
    int n_pontos=(2*(fatias_x+1)*(camadas+1) + 2*(fatias_z+1)*(camadas+1) + 2*(fatias_x+1)*(fatias_z+1))*3;
    n_indices=(2*fatias_x*camadas + 2*fatias_z*camadas + 2* fatias_x*fatias_z)*3*2;
    
    float *vertexB=(float*)malloc(n_pontos*sizeof(float)),
    *normalB=(float*)malloc(n_pontos*sizeof(float));
    indices=(unsigned int*)malloc(n_indices*sizeof(unsigned int));
    
    //1
    for(altura_aux=begin_y;j<=camadas;j++){
        k=0;

        for(lado_aux=begin_x;k<=fatias_x;k++){
            //Inserir Ponto
            vertexB[v++]=lado_aux;vertexB[v++]=altura_aux;vertexB[v++]=fabs(begin_z);
            normalB[n++]=0;normalB[n++]=0;normalB[n++]=1;
            if(k!=fatias_x && j!=camadas){
                indices[i++]=avanco+k;
                indices[i++]=avanco+k+1;
                indices[i++]=avanco+fatias_x+1+k;
                
                indices[i++]=avanco+k+1;
                indices[i++]=avanco+fatias_x+1+k+1;
                indices[i++]=avanco+fatias_x+1+k;
            }
            lado_aux+=change_x;
        }
        avanco+=fatias_x+1;
        altura_aux+=change_y;
    }
    
    //2
    j=0;
    for(altura_aux=begin_y;j<=camadas;j++){
        k=0;
        for(lado_aux=begin_x;k<=fatias_x;k++){
            //Inserir Ponto
            vertexB[v++]=lado_aux;vertexB[v++]=altura_aux;vertexB[v++]=begin_z;
            normalB[n++]=0;normalB[n++]=0;normalB[n++]=-1;
            if(k!=fatias_x && j!=camadas){
                indices[i++]=avanco+k;
                indices[i++]=avanco+fatias_x+1+k;
                indices[i++]=avanco+k+1;
                
                indices[i++]=avanco+k+1;
                indices[i++]=avanco+fatias_x+1+k;
                indices[i++]=avanco+fatias_x+1+k+1;
            }
            lado_aux+=change_x;
        }
        avanco+=fatias_x+1;
        altura_aux+=change_y;
    }
    
    //3
    j=0;
    for(altura_aux=begin_y;j<=camadas;j++){
        k=0;
        for(lado_aux=begin_z;k<=fatias_z;k++){
            //Inserir Ponto
            vertexB[v++]=fabs(begin_x);vertexB[v++]=altura_aux;vertexB[v++]=lado_aux;
            normalB[n++]=1;normalB[n++]=0;normalB[n++]=0;
            if(k!=fatias_z && j!=camadas){
                indices[i++]=avanco+k;
                indices[i++]=avanco+fatias_z+1+k;
                indices[i++]=avanco+k+1;
                
                indices[i++]=avanco+k+1;
                indices[i++]=avanco+fatias_z+1+k;
                indices[i++]=avanco+fatias_z+1+k+1;
            }
            lado_aux+=change_z;
        }
        avanco+=fatias_z+1;
        altura_aux+=change_y;
    }
    
    //4
    j=0;
    for(altura_aux=begin_y;j<=camadas;j++){
        k=0;
        for(lado_aux=begin_z;k<=fatias_z;k++){
            //Inserir Ponto
            vertexB[v++]=begin_x;vertexB[v++]=altura_aux;vertexB[v++]=lado_aux;
            normalB[n++]=-1;normalB[n++]=0;normalB[n++]=0;
            if(k!=fatias_z && j!=camadas){
                indices[i++]=avanco+k;
                indices[i++]=avanco+k+1;
                indices[i++]=avanco+fatias_z+1+k;
                
                indices[i++]=avanco+k+1;
                indices[i++]=avanco+fatias_z+1+k+1;
                indices[i++]=avanco+fatias_z+1+k;
                
            }
            lado_aux+=change_z;
        }
        avanco+=fatias_z+1;
        altura_aux+=change_y;
    }
    
    //5
    j=0;
    for(altura_aux=begin_x;j<=fatias_x;j++){
        k=0;
        for(lado_aux=begin_z;k<=fatias_z;k++){
            //Inserir Ponto
            vertexB[v++]=altura_aux;vertexB[v++]=fabsf(begin_y);vertexB[v++]=lado_aux;
            normalB[n++]=0;normalB[n++]=1;normalB[n++]=0;
            if(k!=fatias_z && j!=fatias_x){
                indices[i++]=avanco+k;
                indices[i++]=avanco+k+1;
                indices[i++]=avanco+fatias_z+1+k;
                
                indices[i++]=avanco+k+1;
                indices[i++]=avanco+fatias_z+1+k+1;
                indices[i++]=avanco+fatias_z+1+k;
                
            }
            lado_aux+=change_z;
        }
        avanco+=fatias_z+1;
        altura_aux+=change_x;
    }
    
    //6
    j=0;
    for(altura_aux=begin_x;j<=fatias_x;j++){
        k=0;
        for(lado_aux=begin_z;k<=fatias_z;k++){
            //Inserir Ponto
            vertexB[v++]=altura_aux;vertexB[v++]=begin_y;vertexB[v++]=lado_aux;
            normalB[n++]=0;normalB[n++]=-1;normalB[n++]=0;
            if(k!=fatias_z && j!=fatias_x){
                indices[i++]=avanco+k;
                indices[i++]=avanco+fatias_z+1+k;
                indices[i++]=avanco+k+1;
                
                indices[i++]=avanco+k+1;
                indices[i++]=avanco+fatias_z+1+k;
                indices[i++]=avanco+fatias_z+1+k+1;
            }
            lado_aux+=change_z;
        }
        avanco+=fatias_z+1;
        altura_aux+=change_x;
    }

    glGenBuffers(2, buffers);
    glBindBuffer(GL_ARRAY_BUFFER,buffers[0]);
    glBufferData(GL_ARRAY_BUFFER,n_pontos*sizeof(float), vertexB, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ARRAY_BUFFER,buffers[1]);
    glBufferData(GL_ARRAY_BUFFER,n_pontos*sizeof(float), normalB, GL_STATIC_DRAW);
}

void Paralelepipedo::desenha(){

    glBindBuffer(GL_ARRAY_BUFFER,buffers[0]);
    glVertexPointer(3,GL_FLOAT,0,0);
    glBindBuffer(GL_ARRAY_BUFFER,buffers[1]);
    glNormalPointer(GL_FLOAT,0,0);
    glDrawElements(GL_TRIANGLES, n_indices ,GL_UNSIGNED_INT, indices);

}

void Plano::desenha(){
    
    glBindBuffer(GL_ARRAY_BUFFER,buffers[0]);
    glVertexPointer(3,GL_FLOAT,0,0);
    glBindBuffer(GL_ARRAY_BUFFER,buffers[1]);
    glNormalPointer(GL_FLOAT,0,0);
    glDrawElements(GL_TRIANGLES, n_indices ,GL_UNSIGNED_INT, indices);
    
}






