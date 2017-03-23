// Dada duas posições A e B, retorna se ambas são idênticas
int isPosEqual (const Pos a, const Pos b) {
    return a.x == b.x && a.y == b.y;
}

// Retorna o índice na lista de tiles dada uma posição x e y
int posToIndex (const Pos pos) {
    return pos.x - 1 + (pos.y - 1) * map_tiles_x;
}

// Retorna o tempo atual em microsegundos
uint64_t getMicroseconds () {
    struct timeval tv;
    gettimeofday (&tv, NULL);
    return tv.tv_sec * (uint64_t) 1000000 + tv.tv_usec;
}