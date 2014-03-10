//
//  cilindro.cpp
//  CG-FORMAS-PRIMARIAS
//
//  Created by Hélder José Alves Gonçalves on 27/02/14.
//  Copyright (c) 2014 Hélder José Alves Gonçalves. All rights reserved.
//

#include "cilindro.h"



void cilindro(float raio,int lados,float alt,int sep_cir,int sep_h, FILE* f){
    float angulo=(2*M_PI)/lados,x,y=0,l_aux,h_aux1,h_aux2=0;
    
    circulo(raio, lados, sep_cir, 0, 0,f);
    circulo(raio, lados, sep_cir, alt, 1,f);
    
    alt=alt/sep_h;
    for(;sep_h>0;sep_h--){
        h_aux1=h_aux2;
        h_aux2+=alt;
        y=0;
        for (l_aux=0; l_aux<=lados; l_aux++) {
            x=y;
            y+=angulo;
            
            fprintf(f,"%f %f %f\n",raio*sin(x), h_aux2, raio*cos(x));
            fprintf(f,"%f %f %f\n",raio*sin(x), h_aux1, raio*cos(x));
            fprintf(f,"%f %f %f\n",raio*sin(y), h_aux2, raio*cos(y));
            
            fprintf(f,"%f %f %f\n",raio*sin(x), h_aux1, raio*cos(x));
            fprintf(f,"%f %f %f\n",raio*sin(y), h_aux1, raio*cos(y));
            fprintf(f,"%f %f %f\n",raio*sin(y), h_aux2, raio*cos(y));
        }
    }
}