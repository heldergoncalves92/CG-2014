//
//  cilindro.cpp
//  CG-FORMAS-PRIMARIAS
//
//  Created by Hélder José Alves Gonçalves on 27/02/14.
//  Copyright (c) 2014 Hélder José Alves Gonçalves. All rights reserved.
//

#include "cilindro.h"



void cilindro(float raio,int fatias,int camadas,float altura,int aneis, FILE* f){
    float angulo=(2*M_PI)/fatias,x,y=0,l_aux,h_aux1,h_aux2=0, r_aux1,r_aux2;
    int aneis_aux=aneis-1;

    raio=raio/aneis;
    
    fprintf(f,"%d\n",(2*fatias*(aneis-1)+fatias)*9*2 + 2*fatias*camadas*9);

    for(l_aux=0;l_aux<fatias;l_aux++){
            x=y;
            y+=angulo;
            fprintf(f,"%d %f %d\n",0, altura, 0);
            fprintf(f,"%f %f %f\n",raio*sin(x), altura, raio*cos(x));
            fprintf(f,"%f %f %f\n",raio*sin(y), altura, raio*cos(y));
        }
        r_aux2=raio;
        y=0;
        for(aneis--;aneis>0;aneis--){
            r_aux1=r_aux2;
            r_aux2+=raio;
        
           for(l_aux=0;l_aux<fatias;l_aux++){
               x=y;
               y+=angulo;
                fprintf(f,"%f %f %f\n",r_aux1*sin(x), altura, r_aux1*cos(x));
                fprintf(f,"%f %f %f\n",r_aux2*sin(x), altura, r_aux2*cos(x));
                fprintf(f,"%f %f %f\n",r_aux1*sin(y), altura, r_aux1*cos(y));
               
                fprintf(f,"%f %f %f\n",r_aux1*sin(y), altura, r_aux1*cos(y));
                fprintf(f,"%f %f %f\n",r_aux2*sin(x), altura, r_aux2*cos(x));
                fprintf(f,"%f %f %f\n",r_aux2*sin(y), altura, r_aux2*cos(y));
            }
        }
    r_aux2=raio;
    y=0;
        for(l_aux=0;l_aux<fatias;l_aux++){
            x=y;
            y+=angulo;
            fprintf(f,"%d %d %d\n",0, 0, 0);
            fprintf(f,"%f %f %f\n",raio*sin(y), 0.0, raio*cos(y));
            fprintf(f,"%f %f %f\n",raio*sin(x), 0.0, raio*cos(x));
        }
        
        
        for(aneis=aneis_aux;aneis>0;aneis--){
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

    raio=r_aux2;

    //Corpo
    altura=altura/camadas;
    for(;camadas>0;camadas--){
        h_aux1=h_aux2;
        h_aux2+=altura;
        y=0;
        for (l_aux=0; l_aux<fatias; l_aux++) {
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

void cilindroVBO(float raio,int fatias,int camadas,float altura,int aneis, FILE* f){
    float angulo=(2*M_PI)/fatias,y=0,l_aux, r_aux,alt_aux=altura;
    int i=0,v=0,j=0,avanco;
    
    altura/=camadas;
    raio=raio/aneis;
    r_aux=raio;
    int n_pontos=((1+fatias*aneis)*3) + (fatias*camadas*3) + ((aneis-1)*fatias+1)*3;
    int n_indices=((fatias*(aneis-1)*2+fatias)*3)  + (fatias*camadas*3*2)  + (((aneis-1)*fatias*2+fatias)*3);
    
    
    int *indices=(int*)malloc(n_indices*sizeof(int));
    float *vertexB=(float*)malloc(n_pontos*sizeof(float));
    
    
        //Circulo do topo
        vertexB[v++]=0;vertexB[v++]=alt_aux;vertexB[v++]=0;
        for(l_aux=0;l_aux<fatias;l_aux++){
            
            vertexB[v++]=r_aux*sin(y);vertexB[v++]=alt_aux;vertexB[v++]=r_aux*cos(y);
            
            indices[i++]=0;
            indices[i++]=l_aux+1;
            indices[i++]=l_aux+2;
            y+=angulo;
        }
        indices[i-1]=1;
        
        for(j++;j<aneis;j++){
            r_aux+=raio;
            y=0;
            for(l_aux=0;l_aux<fatias;l_aux++){
                avanco=j*fatias+1;
                
                vertexB[v++]=r_aux*sin(y); vertexB[v++]=alt_aux; vertexB[v++]=r_aux*cos(y);
                
                indices[i++]=avanco-fatias+l_aux;
                indices[i++]=avanco+l_aux;
                indices[i++]=avanco-fatias+l_aux+1;
                
                indices[i++]=avanco+l_aux;
                indices[i++]=avanco+l_aux+1;
                indices[i++]=avanco-fatias+l_aux+1;
                
                y+=angulo;
            }
            indices[i-4]=avanco-fatias;
            indices[i-2]=avanco;
            indices[i-1]=avanco-fatias;
        }
    //Corpo
    for(;camadas>0;camadas--){
        y=0;
        alt_aux-=altura;
        for(l_aux=0;l_aux<fatias;l_aux++){
            avanco=j*fatias+1;
            
            vertexB[v++]=r_aux*sin(y); vertexB[v++]=alt_aux; vertexB[v++]=r_aux*cos(y);
            
            indices[i++]=avanco-fatias+l_aux;
            indices[i++]=avanco+l_aux;
            indices[i++]=avanco-fatias+l_aux+1;
            
            indices[i++]=avanco+l_aux;
            indices[i++]=avanco+l_aux+1;
            indices[i++]=avanco-fatias+l_aux+1;
            
            y+=angulo;
        }
        indices[i-4]=avanco-fatias;
        indices[i-2]=avanco;
        indices[i-1]=avanco-fatias;
        j++;
    }
    
        //Circulo da base
    
        for(;aneis>1;aneis--){
            r_aux-=raio;
            y=0;
            for(l_aux=0;l_aux<fatias;l_aux++){
                avanco=j*fatias+1;
                
                vertexB[v++]=r_aux*sin(y); vertexB[v++]=0; vertexB[v++]=r_aux*cos(y);
                
                indices[i++]=avanco-fatias+l_aux;
                indices[i++]=avanco+l_aux;
                indices[i++]=avanco-fatias+l_aux+1;
                
                indices[i++]=avanco+l_aux;
                indices[i++]=avanco+l_aux+1;
                indices[i++]=avanco-fatias+l_aux+1;
                
                y+=angulo;
            }
            indices[i-4]=avanco-fatias;
            indices[i-2]=avanco;
            indices[i-1]=avanco-fatias;
            j++;
        }
   
    vertexB[v++]=0;vertexB[v++]=0;vertexB[v++]=0;
    for(l_aux=0;l_aux<fatias;l_aux++){
        
        indices[i++]=avanco+fatias;
        indices[i++]=avanco+l_aux+1;
        indices[i++]=avanco+l_aux;
    }
    indices[i-2]=avanco;
    
    //Imprimir os vertices e indices
    fprintf(f, "%d\n",n_pontos);
    for(i=0;i<n_pontos;i+=3)
        fprintf(f, "%f %f %f\n",vertexB[i],vertexB[i+1],vertexB[i+2]);

    fprintf(f, "%d\n",n_indices);
    for(i=0;i<n_indices;i+=3)
        fprintf(f, "%d %d %d\n",indices[i],indices[i+1],indices[i+2]);
    

}



