#include "./includes/world.h";

static int DEFAULT_WORLD_WIDTH  = 100;
static int DEFAULT_WORLD_HEIGHT = 100;

SimplePoint World::pointFromXYD(int x, int y, int dir) {
	int nx = x, ny = y;
	switch (dir) {
		case 0:
			nx += 1;
			break;
		case 1:
			nx += 1;
			ny -= 1;
			break;
		case 2:
			ny -= 1;
			break;
		case 3:
			nx -= 1;
			ny -= 1;
			break;
		case 4:
			nx -= 1;
			break;
		case 5:
			nx -= 1;
			ny += 1;
			break;
		case 6:
			ny += 1;
			break;
		case 7:
			nx += 1;
			ny += 1;
	}
	if (nx < 0) nx = this->getWidth() - 1;
	if (nx >= this->getWidth()) nx = 0;
	SimplePoint sp = {nx, ny};
	return sp;
}

/*
WorldItem types:
 0 - empty;
 1 - bot;
 2 - compl;
 3 - stone;
*/
World::World(int w, int h) {
	this->width  = (w < 10)?DEFAULT_WORLD_WIDTH:w;
	this->height = (h < 10)?DEFAULT_WORLD_HEIGHT:h;

	this->map = new WorldItem*[this->width];
	for (int x = 0; x < this->width; x++) {
		this->map[x] = new WorldItem[this->height];
	}
}

int World::getWidth() {
	return this->width;
}

int World::getHeight() {
	return this->height;
}

WorldItem World::get(int x, int y) {
	if (x < 0 || x >= this->width || y < 0 || y >= this->height) return WorldItem{};
	return this->map[x][y];
}

void World::set(int x, int y, int type, long pp) {
	if (x < 0 || x >= this->width || y < 0 || y >= this->height || type < 1 || type > 3) return;
	map[x][y].type = type;
	map[x][y].proxyPointer = pp;
}

void World::clear(int x, int y) {
	if (x < 0 || x >= this->width || y < 0 || y >= this->height) return;
	map[x][y].type = 0;
}

bool World::isEmpty(int x, int y) {
	if (x < 0 || x >= this->width || y < 0 || y >= this->height) return false;
	return this->get(x, y).type == 0;
}

void World::setToPoint(int x, int y, int type, long pp) {
	if (y < 0 || y >= this->height) return;
	if (x < 0) x = this->getWidth() - 1;
	if (x >= this->getWidth()) x = 0;
	map[x][y].type = type;
	map[x][y].proxyPointer = pp;
}

void World::setToDir(int x, int y, int dir, int type, long pp) {
	SimplePoint sp = pointFromXYD(x, y, dir);
	this->setToPoint(sp.x, sp.y, type, pp);
}

void World::moveToPoint(int x, int y, int nx, int ny) {
	if (nx < 0) nx = this->getWidth() - 1;
	if (nx >= this->getWidth()) nx = 0;
	if (this->isEmpty(nx, ny)) {
		WorldItem wi = this->get(x, y);
		this->set(nx, ny, wi.type, wi.proxyPointer);
	}
}

void World::moveToDir(int x, int y, int dir) {
	if (x < 0 || x >= this->width || y < 0 || y >= this->height) return;
	WorldItem tmp = this->get(x, y);
	this->setToDir(x, y, dir, tmp.type, tmp.proxyPointer);
}

bool World::isEmptyToDir(int x, int y, int dir) {
	SimplePoint sp = pointFromXYD(x, y, dir);
	return isEmpty(sp.x, sp.y);
}