#include <iostream>
#include <windows.h>
#include <gl/GL.h>
#include <gl/glut.h>
using namespace std;

void myInit(void);
void display(void);
void draw_lines(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2);
void draw_lines_bressenham(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2);

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 150);

    glutCreateWindow("Primitive Display");
    glutDisplayFunc(display);

    myInit();
    glutMainLoop();

    return 0;
}

void myInit(void) {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glColor3f(1.0, 0.0, 0.0);
    //  glPointSize(2.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, 1260, 0.0, 1260);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0f, 1.0f, 0.0f); // Green color
    draw_lines(100, 100, 200, 200);

    glFlush();
}

void draw_lines(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2) {
    GLdouble dx = x2 - x1, dy = y2 - y1, steps;
    float xinc, yinc, x = x1, y = y1;
    steps = (abs(dx) > abs(dy)) ? abs(dx) : abs(dy);
    xinc = dx / static_cast<float>(steps);
    yinc = dy / static_cast<float>(steps);

    glBegin(GL_POINTS);
    glVertex2d(round(x), round(y));

    for (int k = 0; k < steps; k++) {
        x += xinc;
        y += yinc;
        glVertex2d(round(x), round(y));
    }
    glEnd();
    glFlush();
}

void draw_lines_bressenham(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    int x = x1;
    int y = y1;
    int xInc = (dx > 0) ? 1 : -1;
    int yInc = (dy > 0) ? 1 : -1;
    dx = abs(dx);
    dy = abs(dy);

    int twoDy = 2 * dy;
    int twoDyDx = 2 * (dy - dx);
    int p = 2 * dy - dx;

    glBegin(GL_POINTS);
    glVertex2d(x, y);

    if (dx > dy) {  
        while (x != x2) {
            x += xInc;
            if (p < 0) {
                p += twoDy;
            }
            else {
                y += yInc;
                p += twoDyDx;
            }
            glVertex2d(x, y);
        }
    }
    else {
        twoDy = 2 * dx;
        twoDyDx = 2 * (dx - dy);
        p = 2 * dx - dy;
        while (y != y2) {
            y += yInc;
            if (p < 0) {
                p += twoDy;
            }
            else {
                x += xInc;
                p += twoDyDx;
            }
            glVertex2d(x, y);
        }
    }

    glEnd();
    glFlush();
}
