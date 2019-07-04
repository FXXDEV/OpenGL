/// Chicken Cross Roads
#include <stdio.h>
#include <stdlib.h> 
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <GL/glu.h>
#include<math.h>
#include <sstream>

#define windowH 700 
#define windowW 1000 
#define PI 3.1416
#define VK_W 0x57
#define VK_S 0x53

//Functions
void environment();
int stripes(int x);
int lineStripe(int y);
float Car(float tx, float ty);
void fullStripes();
//void keyboard();
void player1();
void anima(int valor);
void update(int valor); int interval = 200;
void display(void);
void screen(GLsizei W, GLsizei h);

//cars
float tx0 = 500, tx1 = 500,  tx2 = 500, tx3 = 500,  tx4 = 500;
float ty0 = -200,  ty1 = -100,  ty2 = 0, ty3 = 100,  ty4 = 200; 
float spd0 = -8,  spd1 = -11,  spd2 = -9, spd3 = -13, spd4 = -7;

//car color
/*int r1 =(rand() % 255),g1=(rand() % 255),b1=(rand() % 255);
int r2 =(rand() % 255),g2=(rand() % 255),b2=(rand() % 255);
int r3 =(rand() % 255),g3=(rand() % 255),b3=(rand() % 255);
int r4 =(rand() % 255),g4=(rand() % 255),b4=(rand() % 255);
int r5 =(rand() % 255),g5=(rand() % 255),b5=(rand() % 255);
*/

int r1 = 255,g1=0,b1=0;
int r2 = 0,g2=225,b2=0;
int r3 =0,g3=100,b3=255;
int r4 =10,g4=255,b4=40;
int r5 =0,g5=50,b5=50;


//Player
float p1X = -300, p1Y = -285, p1Comp = 20, p1Alt = 20;
float p2X = 300, p2Y = -285, p2Comp = 20, p2Alt = 20;
int scorep1=0;
int scorep2=0;

void keyboard(unsigned char key, int x, int y) {
	//if (p1Y > 250) Sleep(2000), exit(0);
	if (key == 'w') if (p1Y < 275) p1Y+=25;
	if (key == 's') if (p1Y > -250) p1Y -= 25;

	if (key == 'o') if (p2Y < 275) p2Y+=25;
	if (key == 'l') if (p2Y > -250) p2Y -= 25;

	if(p1Y > 250) p1Y=-285; scorep1++;
	if(p2Y > 250) p2Y=-285; scorep2++;
 	
}
std::string int2str(int x) {
	// converter inteiro para string
	std::stringstream ss;
	ss << x;
	return ss.str();
}


void drawText(float x, float y, std::string text) {
	glColor3ub(255,0,0);
	glRasterPos2f(x, y);
	glutBitmapString(GLUT_BITMAP_8_BY_13, (const unsigned char*)text.c_str());
}

//Colision
bool Colision(float Ax, float Ay, float Bx, float By, float Bcompr, float Baltu) {

	if (Ay < By) return false;
	else if (Ay > By + Baltu) return false;
	else if (Ax > Bx + Bcompr) return false;
	else if (Ax < Bx) return false;

	return true;
}
int main(int argc, char** argv) {

	glutInit(&argc, argv);
	// suporte a janelas 
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // PADRAO DE CORES 
	glutInitWindowSize(windowW, windowH); // tamanho da janela 
	glutInitWindowPosition(0, 0); // posicao que surge a janela 
	glutCreateWindow("Freeway - OpenGL"); // cria janela 

	//glutFullScreen();
	glutKeyboardFunc(&keyboard); // chama teclado 
	glutTimerFunc(250, update, 1);
	glutTimerFunc(150, anima, 1);
	glutReshapeFunc(screen); // configura a tela 
	glutDisplayFunc(display);
	glutMainLoop(); // redesenhar 	

	return(0);
}
void update(int value) {

	unsigned char key;
	int x;
	int y;
	keyboard(key,x,y);
	glutTimerFunc(interval, update, 0);

	glutPostRedisplay();
}
void anima(int valor) {

	if (Colision(tx0, ty0, p1X, p1Y, p1Comp, p1Alt) == true) p1Y = -285 ;
	if (Colision(tx1, ty1, p1X, p1Y, p1Comp, p1Alt) == true) p1Y = -285;
	if (Colision(tx2, ty2, p1X, p1Y, p1Comp, p1Alt) == true) p1Y = -285;
	if (Colision(tx3, ty3, p1X, p1Y, p1Comp, p1Alt) == true) p1Y = -285;
	if (Colision(tx4, ty4, p1X, p1Y, p1Comp, p1Alt) == true) p1Y = -285;

	if (Colision(tx0, ty0, p2X, p2Y, p2Comp, p2Alt) == true) p2Y = -285;
	if (Colision(tx1, ty1, p2X, p2Y, p2Comp, p2Alt) == true) p2Y = -285;
	if (Colision(tx2, ty2, p2X, p2Y, p2Comp, p2Alt) == true) p2Y = -285;
	if (Colision(tx3, ty3, p2X, p2Y, p2Comp, p2Alt) == true) p2Y = -285;
	if (Colision(tx4, ty4, p2X, p2Y, p2Comp, p2Alt) == true) p2Y = -285;


	


	if (tx0 < -490)	tx0 = 500.0f;
	if (tx1 < -490)	tx1 = 500.0f;
	if (tx2 < -490)	tx2 = 500.0f;
	if (tx3 < -490)	tx3 = 500.0f;
	if (tx4 < -490)	tx4 = 500.0f;
	

	tx0 += spd0;
	tx1 += spd1;
	tx2 += spd2;
	tx3 += spd3;
	tx4 += spd4;
	
	glutPostRedisplay();
	drawText(windowW / 2 , windowH , +"P1:"+ int2str(scorep1) + "  vs  " + "P2:" +int2str(scorep2));
	glutTimerFunc(15, anima, 2);
	drawText(windowW / 2 , windowH , +"P1:"+ int2str(scorep1) + "  vs  " + "P2:" +int2str(scorep2));	
}


void environment() {
	glBegin(GL_QUADS);
	glColor3ub(147, 148, 150);
	glVertex2f(-500, -250);
	glVertex2f(-500, 250);
	glVertex2f(500, 250);
	glVertex2f(500, -250);
	glEnd();
	glBegin(GL_QUADS);
	glColor3ub(173, 175, 178);
	glVertex2f(-500, 253);
	glVertex2f(-500, 297);
	glVertex2f(500, 297);
	glVertex2f(500, 253);
	glEnd();
	glBegin(GL_QUADS);
	glColor3ub(173, 175, 178);
	glVertex2f(-500, -253);
	glVertex2f(-500, -297);
	glVertex2f(500, -297);
	glVertex2f(500, -253);
	glEnd();
	fullStripes();

}
void fullStripes() {
	lineStripe(-50);
	lineStripe(-150);
	lineStripe(-250);
	lineStripe(-350);
}
int lineStripe(int y) {
	glPushMatrix();
	glTranslated(0, y, 0);

	stripes(0);
	stripes(150);
	stripes(300);
	stripes(450);
	stripes(600);
	stripes(750);
	stripes(900);
	stripes(1035);
	glPopMatrix();
	return true;
}
int stripes(int x) {

	glPushMatrix();
	glTranslated(x, 0, 0);

	glBegin(GL_QUADS);
	glColor3ub(173, 175, 178);
	glVertex2f(-550, 200);
	glVertex2f(-550, 205);
	glVertex2f(-440, 205);
	glVertex2f(-440, 200);
	glEnd();

	glPopMatrix();
	return true;
}
void player1() {

	glPushMatrix();
	
	
	glBegin(GL_QUADS);
	glColor3ub(245, 233, 66);
	glVertex2f(p1X + 15, p1Y + p1Alt + 10);
	glVertex2f(p1X + p1Comp + 5, p1Y + p1Alt + 5);
	glVertex2f(p1X + 15, p1Y + 10);
	glVertex2f(p1X + 15, p1Y + 10);
	glEnd();

	glBegin(GL_QUADS);
	glColor3ub(255, 0, 0);
	glVertex2f(p1X + 15, p1Y + p1Alt + 10);
	glVertex2f(p1X - p1Comp + 30, p1Y + p1Alt + 5);
	glVertex2f(p1X + 15, p1Y + 10);
	glVertex2f(p1X + 15, p1Y + 10);
	glEnd();

	glBegin(GL_QUADS);
	glColor3ub(255, 255, 255);
	glVertex2f(p1X + 20, p1Y + p1Alt + 10);
	glVertex2f(p1X - p1Comp + 30, p1Y + p1Alt + 10);
	glVertex2f(p1X + 20, p1Y + 10);
	glVertex2f(p1X + 15, p1Y + 10);
	glEnd();	

	glBegin(GL_QUADS);
	glColor3ub(255, 255, 255);
	glVertex2f(p1X - 10, p1Y + p1Alt);
	glVertex2f(p1X + p1Comp, p1Y + p1Alt);
	glVertex2f(p1X + p1Comp, p1Y + 4);
	glVertex2f(p1X, p1Y + 8);
	glEnd();

	glBegin(GL_QUADS);
	glColor3ub(82, 70, 52);
	glVertex2f(p1X +14, p1Y);
	glVertex2f(p1X + p1Comp -3, p1Y);
	glVertex2f(p1X + p1Comp -3, p1Y - 12);
	glVertex2f(p1X + 14, p1Y - 8);
	glEnd();

	glBegin(GL_QUADS);
	glColor3ub(82, 70, 52);
	glVertex2f(p1X + 4, p1Y+2);
	glVertex2f(p1X + p1Comp - 13, p1Y);
	glVertex2f(p1X + p1Comp - 13, p1Y - 12);
	glVertex2f(p1X + 4, p1Y - 12);
	glEnd();
	glPopMatrix();

}

void player2() {

	glPushMatrix();
	
	
	glBegin(GL_QUADS);
	glColor3ub(245, 233, 66);
	glVertex2f(p2X + 15, p2Y + p2Alt + 10);
	glVertex2f(p2X + p2Comp + 5, p2Y + p2Alt + 5);
	glVertex2f(p2X + 15, p2Y + 10);
	glVertex2f(p2X + 15, p2Y + 10);
	glEnd();

	glBegin(GL_QUADS);
	glColor3ub(255, 0, 0);
	glVertex2f(p2X + 15, p2Y + p2Alt + 10);
	glVertex2f(p2X - p2Comp + 30, p2Y + p2Alt + 5);
	glVertex2f(p2X + 15, p2Y + 10);
	glVertex2f(p2X + 15, p2Y + 10);
	glEnd();

	glBegin(GL_QUADS);
	glColor3ub(0, 0, 0);
	glVertex2f(p2X + 20, p2Y + p2Alt + 10);
	glVertex2f(p2X - p1Comp + 30, p2Y + p2Alt + 10);
	glVertex2f(p2X + 20, p2Y + 10);
	glVertex2f(p2X + 15, p2Y + 10);
	glEnd();	

	glBegin(GL_QUADS);
	glColor3ub(0, 0, 0);
	glVertex2f(p2X - 10, p2Y + p2Alt);
	glVertex2f(p2X + p2Comp, p2Y + p2Alt);
	glVertex2f(p2X + p2Comp, p2Y + 4);
	glVertex2f(p2X, p2Y + 8);
	glEnd();

	glBegin(GL_QUADS);
	glColor3ub(82, 70, 52);
	glVertex2f(p2X +14, p2Y);
	glVertex2f(p2X + p2Comp -3, p2Y);
	glVertex2f(p2X + p2Comp -3, p2Y - 12);
	glVertex2f(p2X + 14, p2Y - 8);
	glEnd();

	glBegin(GL_QUADS);
	glColor3ub(82, 70, 52);
	glVertex2f(p2X + 4, p2Y+2);
	glVertex2f(p2X + p2Comp - 13, p2Y);
	glVertex2f(p2X + p2Comp - 13, p2Y - 12);
	glVertex2f(p2X + 4, p2Y - 12);
	glEnd();
	glPopMatrix();

}



float Car(float tx, float ty, int r, int g, int b) {

	glPushMatrix();

	glTranslatef(tx, ty, 0);
	glBegin(GL_QUADS);
	glColor3ub(r, g, b);
	glVertex2f(-40, -20);
	glVertex2f(-40, 20);
	glVertex2f(-10, 20);
	glVertex2f(-10, -20);
	glEnd();

	glBegin(GL_QUADS);
	glColor3ub(r, g, b);
	glVertex2f(10, -20);
	glVertex2f(10, 20);
	glVertex2f(40, 20);
	glVertex2f(40, -20);
	glEnd();	

	glBegin(GL_QUADS);
	glColor3ub(0,255,225);
	glVertex2f(15, -20);
	glVertex2f(15, 20);
	glVertex2f(-15, 20);
	glVertex2f(-15, -20);
	glEnd();
	

	glBegin(GL_QUADS);
	glColor3ub(r,g,b);
	glVertex2f(8, -20);
	glVertex2f(8, 20);
	glVertex2f(-8, 20);
	glVertex2f(-8, -20);
	glEnd();

	glPopMatrix();
	return true;

}
void display()
{

	glMatrixMode(GL_MODELVIEW); //coordenadas de desenho 
	glLoadIdentity();
	glClearColor(0, 0, 0, 1);

	glClear(GL_COLOR_BUFFER_BIT); // EXECUTA LIMPESA 
								  // Especificar o local aonde o desenho acontece: bem no centro da janela 
	glTranslatef(windowW / 2, windowH / 2, 0.0f);
	glViewport(0, 0, windowW, windowH);

	
	environment();
	player1();
	player2();

	//cars
	Car(tx0, ty0,r1,g1,b1);
	Car(tx1, ty1,r1,g2,b2);
	Car(tx2, ty2,r2,g3,b3);
	Car(tx3, ty3,r3,g4,b4);
	Car(tx4, ty4,r4,g5,b5);
	
	
	glFlush();

}
void screen(GLsizei W, GLsizei h) {

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, windowW, 0, windowH);
	glMatrixMode(GL_MODELVIEW);
}