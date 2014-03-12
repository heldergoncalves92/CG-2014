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
    int i=0;
	//LL *lista = listaPontos;
	//lista = lista->next;
    
	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
	// set the camera
	glLoadIdentity();
	gluLookAt(0.0f, 0.0f, 5.0f,
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
    {
		
		FILE *f = fopen("/Users/duarteduarte/Desktop/esfera.3d", "r");
		while (fscanf(f, "%f %f %f\n", &cx, &cy, &cz)!=EOF){
            glColor3f(cx, cy, cz);
			glVertex3f(cx, cy, cz);
            i++;
            if (i%1000==0)
                printf("%d\n",i);
			//insertLL(lista, 0, cx, cy, cz);
		}
        /*while (lista != NULL){
         if (lista->tipo == 1000){
         glColor3f(lista->coordenadaX, lista->coordenadaY, lista->coordenadaZ);
         }
         else{
         glVertex3f(lista->coordenadaX, lista->coordenadaY, lista->coordenadaZ);
         }
         lista = lista->next;*/
	}
	glEnd();
    
	// End of frame
	glutSwapBuffers();
}

void mexeTecla(unsigned char tecla, int x, int y){
	switch (tecla){
        case ('a') :
            angulo -= 10.0f;
            xr = 0.0f;
            yr = 1.0f;
            break;
        case ('d') :
            angulo += 10.0f;
            xr = 0.0f;
            yr = 1.0f;
            break;
        case ('e') :
            zoom += 1.0f;
            break;
        case ('q') :
            zoom -= 1.0f;
            break;
        case ('w') :
            angulo += 10.0f;
            xr = 1.0f;
            yr = 0.0f;
            break;
        case ('s') :
            angulo -= 10.0f;
            xr = 1.0f;
            yr = 0.0f;
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
    
    
	// registo de funÁıes
	//LL *lista = NULL;
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
    
    
	// pÙr aqui registo da funÁıes do teclado e rato
	glutKeyboardFunc(mexeTecla);
    
	// pÙr aqui a criaÁ„o do menu
    
	// alguns settings para OpenGL
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
    
    glPolygonMode(GL_FRONT, GL_LINE);
    
	// entrar no ciclo do GLUT 
	glutMainLoop();
    
	return 0;
    
}



