//
//  iluminacao1.cpp
//  glutOpenGL
//
//  Created by Gilberto Fernandes Junior on 11/02/25.
//

// ILUMINACÃO AMBIENTE / DIFUSA!


#define GL_SILENCE_DEPRECATION
#include <iostream>
#include <math.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>
// #include <unistd.h>

GLfloat light0_pos[] = {2.0f, 2.0f, 2.0f, 1.0f};
GLfloat white[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat black[] = {0.0f, 0.0f, 0.0f, 1.0f};
GLfloat blue[] = {0,0,1,1};
GLfloat kd = 0.0f;


void lightning(){
    glLightfv(GL_LIGHT0,GL_POSITION,light0_pos); //posicao nas coordenadas do mundo
    glLightfv(GL_LIGHT0,GL_AMBIENT,black); // brilho da cena - preto nao contribui para a iluminacao
    glLightfv(GL_LIGHT0,GL_DIFFUSE,white); //cor de fonte de luz
    glLightfv(GL_LIGHT0,GL_SPECULAR,white); // brilhante ou opaco

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

}
void init(void) {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //define a cor de fundo
    glEnable(GL_DEPTH_TEST); //habilita o teste de profundidade

    glMatrixMode(GL_MODELVIEW); //define que a matrix é a model view
    glLoadIdentity(); //carrega a matrix de identidade
    gluLookAt(0.0, 0.0, 1.0,    //posição da câmera (P_0)
              0.0, 0.0, 0.0,    //para onde a câmera aponta (P_ref)
              0.0, 1.0, 0.0);   //vetor view-up (V)

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0); // projeção paralela
                                             // sistema de coordenadas da CAMERA
    glViewport(0, 0, 500, 500);
    lightning();
    glPushMatrix();
}


void teclado(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP :
            if(kd<1.0)
                kd+=0.1;
            break;
        case GLUT_KEY_DOWN :
            if(kd>0.0)
                kd-=0.1;
            break;
        case GLUT_KEY_LEFT: exit(0);
        default:
            break;
    }
    glutPostRedisplay();
}

void display(void) {
    //glClearColor(1.0,1.0,1.0,0.0);
    GLfloat diffuse[4]; // coeficiente de reflex difusa (kd) [r, g, b, transparencia]
    //GLfloat amb[4]; // coeficiente de reflex ambiente (ka)
    glClear(GL_COLOR_BUFFER_BIT |GL_DEPTH_BUFFER_BIT); //limpa o buffer


//    diffuse[0] = 1;
//    diffuse[1] = 1;
//    diffuse[2] = 1;
//    diffuse[3] = 1.0f;

//    amb[0] = 0.5;
//    amb[1] = 0.5;
//    amb[2] = 0.5;
//    amb[3] = 1.0f;
   diffuse[0] = 0;
   diffuse[1] = 1;
   diffuse[2] = 1;
   diffuse[3] = 1.0f;
    
    // diffuse[0] = kd;
    // diffuse[1] = kd;
    // diffuse[2] = kd;
    // diffuse[3] = 1.0f;

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, diffuse); //GL_AMBIENT_AND_DIFFUSE
    //glMaterialfv(GL_FRONT, GL_AMBIENT, amb);
    //glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    //glMaterialf(GL_FRONT, GL_SHININESS, ns);
    glutSolidSphere(1.0,40,40); //desenha uma esfera
    
    
//    glutSolidCube(1);

    lightning();


    glutSwapBuffers();
}



int main(int argc, char**argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(50, 100);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Iluminacão");
    glutDisplayFunc(display);
    glutSpecialFunc(teclado);
    init(); // inicialização (após a criação da janela)
    glutMainLoop(); // desenha tudo e espera por eventos

    return EXIT_SUCCESS;
}
