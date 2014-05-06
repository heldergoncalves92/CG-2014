//
//  Vbo.cpp
//  Motor3D
//
//  Created by Hélder José Alves Gonçalves on 09/04/14.
//  Copyright (c) 2014 Duarte Nuno Ferreira Duarte. All rights reserved.
//

#include "Vbo.h"

Vbo addVbo(const char* nome, GLuint *buffers, int n_indices, unsigned short *indices, Vbo lista){
 
    Vbo novo=(Vbo)malloc(sizeof(NVbo));
    novo->nome=nome;
    novo->n_indices=n_indices;
    novo->indices=indices;
    novo->buffers=buffers;
    
    if (lista) {
        novo->next=lista;
        return novo;
    }
    novo->next=NULL;
    return novo;
}


Vbo search_Vbo(const char* nome, Vbo lista){
    
    while (lista) {
        if (strcmp(nome, lista->nome)==0)
            return lista;
        lista=lista->next;
    }
    return NULL;
}

void desenha_vbo(Vbo vbo){
    glBindBuffer(GL_ARRAY_BUFFER,vbo->buffers[0]);
    glVertexPointer(3,GL_FLOAT,0,0);
    glDrawElements(GL_TRIANGLES, vbo->n_indices ,GL_UNSIGNED_SHORT, vbo->indices);
}

void ler_VBO(const char* filename, Vbo *lista_vbo){

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
        *lista_vbo=addVbo(filename, buffers, n_indices, indices, *lista_vbo);
        desenha_vbo(*lista_vbo);
        
    }else
        printf("ERRO! Não fez load do ficheiro '%s'!\n",filename);
    
}



