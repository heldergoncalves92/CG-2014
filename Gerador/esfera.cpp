//
//  esfera.cpp
//  CG-FORMAS-PRIMARIAS
//
//  Created by Hélder José Alves Gonçalves on 27/02/14.
//  Copyright (c) 2014 Hélder José Alves Gonçalves. All rights reserved.
//

#include "esfera.h"

void esfera(float raio, int sep_h, int sep_cir, FILE* f){
    float   angulo_cir=(2*M_PI)/sep_cir,
            angulo_h=(M_PI)/sep_h,
            x,y,l_aux,lh_aux,h_aux1,h_aux2=M_PI_2;
    
    
        for(lh_aux=0;lh_aux<sep_h;lh_aux++){
            h_aux1=h_aux2;
            h_aux2+=angulo_h;
            y=0;
            
            for (l_aux=0; l_aux<=sep_cir; l_aux++) {
                x=y;
                y+=angulo_cir;
                fprintf(f,"%f %f %f\n",sin(x)*cos(h_aux1), sin(h_aux1), cos(x)*cos(h_aux1));
                fprintf(f,"%f %f %f\n",sin(x)*cos(h_aux2), sin(h_aux2), cos(x)*cos(h_aux2));
                fprintf(f,"%f %f %f\n",sin(y)*cos(h_aux1), sin(h_aux1), cos(y)*cos(h_aux1));

                fprintf(f,"%f %f %f\n",sin(x)*cos(h_aux2), sin(h_aux2), cos(x)*cos(h_aux2));
                fprintf(f,"%f %f %f\n",sin(y)*cos(h_aux2), sin(h_aux2), cos(y)*cos(h_aux2));
                fprintf(f,"%f %f %f\n",sin(y)*cos(h_aux1), sin(h_aux1), cos(y)*cos(h_aux1));
            }
        }   
}