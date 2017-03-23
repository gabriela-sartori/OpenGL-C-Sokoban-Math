// Tirar as warnings de deprecated do OpenGL no OSX
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

// Importar bibliotecas padrão do C
#include <stdlib.h>   // malloc
#include <string.h>   // strlen
#include <ctype.h>    // tolower
#include <sys/time.h> // gettimeofday

// Importar a biblioteca corretamente dependendo do sistema operacional
#ifdef __APPLE__
    #include <GLUT/glut.h>
#else
    #include <GL/glut.h>
#endif

// Importar arquivos do nosso projeto
#include "constants.c"
#include "level.c"
#include "levels.c"
#include "utils.c"
#include "game.c"
#include "render.c"

// Vetor de lambdas que constroem cada level
Level (** levelBuilders)();

// Índice do level atual. Valores válidos: 0..max_levels - 1
int currentLevel = 0;

// Estrutura do level atual
Level level;

// Função responsável por renderizar a nossa view
void onDisplayFunc () {
    glClear (GL_COLOR_BUFFER_BIT);
    renderLevel (level);
    glutSwapBuffers ();
}

// Função chamada para inicializar o que for necessario na renderização
void onInitialize () { 
    glClearColor (0.0f, 0.5f, 1.0f, 1.0f);
}

// Função chamada quando redimensionamos a janela do app
void onReshape (GLsizei w, GLsizei h) {
    glViewport (0, 0, w, h);
    
    // Especifica sistema de coordenadas de projeção
    glMatrixMode (GL_PROJECTION);

    // Inicializa sistema de coordenadas de projeção
    glLoadIdentity ();

    // Especifica a projeção perspectiva
    gluPerspective (90, (float) map_tiles_x / (float) map_tiles_y, 0.5, 500);

    // Especifica sistema de coordenadas do modelo
    glMatrixMode (GL_MODELVIEW);

    // Inicializa sistema de coordenadas do modelo
    glLoadIdentity ();

    // Especifica posição do observador e do alvo
    gluLookAt (0, 0, 200, 0, 0, 0, 0, 1, 0);
}

// Função chamada quando uma tecla é pressionada
void onKeyPress (unsigned char key, int x, int y) {

    Pos tmp = level.player;

    switch (tolower(key)) {
        case 'w':
            tmp.y--;
            break;
        case 'a':
            tmp.x--;
            break;
        case 's':
            tmp.y++;
            break;
        case 'd':
            tmp.x++;
            break;

        case 'r':
            destroyLevel (level);
            level = (*levelBuilders[currentLevel])();
            glutPostRedisplay ();
            return;
    }

    // Nao apertou nenhuma tecla de andar
    if (isPosEqual (level.player, tmp))
        return;

    // Não conseguiu andar ou empurrar caixas
    if (! canWalk (tmp, level))
        return;

    // Atualiza a posição do player
    level.player = tmp;

    // Caso tenha vencido o level, pula para o proximo
    if (won(level)) {
        destroyLevel (level);
        level = (*levelBuilders[++currentLevel])();
    }

    // Esta função faz a tela ser renderizada novamente
    glutPostRedisplay ();
}

// Função chamada quando está disponível para renderizar novamente
void onIdle () {
    glutPostRedisplay ();
}

int main (int argc, char ** argv) {
    
    // Aloca e preenche o vetor de funções
    // Type Annotation: levelBuilders :: [() -> Level]
    levelBuilders = (Level (**)()) malloc (max_levels * sizeof (Level (*)()));
    levelBuilders[0] = buildLevel_01;
    levelBuilders[1] = buildLevel_02;
    levelBuilders[2] = buildLevel_03;
    levelBuilders[3] = buildLevel_04;
    levelBuilders[4] = buildLevel_fim;

    // Inicializa o jogo na fase 1
    level = (*levelBuilders[currentLevel])();

    // Inicializa configurações do OpenGL
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    
    glutInitWindowSize(tile_size * map_tiles_x, tile_size * map_tiles_y);
    glutCreateWindow("Sokoban 1.0 - OpenGL");

    glutDisplayFunc  (onDisplayFunc);
    glutReshapeFunc  (onReshape);
    glutKeyboardFunc (onKeyPress);
    glutIdleFunc     (onIdle);

    onInitialize ();
    glutMainLoop ();

    return 0;
}
