#ifndef DEFINE_H_INCLUDED
#define DEFINE_H_INCLUDED

void initMap(char[MAP_SIZE][MAP_SIZE]);
void printMap_Raw(char[MAP_SIZE][MAP_SIZE]);
void printMap_Translated(char[MAP_SIZE][MAP_SIZE]);

void GenerateRooms(char[MAP_SIZE][MAP_SIZE]);
void GeneratePath(char[MAP_SIZE][MAP_SIZE]);

char Translate(char);

#endif // DEFINE_H_INCLUDED
