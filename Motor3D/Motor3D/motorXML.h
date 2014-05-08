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

extern Rotacao *rotacoes, *rot_actual;
extern Translacao *translacoes, *tra_actual;
extern Escala escalas, esc_actual;
extern long currentTime;


void motor_XML(TiXmlNode *doc);
void prepara_MotorXML(TiXmlNode* root);

#endif
