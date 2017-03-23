// Representações de cada level do jogo em string

const char * level_01_str =
    "...XXX........"
    "...XoX........"
    "...XbXXXX....."
    ".XXX pboX....."
    ".Xob  XXX....."
    ".XXXXbX......."
    "....XoX......."
    "....XXX......." ;

Level buildLevel_01 () {
    Level lvl = strToLevel (level_01_str);

    lvl.boxes_count = 4;
    lvl.boxes[0] = buildBox (1, buildPos (5, 3), "1 + 1");
    lvl.boxes[1] = buildBox (2, buildPos (7, 4), "2 + 2");
    lvl.boxes[2] = buildBox (3, buildPos (4, 5), "3 + 3");
    lvl.boxes[3] = buildBox (4, buildPos (6, 6), "4 + 4");

    lvl.holes_count = 4;
    lvl.holes[0] = buildHole (1, buildPos (5, 2), "   2");
    lvl.holes[1] = buildHole (2, buildPos (8, 4), "   4");
    lvl.holes[2] = buildHole (3, buildPos (3, 5), "   6");
    lvl.holes[3] = buildHole (4, buildPos (6, 7), "   8");

    return lvl;
}

const char * level_02_str =
    ".XXXXX........"
    ".Xp  X........"
    ".X bbX.XXX...."
    ".X b X.XoX...."
    ".XXX XXXoX...."
    "..XX    oX...."
    "..X   X  X...."
    "..X   XXXX...."
    "..XXXXX......." ;

Level buildLevel_02 () {
    Level lvl = strToLevel (level_02_str);

    lvl.boxes_count = 3;
    lvl.boxes[0] = buildBox (1, buildPos (5, 3), "1 * 1");
    lvl.boxes[1] = buildBox (2, buildPos (4, 3), "2 * 2");
    lvl.boxes[2] = buildBox (3, buildPos (4, 4), "3 * 3");

    lvl.holes_count = 3;
    lvl.holes[0] = buildHole (1, buildPos (9, 4), "   1");
    lvl.holes[1] = buildHole (2, buildPos (9, 5), "   4");
    lvl.holes[2] = buildHole (3, buildPos (9, 6), "   9");

    return lvl;
}

const char * level_03_str =
    "..XXXXXXX....."
    "..X  p  XXX..."
    ".XXbXXX   X..."
    ".X   b  b X..."
    ".X ooX b XX..."
    ".XXooX   X...."
    "..XXXXXXXX...." ;

Level buildLevel_03 () {
    Level lvl = strToLevel (level_03_str);

    lvl.boxes_count = 4;
    lvl.boxes[0] = buildBox (1, buildPos (4, 3), "1 * 1");
    lvl.boxes[1] = buildBox (2, buildPos (6, 4), "2 * 2");
    lvl.boxes[2] = buildBox (3, buildPos (9, 4), "3 * 3");
    lvl.boxes[3] = buildBox (4, buildPos (8, 5), "4 * 4");

    lvl.holes_count = 4;
    lvl.holes[0] = buildHole (1, buildPos (5, 6), "   1");
    lvl.holes[1] = buildHole (2, buildPos (4, 6), "   4");
    lvl.holes[2] = buildHole (3, buildPos (5, 5), "   9");
    lvl.holes[3] = buildHole (4, buildPos (4, 5), "  16");

    return lvl;
}

const char * level_04_str =
    "..XXXX........"
    ".XX  X........"
    ".Xpb X........"
    ".XXb XX......."
    ".XX b X......."
    ".Xob  X......."
    ".XooKoX......."
    ".XXXXXX......." ;
 
 Level buildLevel_04 () {
    Level lvl = strToLevel (level_04_str);

    lvl.boxes_count = 5;
    lvl.boxes[0] = buildBox (1, buildPos (4, 3), "1 * 1");
    lvl.boxes[1] = buildBox (2, buildPos (4, 4), "2 * 2");
    lvl.boxes[2] = buildBox (3, buildPos (5, 5), "3 * 3");
    lvl.boxes[3] = buildBox (4, buildPos (4, 6), "4 * 4");
    lvl.boxes[4] = buildBox (5, buildPos (5, 7), "5 * 5");

    lvl.holes_count = 5; // 4 5 2 3 1
    lvl.holes[0] = buildHole (1, buildPos (5, 7), "   1");
    lvl.holes[1] = buildHole (2, buildPos (4, 7), "   4");
    lvl.holes[2] = buildHole (3, buildPos (6, 7), "   9");
    lvl.holes[3] = buildHole (4, buildPos (3, 6), "  16");
    lvl.holes[4] = buildHole (5, buildPos (3, 7), "  25");

    return lvl;
}   

const char * level_fim_str =
    "XXXXXXXXXXXXXX"
    "Xp           X"
    "X XX X XX XX X"
    "X X  X X X X X"
    "X XX X X   X X"
    "X X  X X   X X"
    "X            X"
    "XXXXXXXXXXXXXX" ;

Level buildLevel_fim () {
    Level lvl = strToLevel (level_fim_str);

    // ...

    return lvl;
}
