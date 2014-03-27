//
//  plano.h
//  CG-FORMAS-PRIMARIAS
//
//  Created by Hélder José Alves Gonçalves on 28/02/14.
//  Copyright (c) 2014 Hélder José Alves Gonçalves. All rights reserved.
//

#ifndef CG_FORMAS_PRIMARIAS_plano_h
#define CG_FORMAS_PRIMARIAS_plano_h

#include <GL/glew.h>
#include <GLUT/glut.h>
#include <math.h>

void plano(float altura, float lado, int sep_h, int sep_v, float z_index, int ori);
void paralelepipedo(float altura, float lado_x, float lado_z, int sep_h, int sep_v);

#endif
