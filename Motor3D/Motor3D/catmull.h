//
//  catmull.h
//  Motor3D
//
//  Created by Duarte Nuno Ferreira Duarte on 23/04/14.
//  Copyright (c) 2014 Duarte Nuno Ferreira Duarte. All rights reserved.
//

#ifndef __Motor3D__catmull__
#define __Motor3D__catmull__

#include <iostream>
#include "tinyxml/tinyxml.h"

typedef struct point {
    float coords[3] = {0.0f, 0.0f,0.0f};
    struct point *next=NULL;
} Point;

typedef struct translacao{
    float res[3];
    int point_count;
    Point *points;
    float tempo;
    struct translacao *next;
}Translacao;

int lerPontos(TiXmlNode* root, Point **res);
Translacao* insereTranslacao(Point *listaPontos, Translacao *translacoes, int numeroPontos, float tempo);
Translacao* do_translacao(Translacao* rot, float a);
void getCatmullRomPointDERIVADA(float t, int *indices, float *res, Point *points);

#endif /* defined(__Motor3D__catmull__) */

