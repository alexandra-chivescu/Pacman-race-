#include <iostream>
#include<windows.h>
#include<stdlib.h>
#include <GL/freeglut.h>

using namespace std;

GLdouble left_m = -100.0;
GLdouble right_m = 700.0;
GLdouble bottom_m = -140.0;
GLdouble top_m = 460.0;
double ok = 1, ok_food = 1;
double j = 0.0;
double i = 0.0;
double contor = 0;
double loc_vert = 800, loc_vert_food = 800;
int vector[3] = { 0, 160, 320 };
double height = vector[rand() % 3], height_food = vector[rand() % 3];
int score = 0;
double timp = 0.4; //cat de repede se misca obiectele si liniile soselei
double timp_food = 0.3;
int pct = 1000;
double rsj, rdj, rss, rds = 0;
int screen = 1;
int x, y;
int window;

struct COLOR {
	GLfloat r, g, b;
};

//crearea ferestrei jocului
void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glOrtho(left_m, right_m, bottom_m, top_m, -1.0, 1.0);
}

void mouse(int button, int state, int mx, int my)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		x = mx;
		y = 600 - my;
	}

}

void RenderString(float x, float y, void* font, const unsigned char* string)
{

	glColor3f(1.0f, 0.0f, 0.0f);
	glRasterPos2f(x, y);

	glutBitmapString(font, string);
}

void startgame(void)
{
	//pentru fantome
	if (height != j || (loc_vert > 64 || loc_vert < -50))
	{

		if (i < -300)
		{
			i = 0;
		}
		i = i - 2 * timp;

		loc_vert -= timp;

		if (loc_vert < -150)
		{
			//pe ce linie se pune urmatorul obiect
			height = vector[rand() % 3];
			char buf[100] = { 0 }; 
			loc_vert = 750;
		}

		if (score >= pct && pct <= 15000)
		{
			timp += 0.1;
			pct += 1000;
		}
	}
	else {
		ok = 0;
	}

	//pentru mancare
	if (true)
	{
		if (i < -300)
		{
			i = 0;
		}
		i = i - 2 * timp_food;

		loc_vert_food -= timp_food;

		if (height_food == j && loc_vert_food < 45 && loc_vert_food > -50) {
			score += 100;
			height_food = vector[rand() % 3];
			loc_vert_food = 800;
		} else if (loc_vert_food < -150) {
			loc_vert_food = 800;
		}

		if (score >= pct && pct <= 15000)
		{
			timp_food += 0.1;
			pct += 1000;
		}

		glutPostRedisplay();
	}
}

//functie pt scor
void renderbitmap(float x, float y, void* font, char* string) {
	char* c;
	glRasterPos2f(x, y);
	for (c = string; *c != '\0'; c++) {
		glutBitmapCharacter(font, *c); 
	}
}

//triunghi pentru gura Pacman
void drawTri()
{
	glBegin(GL_TRIANGLES);
	glColor3f(0, 0, 0);

	glVertex2f(0, 0);
	glVertex2f(40, -30);
	glVertex2f(40, 20);
	glEnd();
}


void drawCircle(double radius, float x1, float y1, COLOR color)
{
	float angle;
	float x2, y2;

	glColor3f(color.r, color.g, color.b);

	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x1, y1);

	for (angle = 1.0f; angle < 361.0f; angle += 0.2)
	{
		if (angle > 2.0f && angle < 250.0f)
			continue;
		else {
			x2 = x1 + sin(angle) * radius;
			y2 = y1 + cos(angle) * radius;
			glVertex2f(x2, y2);
		}
	}

	glEnd();

}

void drawScene(void)
{
	//meniu
	if (screen == 1) {
		glClear(GL_COLOR_BUFFER_BIT);

		glColor3f(0, 0, 0);

		glColor3f(1.0f, 1.0f, 1.0f);
		char titleGame[100] = { 0 };
		sprintf_s(titleGame, "Pacman race - stay away from ghosts and eat proteins for a high score");
		renderbitmap(-40, 400, GLUT_BITMAP_TIMES_ROMAN_24, titleGame);

		glColor3f(0.1, 0.6, 0.1);
		glRecti(235, 185, 310, 230);
		glColor3f(0.0f, 0.0f, 0.0f);
		char bufPlayGame[100] = { 0 };
		sprintf_s(bufPlayGame, "Play");
		renderbitmap(250, 200, GLUT_BITMAP_TIMES_ROMAN_24, bufPlayGame);

		glColor3f(1, 0.2, 0.3);
		glRecti(235, 85, 310, 130);
		glColor3f(0.0f, 0.0f, 0.0f);
		char bufExitGame[100] = { 0 };
		sprintf_s(bufExitGame, "Exit");
		renderbitmap(250, 100, GLUT_BITMAP_TIMES_ROMAN_24, bufExitGame);

		//daca userul face click pe play, se incepe jocul (screen = 2)
		if (x >= 235 && x <= 310 && y >= 185 && y >= 230)
		{
			screen = 2;
		}
		//daca userul face click pe exit, se inchide fereastra
		if (x >= 235 && x <= 310 && y >= 85 && y >= 130)
		{
			glutDestroyWindow(window);
		}
		
		glFlush();
	}
	//in joc
	if (screen == 2)
	{
		glClear(GL_COLOR_BUFFER_BIT);


		glColor3f(0, 0, 1);

		// Imprejurimi jos
		glBegin(GL_POLYGON);
		glVertex2i(-100, -140);// Stanga jos
		glVertex2i(700, -140); // Dreapta jos
		glVertex2i(700, -80);  // Dreapta sus
		glVertex2i(-100, -80); // Stanga sus
		glEnd();

		// Imprejurimi sus
		glBegin(GL_POLYGON);
		glVertex2i(-100, 400);// Stanga jos
		glVertex2i(700, 400); // Dreapta jos
		glVertex2i(700, 460); // Dreapta sus
		glVertex2i(-100, 460);// Stanga sus
		glEnd();
		RenderString(80.0f, 425.0f, GLUT_BITMAP_TIMES_ROMAN_24, (const unsigned char*)"Stay away from ghosts and eat your proteins!");

		// Delimitare sosea
		glLineWidth(15);
		glColor3f(0, 0, 1);


		// Initializare pt tranzitii
		glPushMatrix();
		glTranslated(i * 1.25, 0.0, 0.0);

		//Delimitare sosea - linie punctata jos
		glPushAttrib(GL_ENABLE_BIT);
		glLineStipple(100, 0xAAAA);
		glEnable(GL_LINE_STIPPLE);
		glBegin(GL_LINES);
		glVertex2i(-500, 80);
		glVertex2i(1500, 80);
		glEnd();
		glPopAttrib();

		//Delimitare sosea - linie punctata sus
		glPushAttrib(GL_ENABLE_BIT);
		glLineStipple(100, 0xAAAA);
		glEnable(GL_LINE_STIPPLE);
		glBegin(GL_LINES);
		glVertex2i(-500, 240);
		glVertex2i(1500, 240);
		glEnd();
		glPopAttrib();

		glPopMatrix();

		//black circle for the eyes of the ghosts & Pacman
		struct COLOR circleEyes;
		circleEyes.r = 0;
		circleEyes.g = 0;
		circleEyes.b = 0;

		//desenam pacman
		glPushMatrix();
		glTranslated(0.0, j, 0.0);

		struct COLOR circlePacman;
		circlePacman.r = 1;
		circlePacman.g = 1;
		circlePacman.b = 0;
		drawCircle(40, 0, 0, circlePacman);
		drawCircle(5, 0, 20, circleEyes);
		drawTri();

		if (ok == 0)
		{
			rsj = 8;
			rss = -8;
			rdj = -8;
			rds = 8;
		}

		glPopMatrix();

		if (ok == 0) {
			//afisare mesaj GAME OVER pe mijlocul ferestrei
			RenderString(250.0f, 200.0f, GLUT_BITMAP_8_BY_13, (const unsigned char*)"GAME OVER");
		}

		if (contor == 1 && (j != 160 && j != 320))
			j = j + 1;
		else if (contor == -1 && (j != 160 && j != 0))
			j = j - 1;
		else {
			contor = 0;

		}

		//desenam fantomele pentru Pacman
		glPushMatrix();
		glTranslated(loc_vert, height, 0.0);

		glColor3f(0.471, 0.667, 0.949);
		struct COLOR circleGhost;
		circleGhost.r = 1;
		circleGhost.g = 0.2;
		circleGhost.b = 0.3;
		drawCircle(30, 0, 0, circleGhost);
		drawCircle(10, 0, -30, circleGhost);
		drawCircle(10, -20, -30, circleGhost);
		drawCircle(10, 20, -30, circleGhost);
		glColor3f(1, 0.2, 0.3);
		glRecti(-30, -35, 30, 5);
		drawCircle(5, -10, 6, circleEyes);
		drawCircle(5, 10, 6, circleEyes);
		glPopMatrix();

		//desenam mancarea pentru Pacman
		if (height_food == height && loc_vert == loc_vert_food && height == 320)
			height_food = 160;
		if (height_food == height && loc_vert == loc_vert_food && height == 160)
			height_food = 0;
		if (height_food == height && loc_vert == loc_vert_food && height == 0)
			height_food = 320;

		glPushMatrix();
		glTranslated(loc_vert_food, height_food, 0.0);
		glColor3f(0.471, 0.667, 0.949);
		drawCircle(10, 0, 0, circlePacman);
		glPopMatrix();

		startgame();
		//afisare scor
		glColor3f(1.0f, 0.0f, 0.0f);
		char buf[100] = { 0 };
		sprintf_s(buf, "Score: %d", score);
		renderbitmap(-90, -110, GLUT_BITMAP_TIMES_ROMAN_24, buf);
		glutPostRedisplay();
		glutSwapBuffers();
		glFlush();
	}
}


void miscasus(void)
{
	if (ok != 0)
	{
		if (j < 320)
		{
			contor = 1;
			j += 1;
		}

		glutPostRedisplay();
	}
}

void miscajos(void)
{
	if (ok != 0)
	{
		if (j > 0)
		{
			contor = -1;
			j -= 1;


		}

		glutPostRedisplay();
	}
}

void keyboard(int key, int x, int y)
{


	switch (key) {
	case GLUT_KEY_UP:
		miscasus();
		break;
	case GLUT_KEY_DOWN:
		miscajos();
		break;

	}

}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	window = glutCreateWindow("Pacman game - eat all the proteins");
	init();
	glutMouseFunc(mouse);
	glutDisplayFunc(drawScene);
	glutSpecialFunc(keyboard);

	glutMainLoop();
}