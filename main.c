#include <stdio.h>
#include <stdlib.h>

#include <locale.h>
#include <time.h>

#include "function.c"
#include "define.h"

/*

        ### 2D MAP GENERATOR ###

This program will generate a game map in 2D

--> map size and some

RETURN map[x][y] = {type of room}

*/

typedef struct room{
    int number;
    int type;
    int x;
    int y;
}room;
// room.number  (basic)
// room->number (pointer)

// room myRoom={0,1,5,68};

int main()
{
    char map[MAP_SIZE][MAP_SIZE];
    char answer;



    while (answer != 'q' & answer != 'Q'){
        // Clear screen
        system("cls");

        // Set map to NULL ('.')
        initMap(map);

        // Set origin (center)
        map[MAP_SIZE / 2][MAP_SIZE / 2] = 'x';

        // Create rooms
        GenerateRooms(map);

        // Generate path
        GeneratePath(map);

        // Print
        // printMap_Raw(map);
        printMap_Translated(map);

        // Get action
        printf("Reload [ENTER] | Quit [Q]");
        answer = getchar();
    }
    return 0;
}
