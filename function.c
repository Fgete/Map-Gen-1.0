const int MAP_SIZE = 21;
const int ITERATION = 10;

// PROTOTYPE
void initMap(char[MAP_SIZE][MAP_SIZE]);
void mapToX(char[MAP_SIZE][MAP_SIZE]);
void printMap_Raw(char[MAP_SIZE][MAP_SIZE]);
void printMap_Translated(char[MAP_SIZE][MAP_SIZE]);

void GenerateRooms_Raw(char[MAP_SIZE][MAP_SIZE]);
void RoomExpend(char, int, int, char[MAP_SIZE][MAP_SIZE], int);
void Expend_Up(int, int, char[MAP_SIZE][MAP_SIZE], int);
void Expend_Down(int, int, char[MAP_SIZE][MAP_SIZE], int);
void Expend_Left(int, int, char[MAP_SIZE][MAP_SIZE], int);
void Expend_Right(int, int, char[MAP_SIZE][MAP_SIZE], int);
void TypeModif(char*, int, int, char[MAP_SIZE][MAP_SIZE]);
void GeneratePath(char[MAP_SIZE][MAP_SIZE]);

char Translate(char);

// INIT MAP
void initMap(char map[MAP_SIZE][MAP_SIZE]){
    for (int x = 0; x < MAP_SIZE; x++)
        for (int y = 0; y < MAP_SIZE; y++)
            map[x][y] = '.';
}

// MAP TO X
void mapToX(char map[MAP_SIZE][MAP_SIZE]){
    for (int x = 0; x < MAP_SIZE; x++)
        for (int y = 0; y < MAP_SIZE; y++)
            if (map[x][y] != '.')
                map[x][y] = 'x';
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

// CREATE ROOMS WITHOUT PATH
void GenerateRooms_Raw(char map[MAP_SIZE][MAP_SIZE]){
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

// RECURSIVE METHOD TO CREATE ROOMS
void RoomExpend(char typeRoom, int x, int y, char map[MAP_SIZE][MAP_SIZE], int iter){
    // printf("%c", typeRoom);
    // typeRoom modification
    TypeModif(&typeRoom, x, y, map);
    map[x][y] = typeRoom;
    // printf("%c ", typeRoom);

    iter--;
    if (iter > 0)
        switch(typeRoom){
            case 'a':
                Expend_Up(x, y, map, iter);
                Expend_Down(x, y, map, iter);
                Expend_Left(x, y, map, iter);
                Expend_Right(x, y, map, iter);
            break;
            case 'b':
                Expend_Up(x, y, map, iter);
                Expend_Down(x, y, map, iter);
                Expend_Right(x, y, map, iter);
            break;
            case 'c':
                Expend_Up(x, y, map, iter);
                Expend_Left(x, y, map, iter);
                Expend_Right(x, y, map, iter);
            break;
            case 'd':
                Expend_Up(x, y, map, iter);
                Expend_Down(x, y, map, iter);
                Expend_Left(x, y, map, iter);
            break;
            case 'e':
                Expend_Down(x, y, map, iter);
                Expend_Left(x, y, map, iter);
                Expend_Right(x, y, map, iter);
            break;
            case 'f':
                Expend_Up(x, y, map, iter);
                Expend_Down(x, y, map, iter);
            break;
            case 'g':
                Expend_Left(x, y, map, iter);
                Expend_Right(x, y, map, iter);
            break;
            case 'h':
                Expend_Up(x, y, map, iter);
                Expend_Right(x, y, map, iter);
            break;
            case 'i':
                Expend_Down(x, y, map, iter);
                Expend_Right(x, y, map, iter);
            break;
            case 'j':
                Expend_Down(x, y, map, iter);
                Expend_Left(x, y, map, iter);
            break;
            case 'k':
                Expend_Up(x, y, map, iter);
                Expend_Left(x, y, map, iter);
            break;
            case 'l':
                Expend_Up(x, y, map, iter);
            break;
            case 'm':
                Expend_Right(x, y, map, iter);
            break;
            case 'n':
                Expend_Down(x, y, map, iter);
            break;
            case 'o':
                Expend_Left(x, y, map, iter);
        }
}

void TypeRoomToPath(int path[4], char t){
    // Transform typeRoom to path
    switch(t){
        case 'a': path[0]=1; path[1]=1; path[2]=1; path[3]=1; break;
        case 'b': path[0]=1; path[1]=1; path[2]=0; path[3]=1; break;
        case 'c': path[0]=1; path[1]=0; path[2]=1; path[3]=1; break;
        case 'd': path[0]=1; path[1]=1; path[2]=1; path[3]=0; break;
        case 'e': path[0]=0; path[1]=1; path[2]=1; path[3]=1; break;
        case 'f': path[0]=1; path[1]=1; path[2]=0; path[3]=0; break;
        case 'g': path[0]=0; path[1]=0; path[2]=1; path[3]=1; break;
        case 'h': path[0]=1; path[1]=0; path[2]=0; path[3]=1; break;
        case 'i': path[0]=0; path[1]=1; path[2]=0; path[3]=1; break;
        case 'j': path[0]=0; path[1]=1; path[2]=1; path[3]=0; break;
        case 'k': path[0]=1; path[1]=0; path[2]=1; path[3]=0; break;
        case 'l': path[0]=1; path[1]=0; path[2]=0; path[3]=0; break;
        case 'm': path[0]=0; path[1]=0; path[2]=0; path[3]=1; break;
        case 'n': path[0]=0; path[1]=1; path[2]=0; path[3]=0; break;
        case 'o': path[0]=0; path[1]=0; path[2]=1; path[3]=0; break;
        default : path[0]=1; path[1]=1; path[2]=1; path[3]=1; break;
    }
}

void TypeModif(char *t, int x, int y, char map[MAP_SIZE][MAP_SIZE]){
    int path[4], pathUp[4], pathDown[4], pathLeft[4], pathRight[4];
    TypeRoomToPath(path, *t);
    TypeRoomToPath(pathUp, map[x-1][y]);
    TypeRoomToPath(pathDown, map[x+1][y]);
    TypeRoomToPath(pathLeft, map[x][y-1]);
    TypeRoomToPath(pathRight, map[x][y+1]);
    int pathAround[4] = {pathUp[1],pathDown[0],pathLeft[3],pathRight[2]};

    printf("%d%d%d%d ", path[0], path[1], path[2], path[3]);
    // Modify path
    if (path[0] == 1) // Path Up
        if (path[0] != pathAround[0])
            path[0] = 0;
    if (path[1] == 1) // Path Down
        if (path[1] != pathAround[1])
            path[1] = 0;
    if (path[2] == 1) // Path Left
        if (path[2] != pathAround[2])
            path[2] = 0;
    if (path[3] == 1) // Path Right
        if (path[3] != pathAround[3])
            path[3] = 0;

    printf("%d%d%d%d ", pathUp[1], pathDown[0], pathLeft[3], pathRight[2]);
    printf("%d%d%d%d \n", path[0], path[1], path[2], path[3]);

    // Transform path to modify typeRoom
    if (path[0] == 1 && path[1] == 0 && path[2] == 0 && path[3] == 0){*t = 'l';}
    else if (path[0] == 0 && path[1] == 1 && path[2] == 0 && path[3] == 0){*t = 'n';}
    else if (path[0] == 0 && path[1] == 0 && path[2] == 1 && path[3] == 0){*t = 'o';}
    else if (path[0] == 0 && path[1] == 0 && path[2] == 0 && path[3] == 1){*t = 'm';}

    else if (path[0] == 1 && path[1] == 1 && path[2] == 0 && path[3] == 0){*t = 'f';}
    else if (path[0] == 0 && path[1] == 0 && path[2] == 1 && path[3] == 1){*t = 'g';}

    else if (path[0] == 1 && path[1] == 0 && path[2] == 0 && path[3] == 1){*t = 'h';}
    else if (path[0] == 0 && path[1] == 1 && path[2] == 0 && path[3] == 1){*t = 'i';}
    else if (path[0] == 0 && path[1] == 1 && path[2] == 1 && path[3] == 0){*t = 'j';}
    else if (path[0] == 1 && path[1] == 0 && path[2] == 1 && path[3] == 0){*t = 'k';}

    else if (path[0] == 1 && path[1] == 1 && path[2] == 0 && path[3] == 1){*t = 'b';}
    else if (path[0] == 1 && path[1] == 0 && path[2] == 1 && path[3] == 1){*t = 'c';}
    else if (path[0] == 1 && path[1] == 1 && path[2] == 1 && path[3] == 0){*t = 'd';}
    else if (path[0] == 0 && path[1] == 1 && path[2] == 1 && path[3] == 1){*t = 'e';}

    else if (path[0] == 1 && path[1] == 1 && path[2] == 1 && path[3] == 1){*t = 'a';}
    else {*t = '/';}
}

// UP
void Expend_Up(int x, int y, char map[MAP_SIZE][MAP_SIZE], int iter){
    char childs[9] = {'a','b','d','e','f','i','j','n'};
    if (map[x-1][y] == '.'){
        map[x-1][y] = childs[rand() % 8];
        RoomExpend(map[x-1][y], x-1, y, map, iter);
    }
}

// DOWN
void Expend_Down(int x, int y, char map[MAP_SIZE][MAP_SIZE], int iter){
    char childs[9] = {'a','b','c','d','f','h','k','l'};
    if (map[x+1][y] == '.'){
        map[x+1][y] = childs[rand() % 8];
        RoomExpend(map[x+1][y], x+1, y, map, iter);
    }
}

// LEFT
void Expend_Left(int x, int y, char map[MAP_SIZE][MAP_SIZE], int iter){
    char childs[9] = {'a','b','c','e','g','h','i','m'};
    if (map[x][y-1] == '.'){
        map[x][y-1] = childs[rand() % 8];
        RoomExpend(map[x][y-1], x, y-1, map, iter);
    }
}

// RIGHT
void Expend_Right(int x, int y, char map[MAP_SIZE][MAP_SIZE], int iter){
    char childs[9] = {'a','c','d','e','g','j','k','o'};
    if (map[x][y+1] == '.'){
        map[x][y+1] = childs[rand() % 8];
        RoomExpend(map[x][y+1], x, y+1, map, iter);
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
