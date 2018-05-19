/*
WorldItem types:
 0 - empty;
 1 - bot;
 2 - compl;
 3 - stone;
*/

struct SimplePoint {
	int x, y;
};

SimplePoint pointFromXYD(int x, int y, int dir);

struct WorldItem {
	int type = 0;
	long proxyPointer = 0;
};

class World {
	private:
		WorldItem** map;
		int width, height;

	public:
		World(int w, int h);

		int getWidth();
		int getHeigth();

		WorldItem get(int x, int y);
		void set(int x, int y, int type, long pp);
		void clear(int x, int y);

		bool isEmpty(int x, int y);

		void setToPoint(int x, int y, int type, long pp);
		void setToDir(int x, int y, int dir, int type, long pp);

		void moveToPoint(int x, int y, int nx, int ny);
		void moveToDir(int x, int y, int dir);

		bool isEmptyToDir(int x, int y, int dir);
};