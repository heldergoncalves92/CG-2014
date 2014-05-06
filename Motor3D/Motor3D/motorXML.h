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
#include <stdio.h>
#include "tinyxml/tinyxml.h"
#include "modelo.h"
#include "catmull.h"
#include "rotacoes.h"

void motor_XML(TiXmlNode *doc);
void motor_XML2(TiXmlNode *doc);
void prepara_MotorXML2(TiXmlNode* root);
void prepara_MotorXML_trans(TiXmlNode* root);

#endif
