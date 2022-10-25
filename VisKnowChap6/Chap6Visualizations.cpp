#include <iostream>
#include <vector>
#include <GL/glut.h>
#include "OpenGLPrac.h"

using namespace GLprac;

const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 400;

void init()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, SCREEN_WIDTH, 0.0, SCREEN_HEIGHT);
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);
	//glLineWidth()
	drawArrow(GLintPoint(20, 20), GLintPoint(20, 100));
	drawArrow(GLintPoint(20, 20), GLintPoint(580, 20));

	glColor3f(0.0, 1.0, 0.0);
	glPointSize(4.0);
	for (int i = 42; i < 580; i+= (3*(560/18)))
	{
		drawPoint(i, 40);
	}

	glFlush();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutInitWindowPosition(100, 150);
	glutCreateWindow("Chapter 7 Visualizations");
	glutDisplayFunc(display);
	init();
	glutMainLoop();

	return 0;
}