//
//  motor.cpp
//  Motor3D
//
//  Created by Hélder José Alves Gonçalves on 12/03/14.
//  Copyright (c) 2014 Duarte Nuno Ferreira Duarte. All rights reserved.
//

#include "motorXML.h"

Modelo lista_modelos=NULL;
Rotacao *rotacoes=NULL, *rot_actual=NULL;
Translacao *translacoes=NULL, *tra_actual=NULL;
long currentTime=0;
int rot_flag=1,first;
int tra_flag=1;



void motor_XML(TiXmlNode* root){
    
    TiXmlNode *child;
    TiXmlAttribute * attr;
    Modelo modelo;
    const char* tag;
    float x,y,z,angulo;
    
    
    
    for (child = root->FirstChild(); child; child=child->NextSibling()) {
        tag=child->Value();
        
        if (strcmp(tag, "modelo")==0) {
            attr=child->ToElement()->FirstAttribute();
            if (strcmp(attr->Name(), "ficheiro")==0) {
                modelo=search_Modelo(attr->Value(), lista_modelos);
                if (modelo) {
                   // desenha_modelo(modelo);
                    modelo=NULL;
                }else
                  //  ler_modelo(attr->Value());
                                        modelo=NULL;
            }
        }else
            if (strcmp(tag, "grupo")==0) {
                glPushMatrix();
                motor_XML((child));
                glPopMatrix();
            }else
                if (strcmp(tag, "translacao")==0) {
                    x=y=z=0;
                    for(attr=child->ToElement()->FirstAttribute();attr;attr=attr->Next()){
                        if (strcmp(attr->Name(), "x")==0)
                            x=atof(attr->Value());
                        else
                            if (strcmp(attr->Name(), "y")==0)
                                y=atof(attr->Value());
                            else
                                if (strcmp(attr->Name(), "z")==0)
                                    z=atof(attr->Value());
                    }
                    glTranslatef(x, y, z);
                }else
                    if (strcmp(tag, "rotacao")==0) {
                        angulo=x=y=z=0;
                        for(attr=child->ToElement()->FirstAttribute();attr;attr=attr->Next()){
                            if (strcmp(attr->Name(), "x")==0)
                                x=atof(attr->Value());
                            else
                                if (strcmp(attr->Name(), "y")==0)
                                    y=atof(attr->Value());
                                else
                                    if (strcmp(attr->Name(), "z")==0)
                                        z=atof(attr->Value());
                                    else
                                        if (strcmp(attr->Name(), "angulo")==0)
                                            angulo=atof(attr->Value());
                        }
                        glRotatef(angulo, x, y, z);
                    }else
                        if (strcmp(tag, "escala")==0) {
                            x=y=z=1;
                            for(attr=child->ToElement()->FirstAttribute();attr;attr=attr->Next()){
                                if (strcmp(attr->Name(), "x")==0)
                                    x=atof(attr->Value());
                                else
                                    if (strcmp(attr->Name(), "y")==0)
                                        y=atof(attr->Value());
                                    else
                                        if (strcmp(attr->Name(), "z")==0)
                                            z=atof(attr->Value());
                            }
                            glScalef(x, y, z);
                        }
        
    }
}

void motor_XML2(TiXmlNode* root){
    
    TiXmlNode *child;
    TiXmlAttribute * attr;
    Modelo modelo;
    const char* tag;
    float x,y,z,angulo,tempo;
    static float a = 0;
    Point *listaPontos=NULL;
    int numeroPontos=-1;
    float timeTrans=-1;
  //  int fixo=1;
    
    currentTime = glutGet(GLUT_ELAPSED_TIME);
    
    for (child = root->FirstChild(); child; child=child->NextSibling()) {
        tag=child->Value();
        
        if (strcmp(tag, "modelo")==0) {
            attr=child->ToElement()->FirstAttribute();
            if (strcmp(attr->Name(), "ficheiro")==0) {
                modelo=search_Modelo(attr->Value(), lista_modelos);
                if (modelo) {

                    if(modelo->tipo==1)
                        desenha_RTime(modelo->u.rTime);
                    else
                        desenha_vbo(modelo->u.vbo);
                }else{
                    std::regex e ("(.*)(.vbo)");
                    if(std::regex_match(attr->Value(), e) )
                        lista_modelos=ler_VBO(attr->Value(),lista_modelos);
                    else{
                        std::regex e ("(.*)(.3d)");
                        if(std::regex_match(attr->Value(), e) )
                             lista_modelos=ler_RTime(attr->Value(),lista_modelos);
                    }
                }
            }
        }else
            if (strcmp(tag, "grupo")==0) {
                glPushMatrix();
                motor_XML2((child));
                glPopMatrix();
            }else
                if (strcmp(tag, "translacao")==0) {
                    if(tra_flag){
                        for(attr=child->ToElement()->FirstAttribute();attr;attr=attr->Next())
                            if (strcmp(attr->Name(), "tempo")==0)
                                timeTrans=atof(attr->Value());
                        listaPontos = NULL;
                        numeroPontos = -1;
                        numeroPontos = lerPontos(child, &listaPontos);
                        translacoes=insereTranslacao(listaPontos,translacoes,numeroPontos, timeTrans);
                    }
                    else {
                        tra_actual=do_translacao(tra_actual, a);
                        if(!tra_actual){
                            tra_actual=translacoes;
                        }
                        a+=0.001;
                    }
                }else
                    if (strcmp(tag, "translacaofixa")==0) {
                        x=y=z=0;
                        for(attr=child->ToElement()->FirstAttribute();attr;attr=attr->Next()){
                            if (strcmp(attr->Name(), "x")==0)
                                x=atof(attr->Value());
                            else
                                if (strcmp(attr->Name(), "y")==0)
                                    y=atof(attr->Value());
                                else
                                    if (strcmp(attr->Name(), "z")==0)
                                        z=atof(attr->Value());
                            }
                        glTranslatef(x, y, z);
                }else
                    if (strcmp(tag, "rotacao")==0) {
                        if(rot_flag){
                            angulo=x=y=z=0;
                           // fixo=0;
                            for(attr=child->ToElement()->FirstAttribute();attr;attr=attr->Next()){
                                if (strcmp(attr->Name(), "x")==0)
                                    x=atof(attr->Value());
                                else
                                    if (strcmp(attr->Name(), "y")==0)
                                        y=atof(attr->Value());
                                    else
                                        if (strcmp(attr->Name(), "z")==0)
                                            z=atof(attr->Value());
                                        else
                                            if (strcmp(attr->Name(), "tempo")==0)
                                                tempo=atof(attr->Value());
                                          //  else
                                           //     if (strcmp(attr->Name(), "fixo")==0)
                                           //         fixo=atoi(attr->Value());
                            }
                            rotacoes=insereRotacao(tempo,x,y,z,rotacoes);
                        }
                        else{
                            //if(fixo)
                            rot_actual=do_rotacao(rot_actual,currentTime);
                            if(!rot_actual)
                                rot_actual=rotacoes;
                            // rotacoes->alfa= 360/(rotacoes->periodo);;
                            
                        }
                }else
                    if (strcmp(tag, "rotacaofixa")==0) {
                        angulo=x=y=z=0;
                        for(attr=child->ToElement()->FirstAttribute();attr;attr=attr->Next()){
                            if (strcmp(attr->Name(), "x")==0)
                                x=atof(attr->Value());
                            else
                                if (strcmp(attr->Name(), "y")==0)
                                    y=atof(attr->Value());
                                else
                                    if (strcmp(attr->Name(), "z")==0)
                                        z=atof(attr->Value());
                                    else
                                        if (strcmp(attr->Name(), "angulo")==0)
                                                angulo=atof(attr->Value());
                            }
                            glRotatef(angulo, x, y, z);
                            rot_actual=rotacoes;
                    }else{
                        if (strcmp(tag, "escala")==0) {
                            x=y=z=1;
                            for(attr=child->ToElement()->FirstAttribute();attr;attr=attr->Next()){
                                if (strcmp(attr->Name(), "x")==0)
                                    x=atof(attr->Value());
                                else
                                    if (strcmp(attr->Name(), "y")==0)
                                        y=atof(attr->Value());
                                    else
                                        if (strcmp(attr->Name(), "z")==0)
                                            z=atof(attr->Value());
                            }
                            glScalef(x, y, z);
                        }
                    }
        
    }
}

void prepara_MotorXML2(TiXmlNode* root){
    //if (tipo==0){
    if(rot_flag){
        
        motor_XML2(root);
        rot_flag=0;
        tra_flag=0;
    }
    
    tra_actual=translacoes;
    rot_actual=rotacoes;
    motor_XML2(root);

    
}
