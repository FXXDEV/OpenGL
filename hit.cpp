#include<GL/glut.h>
#include<stdlib.h>
#include<math.h>
#include<stdio.h>


#define windowH 768
#define windowW 1366
#define VK_ESCAPE 27



float PI = atanf(1.0f) * 4.0f;

struct Vertices {
	int x;
	int y;
};


GLfloat ang, circle;
GLfloat circ_pnt = 400;

struct Vertices v1, v2 = {v2.x=100,v2.y=200};



float a_value;
float b_value;
float c_value;
bool touch = false;


void display(void);
void screen(GLsizei w, GLsizei h);
void keyboard(unsigned char key, int x, int y);
void mouseMovement(int x, int y);

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(windowW, windowH);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Circulo - Eventos");
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glutReshapeFunc(screen);
	glutDisplayFunc(display);
	glutKeyboardFunc(&keyboard);
	glutPassiveMotionFunc(mouseMovement);
	glutMainLoop();

	return(0);
}



void mouseMovement(int x, int y) {
	v1.x = x - (windowW / 2);
	v1.y = y - (windowH / 2);

	float a = v1.x - v2.x;
	float b = v1.y - v2.y;
	float c = sqrt((a*a) + (b * b));

	if (c < (circle * 2)) {
		touch = true;
	}
	else {
		touch = false;
	}
}

void draw() {

	glLoadIdentity();
	glPushMatrix();
	glTranslatef((windowW) / 2, (windowH) / 2, 0);
	glScalef(1, -1, 1);
	glPushMatrix();
	glTranslatef(v2.x, v2.y, 0);

	glColor3f(1, 1, 1);
	glBegin(GL_POLYGON);
	for (int i = 0; i < circ_pnt; i++) {
		ang = (2 * PI * i) / circ_pnt;
		glVertex2f(cos(ang) * circle, sin(ang) * circle);
	}

	glEnd();
	glPopMatrix();
	glPushMatrix();
	glTranslatef(v1.x, v1.y, 0);
	glColor3f(1, 1, 0.2f);
	circle = 50;
	glBegin(GL_POLYGON);
	for (int i = 0; i < circ_pnt; i++) {
		ang = (2 * PI * i) / circ_pnt;
		glVertex2f(cos(ang) * circle, sin(ang) * circle);
	}
	glEnd();

	glPopMatrix();

	if (touch == true) {
		glBegin(GL_QUADS);
		glVertex2f(800, 450);
		glVertex2f(800, -450);
		glVertex2f(-800, -450);
		glVertex2f(-800, 450);
		glEnd();
	}

	glutPostRedisplay();
	glPopMatrix();
}

void screen(GLsizei w, GLsizei h) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluOrtho2D(0, windowW, 0, windowH);
	glMatrixMode(GL_MODELVIEW);

}

void display() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glViewport(0, 0, windowW, windowH);
	draw();

	glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
	if (key == 'q') {
		glutDestroyWindow(0);
		exit(0);
	}

}