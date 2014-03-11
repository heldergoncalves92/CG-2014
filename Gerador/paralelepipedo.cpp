//
//  paralelepipedo.cpp
//  CG-FORMAS-PRIMARIAS
//
//  Created by Hélder José Alves Gonçalves on 10/03/14.
//  Copyright (c) 2014 Hélder José Alves Gonçalves. All rights reserved.
//

#include "paralelepipedo.h"


void paralelepipedo(float altura, float lado_x, float lado_z, int sep_h, int sep_v, FILE* f){
    
    plano(altura, lado_x, sep_h, sep_v, lado_z/2, 1,f);
    plano(altura, lado_x, sep_h, sep_v, -lado_z/2, 2,f);
    
    plano(altura, lado_z, sep_h, sep_v, lado_x/2, 3,f);
    plano(altura, lado_z, sep_h, sep_v, -lado_x/2, 4,f);
    
    plano(lado_x, lado_z, sep_h, sep_v, altura/2, 5,f);
    plano(lado_x, lado_z, sep_h, sep_v, -altura/2, 6,f);
}