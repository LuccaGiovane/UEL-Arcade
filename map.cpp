#include "map.h"
#include <GL/glut.h>

// Tamanho da sala
const int ROOM_SIZE = 30;

void drawRoom() {
    // Chão
    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_QUADS);
        glVertex3f(0, 0, 0);
        glVertex3f(ROOM_SIZE, 0, 0);
        glVertex3f(ROOM_SIZE, 0, ROOM_SIZE);
        glVertex3f(0, 0, ROOM_SIZE);
    glEnd();

    // Teto
    glColor3f(0.7f, 0.7f, 0.7f);
    glBegin(GL_QUADS);
        glVertex3f(0, ROOM_SIZE, 0);
        glVertex3f(ROOM_SIZE, ROOM_SIZE, 0);
        glVertex3f(ROOM_SIZE, ROOM_SIZE, ROOM_SIZE);
        glVertex3f(0, ROOM_SIZE, ROOM_SIZE);
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
    glColor3f(0.5f, 0.5f, 0.5f);
    glBegin(GL_QUADS);
        glVertex3f(0, 0, ROOM_SIZE);
        glVertex3f(ROOM_SIZE, 0, ROOM_SIZE);
        glVertex3f(ROOM_SIZE, ROOM_SIZE, ROOM_SIZE);
        glVertex3f(0, ROOM_SIZE, ROOM_SIZE);
    glEnd();

    // Parede esquerda (x = 0)
    glColor3f(0.4f, 0.4f, 0.4f);
    glBegin(GL_QUADS);
        glVertex3f(0, 0, 0);
        glVertex3f(0, 0, ROOM_SIZE);
        glVertex3f(0, ROOM_SIZE, ROOM_SIZE);
        glVertex3f(0, ROOM_SIZE, 0);
    glEnd();

    // Parede direita (x = ROOM_SIZE)
    glColor3f(0.3f, 0.3f, 0.3f);
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
