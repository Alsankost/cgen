#include "./vm.h"
#include "./world.h"

/*
WorldItem types:
 0 - empty;
 1 - bot;
 2 - compl;
 3 - stone;
*/
void drawBot(int x, int y, long pp);
void drawCompl(int x, int y);
void drawStone(int x, int y);

void drawWorldItem(int x, int y, WorldItem item);
void drawWorld(World* world);