//
//  cone.cpp
//  CG-FORMAS-PRIMARIAS
//
//  Created by Hélder José Alves Gonçalves on 10/03/14.
//  Copyright (c) 2014 Hélder José Alves Gonçalves. All rights reserved.
//

#include "cone.h"

//Variavel global, para ajuda do calculo da normal
float resN[3];

void cone(float raio_base, float altura, int fatias, int aneis, int camadas, FILE* f){
    float angulo=(2*M_PI)/fatias,x,y=0,l_aux,  alt_aux1,alt_aux2=0,r_aux1,r_aux2=raio_base;
    altura/=camadas;
    
    float i=1,factor_h=(i/camadas);
    
    fprintf(f,"%d\n",(2*fatias*(aneis-1)+fatias)*9+((camadas-1)*fatias*2+fatias)*9);


    
    float raio = raio_base/aneis;

    for(l_aux=0;l_aux<fatias;l_aux++){
            x=y;
            y+=angulo;
            fprintf(f,"%d %f %d\n",0, 0.0, 0);
            fprintf(f,"%f %f %f\n",raio*sin(y), 0.0, raio*cos(y));
            fprintf(f,"%f %f %f\n",raio*sin(x), 0.0, raio*cos(x));
        }
        r_aux2=raio;
        y=0;
        for(aneis--;aneis>0;aneis--){
            r_aux1=r_aux2;
            r_aux2+=raio;
            
            for(l_aux=0;l_aux<fatias;l_aux++){
                x=y;
                y+=angulo;
                fprintf(f,"%f %f %f\n",r_aux1*sin(x), 0.0, r_aux1*cos(x));
                fprintf(f,"%f %f %f\n",r_aux1*sin(y), 0.0, r_aux1*cos(y));
                fprintf(f,"%f %f %f\n",r_aux2*sin(x), 0.0, r_aux2*cos(x));
                
                fprintf(f,"%f %f %f\n",r_aux1*sin(y), 0.0, r_aux1*cos(y));
                fprintf(f,"%f %f %f\n",r_aux2*sin(y), 0.0, r_aux2*cos(y));
                fprintf(f,"%f %f %f\n",r_aux2*sin(x), 0.0, r_aux2*cos(x));
            }
        }


    for(;camadas>1;camadas--){
        alt_aux1=alt_aux2;
        alt_aux2+=altura;
        y=0;
        i-=factor_h;
        r_aux1=r_aux2;
        r_aux2=raio_base *i;
        
        for (l_aux=0; l_aux<fatias; l_aux++) {
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
    
    for (l_aux=0; l_aux<fatias; l_aux++) {
        x=y;
        y+=angulo;  
        fprintf(f,"%f %f %f\n",r_aux1*sin(x), alt_aux1, r_aux1*cos(x));
        fprintf(f,"%f %f %f\n",r_aux1*sin(y), alt_aux1, r_aux1*cos(y));
        fprintf(f,"%f %f %f\n",r_aux2*sin(y), alt_aux2, r_aux2*cos(y));
    }
}

void normal(float v1[], float v2[]){
    float modulo;
    
    //Vector Normal
    resN[0]= (v1[1] * v2[2]) - (v1[2] * v2[1]);
    resN[1]= (v1[2] * v2[0]) - (v1[0] * v2[2]);
    resN[2]= (v1[0] * v2[1]) - (v1[1] * v2[0]);
    
    //Modulo do vector
    modulo= sqrtf(powf(resN[0], 2) + powf(resN[1], 2)+ powf(resN[2], 2));
    
    //Vector Unitário
    resN[0]/=modulo;
    resN[1]/=modulo;
    resN[2]/=modulo;
}

void coneVBO(float raio, float altura, int fatias, int aneis, int camadas, FILE *f){
    
    float angulo=(2*M_PI)/fatias,y=0, r_aux,factor_h=(raio/camadas),alt_aux=0, v1[3],v2[3];
    int i=0,v=0,j=0,n=0,avanco=0,l_aux;
    
    altura/=camadas;
    raio=raio/aneis;
    r_aux=raio;
    int n_pontos=((1+fatias*aneis)*3)  + ((camadas+1)*fatias)*3;
    int n_indices=(fatias*(aneis-1)*2+fatias)*3  +(fatias*(camadas)*2+fatias)*3;
    
    int *indices=(int*)malloc(n_indices*sizeof(int));
    float *vertexB=(float*)malloc(n_pontos*sizeof(float)),
    *normalB=(float*)malloc(n_pontos*sizeof(float)),
    *normLado=(float*)malloc(fatias*3*sizeof(float));
   
    //Base do cone
    vertexB[v++]=0;vertexB[v++]=0;vertexB[v++]=0;
    normalB[n++]=0;normalB[n++]=-1;normalB[n++]=0;
    for(l_aux=0;l_aux<fatias;l_aux++){
        
        vertexB[v++]=r_aux*sin(y);vertexB[v++]=0;vertexB[v++]=r_aux*cos(y);
        normalB[n++]=0;normalB[n++]=-1;normalB[n++]=0;
        
        indices[i++]=0;
        indices[i++]=l_aux+2;
        indices[i++]=l_aux+1;
        y+=angulo;
    }
    indices[i-2]=1;
    avanco+=fatias+1;

    for(j=1;j<aneis;j++){
        r_aux+=raio;
        y=0;
        for(l_aux=0;l_aux<fatias;l_aux++){
            
            vertexB[v++]=r_aux*sin(y); vertexB[v++]=0; vertexB[v++]=r_aux*cos(y);
            normalB[n++]=0;normalB[n++]=-1;normalB[n++]=0;
            
            indices[i++]=avanco-fatias+l_aux;
            indices[i++]=avanco-fatias+l_aux+1;
            indices[i++]=avanco+l_aux;
            
            indices[i++]=avanco+l_aux;
            indices[i++]=avanco-fatias+l_aux+1;
            indices[i++]=avanco+l_aux+1;
            
            y+=angulo;
        }
        indices[i-5]=avanco-fatias;
        indices[i-1]=avanco;
        indices[i-2]=avanco-fatias;
        avanco+=fatias;
    }
    //Corpo
    
    //Calcular Normais do lado
    y=0;
    for(l_aux=0;l_aux<fatias;l_aux++){
        
        v1[0]=r_aux*sin(y+angulo) - r_aux*sin(y-angulo);
        v1[1]=0;
        v1[2]=r_aux*cos(y+angulo) - r_aux*cos(y-angulo);
        v2[0]=(r_aux-factor_h)*sin(y) - r_aux*sin(y);
        v2[1]=altura;
        v2[2]=(r_aux-factor_h)*cos(y) - r_aux*cos(y);
        normal(v1, v2);
        
        normLado[l_aux*3]=resN[0];
        normLado[l_aux*3+1]=resN[1];
        normLado[l_aux*3+2]=resN[2];
        
        y+=angulo;
    }
    
    for(j=0;j<=camadas;j++){

        y=0;
        for(l_aux=0;l_aux<fatias;l_aux++){
            
            vertexB[v++]=r_aux*sin(y); vertexB[v++]=alt_aux; vertexB[v++]=r_aux*cos(y);
            normalB[n++]= normLado[l_aux*3];normalB[n++]= normLado[l_aux*3+1];normalB[n++]= normLado[l_aux*3+2];
            
            if(j!=camadas){
                indices[i++]=avanco-fatias+l_aux;
                indices[i++]=avanco-fatias+l_aux+1;
                indices[i++]=avanco+l_aux;
                
                indices[i++]=avanco+l_aux;
                indices[i++]=avanco-fatias+l_aux+1;
                indices[i++]=avanco+l_aux+1;
            }else{
                indices[i++]=avanco-fatias+l_aux;
                indices[i++]=avanco-fatias+l_aux+1;
                indices[i++]=avanco+l_aux;
            }
            
            y+=angulo;
        }
        if(j!=camadas){
            indices[i-5]=avanco-fatias;
            indices[i-1]=avanco;
            indices[i-2]=avanco-fatias;
        }else{
            indices[i-2]=avanco-fatias;
        }
        alt_aux+=altura;
        r_aux-=factor_h;
        avanco+=fatias;
    }
    
    //Imprimir os vertices e indices
    fprintf(f, "%d\n",n_pontos);
    for(i=0;i<n_pontos;i+=3)
        fprintf(f, "%f %f %f\n",vertexB[i],vertexB[i+1],vertexB[i+2]);

    fprintf(f, "%d\n",n_indices);
    for(i=0;i<n_indices;i+=3)
        fprintf(f, "%d %d %d\n",indices[i],indices[i+1],indices[i+2]);

    for(i=0;i<n_pontos;i+=3)
        fprintf(f, "%f %f %f\n",normalB[i],normalB[i+1],normalB[i+2]);

}


