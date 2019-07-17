#include <Windows.h>
#include <cstdlib>
#include <glut.h>
#include <gl/GL.h>
#include <iostream>
#include <vector>

int posx;
bool a_pressed = false;
bool d_pressed = false;
bool w_pressed = false;
bool s_pressed = false;

typedef struct {
	GLfloat r;
	GLfloat g;
	GLfloat b;
} color;

color background_color{1, 1, 1};
color ship_color{0.65, 0.65, 0.65};

void myDisplay(){
	glClearColor(background_color.r, background_color.g, background_color.b, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(ship_color.r, ship_color.g, ship_color.b); // Ship Color
	glBegin(GL_POLYGON); // 2nd Roof
		glVertex2i(220, 200);
		glVertex2i(235, 180);
		glVertex2i(285, 180);
		glVertex2i(280, 200);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP); // 2nd Roof Outline
		glVertex2i(220, 200);
		glVertex2i(235, 180);
		glVertex2i(285, 180);
		glVertex2i(280, 200);
	glEnd();

	glColor3f(0.70, 0.90, 0.98);
	glBegin(GL_POLYGON); // 2nd Window
		glVertex2i(220, 200);
		glVertex2i(228, 190);
		glVertex2i(265, 190);
		glVertex2i(260, 200);
	glEnd();

	glColor3f(ship_color.r, ship_color.g, ship_color.b); // Ship Color
	glBegin(GL_POLYGON); // 1st Roof
		glVertex2i(210, 230);
		glVertex2i(210, 200);
		glVertex2i(325, 200);
		glVertex2i(325, 205);
		glVertex2i(275, 230);
	glEnd();

	glColor3f(0, 0, 0);
		glBegin(GL_LINE_LOOP); // 1st Roof Outline
		glVertex2i(210, 230);
		glVertex2i(210, 200);
		glVertex2i(325, 200);
		glVertex2i(325, 205);
		glVertex2i(275, 230);
	glEnd();

	glColor3f(0.70, 0.90, 0.98);
	glBegin(GL_POLYGON); // 1st Window
		glVertex2i(210, 230);
		glVertex2i(210, 210);
		glVertex2i(280, 210);
		glVertex2i(260, 230);
	glEnd();

	glColor3f(0, 0, 0); // Flag Pole
	glBegin(GL_POLYGON);
		glVertex2i(349, 230);
		glVertex2i(349, 193);
		glVertex2i(351, 193);
		glVertex2i(351, 230);
	glEnd();

	glColor3f(0.9, 0.9, 0.9); // Flag (White)
	glBegin(GL_POLYGON);
		glVertex2i(350, 195);
		glVertex2i(380, 195);
		glVertex2i(380, 215);
		glVertex2i(350, 215);
	glEnd();

	glColor3f(0.81, 0.01, 0.09); // Flag (Red)
	glBegin(GL_POLYGON);
		glVertex2i(350, 195);
		glVertex2i(380, 195);
		glVertex2i(380, 205);
		glVertex2i(350, 205);
	glEnd();

	glColor3f(ship_color.r, ship_color.g, ship_color.b); // Ship Color
	glBegin(GL_POLYGON); // Main Ship Constructure
		// rear
		glVertex2i(170, 290);
		glVertex2i(310, 290);
		// rear bumper
		glVertex2i(360, 225);
		glVertex2i(320, 225);
		glVertex2i(310, 230);
		// front bumper
		glVertex2i(210, 230);
		glVertex2i(200, 225);
		glVertex2i(105, 210);
		glVertex2i(120, 230);
		// front
		glVertex2i(360, 230);
		glVertex2i(120, 230);
	glEnd();

	glColor3f(0, 0, 0);
	glBegin(GL_LINE_LOOP); // Main Ship Outline
		glVertex2i(170, 290);
		glVertex2i(310, 290);
		glVertex2i(360, 225);
		glVertex2i(320, 225);
		glVertex2i(310, 230);
		glVertex2i(210, 230);
		glVertex2i(200, 225);
		glVertex2i(105, 210);
		glVertex2i(120, 230);
		glVertex2i(360, 230);
		glVertex2i(120, 230);
	glEnd();

	glColor3f(0.30, 0.30, 0.30); // Shadow
	glBegin(GL_POLYGON);
		glVertex2i(370, 290);
		glVertex2i(330, 295);
		glVertex2i(170, 290);
	glEnd();
	
	glutSwapBuffers();
}

void randomBackgroundColor() {
	background_color.r = (float)(std::rand() % 100) / 100;
	background_color.g = (float)(std::rand() % 100) / 100;
	background_color.b = (float)(std::rand() % 100) / 100;
}

void shipColor() {
	ship_color.r = (float)(std::rand() % 100) / 100;
	ship_color.g = (float)(std::rand() % 100) / 100;
	ship_color.b = (float)(std::rand() % 100) / 100;
}

void repeatlyFunc(int x) { // Update Func
	std::cout << a_pressed << " " << d_pressed << " | zoom in: " << w_pressed
		<< ", zoom out: " << s_pressed <<" | Position : " << posx << std::endl;
	if (a_pressed) {
		glMatrixMode(GL_MODELVIEW);
		glTranslated(-1, 0, 0);
		posx--; // -385
	}

	if (d_pressed) {
		glMatrixMode(GL_MODELVIEW);
		glTranslated(1, 0, 0);
		posx++; // 380
	}

	if (w_pressed) {
		glMatrixMode(GL_PROJECTION);
		glScaled(1.01, 1.01, 0);
	}

	if (s_pressed) {
		glMatrixMode(GL_PROJECTION);
		glScaled(0.99, 0.99, 0);
	}

	if (posx <= -390) {
		glTranslated(765, 0, 0);
		posx += 765;
	}

	if (posx >= 390) {
		glTranslated(-760, 0, 0);
		posx -= 760;
	}

	glutPostRedisplay();
	glutTimerFunc(x, repeatlyFunc, x);
}

void myKeyboard(unsigned char key, int , int ) {
	if (key == 'a' || key == 'A') {
		a_pressed = true;
	}

	if (key == 'd' || key == 'D') {
		d_pressed = true;
	}

	if (key == 'w' || key == 'W') {
		w_pressed = true;
	}

	if (key == 's' || key == 'S') {
		s_pressed = true;
	}

	if (key == 'r' || key == 'R') {
		randomBackgroundColor();
		std::cout << "Pressed R, changing background color" << std::endl; fflush(stdout);
	}

	if (key == 'b' || key == 'B') {
		shipColor();
		std::cout << "Pressed B, changing ship color" << std::endl; fflush(stdout);
	}

	glutPostRedisplay();
}

void keyUpFunc(unsigned char key, int, int) {
	if (key == 'a' || key == 'A') {
		a_pressed = false;
		// std::cout << "Pressed A, sail to right" << std::endl; fflush(stdout);
	}

	if (key == 'd' || key == 'D') {
		d_pressed = false;
		// std::cout << "Pressed D, sail to left" << std::endl; fflush(stdout);
	}

	if (key == 'w' || key == 'W') {
		w_pressed = false;
	}

	if (key == 's' || key == 'S') {
		s_pressed = false;
	}
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(480, 480);
	glutInitWindowPosition(480, 180);
	glutCreateWindow("My Goddamn Yacht | 672017288");

	gluOrtho2D(0, 480, 480, 0);
	glutDisplayFunc(myDisplay);
	repeatlyFunc(10/1000);
	glutKeyboardFunc(myKeyboard);
	glutKeyboardUpFunc(keyUpFunc);
	glutMainLoop();

	return 0;
}