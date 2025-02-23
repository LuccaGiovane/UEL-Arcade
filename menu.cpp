#include "menu.h"
#include <cstdio>

// As variáveis playerHP e playerScore são definidas em player.cpp (declaração em player.h)
extern int playerHP;
extern int playerScore;

/*
    Função drawCrosshair:
    - Desativa o teste de profundidade para desenhar o crosshair em 2D sem interferência do cenário 3D.
    - Configura uma projeção ortogonal (2D) usando gluOrtho2D.
    - Desenha linhas brancas que formam a mira central.
*/
void drawCrosshair() {
    glDisable(GL_DEPTH_TEST);                         // Desativa o teste de profundidade
    glMatrixMode(GL_PROJECTION);                      // Muda para a matriz de projeção
    glPushMatrix();                                   // Salva a matriz de projeção atual
        glLoadIdentity();                             // Reseta a matriz de projeção
        gluOrtho2D(0, 800, 0, 600);                   // Define uma projeção 2D que mapeia a janela (800x600)
    glMatrixMode(GL_MODELVIEW);                       
    glPushMatrix();                                  
        glLoadIdentity();                             
        glColor3f(1, 1, 1);                           
        glBegin(GL_LINES);                            
            // Desenha a linha horizontal do crosshair
            glVertex2i(400 - 10, 300);                
            glVertex2i(400 + 10, 300);                
            // Desenha a linha vertical do crosshair
            glVertex2i(400, 300 - 10);                
            glVertex2i(400, 300 + 10);                
        glEnd();                                      
    glPopMatrix();                                    // Restaura a matriz de modelo/visão
    glMatrixMode(GL_PROJECTION);                      // Volta para a matriz de projeção
    glPopMatrix();                                    // Restaura a matriz de projeção
    glMatrixMode(GL_MODELVIEW);                       // Retorna para a matriz de modelo/visão
    glEnable(GL_DEPTH_TEST);                          // Reativa o teste de profundidade
}

/*
    Função drawHUD:
    - Configura uma projeção ortogonal (2D) para desenhar o HUD sobre a cena 3D.
    - Exibe o HP e a pontuação do jogador usando texto bitmap.
*/
void drawHUD() {
    glMatrixMode(GL_PROJECTION);                      // Muda para a matriz de projeção
    glPushMatrix();                                   // Salva a matriz de projeção atual
        glLoadIdentity();                             // Reseta a matriz de projeção
        gluOrtho2D(0, 800, 0, 600);                   // Define uma projeção 2D para a janela
    glMatrixMode(GL_MODELVIEW);                       // Muda para a matriz de modelo/visão
    glPushMatrix();                                   // Salva a matriz de modelo/visão atual
        glLoadIdentity();                             
        glColor3f(1, 1, 1);                           
        
        // Prepara e desenha o texto do HP
        char hudText[50];
        sprintf(hudText, "HP: %d", playerHP);         
        glRasterPos2i(10, 580);                       
        for (char* c = hudText; *c != '\0'; c++)       
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);  // Desenha o caractere
            
        // Prepara e desenha o texto da pontuação
        sprintf(hudText, "Score: %d", playerScore);   
        glRasterPos2i(10, 560);                       
        for (char* c = hudText; *c != '\0'; c++)       
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);  // Desenha o caractere
    glPopMatrix();                                    // Restaura a matriz de modelo/visão
    glMatrixMode(GL_PROJECTION);                      // Volta para a matriz de projeção
    glPopMatrix();                                    // Restaura a matriz de projeção
    glMatrixMode(GL_MODELVIEW);                       // Retorna para a matriz de modelo/visão
}

/*
    Função drawGameOverScreen:
    - Limpa os buffers e configura uma projeção 2D para exibir a tela de fim de jogo.
    - Exibe a pontuação final e as instruções para reiniciar ou sair.
*/
void drawGameOverScreen() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_PROJECTION);                      
    glPushMatrix();                                   
        glLoadIdentity();                             
        gluOrtho2D(0, 800, 0, 600);                   // Define uma projeção 2D para a janela
    glMatrixMode(GL_MODELVIEW);                       // Muda para a matriz de modelo/visão
    glPushMatrix();                                   // Salva a matriz de modelo/visão atual
        glLoadIdentity();                             
        glColor3f(1, 1, 1);                           
        
        // Prepara e desenha a string da pontuação final
        char finalScoreText[50];
        sprintf(finalScoreText, "Pontuacao: %d", playerScore);
        int textWidth = strlen(finalScoreText) * 9;     // Calcula uma largura aproximada do texto
        int x = (800 - textWidth) / 2;                  
        int y = 300;                                    
        glRasterPos2i(x, y);                            
        for (char* c = finalScoreText; *c != '\0'; c++)  
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c); // Desenha o caractere

        // Prepara e desenha as instruções para reiniciar ou sair
        const char* playAgainText = "[ENTER] Jogar novamente [Q] Sair";
        int textWidth2 = strlen(playAgainText) * 9;     // Calcula uma largura aproximada do texto
        int x2 = (800 - textWidth2) / 2;                
        int y2 = 250;                                   
        glRasterPos2i(x2, y2);                          
        for (const char* c = playAgainText; *c != '\0'; c++)  
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c); // Desenha o caractere
    glPopMatrix();                                    
    glMatrixMode(GL_PROJECTION);                      
    glPopMatrix();                                    
    glMatrixMode(GL_MODELVIEW);                       
}
