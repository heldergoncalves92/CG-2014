//
//  modelo.cpp
//  Motor3D
//
//  Created by Hélder José Alves Gonçalves on 09/04/14.
//  Copyright (c) 2014 Duarte Nuno Ferreira Duarte. All rights reserved.
//

#include "modelo.h"



Modelo addVbo(const char* nome, GLuint *buffers, int n_indices, unsigned short *indices, Modelo lista){
    
    Modelo aux=(Modelo)malloc(sizeof(NModelo));
    Vbo novo=(Vbo)malloc(sizeof(NVbo));

    //Definiçoes do modelo de VBO
    novo->nome=nome;
    novo->n_indices=n_indices;
    novo->indices=indices;
    novo->buffers=buffers;
    
    //Definiçoes para o lista de Modelos
    aux->next=lista;
    aux->tipo=2;
    aux->u.vbo=novo;
    
    return aux;
}


void desenha_vbo(Vbo vbo){
    glBindBuffer(GL_ARRAY_BUFFER,vbo->buffers[0]);
    glVertexPointer(3,GL_FLOAT,0,0);
    glDrawElements(GL_TRIANGLES, vbo->n_indices ,GL_UNSIGNED_SHORT, vbo->indices);
}

Modelo ler_VBO(const char* filename, Modelo lista){
    
    //Inicializações
    int n_pontos,n_indices,i=0;
    unsigned short *indices, sx,sy,sz;
    float cx,cy,cz,*vertices;
    FILE *f = fopen(filename, "r");
    GLuint *buffers=NULL;
    
    //Testa se ficheiro existe
    if(f){
        
        //Lê o número total de pontos e aloca memória
        fscanf(f, "%d\n", &n_pontos);
        vertices=(float*)malloc(n_pontos*sizeof(float));
        
        //Lê todos os pontos que estão no ficheiro
        while (i<n_pontos){
            fscanf(f, "%f %f %f\n", &cx, &cy, &cz);
            vertices[i++]=cx;
            vertices[i++]=cy;
            vertices[i++]=cz;
        }
        
        i=0;
        //Lê o número total de indices e aloca memória
        fscanf(f, "%d\n", &n_indices);
        indices=(unsigned short*)malloc(n_indices*sizeof(unsigned short));
        
        //Lê todos os indices que estão no ficheiro
        while (fscanf(f, "%hu %hu %hu\n", &sx, &sy, &sz)!=EOF){
            indices[i++]=sx;
            indices[i++]=sy;
            indices[i++]=sz;
        }
        
        fclose(f);
        
        //Activar Buffers
        glEnableClientState(GL_VERTEX_ARRAY);
        
        //Aloca memória para os buffers
        buffers=(GLuint*)malloc(1*sizeof(GLuint));
        
        //Guarda pontos na memória da gráfica
        glGenBuffers(1, buffers);
        glBindBuffer(GL_ARRAY_BUFFER,buffers[0]);
        glBufferData(GL_ARRAY_BUFFER,n_pontos*sizeof(float), vertices, GL_STATIC_DRAW);
        
        free(vertices);
        
        //Adiciona a VBO à estrutura e desenha a mesmawa
        return addVbo(filename, buffers, n_indices, indices, lista);
    }else
        printf("ERRO! Não fez load do ficheiro '%s'!\n",filename);
    
    return lista;
    
}

//Real Time '.3d'
Modelo addRTime(const char* nome, float *vertices, int n_pontos, Modelo lista){
    
    Modelo aux=(Modelo)malloc(sizeof(NModelo));
    RTime novo =(RTime)malloc(sizeof(NRTime));
    
    //Definiçoes do modelo de RealTime
    novo->nome=nome;
    novo->vertices=vertices;
    novo->n_pontos=n_pontos;
    
    //Definiçoes para o lista de Modelos
    aux->next=lista;
    aux->tipo=1;
    aux->u.rTime=novo;

    return aux;
}


void desenha_RTime(RTime modelo){
    int i;
    float *vertices=modelo->vertices;
    
    glBegin(GL_TRIANGLES);
    for (i=0; i<modelo->n_pontos; i+=3) {
        glVertex3f(vertices[i], vertices[i+1], vertices[i+2]);
    }
    glEnd();
    
}


Modelo ler_RTime(const char* filename, Modelo lista){
    int n_pontos,i=0;
    float cx,cy,cz,*vertices;
    FILE *f = fopen(filename, "r");
    if(f){
        fscanf(f, "%d\n", &n_pontos);
        vertices=(float*)malloc(n_pontos*sizeof(float));
        while (fscanf(f, "%f %f %f\n", &cx, &cy, &cz)!=EOF){
            vertices[i++]=cx;
            vertices[i++]=cy;
            vertices[i++]=cz;
        }
        fclose(f);
        return addRTime(filename, vertices, n_pontos, lista);
    }else
        printf("ERRO! Não fez load do ficheiro '%s'!\n",filename);
    return lista;
}


Modelo search_Modelo(const char* nome, Modelo lista){
    
    while (lista) {
        
        if(lista->tipo==1){
            if (strcmp(nome, lista->u.rTime->nome)==0)
                return lista;
        }else{
            if (strcmp(nome, lista->u.vbo->nome)==0)
                return lista;
        }
        lista=lista->next;
    }
    return NULL;
}
