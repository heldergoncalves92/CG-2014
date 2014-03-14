//
//  main.cpp
//  Motor3D
//
//  Created by Duarte Nuno Ferreira Duarte on 10/03/14.
//  Copyright (c) 2014 Duarte Nuno Ferreira Duarte. All rights reserved.
//

#include "motor.h"
#include "camera.h"

//Inicializaçoes Principais
TiXmlNode *cena=NULL;
int tipo_camera=0;
char ficheiro[]="test.xml";


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
	
    if (tipo_camera)
        modo_explorador();
    else{
        gluLookAt(0,3,5,
                  0.0, 0.0, 0.0,
                  0.0f, 1.0f, 0.0f);
    }
    
	// pÙr instruÁıes de desenho aqui
	
    motor_XML(cena);
    
	// End of frame
	glutSwapBuffers();
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

    TiXmlDocument doc(ficheiro);
    TiXmlElement *root=NULL;
    TiXmlNode *node=NULL;
    TiXmlAttribute *attr=NULL;
    
	if(doc.LoadFile()){
    
       root=doc.RootElement();
        cena=root->FirstChild("cena");
        
        if (cena) {
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
            if((node=root->FirstChild("camera")) && (attr=node->ToElement()->FirstAttribute())){
                if (strcmp(attr->Name(), "tipo")==0) {
                    if(strcmp(attr->Value(), "explorador")==0){
                        glutKeyboardFunc(teclado_normal_explorador);
                        glutSpecialFunc(teclado_especial_explrador);
                        glutMouseFunc(rato_explorador);
                        glutMotionFunc(mov_rato_explorador);
                        tipo_camera=1;
                    }
                }
            }
            
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
            
            glPolygonMode(GL_FRONT, GL_LINE);
            
            // entrar no ciclo do GLUT 
            glutMainLoop();
            
        }
        else
            printf("Falhou!! Sem tag 'cena' no XML!\n");
    }
    else
        printf("Falhou!! Não fez load do ficheiro!\n");
    
	return 0;
    
}



