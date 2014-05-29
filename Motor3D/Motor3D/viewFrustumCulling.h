//
//  viewFrustumCulling.h
//  Motor3D
//
//  Created by Hélder José Alves Gonçalves on 28/05/14.
//  Copyright (c) 2014 Duarte Nuno Ferreira Duarte. All rights reserved.
//

#ifndef __Motor3D__viewFrustumCulling__
#define __Motor3D__viewFrustumCulling__

#define INSIDE 1001
#define OUT 1002
#define ESFERA 1
#define CUBO 0

#include <iostream>
#include <GLUT/glut.h>

//Tipo  --  0 => Caixa alinhada com os eixos
//          1 => Esfera

typedef struct sVFC{
    
    float maxX, maxY, maxZ;
    float minX, minY, minZ;
    
}*ViewFrustum, NViewFrustum;



int testaModelo(ViewFrustum vfc);

#endif /* defined(__Motor3D__viewFrustumCulling__) */
