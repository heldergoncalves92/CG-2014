//
//  cilindro.cpp
//  CG-FORMAS-PRIMARIAS
//
//  Created by Hélder José Alves Gonçalves on 27/02/14.
//  Copyright (c) 2014 Hélder José Alves Gonçalves. All rights reserved.
//

#include "cilindro.h"

void cilindro(float raio,int lados,float alt,int sep_cir,int sep_h){
    float angulo=(2*M_PI)/lados,x,y=0,l_aux,h_aux1,h_aux2=0;
    
    circulo(raio, lados, sep_cir, 0, 0);
    circulo(raio, lados, sep_cir, alt, 1);
    
    alt=alt/sep_h;
    glBegin(GL_TRIANGLES);
    for(;sep_h>0;sep_h--){
        h_aux1=h_aux2;
        h_aux2+=alt;
        y=0;

        for (l_aux=0; l_aux<=lados; l_aux++) {
            x=y;
            y+=angulo;
            
            glVertex3f(raio*sin(x), h_aux2, raio*cos(x));
            glVertex3f(raio*sin(x), h_aux1, raio*cos(x));
            glVertex3f(raio*sin(y), h_aux2, raio*cos(y));
            
            glVertex3f(raio*sin(x), h_aux1, raio*cos(x));
            glVertex3f(raio*sin(y), h_aux1, raio*cos(y));
            glVertex3f(raio*sin(y), h_aux2, raio*cos(y));
        }
    }
    glEnd();
}

void cilindroVBO(float raio,int lados,float alt,int sep_cir,int sep_h){
    float angulo=(2*M_PI)/lados,x,y=0,l_aux,h_aux1,h_aux2=0;
    
    circulo(raio, lados, sep_cir, 0, 0);
    circulo(raio, lados, sep_cir, alt, 1);
    
    alt=alt/sep_h;
    glBegin(GL_TRIANGLES);
    for(;sep_h>0;sep_h--){
        h_aux1=h_aux2;
        h_aux2+=alt;
        y=0;
        
        for (l_aux=0; l_aux<=lados; l_aux++) {
            x=y;
            y+=angulo;
            
            glVertex3f(raio*sin(x), h_aux2, raio*cos(x));
            glVertex3f(raio*sin(x), h_aux1, raio*cos(x));
            glVertex3f(raio*sin(y), h_aux2, raio*cos(y));
            
            glVertex3f(raio*sin(x), h_aux1, raio*cos(x));
            glVertex3f(raio*sin(y), h_aux1, raio*cos(y));
            glVertex3f(raio*sin(y), h_aux2, raio*cos(y));
        }
    }
    glEnd();
}


