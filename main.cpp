#include <GL/freeglut.h>
#include <cstdlib>
#include <ctime>
#include "player.h"
#include "enemy.h"
#include "map.h"
#include "menu.h"



/*
    Função display: 
    - se o jogo acabou exibe a tela de game over; 
    - caso contrário, desenha a cena
*/
void display() {
    if (gameOver) {
        drawGameOverScreen();
    } else {
        // limpa os buffers e reseta a matriz de modelo/visao
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
        
        // Atualiza câmera seguindo o jogador
        //(posicao da camera, onde a camera esta 'olhando', vetor 'up')
        gluLookAt(playerPos.x, playerPos.y + 0.5f, playerPos.z,
                  playerPos.x + playerDir.x, playerPos.y + 0.5f + playerDir.y, playerPos.z + playerDir.z,
                  0, 1, 0);
        
        // iluminaçao e renderizaçao de cenario/objetos
        glEnable(GL_LIGHTING);
        setupShotLight();    // luz do tiro
        drawRoom();
        glDisable(GL_LIGHTING);
        drawMonsters();
        drawCrosshair();
        drawHUD();
    }

    glutSwapBuffers();
}


/*
    Função resetGame:
    reinicia as variaveis do jogador
    reseta o vetor de inimigos
*/
void resetGame() {
    playerHP = 100;
    playerScore = 0;
    gameOver = false;
    playerPos = Vetor3D(ROOM_SIZE / 2, 0, ROOM_SIZE / 2);
    playerDir = Vetor3D(0, 0, -1);
    monsters.clear();
    glutTimerFunc(3000, spawnMonster, 0);
}


/*
    Função updateScene:
    - glutPostRedisplay() sinaliz que a tela deve ser redesenhada
    - chama a cada 16ms pra atualizar o frame de forma continua
*/
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
    
    // configurações do 3d
    glEnable(GL_DEPTH_TEST);       // teste de profundidade para renderização 3D
    glMatrixMode(GL_PROJECTION);   // configura a matriz de projeção para definir a perspectiva 3D
    gluPerspective(60, 800.0 / 600.0, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
    
    resetGame();
    
    // inicializa o array das teclas
    for (int i = 0; i < 256; i++) keyPressed[i]=false;

    // callbacks para renderização e entrada do usuário
    glutDisplayFunc(display);       // janela precisa ser redesenhada
    glutKeyboardFunc(keyboard);     // teclas pressionadas
    glutKeyboardUpFunc(keyboardUp); // teclas liberadas
    
    
    // registra os timers para atualização do jogo
    glutTimerFunc(16, update, 0);             // Atualiza o estado do jogador (player.cpp)
    glutTimerFunc(16, updateMonsters, 0);     // tualiza o estado dos inimigos (enemy.cpp)
    glutTimerFunc(16, updateScene, 0);        // chama glutPostRedisplay pra redesenhar a cena
    
    // esconde o cursor e trava ele no centro da tela
    glutSetCursor(GLUT_CURSOR_NONE);
    glutWarpPointer(400, 300);
    
    glutMainLoop();
    return 0;
}
