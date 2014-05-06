//
//  Vbo.h
//  Motor3D
//
//  Created by Hélder José Alves Gonçalves on 09/04/14.
//  Copyright (c) 2014 Duarte Nuno Ferreira Duarte. All rights reserved.
//

#ifndef __Motor3D__Vbo__
#define __Motor3D__Vbo__

#include <iostream>
#include <GLUT/glut.h>

//Estrutura para guardar uma VBO
typedef struct sVbo{
    const char* nome;
    GLuint *buffers;
    unsigned short *indices;
    int n_indices;
    struct sVbo *next;
    
}*Vbo, NVbo;



Vbo addVbo(const char* nome, GLuint *buffers, int n_indices, unsigned short *indices, Vbo lista);
Vbo search_Vbo(const char* nome, Vbo lista);
void ler_VBO(const char* filename, Vbo *lista_vbo);
void desenha_vbo(Vbo vbo);

#endif /* defined(__Motor3D__Vbo__) */
