#include "player.h"
#include "map.h"
#include "enemy.h"
#include <GL/glut.h>
#include <cmath>
#include <iostream>
#include <windows.h>
#include <mmsystem.h>


extern void resetGame();

// Constantes para o jogador
const float PLAYER_SPEED = 0.05f;
// Estado inicial do jogo
bool gameOver = false;
bool atirando = false;
int playerHP = 100;
int playerScore = 0;
Vetor3D playerPos(ROOM_SIZE / 2, 0, ROOM_SIZE / 2);  // ROOM_SIZE definido em map.cpp
Vetor3D playerDir(0, 0, -1);
bool keyPressed[256];

bool shotLight = false;


void setupShotLight() {
    if (shotLight) {
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_LIGHT1);
        
        GLfloat lightPos[] = { playerPos.x, playerPos.y + 0.5f, playerPos.z, 1.0f };

        GLfloat lightColor[] = { 0.5f, 0.5f, 0.35f, 1.0f };
        glLightfv(GL_LIGHT1, GL_POSITION, lightPos);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor);
        glLightfv(GL_LIGHT1, GL_SPECULAR, lightColor);

    } else {
        glDisable(GL_LIGHT1);
    }
}


void lightOf(int value){
    shotLight = false;
}

void movePlayer(){
        if(gameOver) return;

        float angle, oldDirX, len;

        // Movimento para frente (W) e para trás (S) já existentes:
        if (keyPressed['w'] || keyPressed['W']) {
            Vetor3D newPos = playerPos;
            newPos.x += playerDir.x * PLAYER_SPEED;
            newPos.z += playerDir.z * PLAYER_SPEED;
            if (!checkCollision(newPos)) playerPos = newPos;
            
        } 
        if (keyPressed['s'] || keyPressed['S']) {
            Vetor3D newPos = playerPos;
            newPos.x -= playerDir.x * PLAYER_SPEED;
            newPos.z -= playerDir.z * PLAYER_SPEED;
            if (!checkCollision(newPos)) playerPos = newPos;
        }
        
        // Movimento lateral para a direita (E) e para a esquerda (Q)
        if (keyPressed['e'] || keyPressed['E']) {
            // Vetor perpendicular à direção do jogador: para a esquerda, (-playerDir.z, 0, playerDir.x)
            Vetor3D left(-playerDir.z, 0, playerDir.x);
            // Normaliza o vetor left
            len = std::sqrt(left.x * left.x + left.z * left.z);
            left.x /= len;
            left.z /= len;
            Vetor3D newPos = playerPos;
            newPos.x += left.x * PLAYER_SPEED;
            newPos.z += left.z * PLAYER_SPEED;
            if (!checkCollision(newPos)) playerPos = newPos;
        }
        if (keyPressed['q'] || keyPressed['Q']) {
            // Vetor perpendicular para a direita: (playerDir.z, 0, -playerDir.x)
            Vetor3D right(playerDir.z, 0, -playerDir.x);
            len = std::sqrt(right.x * right.x + right.z * right.z);
            right.x /= len;
            right.z /= len;
            Vetor3D newPos = playerPos;
            newPos.x += right.x * PLAYER_SPEED;
            newPos.z += right.z * PLAYER_SPEED;
            if (!checkCollision(newPos)) playerPos = newPos;
        }

        // Giro para direita (A) e para esquerda (D)
        if (keyPressed['a'] || keyPressed['A']) {
            angle = -PLAYER_SPEED;
            oldDirX = playerDir.x;
            playerDir.x = playerDir.x * cos(angle) - playerDir.z * sin(angle);
            playerDir.z = oldDirX * sin(angle) + playerDir.z * cos(angle);
        }
        if (keyPressed['d'] || keyPressed['D']) {
            angle = PLAYER_SPEED;
            oldDirX = playerDir.x;
            playerDir.x = playerDir.x * cos(angle) - playerDir.z * sin(angle);
            playerDir.z = oldDirX * sin(angle) + playerDir.z * cos(angle);
        }
        
        if (keyPressed[' ']) { 
            keyPressed[' '] = false;
            shotLight = true;
            PlaySound("shot.wav", NULL, SND_FILENAME | SND_ASYNC);
            glutTimerFunc(100, lightOf, 0);
            shoot();

        }

}


void keyboard(unsigned char key, int x, int y) {
    if (gameOver) {
        // Em game over, o ENTER reinicia e a tecla Q sai do jogo
        if (key == 13) { // Código ASCII para ENTER
            resetGame();
        } else if (key == 'q' || key == 'Q') exit(0);
    } else keyPressed[key] = true;
}

void keyboardUp(unsigned char key, int x, int y) {
    keyPressed[key] = false;
}

void update(int value) {
    if (!gameOver) {
        movePlayer();
        if (playerHP <= 0) gameOver = true;
    }
    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}
