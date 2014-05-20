//
//  main.cpp
//  Motor3D
//
//  Created by Duarte Nuno Ferreira Duarte on 10/03/14.
//  Copyright (c) 2014 Duarte Nuno Ferreira Duarte. All rights reserved.
//


#include "motorXML.h"
#include "camera_explorador.h"
#include "camera_fps.h"

//Inicializaçoes Principais
TiXmlNode *cena=NULL;
int tipo_camera=0;

Rotacao *rotacoes=NULL, *rot_actual=NULL;
Translacao *translacoes=NULL, *tra_actual=NULL;
Escala escalas=NULL, esc_actual=NULL;
long currentTime=0,test;

//LUZES
float pos[4]={0,17,0,1},pos1[4]={0,-17,0,1},pos2[4]={17,0,0,1},pos3[4]={-17,0,0,1},
diff[3]={1,1,1},
amb[3]={0.03,0.09,0.09};

void changeSize(int w, int h){
    
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
    
	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
	// set the camera
	glLoadIdentity();
	
    if (tipo_camera==1)
        modo_explorador();
    else
        if (tipo_camera==2)
            modo_fps();
        else{
            gluLookAt(0,3,5,
                      0.0, 0.0, 0.0,
                      0.0f, 1.0f, 0.0f);
        }
    
    
	// pÙr instruÁıes de desenho aqui
   
    //LUZES
    glLightfv(GL_LIGHT0, GL_POSITION,pos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diff);
    
    glLightfv(GL_LIGHT1, GL_POSITION,pos1);
    glLightfv(GL_LIGHT1, GL_AMBIENT, amb);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diff);
    
    glLightfv(GL_LIGHT2, GL_POSITION,pos2);
    glLightfv(GL_LIGHT2, GL_AMBIENT, amb);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, diff);
    
    glLightfv(GL_LIGHT3, GL_POSITION,pos3);
    glLightfv(GL_LIGHT3, GL_AMBIENT, amb);
    glLightfv(GL_LIGHT3, GL_DIFFUSE, diff);
    
    
	rot_actual=rotacoes;
    tra_actual=translacoes;
    esc_actual=escalas;
    test=currentTime;
    motor_XML(cena);
    currentTime = glutGet(GLUT_ELAPSED_TIME);
    
    printf("Diferença: %lo\n",currentTime-test);
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
        case 4:
            glutKeyboardFunc(teclado_normal_explorador);
            glutSpecialFunc(teclado_especial_explorador);
            glutMouseFunc(rato_explorador);
            glutMotionFunc(mov_rato_explorador);
            tipo_camera=1;
            break;
        case 5:
            glutKeyboardFunc(teclado_normal_fps);
            glutSpecialFunc(teclado_especial_fps);
            glutMouseFunc(rato_fps);
            glutMotionFunc(mov_rato_fps);
            tipo_camera=2;
            break;
        default:
            break;
    }
    glutPostRedisplay();
}

int main(int argc, char* argv[]){
    
    TiXmlDocument doc;
    TiXmlElement *root=NULL;
    TiXmlNode *node=NULL;
    TiXmlAttribute *attr=NULL;
    
    
    //if(argc!=2){
    //    printf("ERRO!! Número de argumentos errado, falta XML de input!\n");
    //    return 1;
    //}
    
	//if(doc.LoadFile(argv[1])){
    if(doc.LoadFile("sistema_solar.xml")){
        
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
            //glutIdleFunc(renderScene);
            
            // funções do teclado e rato
            if((node=root->FirstChild("camera")) && (attr=node->ToElement()->FirstAttribute())){
                if (strcmp(attr->Name(), "tipo")==0) {
                    if(strcmp(attr->Value(), "fps")==0){
                        glutKeyboardFunc(teclado_normal_fps);
                        glutSpecialFunc(teclado_especial_fps);
                        glutMouseFunc(rato_fps);
                        glutMotionFunc(mov_rato_fps);
                        tipo_camera=2;
                    }else
                        if (strcmp(attr->Value(), "explorador")==0){
                            preDefinicoes_Explorador(node);
                            glutKeyboardFunc(teclado_normal_explorador);
                            glutSpecialFunc(teclado_especial_explorador);
                            glutMouseFunc(rato_explorador);
                            glutMotionFunc(mov_rato_explorador);
                            tipo_camera=1;
                        }
                }
            }
            
            //Caso não esteja definida nenhuma camera, o modo explorador fica activo por defeito
            if(tipo_camera==0){
                glutKeyboardFunc(teclado_normal_explorador);
                glutSpecialFunc(teclado_especial_explorador);
                glutMouseFunc(rato_explorador);
                glutMotionFunc(mov_rato_explorador);
                tipo_camera=1;
                
                //Atribuir valores base

            }
            
            
            //MENU
            glutCreateMenu(front_menu);
            glutAddMenuEntry("GL POINT",1);
            glutAddMenuEntry("GL LINE",2);
            glutAddMenuEntry("GL FILL",3);
            glutAddMenuEntry("Modo Explorador",4);
            glutAddMenuEntry("Modo FPS",5);
            
            glutAttachMenu(GLUT_RIGHT_BUTTON);
            
            //Callback do GLEW - Tem de estar depois de todos os callbacks do GLUT
            //glewInit();
            
            // alguns settings para OpenGL
            glEnable(GL_DEPTH_TEST);
            glEnable(GL_CULL_FACE);
            glClearColor(0.0f,0.0f,0.0f,0.0f);
            
            //glPolygonMode(GL_FRONT, GL_LINE);
            
            prepara_MotorXML(cena);
            
            //Luzes
            glEnable(GL_LIGHTING);
            glEnable(GL_LIGHT0);
            glEnable(GL_LIGHT1);
            glEnable(GL_LIGHT2);
            glEnable(GL_LIGHT3);
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



