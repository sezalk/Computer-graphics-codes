#include <stdio.h>
#include <iostream>
#include <GL/glut.h>
using namespace std;

int pntX, pntY, a, b;

void myInit(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0f, 0.0f, 0.0f);
	glPointSize(4.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-300.0, 300.0, -200.0, 200);
}


void midPointEllipseAlgo()
{
	int x = 0;
	int y = b;
	float p1 = b * b - (a * a) * b + (a * a) * (0.25);
	float dx = 2 * (b * b) * x;
	float dy = 2 * (a * a) * y;

	while (dx < dy)
	{
		glBegin(GL_POINTS);
		glVertex2i(pntX + x, pntY + y);
		glVertex2i(pntX - x, pntY + y);
		glVertex2i(pntX + x, pntY - y);
		glVertex2i(pntX - x, pntY - y);
		glEnd();

		if (p1 < 0)
		{
			x = x + 1;
			dx = 2 * (b * b) * x;
			p1 = p1 + 2 * (b * b) * x + (b * b);
		}
		else
		{
			x = x + 1;
			y = y - 1;
			dx = 2 * (b * b) * x;
			dy = 2 * (a * a) * y;
			p1 = p1 + 2 * (b * b) * x - 2 * (a * a) * y + (b * b);
		}

	}
	float p2 = (b * b) * (x + 0.5) * (x + 0.5) + (a * a) * (y - 1) * (y - 1) - (a * a) * (b * b);

	while (y > 0)
	{
		glBegin(GL_POINTS);
		glVertex2i(pntX + x, pntY + y);
		glVertex2i(pntX - x, pntY + y);
		glVertex2i(pntX + x, pntY - y);
		glVertex2i(pntX - x, pntY - y);
		glEnd();

		if (p2 > 0)
		{
			x = x;
			y = y - 1;
			dy = 2 * (a * a) * y;
			p2 = p2 - 2 * (a * a) * y + (a * a);
		}
		else
		{
			x = x + 1;
			y = y - 1;
			dy = 2 * (a * a) * y;
			dx = 2 * (b * b) * x;
			p2 = p2 + dx - dy + (a * a);
		}
		glFlush();

	}
}

void myDisplay(void) 
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);
	glPointSize(1.0);
	midPointEllipseAlgo();
	glFlush();
}

void main(int argc, char** argv)
{
	cout << "Enter the coordinates of the center:\n\n" << endl;

	cout << "X-coordinate   : "; cin >> pntX;
	cout << "\nY-coordinate : "; cin >> pntY;
	cout << "\nEnter a : "; cin >> a;
	cout << "\nEnter b : "; cin >> b;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(100, 150);
	glutCreateWindow("ellipse");
	glutDisplayFunc(myDisplay);
	myInit();
	glutMainLoop();

}
