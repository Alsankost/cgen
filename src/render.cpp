#include "./includes/render.h"
#include <GL/glut.h>

static int WIDTH_WORLD_ITEM = 10;
static int HEIGTH_WORLD_ITEM = 10;
/*
WorldItem types:
 0 - empty;
 1 - bot;
 2 - compl;
 3 - stone;
*/
void drawBot(int x, int y, long pp) {
	/*Properties:
	 0bit - is predator;
	 1bit - is chlorophyll;
	 2bit - is mineral;
	 3bit - is toxic;
	*/
	Bot* bot = (Bot*) pp;

	if (getProp(bot, 1)) glColor3f(0, 1, 0);
	if (getProp(bot, 2)) glColor3f(0, 0, 1);
	if (getProp(bot, 0)) glColor3f(1, 0, 0);

	glBegin(GL_QUADS);
		glVertex3f(x + WIDTH_WORLD_ITEM / 2, y, 0);
		glVertex3f(x + WIDTH_WORLD_ITEM, y + HEIGTH_WORLD_ITEM / 2, 0);
		glVertex3f(x + WIDTH_WORLD_ITEM / 2, y + HEIGTH_WORLD_ITEM, 0);
		glVertex3f(x, y + HEIGTH_WORLD_ITEM / 2, 0);
	glEnd();
}

void drawCompl(int x, int y) {
	glBegin(GL_QUADS);
		glVertex3f(x + WIDTH_WORLD_ITEM / 2, y, 0);
		glVertex3f(x + WIDTH_WORLD_ITEM, y + HEIGTH_WORLD_ITEM / 2, 0);
		glVertex3f(x + WIDTH_WORLD_ITEM / 2, y + HEIGTH_WORLD_ITEM, 0);
		glVertex3f(x, y + HEIGTH_WORLD_ITEM / 2, 0);
	glEnd();
}

void drawStone(int x, int y) {
	glBegin(GL_QUADS);
		glVertex3f(x + WIDTH_WORLD_ITEM, y, 0);
		glVertex3f(x + WIDTH_WORLD_ITEM, y + HEIGTH_WORLD_ITEM, 0);
		glVertex3f(x, y + HEIGTH_WORLD_ITEM, 0);
		glVertex3f(x, y, 0);
	glEnd();
}

void drawWorldItem(int x, int y, WorldItem item) {
	switch (item.type) {
		case 1:
			drawBot(x, y, item.proxyPointer);
			break;
		case 2:
			drawCompl(x, y);
			break;
		case 3:
			drawStone(x, y);
			break;
	}
}

void drawWorld(World* world) {
	for (int x = 0; x < world->getWidth(); x++) {
		for (int y = 0; y < world->getWidth(); y++) {
			drawWorldItem(x, y, world->get(x, y));
		}
	}
}