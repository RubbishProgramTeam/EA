#include <iostream>
#include "GL/freeglut.h"
#include <string>
#include "Sprite.h"

using namespace std;

//User define
#include "BaseTower.h"
#include "Tower.h"
#include <list>

#define _USE_MATH_DEFINES
#include <math.h>
#define GRID_SIZE 30
#define GAMESTORE_HEIGTH 3
#define GAMEBOARD_WIDTH 19
#define GAMEBOARD_HEIGTH 6
#define MAX_TOWER_NUM 100

//User public
list<int> towerList;
int towernum;

int mouse_x;
int mouse_y;
int CurTower;
bool isGameOver;
int GameBoard[GRID_SIZE * GAMEBOARD_WIDTH][GRID_SIZE * GAMEBOARD_HEIGTH];

Tower t[MAX_TOWER_NUM];

void GameInit() {
	isGameOver = false;
	for (int i = 0; i < MAX_TOWER_NUM; i++) {
		t[i].isActive = false;
	}


	for (int i = 0; i < GAMEBOARD_WIDTH; i++) {
		for (int j = 0; j < GAMEBOARD_HEIGTH; j++) {
			GameBoard[i][j] = 0;
			//GameBoard[i][j] = 0; emtry
			//GameBoard[i][j] = 1; HaveThing
		}
	}
}

void DrawGameBoard() {
	glColor3f(0.73, 0.45, 0.33);
	glBegin(GL_POLYGON);
	glVertex2f(0, GRID_SIZE * GAMEBOARD_HEIGTH);
	glVertex2f(0, GRID_SIZE * (GAMEBOARD_HEIGTH + GAMESTORE_HEIGTH));
	glVertex2f(GRID_SIZE * GAMEBOARD_WIDTH, GRID_SIZE * (GAMEBOARD_HEIGTH + GAMESTORE_HEIGTH));
	glVertex2f(GRID_SIZE * GAMEBOARD_WIDTH, GRID_SIZE * GAMEBOARD_HEIGTH);
	glEnd();

	glLineWidth(2);
	glColor3f(0, 0, 0);
	for (int i = 0; i < GAMEBOARD_HEIGTH; i++) {
		glBegin(GL_LINES);
		glVertex2f(0, GRID_SIZE * i);
		glVertex2f(GRID_SIZE * GAMEBOARD_WIDTH, GRID_SIZE * i);
		glEnd();
	}

	for (int i = 0; i < GAMEBOARD_WIDTH; i++) {
		glBegin(GL_LINES);
		glVertex2f(GRID_SIZE * i, 0);
		glVertex2f(GRID_SIZE * i, GRID_SIZE * GAMEBOARD_HEIGTH);
		glEnd();
	}

	glColor3f(0.57, 0.89, 0.25);
	glBegin(GL_POLYGON);
	glVertex2f(0, 0);
	glVertex2f(0, GRID_SIZE * (GAMEBOARD_HEIGTH + GAMESTORE_HEIGTH));
	glVertex2f(GRID_SIZE * GAMEBOARD_WIDTH, GRID_SIZE * (GAMEBOARD_HEIGTH + GAMESTORE_HEIGTH));
	glVertex2f(GRID_SIZE * GAMEBOARD_WIDTH, 0);
	glEnd();
}

void DrawBaseTower(int x, int y) {
	glBegin(GL_POLYGON);
	glColor3f(0, 1, 0);
	for (int i = 0; i < 360; i++) {
		glVertex2f((15 * cos(i * M_PI / 180.0f)) + (((x * GRID_SIZE) + ((x + 1) * GRID_SIZE)) / 2), (15 * sin(i * M_PI / 180.0f)) + (((y * GRID_SIZE) + ((y + 1) * GRID_SIZE + 1)) / 2));
	}
	glEnd();
}

void mouseClick(int button, int state, int x, int y) {

	if (isGameOver) {
		return;
	}

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		mouse_x = x;
		mouse_y = (GRID_SIZE * (GAMEBOARD_HEIGTH + GAMESTORE_HEIGTH)) - y;

		mouse_x = mouse_x / GRID_SIZE;
		mouse_y = mouse_y / GRID_SIZE;

		//cout << "Mouse Click: " << mouse_x << ", " << mouse_y << endl;

		if (mouse_x < GAMEBOARD_WIDTH && mouse_y < GAMEBOARD_HEIGTH) {
			if (GameBoard[mouse_x][mouse_y] != 0) {
				MessageBox(NULL, "Please choose other grid!", "ERROR", MB_OK | MB_ICONERROR);
				return;
			}
			
			if (CurTower = 1) {
				t[0].isActive = true;
				GameBoard[mouse_x][mouse_y] = 1;
				
			}
		}
		else {
			cout << "Clicked on store" << endl;
		}
	}

}

void initRendering() {
	glEnable(GL_DEPTH_TEST);                    // test 3D depth
	glEnable(GL_BLEND); 
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


}

void cameraSetup(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);                // select projection matrix
	glLoadIdentity();                           // reset projection matrix
	//gluPerspective(45.0, 1, 1.0, 100.0);        // set up a perspective projection matrix
	gluOrtho2D(0, w, 0, h);
}

void display() {
	glClearColor(0.5, 0.5, 0.5, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear Screen and Depth Buffer
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	for (int i = 0; i < MAX_TOWER_NUM; i++) {
		if (t[i].isActive) {
			t[i].DrawBaseTower(mouse_x, mouse_y);
		}
	}
	DrawGameBoard();

	glutSwapBuffers();
}

void update(int value) {

	glutPostRedisplay();
	glutTimerFunc(30, update, 0);
}

int main(int argc, char **argv) {
	std::cout << "Programmer: <Lau Chin Ho 190034501>\n";
	std::cout << "Compiled on " << __DATE__ << ", " << __TIME__ << std::endl << std::endl;

	// init GLUT and create Window
	glutInit(&argc, argv);                      // GLUT initialization
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(GRID_SIZE * GAMEBOARD_WIDTH, GRID_SIZE * (GAMEBOARD_HEIGTH + GAMESTORE_HEIGTH));               // set the window size

	// create the window
	glutCreateWindow("Introduction to OpenGL");
	initRendering();                            // initialize rendering

	// register handler functions
	glutReshapeFunc(cameraSetup);               // resiz window and camera setup
	glutDisplayFunc(display);                   // Display function
	glutTimerFunc(30, update, 0);
	glutMouseFunc(mouseClick);

	GameInit();

	glutMainLoop();                             // run GLUT mainloop
	return(0);                                  // this line is never reached
}
