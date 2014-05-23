//
//  main.cpp
//  CG-Aula01
//
//  Created by Hélder José Alves Gonçalves on 27/02/14.
//  Copyright (c) 2014 Hélder José Alves Gonçalves. All rights reserved.
//

#include <stdio.h>

#include "cilindro.h"
#include "esfera.h"
#include "plano.h"
#include "cone.h"
#include "anel.h"
#include <il.h>

float raio=8,cam_h=0,cam_v=0.5,camh_x=0,camh_y=0, cir1=0,cir2=0;
float x_tela, y_tela; //Variaveis para guardar posição da tela em que se carrega no rato
float pos[4]={0,7,5,1},
    amb[3]={0,0,0.5};

int estado_botao=0;
unsigned int texID;


void changeSize(int w, int h) {
    
	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if(h == 0)
		h = 1;
    
	// compute window's aspect ratio
	float ratio = w * 1.0 / h;
    
	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load Identity Matrix
	glLoadIdentity();
	
	// Set the viewport to be the entire window
    glViewport(0, 0, w, h);
    
	// Set perspective
	gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);
    
	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}


void renderScene(void) {
    
	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();
    
    //glLightfv(GL_LIGHT0, GL_POSITION, pos);
    
	
    //Câmera em modo explorador (Câmera move-se nas bordas de 1 esfera)
	gluLookAt(raio*sin(cam_h+camh_x)*cos(cam_v+camh_y),raio*sin(cam_v+camh_y),raio*cos(cam_h+camh_x)*cos(cam_v+camh_y),
		      0.0,0.0,0.0,
			  0.0f,1.0f,0.0f);
    // pÙr instruÁıes de desenho aqui
   // glLightfv(GL_LIGHT0, GL_POSITION, pos);
     //  glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
    
    //plano(3, 5, 4, 3, 0, 1);
    
   // Paralelepipedo an = Paralelepipedo(2, 4, 3, 1, 3, 4);
    Esfera an= Esfera(2, 30, 30);
    //Circulo an= Circulo(1, 15, 3, 0, 0);
  // Cilindro an = Cilindro(1, 10, 2, 3, 3);
    //Anel an= Anel(3, 1, 20, 3, 1);
   // Cone an = Cone(1, 2, 20, 5, 10);
    //Plano an1= Plano(8, 8, 3, 3, -4, 1);
    //Plano an= Plano(8, 8, 3, 3, -4, 3);
   
    
    
   // an1.desenha();
    an.desenha();
   
    
    //Cone an= Cone(2, 2, 20, 3, 3);
   
   // an2.desenha();
   // an3.desenha();
    //an4.desenha();
    //an5.desenha();
    //an6.desenha();
    
    
   
	// End of frame
	
    glutSwapBuffers();
}

void teclado_normal(unsigned char tecla,int x, int y){
    switch (tecla) {
        case 'a':
            raio-=1;
            break;
        case 'd':
            raio+=1;
            break;
            
        default:
            break;
    }
    glutPostRedisplay();
}

void teclado_especial(int tecla,int x, int y){
    switch (tecla) {
        case GLUT_KEY_UP:
            if(cam_v+0.05<M_PI_2)   //Para câmera não virar ao contrário
                cam_v+=0.05;
            break;
        case GLUT_KEY_DOWN:
            if(cam_v-0.05>-M_PI_2)  //Para câmera não virar ao contrário
                cam_v-=0.05;
            break;
            
        case GLUT_KEY_LEFT:
            cam_h-=0.05;
            break;
        case GLUT_KEY_RIGHT:
            cam_h+=0.05;
            break;
            
        default:
            break;
    }
        glutPostRedisplay();
}

void front_menu(int op){
    switch (op) {
        case 1:
            glPolygonMode(GL_FRONT,GL_POINT);
            break;
        case 2:
            glPolygonMode(GL_FRONT,GL_LINE);
            break;
        case 3:
            glPolygonMode(GL_FRONT,GL_FILL);
            break;
        default:
            break;
    }
    glutPostRedisplay();
}

void rato(int botao, int estado, int x, int y){
    if (botao==GLUT_LEFT_BUTTON){
        if (estado==GLUT_DOWN){
            estado_botao=1;
            x_tela=x;
            y_tela=y;
        }
        else{
            estado_botao=0;
            cam_v+=camh_y;
            cam_h+=camh_x;
            camh_x=0;
            camh_y=0;
        }
    }
}

void mov_rato(int x, int y){
    float teste;
    if(estado_botao){
        if(x_tela!=x)
            camh_x= (x_tela-x)*0.007;
        
        if(y_tela!=y){
            teste= (y-y_tela)*0.007;
            if(teste+cam_v>-M_PI_2 && teste+cam_v<M_PI_2 )
                camh_y=teste;
        }
        
        glutPostRedisplay();
    }
}

void loadTexture() {
    
	unsigned int t,tw,th;
	unsigned char *texData;
    
	ilInit();
	ilEnable(IL_ORIGIN_SET);
	ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
	ilGenImages(1,&t);
	ilBindImage(t);
	ilLoadImage((ILstring)"12.jpg");
	tw = ilGetInteger(IL_IMAGE_WIDTH);
	th = ilGetInteger(IL_IMAGE_HEIGHT);
	ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
	texData = ilGetData();
    
	glGenTextures(1,&texID);
	
	glBindTexture(GL_TEXTURE_2D,texID);
	glTexParameteri(GL_TEXTURE_2D,	GL_TEXTURE_WRAP_S,		GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,	GL_TEXTURE_WRAP_T,		GL_REPEAT);
    
	glTexParameteri(GL_TEXTURE_2D,	GL_TEXTURE_MAG_FILTER,   	GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,	GL_TEXTURE_MIN_FILTER,    	GL_LINEAR);
    
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tw, th, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
    
}


int main(int argc, char **argv) {
    
    // pÙr inicializaÁ„o aqui
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(800,800);
    glutCreateWindow("CG@DI");
    
    
    // pÙr registo de funÁıes aqui
    glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);

    
    // funções do teclado e rato
	glutKeyboardFunc(teclado_normal);
    glutSpecialFunc(teclado_especial);
    glutMouseFunc(rato);
    glutMotionFunc(mov_rato);
    
    //MENU
    glutCreateMenu(front_menu);
    glutAddMenuEntry("GL POINT",1);
    glutAddMenuEntry("GL LINE",2);
    glutAddMenuEntry("GL FILL",3);
    
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    
    glewInit();
    loadTexture();
    // alguns settings para OpenGL
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
    glEnable(GL_TEXTURE_2D);
	glClearColor(0.0f,0.0f,0.0f,0.0f);
   // glPolygonMode(GL_FRONT, GL_LINE);
    
    //Luzes
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    
    // entrar no ciclo do GLUT aqui
	glutMainLoop();
    
    return 0;
    
}

