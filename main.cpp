#include <GL/freeglut.h>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "player.h"
#include "enemy.h"
#include "map.h"

int score = 0;

void drawCrosshair() {
    glDisable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, 800, 0, 600);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glColor3f(1, 1, 1);
    glBegin(GL_LINES);
        glVertex2i(400 - 10, 300);
        glVertex2i(400 + 10, 300);
        glVertex2i(400, 300 - 10);
        glVertex2i(400, 300 + 10);
    glEnd();
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
}

#include <cstdio>  // Para sprintf

void drawHUD() {
    // Configura a projeção 2D
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, 800, 0, 600);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glColor3f(1, 1, 1);  // Cor branca para o texto

    // Mostra o HP
    char hudText[50];
    sprintf(hudText, "HP: %d", playerHP);
    glRasterPos2i(10, 580);  // Posição (10,580)
    for (char* c = hudText; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }

    // Mostra a Pontuação
    sprintf(hudText, "Score: %d", playerScore);
    glRasterPos2i(10, 560);  // Abaixo do HP
    for (char* c = hudText; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }

    // Restaura as matrizes
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(playerPos.x, playerPos.y + 0.5, playerPos.z,
              playerPos.x + playerDir.x, playerPos.y + 0.5 + playerDir.y, playerPos.z + playerDir.z,
              0, 1, 0);
    drawRoom();
    drawMonsters();
    drawCrosshair();

    drawHUD();
    
    glutSwapBuffers();
}

int main(int argc, char** argv) {
    srand(time(NULL));
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Mini DOOM");
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    gluPerspective(60, 800.0/600.0, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);
    glutPassiveMotionFunc(mouse);
    glutMouseFunc(mouseButton);

    glutTimerFunc(16, update, 0);
    glutTimerFunc(16, updateMonsters, 0);
    glutTimerFunc(3000, spawnMonster, 0);

    glutSetCursor(GLUT_CURSOR_NONE);
    glutWarpPointer(400, 300);

    glutMainLoop();
    return 0;
}
