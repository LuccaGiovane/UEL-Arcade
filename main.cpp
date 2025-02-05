#include <GL/freeglut.h>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>

// Constantes
const float PLAYER_SPEED = 0.1f;
const float MOUSE_SENSITIVITY = 0.002f;
const int ROOM_SIZE = 30;

//texturas
GLuint floorTexture, wallTexture, enemyTexture;

// Estruturas
struct Vector3 {
    float x, y, z;
    Vector3(float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z) {}
};

struct Monster {
    Vector3 position;
    bool active;
};

// Variáveis globais
Vector3 playerPos(ROOM_SIZE/2, 0, ROOM_SIZE/2);
Vector3 playerDir(0, 0, -1);
Vector3 playerPlane(-1, 0, 0);
float playerAngle = 0;
std::vector<Monster> monsters;
int score = 0;
bool keyPressed[256] = {false};

// Funções auxiliares
float degToRad(float degrees) { return degrees * M_PI / 180.0; }



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

// Desenhar a sala
void drawRoom() {
    // Chão - Cor cinza escuro
    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_QUADS);
    glVertex3f(0, 0, 0);
    glVertex3f(ROOM_SIZE, 0, 0);
    glVertex3f(ROOM_SIZE, 0, ROOM_SIZE);
    glVertex3f(0, 0, ROOM_SIZE);
    glEnd();

    // Teto - Cor cinza claro
    glColor3f(0.7f, 0.7f, 0.7f);
    glBegin(GL_QUADS);
    glVertex3f(0, ROOM_SIZE, 0);
    glVertex3f(ROOM_SIZE, ROOM_SIZE, 0);
    glVertex3f(ROOM_SIZE, ROOM_SIZE, ROOM_SIZE);
    glVertex3f(0, ROOM_SIZE, ROOM_SIZE);
    glEnd();

    // Parede frontal (z = 0) - Vermelho
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex3f(0, 0, 0);
    glVertex3f(ROOM_SIZE, 0, 0);
    glVertex3f(ROOM_SIZE, ROOM_SIZE, 0);
    glVertex3f(0, ROOM_SIZE, 0);
    glEnd();

    // Parede traseira (z = ROOM_SIZE) - Azul
    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex3f(0, 0, ROOM_SIZE);
    glVertex3f(ROOM_SIZE, 0, ROOM_SIZE);
    glVertex3f(ROOM_SIZE, ROOM_SIZE, ROOM_SIZE);
    glVertex3f(0, ROOM_SIZE, ROOM_SIZE);
    glEnd();

    // Parede esquerda (x = 0) - Verde
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, ROOM_SIZE);
    glVertex3f(0, ROOM_SIZE, ROOM_SIZE);
    glVertex3f(0, ROOM_SIZE, 0);
    glEnd();

    // Parede direita (x = ROOM_SIZE) - Amarelo
    glColor3f(1.0f, 1.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex3f(ROOM_SIZE, 0, 0);
    glVertex3f(ROOM_SIZE, 0, ROOM_SIZE);
    glVertex3f(ROOM_SIZE, ROOM_SIZE, ROOM_SIZE);
    glVertex3f(ROOM_SIZE, ROOM_SIZE, 0);
    glEnd();
}
// Desenhar monstros
void drawMonsters() {
    for(auto& m : monsters) {
        if(!m.active) continue;
        glPushMatrix();
        glTranslatef(m.position.x, 0.5f, m.position.z);
        glColor3f(1, 0, 0);
        glutSolidSphere(0.3, 10, 10);
        glPopMatrix();
    }
}

// Verificar colisões
bool checkCollision(Vector3 pos) {
    return pos.x < 0 || pos.x > ROOM_SIZE || pos.z < 0 || pos.z > ROOM_SIZE;
}

// Atualizar monstros
void updateMonsters(int value) {
    for(auto& m : monsters) {
        if(!m.active) continue;
        Vector3 dir = Vector3(playerPos.x - m.position.x, 0, playerPos.z - m.position.z);
        float len = sqrt(dir.x*dir.x + dir.z*dir.z);
        if(len > 0) {
            dir.x /= len;
            dir.z /= len;
            m.position.x += dir.x * 0.05f;
            m.position.z += dir.z * 0.05f;
        }
    }
    glutTimerFunc(16, updateMonsters, 0);
}

// Spawn de monstros
void spawnMonster(int value) {
    Monster m;
    m.position = Vector3(rand()%ROOM_SIZE, 0, rand()%ROOM_SIZE);
    m.active = true;
    monsters.push_back(m);
    glutTimerFunc(3000, spawnMonster, 0);
}

// Função de display
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(playerPos.x, playerPos.y + 0.5, playerPos.z,
              playerPos.x + playerDir.x, playerPos.y + 0.5 + playerDir.y, playerPos.z + playerDir.z,
              0, 1, 0);

    drawRoom();
    drawMonsters();
    drawCrosshair();

    glutSwapBuffers();
}

// Teclado
void keyboard(unsigned char key, int x, int y) {
    keyPressed[key] = true;
}

void keyboardUp(unsigned char key, int x, int y) {
    keyPressed[key] = false;
}

// Movimento do jogador
void movePlayer() {
    if(keyPressed['w']) {
        Vector3 newPos = playerPos;
        newPos.x += playerDir.x * PLAYER_SPEED;
        newPos.z += playerDir.z * PLAYER_SPEED;
        if(!checkCollision(newPos)) playerPos = newPos;
    }
    if(keyPressed['s']) {
        Vector3 newPos = playerPos;
        newPos.x -= playerDir.x * PLAYER_SPEED;
        newPos.z -= playerDir.z * PLAYER_SPEED;
        if(!checkCollision(newPos)) playerPos = newPos;
    }
    if(keyPressed['a']) {
        float angle = -PLAYER_SPEED;
        float oldDirX = playerDir.x;
        playerDir.x = playerDir.x * cos(angle) - playerDir.z * sin(angle);
        playerDir.z = oldDirX * sin(angle) + playerDir.z * cos(angle);
    }
    if(keyPressed['d']) {
        float angle = PLAYER_SPEED;
        float oldDirX = playerDir.x;
        playerDir.x = playerDir.x * cos(angle) - playerDir.z * sin(angle);
        playerDir.z = oldDirX * sin(angle) + playerDir.z * cos(angle);
    }
}

// Mouse
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

// Tiro
void shoot() {
    for(auto& m : monsters) {
        if(!m.active) continue;
        if(fabs(m.position.x - playerPos.x) < 0.5 &&
           fabs(m.position.z - playerPos.z) < 0.5) {
            m.active = false;
            score++;
            //printf("Score: %d\n", score);
        }
    }
}

// Botão do mouse
void mouseButton(int button, int state, int x, int y) {
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        shoot();
    }
}

// Loop principal
void update(int value) {
    movePlayer();
    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
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