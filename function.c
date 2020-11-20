const int MAP_SIZE = 21;
const int ITERATION = 10;

// PROTOTYPE
void initMap(char[MAP_SIZE][MAP_SIZE]);
void printMap_Raw(char[MAP_SIZE][MAP_SIZE]);
void printMap_Translated(char[MAP_SIZE][MAP_SIZE]);

void GenerateRooms(char[MAP_SIZE][MAP_SIZE]);
void GeneratePath(char[MAP_SIZE][MAP_SIZE]);

char Translate(char);

// INIT MAP
void initMap(char map[MAP_SIZE][MAP_SIZE]){
    for (int x = 0; x < MAP_SIZE; x++)
        for (int y = 0; y < MAP_SIZE; y++)
            map[x][y] = '.';
}

// PRINT MAP
void printMap_Raw(char map[MAP_SIZE][MAP_SIZE]){
    printf("--- MAP RAW ---\n");
    for (int x = 0; x < MAP_SIZE; x++){
        for (int y = 0; y < MAP_SIZE; y++)
            printf("%c", map[x][y]);
    printf("\n");
    }
    printf("\n");
}

// PRINT MAP TRANSLATED WITH Translate()
void printMap_Translated(char map[MAP_SIZE][MAP_SIZE]){
    printf("--- MAP TRANSLATED ---\n");
    for (int x = 0; x < MAP_SIZE; x++){
        for (int y = 0; y < MAP_SIZE; y++)
            printf("%c", Translate(map[x][y]));
    printf("\n");
    }
    printf("\n");
}

// TRANSLATE ROOM TYPE IN APPROPRIATE CARACTER TO BE VISUALLY CLEAN
char Translate(char c){
    switch(c){
        case 'a': return 206; break; // ╬

        case 'b': return 204; break; // ╠
        case 'c': return 202; break; // ╩
        case 'd': return 185; break; // ╣
        case 'e': return 203; break; // ╦

        case 'f': return 186; break; // ║
        case 'g': return 205; break; // ═

        case 'h': return 200; break; // ╚
        case 'i': return 201; break; // ╔
        case 'j': return 187; break; // ╗
        case 'k': return 188; break; // ╝

        case 'l': return 193; break; // ┴
        case 'm': return 195; break; // ├
        case 'n': return 194; break; // ┬
        case 'o': return 180; break; // ┤

        case '.': return ' '; break; // Set void
        default : return 176;        // ░ (for error)
    }
}

// CREATE ROOMS
void GenerateRooms(char map[MAP_SIZE][MAP_SIZE]){
    // Random init
    srand(GetTickCount());
    // for n iterations
    for (int i = 0; i < ITERATION; i++){
        for (int x = 0; x < MAP_SIZE; x++)
            for (int y = 0; y < MAP_SIZE; y++)
                // if it's a room
                if (map[x][y] == 'x'){
                    // if we don't touch border up
                    if (x > 0){
                        int r = (rand() % 2);
                        if (r)
                            map[x-1][y] = 'o';
                    }
                    // if we don't touch border down
                    if (x < MAP_SIZE-1){
                        int r = (rand() % 2);
                        if (r)
                            map[x+1][y] = 'o';
                    }
                    // if we don't touch border left
                    if (y > 0){
                        int r = (rand() % 2);
                        if (r)
                            map[x][y-1] = 'o';
                    }
                    // if we don't touch border right
                    if (y < MAP_SIZE-1){
                        int r = (rand() % 2);
                        if (r)
                            map[x][y+1] = 'o';
                    }
                }
        for (int x = 0; x < MAP_SIZE; x++)
            for (int y = 0; y < MAP_SIZE; y++)
                if (map[x][y] == 'o')
                    map[x][y] = 'x';
    }
}

// CHANGE ROOM TYPE TO HAVE PATH
void GeneratePath(char map[MAP_SIZE][MAP_SIZE]){
    for (int x = 0; x < MAP_SIZE; x++)
        for (int y = 0; y < MAP_SIZE; y++){
            if (map[x][y] == 'x'){
                int path[4]={0,0,0,0}; // room path

                // path up
                if (x > 0)
                    if (map[x-1][y] != '.')
                        path[0] = 1;
                // path down
                if (x < MAP_SIZE-1)
                    if (map[x+1][y] != '.')
                        path[1] = 1;
                // path left
                if (y > 0)
                    if (map[x][y-1] != '.')
                        path[2] = 1;
                // path right
                if (y < MAP_SIZE-1)
                    if (map[x][y+1] != '.')
                        path[3] = 1;

                /*
                switch(path[]){
                    case {1,0,0,0}: map[x][y] = 'l'; break;
                    case {0,1,0,0}: map[x][y] = 'n'; break;
                    case {0,0,1,0}: map[x][y] = 'o'; break;
                    case {0,0,0,1}: map[x][y] = 'm'; break;
                    default : map[x][y] = '/';
                }
                */


                if (path[0] == 1 && path[1] == 0 && path[2] == 0 && path[3] == 0){map[x][y] = 'l';}
                else if (path[0] == 0 && path[1] == 1 && path[2] == 0 && path[3] == 0){map[x][y] = 'n';}
                else if (path[0] == 0 && path[1] == 0 && path[2] == 1 && path[3] == 0){map[x][y] = 'o';}
                else if (path[0] == 0 && path[1] == 0 && path[2] == 0 && path[3] == 1){map[x][y] = 'm';}

                else if (path[0] == 1 && path[1] == 1 && path[2] == 0 && path[3] == 0){map[x][y] = 'f';}
                else if (path[0] == 0 && path[1] == 0 && path[2] == 1 && path[3] == 1){map[x][y] = 'g';}

                else if (path[0] == 1 && path[1] == 0 && path[2] == 0 && path[3] == 1){map[x][y] = 'h';}
                else if (path[0] == 0 && path[1] == 1 && path[2] == 0 && path[3] == 1){map[x][y] = 'i';}
                else if (path[0] == 0 && path[1] == 1 && path[2] == 1 && path[3] == 0){map[x][y] = 'j';}
                else if (path[0] == 1 && path[1] == 0 && path[2] == 1 && path[3] == 0){map[x][y] = 'k';}

                else if (path[0] == 1 && path[1] == 1 && path[2] == 0 && path[3] == 1){map[x][y] = 'b';}
                else if (path[0] == 1 && path[1] == 0 && path[2] == 1 && path[3] == 1){map[x][y] = 'c';}
                else if (path[0] == 1 && path[1] == 1 && path[2] == 1 && path[3] == 0){map[x][y] = 'd';}
                else if (path[0] == 0 && path[1] == 1 && path[2] == 1 && path[3] == 1){map[x][y] = 'e';}

                else if (path[0] == 1 && path[1] == 1 && path[2] == 1 && path[3] == 1){map[x][y] = 'a';}
                else {map[x][y] = '/';}

                // map[x][y] = path[0] + path[1] + path[2] + path[3] + '0';
            }
        }
}
