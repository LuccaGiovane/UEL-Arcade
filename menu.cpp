#include "menu.h"
#include <cstdio>

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

// As variáveis playerHP e playerScore são definidas em player.cpp (declaração em player.h)
extern int playerHP;
extern int playerScore;

void drawHUD() {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
        glLoadIdentity();
        gluOrtho2D(0, 800, 0, 600);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        glLoadIdentity();
        glColor3f(1, 1, 1);
        char hudText[50];
        sprintf(hudText, "HP: %d", playerHP);
        glRasterPos2i(10, 580);
        for (char* c = hudText; *c != '\0'; c++)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
        sprintf(hudText, "Score: %d", playerScore);
        glRasterPos2i(10, 560);
        for (char* c = hudText; *c != '\0'; c++)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

void drawGameOverScreen() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
        glLoadIdentity();
        gluOrtho2D(0, 800, 0, 600);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        glLoadIdentity();
        glColor3f(1, 1, 1);
        char finalScoreText[50];
        sprintf(finalScoreText, "Pontuacao: %d", playerScore);
        int textWidth = strlen(finalScoreText) * 9;
        int x = (800 - textWidth) / 2;
        int y = 300;
        glRasterPos2i(x, y);
        for (char* c = finalScoreText; *c != '\0'; c++)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
        const char* playAgainText = "[ENTER] Jogar novamente [Q] Sair";
        int textWidth2 = strlen(playAgainText) * 9;
        int x2 = (800 - textWidth2) / 2;
        int y2 = 250;
        glRasterPos2i(x2, y2);
        for (const char* c = playAgainText; *c != '\0'; c++)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}
