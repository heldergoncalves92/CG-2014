//
//  motor.h
//  Motor3D
//
//  Created by Hélder José Alves Gonçalves on 12/03/14.
//  Copyright (c) 2014 Duarte Nuno Ferreira Duarte. All rights reserved.
//

#ifndef Motor3D_motorXML_h
#define Motor3D_motorXML_h


//#include <GL/glew.h>
#include <GLUT/glut.h>
#include <iostream>
#include <string>
#include <regex>
#include "tinyxml/tinyxml.h"
#include "modelo.h"
#include "catmull.h"
#include "rotacoes.h"
#include "escala.h"

typedef struct sAccao{
    int tipo;
    union{
        Modelo modelo;
        Escala escala;
        Rotacao *rotacao;
        Translacao *translacao;
    }u;
    struct sAccao *next;
}*Accao, NAccao;


extern Accao accao, accao_actual;
extern long currentTime;


void motor_XML();
void prepara_MotorXML(TiXmlNode* root);

#endif
