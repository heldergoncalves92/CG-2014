//
//  motor.cpp
//  Motor3D
//
//  Created by Hélder José Alves Gonçalves on 12/03/14.
//  Copyright (c) 2014 Duarte Nuno Ferreira Duarte. All rights reserved.
//

#include "motor.h"

void desenha_modelo(const char* filename){

    float cx,cy,cz;
    FILE *f = fopen(filename, "r");
    if(f){
        glBegin(GL_TRIANGLES);
        while (fscanf(f, "%f %f %f\n", &cx, &cy, &cz)!=EOF){
            glColor3f(cx, cy, cz);
            glVertex3f(cx, cy, cz);
        }
        glEnd();
    }

}

void motor_XML(TiXmlDocument doc){
    
    TiXmlElement *root = doc.RootElement();
    TiXmlNode *child;
    TiXmlAttribute * attr;
    const char* tag;
    
    
    for (child = root->FirstChild(); child; child=child->NextSibling()) {
        tag=child->Value();

        if (strcmp(tag, "modelo")==0) {
            attr=child->ToElement()->FirstAttribute();
            if (strcmp(attr->Name(), "ficheiro")==0) {
                desenha_modelo(attr->Value());
            }

        }
    }
}