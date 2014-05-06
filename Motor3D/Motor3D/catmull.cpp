//
//  catmull.cpp
//  Motor3D
//
//  Created by Duarte Nuno Ferreira Duarte on 23/04/14.
//  Copyright (c) 2014 Duarte Nuno Ferreira Duarte. All rights reserved.
//

#include "catmull.h"
#include <math.h>
#include <GLUT/GLUT.h>

//Point *points=NULL, //*last=NULL;
//int point_count;
//p = {{-1,-1,0},{-1,1,0},{1,1,0},{0,0,1},{1,-1,0}};
Point *globalPoints=NULL;
int global_point_count=0;

int lerPontos(TiXmlNode* root, Point **res){
   // int i=0,j=0;
    TiXmlNode *child;
    TiXmlAttribute * attr;
    const char* tag;
    int point_count=0;
    Point *aux=NULL,*points=NULL,*last=NULL;
    int x,y,z;
    
    /*    for (child = root->FirstChild(); child; child=child->NextSibling()){
     tag=child->Value();
     if (strcmp(tag, "ponto")==0) {
     point_count++;
     }
     }
     */
    x=y=z=0;
    //p = (float**)malloc(sizeof(float)*point_count*3);
    //float *pontoLidos = (float*)malloc(sizeof(float)*point_count*3);
    
    for (child = root->FirstChild(); child; child=child->NextSibling()) {
        tag=child->Value();
        if (strcmp(tag, "ponto")==0) {
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
            aux=(Point *)malloc(sizeof(Point));
            aux->coords[0]=x;aux->coords[1]=y;aux->coords[2]=z;
            if(last!=NULL)
                last->next=aux;
            last=aux;
            if(points==NULL)
                points=last;
            
            point_count++;
            
        }
    }
    *res=points;
    return point_count;
}


float getAt(int index, Point *points, int k) {
    int i=0;
    float res=0.0;
    Point *aux=points;
    while(i++<index && aux!=NULL){
        aux=aux->next;
    }
    
    res=aux->coords[k];
    
    return res;
}

void getCatmullRomPoint(float t, int *indices, float *res, Point *points) {
    
    int i,j,k;
    float aux[4];
    float tt[4];
    tt[0]=t*t*t;
    tt[1]=t*t;
    tt[2]=t;
    tt[3]=1;
	// catmull-rom matrix
	float m[4][4] = {	{-0.5f,  1.5f, -1.5f,  0.5f},
        { 1.0f, -2.5f,  2.0f, -0.5f},
        {-0.5f,  0.0f,  0.5f,  0.0f},
        { 0.0f,  1.0f,  0.0f,  0.0f}};
    
	res[0] = 0.0; res[1] = 0.0; res[2] = 0.0;
    // Calcular o ponto res = T * M * P
    // sendo Pi = p[indices[i]]
    for (k=0;k<3;k++){
        for (i=0;i<4;i++){
            aux[i]=0;
            for (j=0;j<4;j++){
                aux[i]+=(tt[j]*m[j][i]);
            }
        }
        for(i=0;i<4;i++){
            res[k]+=aux[i]*getAt(indices[i],points,k);
        }
    }
}


void getGlobalCatmullRomPoint(float gt, float *res) {
    
	float t = gt * global_point_count; // this is the real global t
	int index = floor(t);  // which segment
	t = t - index; // where within  the segment
    
	// indices store the points
	int indices[4];
	indices[0] = (index + global_point_count-1)%global_point_count;
    indices[1] = (indices[0]+1)%global_point_count;
	indices[2] = (indices[1]+1)%global_point_count;
    indices[3] = (indices[2]+1)%global_point_count;
    
	getCatmullRomPoint(t, indices, res, globalPoints);
}

/*
void getGlobalCatmullRomPoint(float gt, float *res) {
    int point_count = global_point_count;
    float t = gt * point_count; // this is the real global t
	int index = floor(t);  // which segment
	t = t - index; // where within  the segment
    Point *points = globalPoints;

	// indices store the points
	int indices[4];
	indices[0] = (index + point_count-1)%point_count;
    indices[1] = (indices[0]+1)%point_count;
	indices[2] = (indices[1]+1)%point_count;
    indices[3] = (indices[2]+1)%point_count;
    
	getCatmullRomPoint(t, indices, res, points);
}*/


void renderCatmullRomCurve() {
    int i;
    float res[3];
    glBegin(GL_LINE_LOOP);
    for(i=0;i<2000;i++){
        getGlobalCatmullRomPoint(i/2000.0f,res);
        glVertex3fv(res);
    }
    glEnd();
}

/*
void renderCatmullRomCurve(int point_count, Point* points) {
    int i;
    globalPoints=points;
    global_point_count=point_count;
    float res[3];
    glBegin(GL_LINE_LOOP);
    for(i=0;i<2000;i++){
        getGlobalCatmullRomPoint(i/2000.0f,res);
        glVertex3fv(res);
    }
    glEnd();
}*/

Translacao* insereTranslacao(Point *listaPontos, Translacao *translacoes, int numeroPontos, float tempo){
    Translacao *aux=NULL;
    Translacao *toEnd=NULL;
    aux=(Translacao*)malloc(sizeof(Translacao));
    aux->points=listaPontos;
    aux->point_count = numeroPontos;
    aux->tempo = tempo;
    aux->next=NULL;
    if(translacoes==NULL){
        translacoes=aux;
    } else {
        if(translacoes!=NULL)
            for(toEnd=translacoes; toEnd->next!=NULL; toEnd=toEnd->next);
        toEnd->next=aux;
    }
    return translacoes;
}

Translacao* do_translacao(Translacao* trans, float a){
    
    global_point_count=trans->point_count;
    globalPoints = trans->points;

    //float res[3];
    
    
    
    //glPushMatrix();
    getGlobalCatmullRomPoint(a/trans->tempo,trans->res);
    renderCatmullRomCurve();

    glTranslatef(trans->res[0],trans->res[1],trans->res[2]);
    //glTranslatef(res[0],res[1],res[2]);
    //glPopMatrix();
    return trans->next;
}
