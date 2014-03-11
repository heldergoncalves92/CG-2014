//
//  cone.cpp
//  CG-FORMAS-PRIMARIAS
//
//  Created by Hélder José Alves Gonçalves on 10/03/14.
//  Copyright (c) 2014 Hélder José Alves Gonçalves. All rights reserved.
//

#include "cone.h"

void cone(float raio_base, float altura, int lados, int sep_circulo, int sep_h, FILE* f){
    float angulo=(2*M_PI)/lados,x,y=0,l_aux,  alt_aux1,alt_aux2=0,r_aux1,r_aux2=raio_base;
    altura/=sep_h;
    
    float i=1,factor_h=(i/sep_h);
    
    circulo(raio_base, lados, sep_circulo, 0, 0,f);
    for(;sep_h>1;sep_h--){
        alt_aux1=alt_aux2;
        alt_aux2+=altura;
        y=0;
        i-=factor_h;
        r_aux1=r_aux2;
        r_aux2=raio_base *i;
        
        for (l_aux=0; l_aux<lados; l_aux++) {
            x=y;
            y+=angulo;
            fprintf(f,"%f %f %f\n",r_aux2*sin(x), alt_aux2, r_aux2*cos(x));
            fprintf(f,"%f %f %f\n",r_aux1*sin(x), alt_aux1, r_aux1*cos(x));
            fprintf(f,"%f %f %f\n",r_aux2*sin(y), alt_aux2, r_aux2*cos(y));

            fprintf(f,"%f %f %f\n",r_aux1*sin(x), alt_aux1, r_aux1*cos(x));
            fprintf(f,"%f %f %f\n",r_aux1*sin(y), alt_aux1, r_aux1*cos(y));
            fprintf(f,"%f %f %f\n",r_aux2*sin(y), alt_aux2, r_aux2*cos(y));
        }
    }
    
    alt_aux1=alt_aux2;
    alt_aux2+=altura;
    y=0;
    i-=factor_h;
    r_aux1=r_aux2;
    r_aux2=raio_base *i;
    
    for (l_aux=0; l_aux<lados; l_aux++) {
        x=y;
        y+=angulo;  
        fprintf(f,"%f %f %f\n",r_aux1*sin(x), alt_aux1, r_aux1*cos(x));
        fprintf(f,"%f %f %f\n",r_aux1*sin(y), alt_aux1, r_aux1*cos(y));
        fprintf(f,"%f %f %f\n",r_aux2*sin(y), alt_aux2, r_aux2*cos(y));
    }
}

