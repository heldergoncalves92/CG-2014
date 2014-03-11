//
//  main.cpp
//  Motor3D
//
//  Created by Duarte Nuno Ferreira Duarte on 10/03/14.
//  Copyright (c) 2014 Duarte Nuno Ferreira Duarte. All rights reserved.
//

#include <iostream>

#include <GLUT/glut.h>
#include <math.h>
#include <stdio.h>
#include "tinyxml/tinyxml.h"

//#include "CenaHandler.h"

#undef _CRT_TERMINATE_DEFINED
#define _CRT_TERMINATE_DEFINED 0

float angulo = 0.0f;
float xr = 0.0f;
float yr = 1.0f;
float zr = 0.0f;
float zoom = 2.0f;

float raio=5,cam_h=0,cam_v=0.5;

void changeSize(int w, int h) {
    
	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if (h == 0)
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
	gluPerspective(45.0f, ratio, 1.0f, 1000.0f);
    
	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}



void renderScene(void) {
    
	//LL *lista = listaPontos;
	//lista = lista->next;
    
	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
	// set the camera
	glLoadIdentity();
	
    //Câmera em modo explorador
	gluLookAt(raio*sin(cam_h)*cos(cam_v),raio*sin(cam_v),raio*cos(cam_h)*cos(cam_v),
	          0.0, 0.0, 0.0,
              0.0f, 1.0f, 0.0f);
    
	glRotatef(angulo, xr, yr, zr); // ‚ngulo em graus
    
	// pÙr instruÁıes de desenho aqui
	float cx=0, cy=0, cz=0;
    
	glBegin(GL_TRIANGLES);
	//TiXmlDocument *doc = new TiXmlDocument("/Users/duarteduarte/Desktop/esfera.3d");
	//bool loaded = doc->LoadFile();
    
	//TiXmlElement *root = doc->RootElement();
	//for (TiXmlNode *child = root->FirstChild(); child != NULL; child = child->NextSibling()){
	//	child->Print(stdout, NULL);
	//	TiXmlAttribute *attr = child->ToElement()->FirstAttribute();
	//	const char *attrName = attr->Name();
	//	const char *attrValue = attr->Value();
    
		
		FILE *f = fopen("/Users/helderjosealvesgoncalves/Desktop/esfera.3d", "r");
		while (fscanf(f, "%f %f %f\n", &cx, &cy, &cz)!=EOF){
            glColor3f(cx, cy, cz);
			glVertex3f(cx, cy, cz);
        }
        
        /*while (lista != NULL){
         if (lista->tipo == 1000){
         glColor3f(lista->coordenadaX, lista->coordenadaY, lista->coordenadaZ);
         }
         else{
         glVertex3f(lista->coordenadaX, lista->coordenadaY, lista->coordenadaZ);
         }
         lista = lista->next;*/
	
	glEnd();
    
	// End of frame
	glutSwapBuffers();
}


void teclado_normal(unsigned char tecla,int x, int y){
    switch (tecla) {
        case 'a':
            raio-=0.1;
            break;
        case 'd':
            raio+=0.1;
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

int main(int argc, char* argv[]){
	/*if (argc < 2){
     perror("Usage: motor <scene.xml>");
     exit(-1);
     }*/
    
    
    
	//CenaHandler *ch = new CenaHandler();
	/*argv[1]*/
	//listaPontos = (LL*)malloc(sizeof(LL));
	//listaPontos->coordenadaX = INT_MAX;
	//listaPontos->coordenadaY = INT_MAX;
	//listaPontos->coordenadaZ = INT_MAX;
	//listaPontos->next = NULL;
	//ch->LoadFile("C:/Users/Duarte Duarte/Desktop/abrir.xml",listaPontos);
    
	// inicializaÁ„o
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 800);
	glutCreateWindow("BananaCorp®");
    
    
    // pÙr registo de funÁıes aqui
    glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
    
    // funções do teclado e rato
	glutKeyboardFunc(teclado_normal);
    glutSpecialFunc(teclado_especial);
    
    
    //MENU
    glutCreateMenu(front_menu);
    glutAddMenuEntry("GL POINT",1);
    glutAddMenuEntry("GL LINE",2);
    glutAddMenuEntry("GL FILL",3);
    
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    
    
    // alguns settings para OpenGL
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glClearColor(0.0f,0.0f,0.0f,0.0f);
    
	// alguns settings para OpenGL
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
    
    glPolygonMode(GL_FRONT, GL_LINE);
    
	// entrar no ciclo do GLUT 
	glutMainLoop();
    
	return 0;
    
}



