//
//  plano.cpp
//  CG-FORMAS-PRIMARIAS
//
//  Created by Hélder José Alves Gonçalves on 28/02/14.
//  Copyright (c) 2014 Hélder José Alves Gonçalves. All rights reserved.
//

#include "plano.h"
#include <stdio.h>

/* Tipos de planos
 1 -> +XoY
 2 -> -XoY
 
 3 -> +ZoY
 4 -> -ZoY
 
 5 -> +ZoX
 6 -> -ZoX
 
*/

void plano(float altura, float lado, int sep_h, int sep_v, float z_index, int ori){
    int i;
    
    float l_const=lado/sep_v, alt_const=altura/sep_h,alt_ori=-altura/2,lado_ori=-lado/2;
    
    glBegin(GL_TRIANGLES);
    switch (ori) {
        case 1:
            for(altura=alt_ori;sep_h>0;sep_h--){
                i=0;
                for(lado=lado_ori;i<sep_v;i++){
                    glColor3f(1, 0, 0);
                    glVertex3f(lado,altura, z_index);
                    glVertex3f(lado+l_const,altura, z_index);
                    glVertex3f(lado,altura+alt_const, z_index);
            
                    glVertex3f(lado+l_const,altura, z_index);
                    glVertex3f(lado+l_const,altura+alt_const, z_index);
                    glVertex3f(lado,altura+alt_const, z_index);
                    lado+=l_const;
                }
                altura+=alt_const;
            }
            break;
        case 2:
            for(altura=alt_ori;sep_h>0;sep_h--){
                i=0;
                for(lado=lado_ori;i<sep_v;i++){
                                        glColor3f(1, 0.5, 0);
                    glVertex3f(lado,altura, z_index);
                    glVertex3f(lado,altura+alt_const, z_index);
                    glVertex3f(lado+l_const,altura, z_index);
                    
                    glVertex3f(lado+l_const,altura, z_index);
                    glVertex3f(lado,altura+alt_const, z_index);
                    glVertex3f(lado+l_const,altura+alt_const, z_index);
                    lado+=l_const;
                }
                altura+=alt_const;
            }
            break;
        case 3:
            for(altura=alt_ori;sep_h>0;sep_h--){
                i=0;
                for(lado=lado_ori;i<sep_v;i++){
                                        glColor3f(1, 1, 0);
                    glVertex3f(z_index,altura, lado);
                    glVertex3f(z_index,altura+alt_const, lado);
                    glVertex3f(z_index,altura, lado+l_const);
                    
                    glVertex3f(z_index,altura, lado+l_const);
                    glVertex3f(z_index,altura+alt_const, lado);
                    glVertex3f(z_index,altura+alt_const, lado+l_const);
                    lado+=l_const;
                }
                altura+=alt_const;
            }
            break;
        case 4:
            for(altura=alt_ori;sep_h>0;sep_h--){
                i=0;
                for(lado=lado_ori;i<sep_v;i++){
                                        glColor3f(0, 0, 1);
                    glVertex3f(z_index,altura, lado);
                    glVertex3f(z_index,altura, lado+l_const);
                    glVertex3f(z_index,altura+alt_const, lado);
                    
                    glVertex3f(z_index,altura,lado+l_const);
                    glVertex3f(z_index,altura+alt_const, lado+l_const);
                    glVertex3f(z_index,altura+alt_const, lado);
                    lado+=l_const;
                }
                altura+=alt_const;
            }
            break;
        case 5:
            for(altura=alt_ori;sep_h>0;sep_h--){
                i=0;
                for(lado=lado_ori;i<sep_v;i++){
                                        glColor3f(1, 0, 1);
                    glVertex3f(altura,z_index, lado);
                    glVertex3f(altura,z_index, lado+l_const);
                    glVertex3f(altura+alt_const,z_index, lado);
                    
                    glVertex3f(altura,z_index,lado+l_const);
                    glVertex3f(altura+alt_const,z_index, lado+l_const);
                    glVertex3f(altura+alt_const,z_index, lado);
                    lado+=l_const;
                }
                altura+=alt_const;
            }
            break;
        case 6:
            for(altura=alt_ori;sep_h>0;sep_h--){
                i=0;
                for(lado=lado_ori;i<sep_v;i++){
                                        glColor3f(0, 1, 0);
                    glVertex3f(altura,z_index, lado);
                    glVertex3f(altura+alt_const,z_index, lado);
                    glVertex3f(altura,z_index, lado+l_const);
                    
                    glVertex3f(altura,z_index, lado+l_const);
                    glVertex3f(altura+alt_const,z_index, lado);
                    glVertex3f(altura+alt_const,z_index, lado+l_const);
                    lado+=l_const;
                }
                altura+=alt_const;
            }
            break;
            
        default:
            break;
    }
    glEnd();
}


void paralelepipedo(float altura, float lado_x, float lado_z, int sep_h, int sep_v){
    
    plano(altura, lado_x, sep_h, sep_v, lado_z/2, 1);
    plano(altura, lado_x, sep_h, sep_v, -lado_z/2, 2);
    
    plano(altura, lado_z, sep_h, sep_v, lado_x/2, 3);
    plano(altura, lado_z, sep_h, sep_v, -lado_x/2, 4);
    
    plano(lado_x, lado_z, sep_h, sep_v, altura/2, 5);
    plano(lado_x, lado_z, sep_h, sep_v, -altura/2, 6);
}








