// Includes
#include <stdlib.h>
#include<stdio.h>
#include<math.h>
//#include<windows.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <string>
#include <sstream>
//#include <linux/input.h>



// tramanho da janela
int width = 500;
int height = 200;
int interval = 1000/240;//240 hz por segundo

// placar
int score_esq = 0;
int score_dir = 0;
int score_max = 0;


// raquetes
int raq_larg = 10;
int raq_alt = 80;
int raq_vel = 3;

//  posição da raquete  esquerda
float raq_esq_x = 10.0f;
float raq_esq_y = 50.0f;

// posição da raquete direita
float raq_dir_x = width - raq_larg - 10;
float raq_dir_y = 50;

// codigos de teclas
#define VK_W 0x57
#define VK_S 0x53
#define VK_SPACE 32

float preto = 0.0f;
float branco = 1.0f;
float corBola = branco;



// bola
float bola_pos_x = width / 2;
float bola_pos_y = height / 2;
float bola_dir_x = -1.0f;
float bola_dir_y = 0.0f;
int bola_tam = 5;
int bola_vel = 5;


void draw(void);
void desenhaRaq(void);
void e2D(void);


void keyboard(unsigned char key, int x, int y) {
	// raquete da esquerda
	if (key == 'w') raq_esq_y += raq_vel;
	//if (GetAsyncKeyState(VK_W)) raq_esq_y += raq_vel;
	if (key == 's') raq_esq_y -= raq_vel;
	//if (GetAsyncKeyState(VK_S)) raq_esq_y -= raq_vel;
	//evitar que a raquete da esquerda passe do campo do jogo
	if (raq_esq_y <= 0 || raq_esq_y >= height) {
		raq_esq_y = 50.0f;
	}

	// raquete da direita
	if (key == 'o')raq_dir_y += raq_vel;
	//if (GetAsyncKeyState(VK_UP)) raq_dir_y += raq_vel;
	if (key == 'l')raq_dir_y -= raq_vel;
	//if (GetAsyncKeyState(VK_DOWN)) raq_dir_y -= raq_vel;
	//evitar que a raquete da direita passe do campo do jogo
	if (raq_dir_y <= 0 || raq_dir_y >= height) {
		raq_dir_y = 50;
	}
	if(key == 32){
		if (corBola == preto) {
			corBola = branco;
		}
		else {
			corBola = preto;
		}
	}

	if (key == 'q') {
		glutDestroyWindow(0);
		exit(0);
	}
	/*if (GetAsyncKeyState(VK_SPACE)) {
		if (corBola == preto) {
			corBola = branco;
		}
		else {
			corBola = preto;
		}
	
	}*/
		
		
	
	
}


void desenhaRaq(float x, float y, float larg, float alt,float cor) {
	glColor3f(cor, cor, cor);
	glBegin(GL_QUADS);
	glVertex2f(x, y);
	glVertex2f(x + larg, y);
	glVertex2f(x + larg, y + alt);
	glVertex2f(x, y + alt);
	glEnd();
}

std::string int2str(int x) {
	// converter inteiro para string
	std::stringstream ss;
	ss << x;
	return ss.str();
}

void drawText(float x, float y, std::string text) {
	glRasterPos2f(x, y);
	glutBitmapString(GLUT_BITMAP_8_BY_13, (const unsigned char*)text.c_str());
}

void draw() {
	glClearColor(preto, preto, preto, preto);  // cor do fundo

	//glClear(GL_COLOR_BUFFER_BIT);  // limpa a tela com a cor do fundo


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	// desenha raquetes rackets
	desenhaRaq(raq_esq_x, raq_esq_y, raq_larg, raq_alt,branco);
	desenhaRaq(raq_dir_x, raq_dir_y, raq_larg, raq_alt,branco);

	// desenha placar
	drawText(width / 2 - 150, height - 15, +"PONTOS ESQUERDA:"+ int2str(score_esq) + "  vs  " + "PONTOS DIREITA:" +int2str(score_dir));

	// desenha bola
	desenhaRaq(bola_pos_x, bola_pos_y, bola_tam, bola_tam,corBola);

	glutSwapBuffers();


	glutSwapBuffers();
}




void vec2_norm(float& x, float &y) {
	// x+y =1 
	float length = sqrt((x * x) + (y * y));
	if (length != 0.0f) {
		length = 1.0f / length;
		x *= length;
		y *= length;
	}
}

void Reset() {
	if ((score_dir == score_max || score_esq == score_max) ) {
		score_dir = 0;
		score_esq = 0;
		bola_pos_x = width / 2;
		bola_pos_y = height / 2;

	}
	
}

void updateBola() {
	// voar
	bola_pos_x += bola_dir_x * bola_vel;
	bola_pos_y += bola_dir_y * bola_vel;

	
	// raquete esquerda
	if (bola_pos_x < raq_esq_x + raq_larg &&
		bola_pos_x > raq_esq_x &&
		bola_pos_y < raq_esq_y + raq_alt &&
		bola_pos_y > raq_esq_y) {
		// definir posição de acordo com posicao

		// t é 0.5 no topo, 0 no centro e -0.5 na parte de baixo
		float t = ((bola_pos_y - raq_esq_y) / raq_alt) - 0.5f;
		bola_dir_x = fabs(bola_dir_x); // force it to be positive
		bola_dir_y = t;
	}

	// raquete direita
	if (bola_pos_x > raq_dir_x &&
		bola_pos_x < raq_dir_x + raq_larg &&
		bola_pos_y < raq_dir_y + raq_alt &&
		bola_pos_y > raq_dir_y) {
		// definir posição de acordo com posicao
		// t é 0.5 no topo, 0 no centro e -0.5 na parte de baixo
		float t = ((bola_pos_y - raq_dir_y) / raq_alt) - 0.5f;
		bola_dir_x = -fabs(bola_dir_x); // negativar
		bola_dir_y = t;
	}

	// acertou parede da esquerda
	if (bola_pos_x < 0) {
		++score_dir;
		Reset();
		bola_pos_x = width / 2;
		bola_pos_x = height / 2;
		bola_dir_x = fabs(bola_dir_x); // positivar
		bola_dir_y = 0;

		
	}

	// acertou parede da direita
	if (bola_pos_x > width) {
		++score_esq;
		Reset();
		bola_pos_x = width / 2;
		bola_pos_y = height / 2;
		bola_dir_x = -fabs(bola_dir_x); // negativar
		bola_dir_y = 0;
	}

	// acertou parede de cima
	if (bola_pos_y > height) {
		bola_dir_y = -fabs(bola_dir_y); // negativar
	}

	// acertou parede de baixo
	if (bola_pos_y < 0) {
		bola_dir_y = fabs(bola_dir_y); // positivar
	}

	
	// manter tamanho da direcao em 1
	vec2_norm(bola_dir_x, bola_dir_y);
}

void update(int value) {
	
	unsigned char key;
	int x;
	int y;
	keyboard(key,x,y);

	updateBola();
	// Chama o update no intervalo de 0 segundos
	glutPostRedisplay();
	glutTimerFunc(interval, update, 0);
	// mostra o frame novamente
	
}

void e2D(int width, int height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f, width, 0.0f, height, 0.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


void setScore(int x) {
	score_max = x;
}

void win() {

}

void menu() {
	int opt;
	printf("Selecione o numero de pontos para a vitoria\n\1 - 2 Pontos\n2 - 3 Pontos\n3 - 5 Pontos\n\n");
	scanf("%i", &opt);
		if (opt == 1) {
			setScore(2);
		}
		else if (opt == 2) {
			setScore(3);
		}
		else if (opt == 3) {
			setScore(5);
		}
		else if (opt == 4) {
			printf("Raquete da esquerda: W move para cima, e S para baixo\n\nRaquete da direita: Seta para cima move para cima, e seta para baixo move para baixo");
			getchar();
			system("clear");
			menu();
		}
		else {
			system("clear");
			printf("Opcao invalida\n\n");
			menu();
		}
}




int main(int argc, char** argv) {
	// initialize opengl (via glut)
	menu();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutCreateWindow("Pong - Andre Robert");

	//chama a função inicial e intervalo
	glutDisplayFunc(draw);
	glutTimerFunc(interval, update, 0);
	glutKeyboardFunc(&keyboard);
	e2D(width, height);
	glColor3f(branco, branco, branco);

	glutMainLoop();
	return 0;
}
