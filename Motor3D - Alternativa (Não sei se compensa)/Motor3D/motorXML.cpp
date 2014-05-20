//
//  motor.cpp
//  Motor3D
//
//  Created by Hélder José Alves Gonçalves on 12/03/14.
//  Copyright (c) 2014 Duarte Nuno Ferreira Duarte. All rights reserved.
//

#include "motorXML.h"

Modelo lista_modelos=NULL;
Rotacao *rotacao=NULL;
Translacao *translacao=NULL;
Escala escala=NULL;

int first;



Accao insereAccao(int tipo, void* accao, Accao lista){
    
    Accao aux=(Accao)malloc(sizeof(NAccao)),aux2=lista;
    
    aux->tipo=tipo;
    aux->next=NULL;
    
    switch (tipo) {
        case 0: //Modelo
            aux->u.modelo=(Modelo)accao;
            break;
        case 1: //Rotacao
            aux->u.rotacao=(Rotacao*)accao;
            break;
        case 2: //Translacao
            aux->u.translacao=(Translacao*)accao;
            break;
        case 3: //Escala
            aux->u.escala=(Escala)accao;
            break;
        default:
            break;
    }
    
    if(!lista)
        return aux;
    
    while (lista->next)
        lista=lista->next;
    lista->next=aux;
    
    return aux2;
}

void motor_XML(){
    
    
    while(accao_actual) {
        switch (accao_actual->tipo) {
            case 0:
                if (accao_actual->u.modelo->tipo==1)
                    desenha_RTime(accao_actual->u.modelo->u.rTime);
                else
                    desenha_vbo(accao_actual->u.modelo->u.vbo);
                break;
            case 1:
                do_rotacao(accao_actual->u.rotacao ,currentTime);
                break;
            case 2:
                do_translacao(accao_actual->u.translacao, currentTime);
                break;
            case 3:
                do_escala(accao_actual->u.escala);
                break;
            case 4:
                glPushMatrix();
                break;
            case 5:
                glPopMatrix();
                break;
            default:
                break;
        }
        
        if(accao_actual)
            accao_actual=accao_actual->next;
        
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
    int flag;
    
    
    for (child = root->FirstChild(); child; child=child->NextSibling()) {
        tag=child->Value();
        if (strcmp(tag, "grupo")==0) {
            accao=insereAccao(4, NULL, accao);
            prepara_MotorXML((child));
            accao=insereAccao(5, NULL, accao);
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
                        accao=insereAccao(0, (void*)search_Modelo(attr->Value(), lista_modelos), accao);
                    }else
                        accao=insereAccao(0, (void*)modelo, accao);
                }
            }else
                if (strcmp(tag, "translacao")==0) {
                    x=y=z=0;
                    flag=0;
                    timeTrans=0;
                    for(attr=child->ToElement()->FirstAttribute();attr;attr=attr->Next()){
                        if (strcmp(attr->Name(), "tempo")==0)
                            timeTrans=atof(attr->Value());
                        else
                            if (strcmp(attr->Name(), "x")==0){
                                x=atof(attr->Value());
                                flag=1;}
                            else
                                if (strcmp(attr->Name(), "y")==0){
                                        y=atof(attr->Value());
                                        flag=1;}
                                else
                                    if (strcmp(attr->Name(), "z")==0){
                                        z=atof(attr->Value());
                                        flag=1;
                                    }
                    }
                    if(flag==1)
                        timeTrans=0;
                    listaPontos = NULL;
                    numeroPontos = -1;
                    numeroPontos = lerPontos(child, &listaPontos);
                    translacao=insereTranslacao(listaPontos,translacao,numeroPontos, timeTrans, x, y, z);
                    accao=insereAccao(2, (void*) translacao, accao);
                }
                else
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
                                        else
                                            if (strcmp(attr->Name(), "angulo")==0)
                                                angulo=atof(attr->Value());
                        }
                        if(angulo)
                            rotacao=insereRotacao(0,angulo,x,y,z,rotacao);
                        else
                            rotacao=insereRotacao(tempo,0,x,y,z,rotacao);
                        accao=insereAccao(1, (void*)rotacao, accao);
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
                            escala=insereEscala(x,y,z,escala);
                            accao=insereAccao(3, (void*)escala, accao);
                        }
    }
}

