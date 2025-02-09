#include <GL/freeglut.h>
#include <cstdlib>
#include <ctime>
#include "player.h"
#include "enemy.h"
#include "map.h"
#include "menu.h"

// Função display: se o jogo acabou exibe a tela de game over; caso contrário, desenha a cena
void display() {
    if (gameOver) {
        drawGameOverScreen();
    } else {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
        gluLookAt(playerPos.x, playerPos.y + 0.5, playerPos.z,
                  playerPos.x + playerDir.x, playerPos.y + 0.5 + playerDir.y, playerPos.z + playerDir.z,
                  0, 1, 0);
        drawRoom();
        drawMonsters();
        drawCrosshair();
        drawHUD();
    }
    glutSwapBuffers();
}

// Função para reiniciar o jogo: reseta variáveis do jogador e limpa os inimigos
void resetGame() {
    playerHP = 100;
    playerScore = 0;
    gameOver = false;
    playerPos = Vetor3D(ROOM_SIZE / 2, 0, ROOM_SIZE / 2);
    playerDir = Vetor3D(0, 0, -1);
    monsters.clear();
    glutTimerFunc(3000, spawnMonster, 0);
}

// Função update (mínima, já que update() do player.cpp também é registrada)
void updateScene(int value) {
    glutPostRedisplay();
    glutTimerFunc(16, updateScene, 0);
}

int main(int argc, char** argv) {
    srand(time(NULL));
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Pew-Pew");
    
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    gluPerspective(60, 800.0 / 600.0, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
    
    resetGame();
    
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);
    glutPassiveMotionFunc(mouse);

    glutMouseFunc(mouseClick);
    
    // Registra os timers para atualização do jogador, inimigos e cena
    glutTimerFunc(16, update, 0);             // update() definida em player.cpp
    glutTimerFunc(16, updateMonsters, 0);       // updateMonsters() de enemy.cpp
    glutTimerFunc(3000, spawnMonster, 0);       // spawnMonster() de enemy.cpp
    glutTimerFunc(16, updateScene, 0);          // Apenas para chamar glutPostRedisplay
    
    glutSetCursor(GLUT_CURSOR_NONE);
    glutWarpPointer(400, 300);
    
    glutMainLoop();
    return 0;
}
