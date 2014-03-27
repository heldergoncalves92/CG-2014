//
//  esfera.h
//  CG-FORMAS-PRIMARIAS
//
//  Created by Hélder José Alves Gonçalves on 27/02/14.
//  Copyright (c) 2014 Hélder José Alves Gonçalves. All rights reserved.
//

#ifndef CG_FORMAS_PRIMARIAS_esfera_h
#define CG_FORMAS_PRIMARIAS_esfera_h

#include <GL/glew.h>
#include <GLUT/glut.h>
#include <math.h>
#include "circulo.h"

void esfera(float raio, int sep_h, int sep_cir);
void esferaVBO(float raio, int sep_h, int sep_cir);
void drawEsfera();


#endif
