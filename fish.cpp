//#include<GL/glew.h>
#include<GL/glut.h>
#include<math.h>
#include<stdio.h>
#include<stdlib.h>

#define windowH 768
#define windowW 1366

//PI
float PI = atanf(1.0f)*4.0f;

//tamanhos
float fScale = 5;
float sScale = 1;

//direcao
float dx = 0.0;
float dy = 0.0;

//variaveis de incrementação
float dirX = 1;
float dirY = 0.25;



//Cores 
float r = 175;
float g = 171;
float b = 167;

GLfloat circ_pnt = 500;
GLfloat ang, raioX, raioY;

void display(void);
void screen(GLsizei w, GLsizei h);
void keyboard(unsigned char key, int x, int y);
void anim(int value);


int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(windowW, windowH);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Fish");
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	glutReshapeFunc(screen);
	glutDisplayFunc(display);
	glutKeyboardFunc(&keyboard);
	glutTimerFunc(40, anim, 1);
	glutMainLoop();

	return(0);
}

void anim(int value) {

	if ((dx) > (80) || (dx) < (-80)) {
		dirX = -dirX;
	}
	if ((dx) > (20) || (dy) < (-20)) {
		dirY = -dirY;
	}
	dx += dirX;
	dy += dirY;

	glutPostRedisplay();
	glutTimerFunc(30, anim, 1);
}




void peixe() {
	glPushMatrix();
	if (dirX == 1) {
		glScaled(sScale, sScale, sScale);
	}

	if (dirX == -1) {
		glScaled(-(sScale), sScale, sScale);
	}

	
	//cima
	glBegin(GL_POLYGON);
	glColor3ub(r, g, b);
	glVertex2f(5, 5);
	glVertex2f(10, 7.5);
	glVertex2f(15, 8);
	glVertex2f(14, 11);
	glVertex2f(9, 9);
	glEnd();

	
	//cauda
	glBegin(GL_POLYGON);
	glVertex2f(0, 0);
	glColor3ub(r, g, b);
	glVertex2f(-7, 7);
	glVertex2f(-5, 0);
	glVertex2f(-7, -7);
	glEnd();
	
	//corpo
	glBegin(GL_POLYGON);
	glColor3ub(r, g, b);
	glVertex2f(0, 0);
	glVertex2f(10, 5);
	glVertex2f(10, 7.5);
	glVertex2f(15, 8);
	glVertex2f(25, 3);
	glVertex2f(28, 0);
	glVertex2f(20, -6);
	glVertex2f(15, -8);
	glVertex2f(10, -7.5);
	glVertex2f(5, -5);
	glEnd();


	//olhos
	raioX = 1.4f;
	raioY = 3;
	glPushMatrix();
	glTranslatef(20, 0, 0);
	glBegin(GL_POLYGON);
	glColor3ub(255, 255, 255);
	for (int i = 0;i < 100; i++) {
		ang = (2 * PI*i) / 100;
		glVertex2f(cos(ang)*raioY, sin(ang)*raioY);
	}
	glEnd();
	glBegin(GL_POLYGON);
	glColor3ub(0, 0, 0);
	for (int i = 0;i < 100; i++) {
		ang = (2 * PI*i) / 100;
		glVertex2f(cos(ang)*raioX, sin(ang)*raioX);
	}
	glEnd();
	glPopMatrix();
	glPopMatrix();
}

void aquario() {
	raioX = 120;
	raioY = 30;
	circ_pnt = 500;

	//arquario
	glLineWidth(2.0);
	glColor3ub(100, 100, 100);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < circ_pnt; i++) {
		if (i <= 250) {
			raioY = 50;
		}
		else if (i > 250) {
			raioY =70;
		}

		ang = (2 * PI * i) / circ_pnt;
		glVertex2d(cos(ang) * raioX, sin(ang) * raioY);
	}
	glEnd();

	//cor vidro
	glColor4ub(255, 255, 255, 110);
	glBegin(GL_POLYGON);
	for (int i = 0; i < circ_pnt; i++) {
		if (i <= 250) {
			raioY = 50;
		}
		else if (i > 250) {
			raioY = 70;
		}

		ang = (2 * PI * i) / circ_pnt;
		glVertex2d(cos(ang) * raioX, sin(ang) * raioY);
	}
	glEnd();


	//mesa
	glPushMatrix();
	glTranslatef(0, -70, 0);
	glBegin(GL_QUADS);
	glColor3ub(91, 52,52);
	glVertex2f(-200, 0);
	glVertex2f(200, 0);
	glVertex2f(200, -40);
	glVertex2f(-200, -40);
	glEnd();
	glPopMatrix();
}



void elementos() {

	glLoadIdentity();
	glPushMatrix();
	glTranslatef((windowW) / 2, (windowH) / 2, 0);
	glScalef(fScale, fScale, fScale);

	//Movimento
	glPushMatrix();
	glTranslatef(dx, dy, 0);
	peixe();
	glPopMatrix();

	//Posição fixa
	glPushMatrix();
	glScalef(-0.8, 1, 1);
	glRotatef(8, 0, 0, 1);
	glTranslatef(2, 0, 0);
	glPopMatrix();
	aquario();
	glPopMatrix();
}

void display() {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClearColor(0.69f, 0.75f, 0.8f,0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glViewport(0, 0, windowW, windowH);
	elementos();

	glFlush();
}



void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'x':
		dirX = -dirX;
		break;

	case '1':
		r = 255;
		g = 0;
		b = 0;

		break;
	case '2':
		r = 0;
		g = 255;
		b = 0;

		break;
	case '3':
		r = 0;
		g = 0;
		b = 255;

		break;
	case '4':
		r = 244;
		g = 146;
		b = 66;

		break;
	}


}
void screen(GLsizei w, GLsizei h) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, windowW, 0, windowH);
	glMatrixMode(GL_MODELVIEW);
}
