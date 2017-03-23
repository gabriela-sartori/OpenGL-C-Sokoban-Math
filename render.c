// Renderiza texto na tela, posição e cor precisam ser definidas antes
void renderText (const char * str) {
    const int len = strlen (str);
    for (int i = 0; i < len; i++)
        glutBitmapCharacter (GLUT_BITMAP_TIMES_ROMAN_10, str[i]);
}

// Renderiza um bloco dada uma posição e o tipo do bloco
void renderBlock (const Pos pos, const enum RenderBlock block, const char * text) {

    switch (block) {
        case RFloor:
            glColor3f (0.0f, 0.5f, 1.0f);
            break;
        case RWall:
            glColor3f (0.75f, 0.75f, 0.75f);
            break;
        case RBox:
            glColor3f (0.9f, 0.9f, 0.2f);
            break;
        case RHole:
            glColor3f (0.85f, 1.0f, 0.85f);
            break;
        case RBoxOk:
            glColor3f (0.0f, 1.0f, 0.0f);
            break;
        case RBoxWrong:
            glColor3f (1.0f, 0.0f, 0.0f);
            break;
        case RPlayer: {
            float color  = (getMicroseconds () / 100000) % 2 == 0 ? 0.90 : 0.70;
            glColor3f (1.0f, 0.0f, color);
            break;
        }
        default:
            glColor3f (1.0f, 1.0f, 1.0f);
    }

    glBegin(GL_QUADS);

    const int baseX = - map_init_x + (pos.x - 1) * tile_size ;
    const int baseY =   map_init_y - (pos.y - 1) * tile_size ;

    glVertex3f (baseX +         0, baseY +         0, 0.0f);
    glVertex3f (baseX +         0, baseY + tile_size, 0.0f);
    glVertex3f (baseX + tile_size, baseY + tile_size, 0.0f);
    glVertex3f (baseX + tile_size, baseY +         0, 0.0f);

    glEnd();

    if (text != NULL) {
        glColor3f (0.0f, 0.0f, 0.0f);
        glRasterPos2f(baseX + 5, baseY + 10);
        renderText (text);
    }
} 

// Dado uma estrutura level, renderiza os blocos,
//   buracos, caixas e o player, além de uns textos
void renderLevel (const Level level) {

    int i;

    // Desenhar tiles do mapa
    for (i = 0; i < level.tiles_count; i++) {
        const Tile tile = level.tiles[i];
        renderBlock (tile.pos, tile.walkable ? RFloor : RWall, NULL);
    }

    // Desenhar buracos
    for (i = 0; i < level.holes_count; i++)
        renderBlock (level.holes[i].pos, RHole, level.holes[i].text);

    // Desenhar caixas
    for (i = 0; i < level.boxes_count; i++) {
        const enum RenderBlock boxBlock =
            getRenderBlock (level.boxes[i], level);

        renderBlock (level.boxes[i].pos, boxBlock, level.boxes[i].text);
    }

    // Desenhar player
    renderBlock (level.player, RPlayer, NULL);

    // Escrever no topo da tela
    glColor3f (1.0f, 1.0f, 1.0f);
    glRasterPos2f(-map_init_x - 44, map_init_y + 72);
    renderText ("Controls:");
    glRasterPos2f(-map_init_x + 20, map_init_y + 72);
    renderText ("WASD - Walk");
    glRasterPos2f(-map_init_x + 20, map_init_y + 58);
    renderText ("R - Reset level");
}
