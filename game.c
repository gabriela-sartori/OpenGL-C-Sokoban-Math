// Verifica se existe uma caixa em uma dada posição
int isBoxOn (const Pos pos, const Level level) {
    for (int i = 0; i < level.boxes_count; i++)
        if (isPosEqual (pos, level.boxes[i].pos))
            return 1;
    return 0;
}

// Verifica se existe um buraco em uma dada posição
enum RenderBlock getRenderBlock (const Box box, const Level level) {
    for (int i = 0; i < level.holes_count; i++)
        if (isPosEqual (box.pos, level.holes[i].pos))
            return box.id == level.holes[i].id
                ? RBoxOk
                : RBoxWrong ;
    return RBox;
}

// Verifica se pode-se andar em uma dada posição
// Atenção, esta função possui efeitos colaterais, pois caso o player ande
//   em cima de uma caixa, ela se encarrega de movê-la caso possível
int canWalk (const Pos new, Level level) {

    // Não permitir andar na parede
    if (! level.tiles[posToIndex (new)].walkable)
        return 0;

    // Percorre as caixas para encontrar a que estamos tentando empurrar
    for (int i = 0; i < level.boxes_count; i++) {
        const Pos box = level.boxes[i].pos;

        // Tentar empurrar a caixa
        if (isPosEqual (box, new)) {

            // Define a nova posição da caixa apos empurrá-la
            const Pos newBoxPos =
                buildPos ( box.x - (level.player.x - new.x)
                         , box.y - (level.player.y - new.y) );


            // Verifica se tem uma outra caixa na frente desta
            if (isBoxOn (newBoxPos, level))
                return 0;

            const bool isNewBoxPosWall =
                !level.tiles[posToIndex (newBoxPos)].walkable;

            // Nao deixar empurrar caixa contra a parede
            if (isNewBoxPosWall)
                return 0;
            
            // Empurra a caixa
            level.boxes[i].pos = newBoxPos;
            return 1;
        }
    }

    return 1;
}

// Dada uma estrutura level, verifica se o jogador venceu a fase atual
//   verificando se todas as caixas estão em cima do respectivo buraco
int won (const Level level) {
    
    for (int i = 0; i < level.holes_count; i++) {
        
        int ok = 0;
        for (int o = 0; o < level.boxes_count; o++) {
            if (isPosEqual (level.holes[i].pos, level.boxes[o].pos)
            && level.holes[i].id == level.boxes[o].id) {
                ok = 1;
                break;
            }
        }

        // Uma caixa não foi posicionada no buraco, então nao ganhou
        if (! ok)
            return 0;
    }

    // Para que não seja possivel ganhar o ultimo nivel que não tem buracos
    return level.holes_count > 0;
}
