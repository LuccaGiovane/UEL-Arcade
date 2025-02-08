#include "player.h"
#include "map.h"
#include "enemy.h"
#include "vector3.h"
#include "game.h"
#include <cmath>
#include <GL/glut.h>

const float PLAYER_SPEED = 0.1f;
const float MOUSE_SENSITIVITY = 0.002f;
int playerHP = 100;
int playerScore = 0;


Vector3 playerPos(ROOM_SIZE / 2, 0, ROOM_SIZE / 2);
Vector3 playerDir(0, 0, -1);

bool keyPressed[256] = { false };

void movePlayer() {
    // Avança com a tecla W
    if (keyPressed['w'] || keyPressed['W']) {
        Vector3 newPos = playerPos;
        newPos.x += playerDir.x * PLAYER_SPEED;
        newPos.z += playerDir.z * PLAYER_SPEED;
        if (!checkCollision(newPos))
            playerPos = newPos;
    }
    // Retrocede com a tecla S
    if (keyPressed['s'] || keyPressed['S']) {
        Vector3 newPos = playerPos;
        newPos.x -= playerDir.x * PLAYER_SPEED;
        newPos.z -= playerDir.z * PLAYER_SPEED;
        if (!checkCollision(newPos))
            playerPos = newPos;
    }
    // Rotaciona para a esquerda com a tecla A
    if (keyPressed['a'] || keyPressed['A']) {
        float angle = -PLAYER_SPEED;  // Rotaciona negativamente
        float oldDirX = playerDir.x;
        playerDir.x = playerDir.x * cos(angle) - playerDir.z * sin(angle);
        playerDir.z = oldDirX * sin(angle) + playerDir.z * cos(angle);
    }
    // Rotaciona para a direita com a tecla D
    if (keyPressed['d'] || keyPressed['D']) {
        float angle = PLAYER_SPEED;  // Rotaciona positivamente
        float oldDirX = playerDir.x;
        playerDir.x = playerDir.x * cos(angle) - playerDir.z * sin(angle);
        playerDir.z = oldDirX * sin(angle) + playerDir.z * cos(angle);
    }
}

void mouse(int x, int y) {
    static int lastX = 400;
    int deltaX = x - lastX;
    lastX = x;
    float angle = deltaX * MOUSE_SENSITIVITY;
    float oldDirX = playerDir.x;
    playerDir.x = playerDir.x * cos(angle) - playerDir.z * sin(angle);
    playerDir.z = oldDirX * sin(angle) + playerDir.z * cos(angle);

    glutWarpPointer(400, 300);
}

// Se a tecla pressionada for espaço, dispara; caso contrário, registra o estado para movimentação.
void keyboard(unsigned char key, int x, int y) {
    if (gameOver) {
        // Se o jogo acabou, tratamos as teclas para reiniciar ou sair
        if (key == 13) { // 13 é o código ASCII para ENTER
            resetGame();
        } else if (key == 'q' || key == 'Q') {
            exit(0);
        }
        return;
    }

    if (key == ' ') {
        shoot();  // Dispara utilizando o range definido em enemy.cpp
    } else {
        keyPressed[key] = true;
    }
}

void keyboardUp(unsigned char key, int x, int y) {
    keyPressed[key] = false;
}

#include <cstring> // Para strlen

void mouseButton(int button, int state, int x, int y) {
    // Se necessário, trate outros cliques aqui.
    // Agora o reinício do jogo será feito via teclado (ENTER e 'q' no game over).
}



void update(int value) {
    if (!gameOver) {
        movePlayer();
        // Se o HP zerar, interrompa a atualização normal:
        if (playerHP <= 0) {
            gameOver = true;
        }
    }
    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

