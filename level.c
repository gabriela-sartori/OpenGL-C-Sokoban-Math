// Definimos os tipos de blocos em um enum
enum RenderBlock { RFloor = 1, RWall, RBox, RHole, RBoxWrong, RBoxOk, RPlayer };

#define bool int
#define true 1
#define false 0

// Definindo a estrutura Pos com x e y
typedef struct {
    int x, y;
} Pos;

// Defindo a estrutura Tile com uma posição e o tipo do bloco
typedef struct {
    Pos pos;
    bool walkable;
} Tile;

typedef struct {
    int id;
    Pos pos;
    char * text;
} Box;

typedef struct {
    int id;
    Pos pos;
    char * text;
} Hole;

// Definindo a estrutura Level com um vetor de tiles, um vetor de caixas,
//   um vetor de buracos e suas respectivas quantidades
typedef struct {
    Tile * tiles;
    int tiles_count;
    Box  * boxes;
    int boxes_count;
    Hole  * holes;
    int holes_count;
    Pos    player;
} Level;

Box buildBox (const int id, const Pos pos, const char * text) {
    Box box;
    box.id   = id;
    box.pos  = pos;
    box.text = (char *) text;
    return box;
}

Hole buildHole (const int id, const Pos pos, const char * text) {
    Hole h;
    h.id   = id;
    h.pos  = pos;
    h.text = (char *) text;
    return h;
}

// Construtor da estrutura Pos
Pos buildPos (const int x, const int y) {
    Pos pos;
    pos.x = x;
    pos.y = y;
    return pos;
}

// Construtor da estrutura Tile
Tile buildTile (const Pos pos, const bool walkable) {
    Tile tile;
    tile.pos      = pos;
    tile.walkable = walkable;
    return tile;
}

// Desaloca memória da estrutura Level
void destroyLevel (const Level level) {
    free (level.tiles);
    free (level.boxes);
    free (level.holes);
}

// Transforma uma fase representada em string na estrutura de dados Level
Level strToLevel (const char * strLevel) {
    int i = 0;
    int x = 1;
    int y = 1;

    Level level;
    level.tiles_count = strlen (strLevel);
    level.boxes_count = 0;
    level.holes_count = 0;
    level.tiles       = (Tile *) malloc (level.tiles_count * sizeof (Tile));
    level.boxes       = (Box  *) malloc (50 * sizeof (Box));
    level.holes       = (Hole *) malloc (50 * sizeof (Hole));
    level.player      = buildPos (2, 2);

    while (i < level.tiles_count) {

        x = 1 + i % map_tiles_x;
        y = 1 + i / map_tiles_x;

        const char c = tolower (strLevel[i]);
        const bool walkable = c != 'x';
        level.tiles[i] = buildTile (buildPos(x, y), walkable);

        // Definir a posição do player
        if (c == 'p')
            level.player = buildPos (x, y);

        /*

        // Boxes and Holes now are defined in levels.c

        // Adicionar buraco
        if (c == 'o' || c == 'k')
            level.holes[level.holes_count++] =
                buildHole (level.holes_count, buildPos (x, y), "kk eae man");

        // Adicionar caixa
        if (c == 'b' || c == 'k')
            level.boxes[level.boxes_count++] =
                buildBox (level.boxes_count, buildPos (x, y), "Hmm");
        */

        i++;
    }

    return level;
}
