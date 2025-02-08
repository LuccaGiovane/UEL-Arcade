#include "map.h"    // Para usar ROOM_SIZE
#include "player.h"
#include "enemy.h"
#include "game.h"

void resetGame() {
    playerHP = 100;
    playerScore = 0;
    gameOver = false;
    
    // Reinicia a posição e a direção do jogador
    playerPos = Vector3(ROOM_SIZE / 2, 0, ROOM_SIZE / 2);
    playerDir = Vector3(0, 0, -1);
    
    // Limpa os monstros da partida anterior
    monsters.clear();
    
    // Opcional: reinicia o timer para spawn de monstros
    glutTimerFunc(3000, spawnMonster, 0);
}
