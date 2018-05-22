#include <GL/glut.h>
#include <stdio.h>
#include <iostream>

#include "./includes/render.h"
#include "./includes/testVM.h"

using namespace std;

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w, 0, h);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

World* world;
VM* vm;

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	drawWorld(world);
	glutSwapBuffers();
}

void tim(int val)
{
	glutPostRedisplay();
	vm->executeWorld(world);
	glutTimerFunc(20, tim, 0);
}

int main(int argc, char * argv[])
{
	cout << "# Start" << '\n';

	world = new World(50, 50);
	cout << "# World - OK" << '\n';

	vm = createTestVM();
	cout << "# VM - OK" << '\n';

	world->set(25, 25, 1, (long) createFirsBot(vm));
	cout << "# New bot - OK" << '\n';

	Bot* bot = vm->createNewBot();
	setProp(bot, 0, true);
	setProp(bot, 1, true);
	setProp(bot, 4, true);
	cout << bot->prop << '\n';
	cout << getProp(bot, 4) << " " << getProp(bot, 3) << '\n';

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	cout << "# GLUT init - OK" << '\n';

	glutInitWindowSize(800, 600);
	glutCreateWindow("C-Gen");
	cout << "# GLUT window - OK" << '\n';

	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	cout << "# Register function - OK" << '\n';

	glutTimerFunc(20, tim, 0);
	cout << "# Timer - OK" << '\n';

	glutMainLoop();

	return 0;
}

