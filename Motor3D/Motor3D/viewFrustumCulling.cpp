//
//  viewFrustumCulling.cpp
//  Motor3D
//
//  Created by Hélder José Alves Gonçalves on 28/05/14.
//  Copyright (c) 2014 Duarte Nuno Ferreira Duarte. All rights reserved.
//

#include "viewFrustumCulling.h"

float M[16],P[16],A[16];


int testaPonto(float x, float y, float z){
    float lx, ly, lz, lw, w=1;
    
    lx= A[0]*x + A[4]*y + A[8]*z + A[12]*w;
    ly= A[1]*x + A[5]*y + A[9]*z + A[13]*w;
    lz= A[2]*x + A[6]*y + A[10]*z + A[14]*w;
    lw= A[3]*x + A[7]*y + A[11]*z + A[15]*w;
    
    if ( lx<-lw || lx>lw)
        return OUT;
    if ( ly<-lw || ly>lw)
        return OUT;
    if ( lz<-lw || lz>lw)
        return OUT;
    
    return INSIDE;
}


int testaSOLID(float maxX, float minX, float maxY, float minY, float maxZ, float minZ){
    
    
    if(testaPonto(maxX, maxY, maxZ)==INSIDE)
        return INSIDE;
    
    if(testaPonto(minX, maxY, maxZ)==INSIDE)
        return INSIDE;
    
    if(testaPonto(maxX, minY, maxZ)==INSIDE)
        return INSIDE;
    
    if(testaPonto(minX, minY, maxZ)==INSIDE)
        return INSIDE;
    
    if(testaPonto(maxX, maxY, minZ)==INSIDE)
        return INSIDE;
    
    if(testaPonto(minX, maxY, minZ)==INSIDE)
        return INSIDE;
    
    if(testaPonto(maxX, minY, minZ)==INSIDE)
        return INSIDE;
    
    if(testaPonto(minX, minY, minZ)==INSIDE)
        return INSIDE;
    
    
    
    return OUT;
}


int testaModelo(ViewFrustum vfc){
    glGetFloatv(GL_MODELVIEW_MATRIX,M);
    glGetFloatv(GL_PROJECTION_MATRIX,P);
    
    
    //Push para guardar matriz original
    glPushMatrix();
    
    //Carregar a matriz P e multiplicar pela matriz M
    glLoadMatrixf(P);
    glMultMatrixf(M);
    
    //Obter a matriz A e POP para a matriz original
    glGetFloatv(GL_MODELVIEW_MATRIX, A);
    glPopMatrix();
    
    if (testaSOLID(vfc->maxX,vfc->minX,vfc->maxY,vfc->minY,vfc->maxZ,vfc->minZ)==OUT)
        return OUT;

    
    
    return INSIDE;
}




void desenhaCaixa(ViewFrustum view){
    
    if(view){
        //Para ver caixas utilizadas no viewfruntum
        glBegin(GL_LINE_LOOP);
        glVertex3f(view->maxX, view->maxY, view->maxZ);
        glVertex3f(view->maxX, view->minY, view->maxZ);
        glVertex3f(view->minX, view->minY, view->maxZ);
        glVertex3f(view->minX, view->maxY, view->maxZ);
        glEnd();
        
        glBegin(GL_LINE_LOOP);
        glVertex3f(view->maxX, view->maxY, view->minZ);
        glVertex3f(view->maxX, view->minY, view->minZ);
        glVertex3f(view->minX, view->minY, view->minZ);
        glVertex3f(view->minX, view->maxY, view->minZ);
        glEnd();
        
        glBegin(GL_LINE_STRIP);
        glVertex3f(view->maxX, view->maxY, view->maxZ);
        glVertex3f(view->maxX, view->maxY, view->minZ);
        glEnd();
        
        glBegin(GL_LINE_STRIP);
        glVertex3f(view->minX, view->maxY, view->maxZ);
        glVertex3f(view->minX, view->maxY, view->minZ);
        glEnd();
        
        glBegin(GL_LINE_STRIP);
        glVertex3f(view->maxX, view->minY, view->maxZ);
        glVertex3f(view->maxX, view->minY, view->minZ);
        glEnd();
        
        glBegin(GL_LINE_STRIP);
        glVertex3f(view->minX, view->minY, view->maxZ);
        glVertex3f(view->minX, view->minY, view->minZ);
        glEnd();

    }
}

/*
 //Calcula a matrix A
 A[0] =P[0]*M[0] + P[4]*M[1] + P[8]*M[2]  + P[12]*M[3];
 A[1] =P[1]*M[0] + P[5]*M[1] + P[9]*M[2]  + P[13]*M[3];
 A[2] =P[2]*M[0] + P[6]*M[1] + P[10]*M[2] + P[14]*M[3];
 A[3] =P[3]*M[0] + P[7]*M[1] + P[11]*M[2] + P[15]*M[3];
 
 A[4] =P[0]*M[4] + P[4]*M[5] + P[8]*M[6]  + P[12]*M[7];
 A[5] =P[1]*M[4] + P[5]*M[5] + P[9]*M[6]  + P[13]*M[7];
 A[6] =P[2]*M[4] + P[6]*M[5] + P[10]*M[6] + P[14]*M[7];
 A[7] =P[3]*M[4] + P[7]*M[5] + P[11]*M[6] + P[15]*M[7];
 
 A[8] =P[0]*M[8] + P[4]*M[9] + P[8]*M[10]  + P[12]*M[11];
 A[9] =P[1]*M[8] + P[5]*M[9] + P[9]*M[10]  + P[13]*M[11];
 A[10]=P[2]*M[8] + P[6]*M[9] + P[10]*M[10] + P[14]*M[11];
 A[11]=P[3]*M[8] + P[7]*M[9] + P[11]*M[10] + P[15]*M[11];
 
 A[12]=P[0]*M[12] + P[4]*M[13] + P[8]*M[14]  + P[12]*M[15];
 A[13]=P[1]*M[12] + P[5]*M[13] + P[9]*M[14]  + P[13]*M[15];
 A[14]=P[2]*M[12] + P[6]*M[13] + P[10]*M[14] + P[14]*M[15];
 A[15]=P[3]*M[12] + P[7]*M[13] + P[11]*M[14] + P[15]*M[15];
 */