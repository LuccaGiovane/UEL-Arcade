#include "map.h"
#include <GL/freeglut.h>

// Tamanho da sala
const int ROOM_SIZE = 30;
const int WALL_SIZE = 10;


/*
    Função setupLighting:
    - Configura a iluminação global do cenário.
    - Define a luz ambiente e a posição/difusão para iluminar a sala.
*/
void setupLighting() {
    // define a posição e características da luz principal
    GLfloat lightPosition[] = {ROOM_SIZE / 2, WALL_SIZE-1.0f, ROOM_SIZE / 2, 1.0f};
    GLfloat lightAmbient[] = {0.1f, 0.1f, 0.1f, 1.0f};
    GLfloat lightDiffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};

    // habilita a luz
    glEnable(GL_LIGHT0);
    
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
}


/*
    Função drawRoom:
    - Configura a iluminação 
    - Desenha o chão e as quatro paredes da sala
*/
void drawRoom() {
    setupLighting();
    // Chão
    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_QUADS);
        glNormal3f(0.0f, 1.0f, 0.0f); // Normal para o chão
        glVertex3f(0.0f, 0, 0.0f);
        glVertex3f(ROOM_SIZE, 0, 0.0f);
        glVertex3f(ROOM_SIZE, 0, ROOM_SIZE);
        glVertex3f(0.0f, 0, ROOM_SIZE);
    glEnd();

    // Teto
    glColor3f(0.2f, 0.2f, 0.6f);
    glBegin(GL_QUADS);
        glNormal3f(0.0f, -1.0f, 0.0f); // Normal para o teto
        glVertex3f(0.0f, WALL_SIZE, 0.0f);
        glVertex3f(ROOM_SIZE, WALL_SIZE, 0.0f);
        glVertex3f(ROOM_SIZE, WALL_SIZE, ROOM_SIZE);
        glVertex3f(0.0f, WALL_SIZE, ROOM_SIZE);
    glEnd();

    // Parede frontal (z = 0)
    glColor3f(0.6f, 0.6f, 0.6f);
    glBegin(GL_QUADS);
        glNormal3f(0.0f, -1.0f, 1.0f); // Normal para a parede frontal
        glVertex3f(0.0f, 0, 0.0f);
        glVertex3f(ROOM_SIZE, 0, 0.0f);
        glVertex3f(ROOM_SIZE, WALL_SIZE, 0.0f);
        glVertex3f(0.0f, WALL_SIZE, 0.0f);
    glEnd();

    // Parede traseira (z = ROOM_SIZE)
    glColor3f(0.6f, 0.6f, 0.6f);
    glBegin(GL_QUADS);
        glNormal3f(0.0f, -1.0f, -1); // Normal para a parede traseira
        glVertex3f(0.0f, 0, ROOM_SIZE);
        glVertex3f(ROOM_SIZE, 0, ROOM_SIZE);
        glVertex3f(ROOM_SIZE, WALL_SIZE, ROOM_SIZE);
        glVertex3f(0.0f, WALL_SIZE, ROOM_SIZE);
    glEnd();

    // Parede esquerda (x = 0)
    glColor3f(0.6f, 0.6f, 0.6f);
    glBegin(GL_QUADS);
        glNormal3f(1.0f, -1.0f, 0.0f);
        glVertex3f(0.0f, 0, 0.0f);
        glVertex3f(0.0f, 0, ROOM_SIZE);
        glVertex3f(0.0f, WALL_SIZE, ROOM_SIZE);
        glVertex3f(0.0f, WALL_SIZE, 0.0f);
    glEnd();

    // Parede direita (x = ROOM_SIZE)
    glColor3f(0.6f, 0.6f, 0.6f);
    glBegin(GL_QUADS);
        glNormal3f(-1.0f, -1.0f, 0.0f); // Normal para a parede direita
        glVertex3f(ROOM_SIZE, 0, 0.0f);
        glVertex3f(ROOM_SIZE, 0, ROOM_SIZE);
        glVertex3f(ROOM_SIZE, WALL_SIZE, ROOM_SIZE);
        glVertex3f(ROOM_SIZE, WALL_SIZE, 0.0f);
    glEnd();
}


/*
    Função checkCollision:
    - true se houver colisão (posição inválida)
    - false caso contrário
*/
bool checkCollision(const Vetor3D &pos) {
    return pos.x < 0 || pos.x > ROOM_SIZE || pos.z < 0 || pos.z > ROOM_SIZE;
}