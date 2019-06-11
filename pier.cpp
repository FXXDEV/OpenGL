#include <stdlib.h>
#include <GL/glut.h>


void keyboard(unsigned char key, int x, int y);
void resize(GLsizei w, GLsizei h);
void display(void);


int main(int argc, char** argv)
{
	glutInit(&argc, argv);  // controla se o sistema operacional tem suporte a janelas.

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  // quantidade de buffer de cores e que o padrao de cores é RGB ou RGBA

	glutInitWindowSize(1000, 500);  // tamanho da janela

								   //glutFullScreen();  // full screen

	glutInitWindowPosition(0, 0); // posicao inicial da janela

	glutCreateWindow("Pier");   /// cria a janela

	glutKeyboardFunc(&keyboard);

	glutReshapeFunc(&resize); // 

	glutDisplayFunc(display);

	glutMainLoop();

	return EXIT_SUCCESS;
}


void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case '\x1B':
		exit(EXIT_SUCCESS);
		break;
	}
}

void resize(GLsizei w, GLsizei h)
{

	if (h == 0) h = 1;  // Evita a divisao por zero

	glViewport(0, 0, w, h);  // Especifica as dimensões da Viewport

							 // Inicializa o sistema de coordenadas
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Estabelece a janela de seleção (left, right, bottom, top)
	if (w <= h)
	{
		gluOrtho2D(0.0f, 250.0f, 0.0f, 250.0f*h / w);
	}
	else
	{
		gluOrtho2D(0.0f, 250.0f*w / h, 0.0f, 250.0f);
	}
	glMatrixMode(GL_MODELVIEW);


}

void display()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClearColor(0.02f, 1.0f, 1.0f, 0.9f);  // cor do fundo

	glClear(GL_COLOR_BUFFER_BIT);  // limpa a tela com a cor do fundo
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPointSize(6.0);

	

	//boat
	

	glBegin(GL_QUADS);
	glColor3f(0.62, 0.16, 0.10);
	glVertex2f(50, 100);
	glVertex2f(250, 100);
	glVertex2f(220, 50);
	glVertex2f(80, 50);
	glEnd();


	//smoke
	glBegin(GL_QUADS);
	glColor3f(0.25, 0.14, 0.04);
	glVertex2f(180, 150);
	glVertex2f(210, 150);
	glVertex2f(210, 100);
	glVertex2f(180, 100);
	glEnd();

	//red-line
	glBegin(GL_QUADS);
	glColor3f(1, 0, 0);
	glVertex2f(180, 140);
	glVertex2f(210, 140);
	glVertex2f(210, 130);
	glVertex2f(180, 130);
	glEnd();


	//
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glVertex2f(100, 140);
	glVertex2f(180, 140);
	glVertex2f(180, 100);
	glVertex2f(100, 100);
	glEnd();

	//windows

	glBegin(GL_QUADS);
	glColor3f(0.02f, 1.0f, 1.0);
	glVertex2f(105, 130);
	glColor3f(0, 0, 1);
	glVertex2f(135, 130);
	glVertex2f(135, 110);
	glColor3f(1, 1, 1);
	glVertex2f(105, 110);
	glEnd();

	glBegin(GL_QUADS);
	glColor3f(0.02f, 1.0f, 1.0f);
	glVertex2f(140, 130);
	glColor3f(0, 0, 1);
	glVertex2f(170, 130);
	glVertex2f(170, 110);
	glColor3f(1, 1, 1);
	glVertex2f(140, 110);
	glEnd();




	//sea
	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex2f(0, 50);
	glVertex2f(250, 50);
	glVertex2f(250, 0);
	glVertex2f(0, 0);
	glEnd();

	//pier
	glBegin(GL_QUADS);
	glColor3f(0.3f, 0.09f, 0.04f);
	glVertex2f(250, 70);
	glVertex2f(330, 70);
	glVertex2f(330, 0);
	glVertex2f(250, 0);
	glEnd();

	//grass

	glBegin(GL_QUADS);
	glColor3f(0.3f, 1.0f, 0.04f);
		glVertex2f(330, 70);
		glVertex2f(500, 70);
		glVertex2f(500, 0);
		glVertex2f(330, 0);
	glEnd();


	//tree
	glBegin(GL_QUADS);
	glColor3f(0.25, 0.14, 0.04);
	glVertex2f(400, 120);
	glVertex2f(430, 120);
	glVertex2f(430, 70);
	glVertex2f(400, 70);
	glEnd();

	//tree-top
	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex2f(390, 120);
	glVertex2f(440, 120);
	glVertex2f(417, 180);
	glEnd();


	glFlush(); // executa o desenho

}
