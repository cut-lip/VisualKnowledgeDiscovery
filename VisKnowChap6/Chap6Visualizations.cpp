#include <iostream>
#include <GL/glut.h>

const int SCREEN_WIDTH = 680;
const int SCREEN_HEIGHT = 420;

void init()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, SCREEN_WIDTH, 0.0, SCREEN_HEIGHT);
}

void display() {

}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutCreateWindow("Chapter 7 Visualizations");
	glutInitWindowPosition(0,0);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutDisplayFunc(display);
	init();
	glutMainLoop();

	return 0;
}