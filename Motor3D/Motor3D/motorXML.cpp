//
//  motor.cpp
//  Motor3D
//
//  Created by Hélder José Alves Gonçalves on 12/03/14.
//  Copyright (c) 2014 Duarte Nuno Ferreira Duarte. All rights reserved.
//

#include "motorXML.h"

Modelo lista_modelos=NULL;
//Rotacao *rotacoes=NULL, *rot_actual=NULL;
//Translacao *translacoes=NULL, *tra_actual=NULL;
long currentTime=0;
int first;





void motor_XML(TiXmlNode* root){
    
    TiXmlNode *child;
    TiXmlAttribute * attr;
    Modelo modelo;
    const char* tag;
    float x,y,z,angulo;
    static float a = 0;

    
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
                }
            }
        }else
            if (strcmp(tag, "grupo")==0) {
                glPushMatrix();
                motor_XML((child));
                glPopMatrix();
            }else
                if (strcmp(tag, "translacao")==0) {
                        tra_actual=do_translacao(tra_actual, a);
                        if(!tra_actual){
                            tra_actual=translacoes;
                        }
                        a+=0.001;
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
                            rot_actual=do_rotacao(rot_actual,currentTime);
                            if(!rot_actual)
                                rot_actual=rotacoes;
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

void prepara_MotorXML(TiXmlNode* root){
    
    TiXmlNode *child;
    TiXmlAttribute * attr;
    Modelo modelo;
    const char* tag;
    float x,y,z,angulo,tempo;
    Point *listaPontos=NULL;
    int numeroPontos=-1;
    float timeTrans=-1;
    
    
    for (child = root->FirstChild(); child; child=child->NextSibling()) {
        tag=child->Value();
        if (strcmp(tag, "grupo")==0) {
            prepara_MotorXML((child));
        }else
            if (strcmp(tag, "modelo")==0) {
                attr=child->ToElement()->FirstAttribute();
                if (strcmp(attr->Name(), "ficheiro")==0) {
                    modelo=search_Modelo(attr->Value(), lista_modelos);
                    if (!modelo) {
                        
                        std::regex e ("(.*)(.vbo)");
                        if(std::regex_match(attr->Value(), e) )
                            lista_modelos=ler_VBO(attr->Value(),lista_modelos);
                        else{
                            std::regex e ("(.*)(.3d)");
                            if(std::regex_match(attr->Value(), e) )
                                lista_modelos=ler_RTime(attr->Value(),lista_modelos);
                            else
                                printf("ERRO! Ficheiro '%s' inexistente\n", attr->Value());
                        }
                    }
                }
            }else
                if (strcmp(tag, "translacao")==0) {
                    for(attr=child->ToElement()->FirstAttribute();attr;attr=attr->Next())
                        if (strcmp(attr->Name(), "tempo")==0)
                            timeTrans=atof(attr->Value());
                    listaPontos = NULL;
                    numeroPontos = -1;
                    numeroPontos = lerPontos(child, &listaPontos);
                    translacoes=insereTranslacao(listaPontos,translacoes,numeroPontos, timeTrans);
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
                                        if (strcmp(attr->Name(), "tempo")==0)
                                            tempo=atof(attr->Value());
                        }
                        rotacoes=insereRotacao(tempo,x,y,z,rotacoes);
                    }
    }
}

