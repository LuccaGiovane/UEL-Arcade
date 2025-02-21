#include "map.h"
#include <GL/glut.h>

// Tamanho da sala
const int ROOM_SIZE = 30;

void setupLighting() {
    GLfloat globalAmbient[] = {0.2f, 0.2f, 0.2f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbient);

    GLfloat lightPosition[] = {ROOM_SIZE / 2, ROOM_SIZE, ROOM_SIZE / 2, 1.0f}; 
    GLfloat lightDiffuse[] = {0.5f, 0.5f, 0.5f, 1.0f}; 
    GLfloat lightSpecular[] = {0.1f, 0.1f, 0.1f, 1.0f}; 

    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);

}


void drawRoom() {
    setupLighting();

    // Chão
    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_QUADS);
        glVertex3f(0, 0, 0);
        glVertex3f(ROOM_SIZE, 0, 0);
        glVertex3f(ROOM_SIZE, 0, ROOM_SIZE);
        glVertex3f(0, 0, ROOM_SIZE);
    glEnd();

    
    // Parede frontal (z = 0)
    glColor3f(0.6f, 0.6f, 0.6f);
    glBegin(GL_QUADS);
        glVertex3f(0, 0, 0);
        glVertex3f(ROOM_SIZE, 0, 0);
        glVertex3f(ROOM_SIZE, ROOM_SIZE, 0);
        glVertex3f(0, ROOM_SIZE, 0);
    glEnd();

    // Parede traseira (z = ROOM_SIZE)
    glColor3f(0.6f, 0.6f, 0.6f);
    glBegin(GL_QUADS);
        glVertex3f(0, 0, ROOM_SIZE);
        glVertex3f(ROOM_SIZE, 0, ROOM_SIZE);
        glVertex3f(ROOM_SIZE, ROOM_SIZE, ROOM_SIZE);
        glVertex3f(0, ROOM_SIZE, ROOM_SIZE);
    glEnd();

    // Parede esquerda (x = 0)
    glColor3f(0.6f, 0.6f, 0.6f);
    glBegin(GL_QUADS);
        glVertex3f(0, 0, 0);
        glVertex3f(0, 0, ROOM_SIZE);
        glVertex3f(0, ROOM_SIZE, ROOM_SIZE);
        glVertex3f(0, ROOM_SIZE, 0);
    glEnd();

    // Parede direita (x = ROOM_SIZE)
    glColor3f(0.6f, 0.6f, 0.6f);
    glBegin(GL_QUADS);
        glVertex3f(ROOM_SIZE, 0, 0);
        glVertex3f(ROOM_SIZE, 0, ROOM_SIZE);
        glVertex3f(ROOM_SIZE, ROOM_SIZE, ROOM_SIZE);
        glVertex3f(ROOM_SIZE, ROOM_SIZE, 0);
    glEnd();

    
}

bool checkCollision(const Vetor3D &pos) {
    return pos.x < 0 || pos.x > ROOM_SIZE || pos.z < 0 || pos.z > ROOM_SIZE;
}