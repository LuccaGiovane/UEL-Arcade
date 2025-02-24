#ifndef PLAYER_H
#define PLAYER_H

#include "menu.h"  // Para usar Vetor3D

// Variáveis globais do jogador e estado do jogo
extern bool gameOver;
extern int playerHP;
extern int playerScore;
extern Vetor3D playerPos;
extern Vetor3D playerDir;
extern bool keyPressed[256];

// Funções relacionadas ao jogador
void keyboard(unsigned char key, int x, int y);     // callback p/ quando pressionar tecla
void keyboardUp(unsigned char key, int x, int y);   // callback p/ quando liberar tecla
void update(int value);
void setupShotLight();                              // luz do tiro

#endif
