#include "map.h"

// Constante para o tamanho da sala
const int ROOM_SIZE = 30;

// Função para desenhar a sala
void drawRoom() {
    // Chão - Cor cinza escuro
    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_QUADS);
    glVertex3f(0, 0, 0);
    glVertex3f(ROOM_SIZE, 0, 0);
    glVertex3f(ROOM_SIZE, 0, ROOM_SIZE);
    glVertex3f(0, 0, ROOM_SIZE);
    glEnd();

    // Teto - Cor cinza claro
    glColor3f(0.7f, 0.7f, 0.7f);
    glBegin(GL_QUADS);
    glVertex3f(0, ROOM_SIZE, 0);
    glVertex3f(ROOM_SIZE, ROOM_SIZE, 0);
    glVertex3f(ROOM_SIZE, ROOM_SIZE, ROOM_SIZE);
    glVertex3f(0, ROOM_SIZE, ROOM_SIZE);
    glEnd();

    // Parede frontal (z = 0) - Cinza claro 1
    glColor3f(0.6f, 0.6f, 0.6f); // Tom de cinza claro diferente
    glBegin(GL_QUADS);
    glVertex3f(0, 0, 0);
    glVertex3f(ROOM_SIZE, 0, 0);
    glVertex3f(ROOM_SIZE, ROOM_SIZE, 0);
    glVertex3f(0, ROOM_SIZE, 0);
    glEnd();

    // Parede traseira (z = ROOM_SIZE) - Cinza claro 2
    glColor3f(0.5f, 0.5f, 0.5f); // Tom de cinza claro diferente
    glBegin(GL_QUADS);
    glVertex3f(0, 0, ROOM_SIZE);
    glVertex3f(ROOM_SIZE, 0, ROOM_SIZE);
    glVertex3f(ROOM_SIZE, ROOM_SIZE, ROOM_SIZE);
    glVertex3f(0, ROOM_SIZE, ROOM_SIZE);
    glEnd();

    // Parede esquerda (x = 0) - Cinza claro 3
    glColor3f(0.4f, 0.4f, 0.4f); // Tom de cinza claro diferente
    glBegin(GL_QUADS);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, ROOM_SIZE);
    glVertex3f(0, ROOM_SIZE, ROOM_SIZE);
    glVertex3f(0, ROOM_SIZE, 0);
    glEnd();

    // Parede direita (x = ROOM_SIZE) - Cinza claro 4
    glColor3f(0.3f, 0.3f, 0.3f); // Tom de cinza claro diferente
    glBegin(GL_QUADS);
    glVertex3f(ROOM_SIZE, 0, 0);
    glVertex3f(ROOM_SIZE, 0, ROOM_SIZE);
    glVertex3f(ROOM_SIZE, ROOM_SIZE, ROOM_SIZE);
    glVertex3f(ROOM_SIZE, ROOM_SIZE, 0);
    glEnd();
}

// Função para verificar colisões
bool checkCollision(Vector3 pos) {
    return pos.x < 0 || pos.x > ROOM_SIZE || pos.z < 0 || pos.z > ROOM_SIZE;
}