#include "map.h"
#include <GL/glut.h>

// tamanho da sala
const int ROOM_SIZE = 30;
const int WALL_SIZE = 10;



/*
    Função setupLighting:
    - Configura a iluminação global do cenário.
    - Define a luz ambiente e a posição/difusão para iluminar a sala.
*/
void setupLighting() {
<<<<<<< HEAD

    // define a luz ambiente global
    GLfloat globalAmbient[] = {0.2f, 0.2f, 0.2f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbient);

    // define a posição e características da luz principal
    GLfloat lightPosition[] = {ROOM_SIZE / 2, ROOM_SIZE, ROOM_SIZE / 2, 1.0f}; 
    GLfloat lightDiffuse[] = {0.5f, 0.5f, 0.5f, 1.0f}; 
    GLfloat lightSpecular[] = {0.1f, 0.1f, 0.1f, 1.0f}; // essa e para dar efeito de "brilho" na superficie

    // habilita a posição da luz e suas caracteristicas
    glEnable(GL_LIGHT0);                                
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);   // centralizada no meio da sala
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);     // luz difusa
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);   // especular

}


/*
    Função drawRoom:
    - Configura a iluminação 
    - Desenha o chão e as quatro paredes da sala
*/
=======
    GLfloat lightPosition[] = {ROOM_SIZE/2.0f, WALL_SIZE-1.0f, ROOM_SIZE/2.0f, 1.0f}; 
    
    GLfloat lightAmbient[] = {0.2f, 0.2f, 0.2f, 1.0f};
    GLfloat lightDiffuse[] = {0.5f, 0.5f, 0.5f, 1.0f}; 
    GLfloat lightSpecular[] = {0.2f, 0.2f, 0.2f, 1.0f};
    
    glEnable(GL_LIGHT0);

    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
}

>>>>>>> a9858965c83eeb8326114f6b84129e39514d1919
void drawRoom() {
    setupLighting();

    // Chão
    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_QUADS);
        glNormal3f(0, 1, 0); // Normal para o chão
        glVertex3f(0, 0, 0);
        glVertex3f(ROOM_SIZE, 0, 0);
        glVertex3f(ROOM_SIZE, 0, ROOM_SIZE);
        glVertex3f(0, 0, ROOM_SIZE);
    glEnd();

    // Teto
    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_QUADS);
        glNormal3f(0, -1, 0); // Normal para o teto
        glVertex3f(0, WALL_SIZE, 0);
        glVertex3f(ROOM_SIZE, WALL_SIZE, 0);
        glVertex3f(ROOM_SIZE, WALL_SIZE, ROOM_SIZE);
        glVertex3f(0, WALL_SIZE, ROOM_SIZE);
    glEnd();
    
    // Parede frontal (z = 0)
    glColor3f(0.2f, 0.3f, 0.3f);
    glBegin(GL_QUADS);
        glNormal3f(0, 0, 1); // Normal para a parede frontal
        glVertex3f(0, 0, 0);
        glVertex3f(ROOM_SIZE, 0, 0);
        glVertex3f(ROOM_SIZE, WALL_SIZE, 0);
        glVertex3f(0, WALL_SIZE, 0);
    glEnd();

    // Parede traseira (z = ROOM_SIZE)
    glColor3f(0.6f, 0.6f, 0.6f);
    glBegin(GL_QUADS);
        glNormal3f(0, 0, -1); // Normal para a parede traseira
        glVertex3f(0, 0, ROOM_SIZE);
        glVertex3f(ROOM_SIZE, 0, ROOM_SIZE);
        glVertex3f(ROOM_SIZE, WALL_SIZE, ROOM_SIZE);
        glVertex3f(0, WALL_SIZE, ROOM_SIZE);
    glEnd();

    // Parede esquerda (x = 0)
    glColor3f(0.6f, 0.6f, 0.6f);
    glBegin(GL_QUADS);
        glNormal3f(1, 0, 0);
        glVertex3f(0, 0, 0);
        glVertex3f(0, 0, ROOM_SIZE);
        glVertex3f(0, WALL_SIZE, ROOM_SIZE);
        glVertex3f(0, WALL_SIZE, 0);
    glEnd();

    // Parede direita (x = ROOM_SIZE)
    glColor3f(0.6f, 0.6f, 0.6f);
    glBegin(GL_QUADS);
        glNormal3f(-1, 0, 0); // Normal para a parede direita
        glVertex3f(ROOM_SIZE, 0, 0);
        glVertex3f(ROOM_SIZE, 0, ROOM_SIZE);
        glVertex3f(ROOM_SIZE, WALL_SIZE, ROOM_SIZE);
        glVertex3f(ROOM_SIZE, WALL_SIZE, 0);
    glEnd();
}


<<<<<<< HEAD
/*
    Função checkCollision:
    - true se houver colisão (posição inválida)
    - false caso contrário
*/
=======
>>>>>>> a9858965c83eeb8326114f6b84129e39514d1919
bool checkCollision(const Vetor3D &pos) {
    return pos.x < 0 || pos.x > ROOM_SIZE || pos.z < 0 || pos.z > ROOM_SIZE;
}