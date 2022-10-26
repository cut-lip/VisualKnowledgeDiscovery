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
	 
	// Figure 6.1 - Upper PC
	// Draw main coordinate frame
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINE_STRIP);
	glVertex2f(560, 150);
	glVertex2f(20, 150);
	glVertex2f(20, 380);
	glVertex2f(560, 380);
	glEnd();
	
	// Draw inner lines
	for (int i = 150 + ((380 - 150) / 4); i < 350; i += ((380 - 150) / 4))
	{
		glBegin(GL_LINES);
		glVertex2i(20, i);
		glVertex2i(560, i);
		glEnd();
	}

	// Draw 2-D graphs
	glColor3f(0.0, 1.0, 0.0);
	glLineWidth(4.0);
	glBegin(GL_LINE_STRIP);
		glVertex2i(40, 180);
		glVertex2i(111,180);
		glVertex2i(182,180);
		glVertex2i(253, 210);
		glVertex2i(324, 210);
		glVertex2i(395, 210);
		glVertex2i(466, 210);
		glVertex2i(537, 180);
	glEnd();

	glColor3f(1.0, 0.0, 0.0);
	glLineWidth(4.0);
	glBegin(GL_LINE_STRIP);
	glVertex2i(40, 230);
	glVertex2i(111, 180);
	glVertex2i(182, 230);
	glVertex2i(253, 210);
	glVertex2i(321, 310);
	glVertex2i(395, 210);
	glVertex2i(466, 310);
	glVertex2i(537, 180);
	glEnd();

	glColor3f(0.0, 0.0, 1.0);
	glLineWidth(4.0);
	glBegin(GL_LINE_STRIP);
	glVertex2i(40, 310);
	glVertex2i(111, 180);
	glVertex2i(182, 310);
	glVertex2i(253, 210);
	glVertex2i(321, 350);
	glVertex2i(395, 210);
	glVertex2i(466, 350);
	glVertex2i(537, 180);
	glEnd();
	
	// Figure 6.1 - Lower CPC
	glColor3f(0.0, 0.0, 0.0);
	glLineWidth(1.0);
	GLprac::drawArrow(GLintPoint(20, 20), GLintPoint(20, 100));
	GLprac::drawArrow(GLintPoint(20, 20), GLintPoint(580, 20));

	glColor3f(0.0, 1.0, 0.0);
	drawArrow(GLintPoint(130, 30), GLintPoint(130, 90));
	drawArrow(GLintPoint(130, 90), GLintPoint(200, 90));
	drawArrow(GLintPoint(200, 90), GLintPoint(200, 30));
	drawArrow(GLintPoint(200, 30), GLintPoint(130, 30));

	glColor3f(1.0, 0.0, 0.0);
	drawArrow(GLintPoint(230, 30), GLintPoint(230, 90));
	drawArrow(GLintPoint(230, 90), GLintPoint(300, 90));
	drawArrow(GLintPoint(300, 90), GLintPoint(300, 30));
	drawArrow(GLintPoint(300, 30), GLintPoint(230, 30));

	glColor3f(0.0, 0.0, 1.0);
	drawArrow(GLintPoint(330, 30), GLintPoint(330, 90));
	drawArrow(GLintPoint(330, 90), GLintPoint(400, 90));
	drawArrow(GLintPoint(400, 90), GLintPoint(400, 30));
	drawArrow(GLintPoint(400, 30), GLintPoint(330, 30));

	/*
	glPointSize(4.0);
	for (int i = 42; i < 580; i+= (3*(560/18)))
	{
		drawPoint(i, 40);
	}
	*/

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