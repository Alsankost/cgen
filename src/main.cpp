#include <GL/glut.h>
#include <stdio.h>

#include "./includes/render.h"
#include "./includes/testVM.h"

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
	world = new World(50, 50);
	vm = createTestVM();

	world->set(25, 25, 1, (long) vm->createNewBot());

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	glutInitWindowSize(800, 600);
	glutCreateWindow("C-Gen");

	glutReshapeFunc(reshape);
	glutDisplayFunc(display);

	glutTimerFunc(20, tim, 0);

	glutMainLoop();	

	return 0;
}

