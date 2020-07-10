#include <iostream>
#include "GL/freeglut.h"
#include <string>
#include "Sprite.h"

using namespace std;

//User define
#include "Tower.h"
#include "Enemy.h"

#include <list>
#include <stdlib.h>;
#include <time.h>;

#define _USE_MATH_DEFINES
#include <math.h>
#define GRID_SIZE 30
#define GAMESTORE_HEIGTH 4
#define GAMEBOARD_WIDTH 22
#define GAMEBOARD_HEIGTH 6
#define MAX_TOWER_NUM 114

//User public
int mouse_x;
int mouse_y;

int CurTower = 1;
bool isGameOver;
int GameBoard[GRID_SIZE * GAMEBOARD_WIDTH][GRID_SIZE * GAMEBOARD_HEIGTH];

int money;

Tower t[MAX_TOWER_NUM];
list<Tower*> *TowerList;

Enemy e[MAX_ENEMY_NUM];

void GameInit() {
	isGameOver = false;

	money = 100;

	TowerList = new list<Tower*>();

	for (int i = 0; i < MAX_TOWER_NUM; i++) {
		t[i].isActive = false;
		e[i].isActive = false;
		for (int j = 0; j < GAMEBOARD_HEIGTH; j++) {
			GameBoard[i][j] = 0;
			//GameBoard[i][j] = 0; emtry
			//GameBoard[i][j] = 1; HaveThing
		}
	}
}

void DrawGameBoard() {
	//StoreBoard
	glColor3f(0.73, 0.45, 0.33);
	glBegin(GL_POLYGON);
	glVertex2f(0, GRID_SIZE * GAMEBOARD_HEIGTH);
	glVertex2f(0, GRID_SIZE * (GAMEBOARD_HEIGTH + GAMESTORE_HEIGTH));
	glVertex2f(GRID_SIZE * GAMEBOARD_WIDTH, GRID_SIZE * (GAMEBOARD_HEIGTH + GAMESTORE_HEIGTH));
	glVertex2f(GRID_SIZE * GAMEBOARD_WIDTH, GRID_SIZE * GAMEBOARD_HEIGTH);
	glEnd();

	//GameBoard Line
	glLineWidth(2);
	glColor3f(0, 0, 0);
	for (int i = 0; i < GAMEBOARD_HEIGTH; i++) {
		glBegin(GL_LINES);
		glVertex2f(0, GRID_SIZE * i);
		glVertex2f(GRID_SIZE * (GAMEBOARD_WIDTH - 3), GRID_SIZE * i);
		glEnd();
	}

	for (int i = 0; i < GAMEBOARD_WIDTH - 2; i++) {
		glBegin(GL_LINES);
		glVertex2f(GRID_SIZE * i, 0);
		glVertex2f(GRID_SIZE * i, GRID_SIZE * GAMEBOARD_HEIGTH);
		glEnd();
	}

	//GameBoard
	glColor3f(1, 0.89, 0.25);
	glBegin(GL_POLYGON);
	glVertex2f(0, 0);
	glVertex2f(0, GRID_SIZE * (GAMEBOARD_HEIGTH + GAMESTORE_HEIGTH));
	glVertex2f(GRID_SIZE * GAMEBOARD_WIDTH, GRID_SIZE * (GAMEBOARD_HEIGTH + GAMESTORE_HEIGTH));
	glVertex2f(GRID_SIZE * GAMEBOARD_WIDTH, 0);
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

		//cout << "Mouse Click: " << mouse_x << ", " << mouse_y << endl;   //debug

		if (mouse_x < GAMEBOARD_WIDTH - 3 && mouse_y < GAMEBOARD_HEIGTH) {
			if (GameBoard[mouse_x][mouse_y] != 0) {
				MessageBox(NULL, "Please choose other grid!", "ERROR", MB_OK | MB_ICONERROR);
				return;
			}
			
			Tower *newTower = new Tower();
			newTower->isActive = true;
			newTower->x = mouse_x;
			newTower->y = mouse_y;
			newTower->CurTower = CurTower;
	
			TowerList->push_back(newTower);
			
			if (newTower->CurTower != 0) {
				GameBoard[mouse_x][mouse_y] = 1;
			}

			//cout << newTower->x << " " << newTower->y << endl; //debug
		}
	}
	else if(mouse_x < GAMEBOARD_WIDTH - 3 && mouse_y >= GAMEBOARD_HEIGTH){
		//store area
		if (mouse_x >= 4 && mouse_x <= 6 && mouse_y >= 6 && mouse_y <= 9) {

			cout << "Button_1" << endl;   //debug
		}
		if (mouse_x >= 7 && mouse_x <= 9 && mouse_y >= 6 && mouse_y <= 9) {

			cout << "Button_2" << endl;   //debug
		}
		if (mouse_x >= 10 && mouse_x <= 12 && mouse_y >= 6 && mouse_y <= 9) {

			cout << "Button_3" << endl;   //debug
		}
		if (mouse_x >= 13 && mouse_x <= 15 && mouse_y >= 6 && mouse_y <= 9) {

			cout << "Button_4" << endl;   //debug
		}

		//cout << "mouse_x=" << mouse_x << " mouse_y=" << mouse_y << endl;   //debug
		cout << "Clicked on store" << endl;   //debug
	}
}

void Draw_UI() {
	//Draw Button 1
	glBegin(GL_POLYGON);
	glColor3f(0, 1, 0);
	glVertex2f(120, 180);
	glVertex2f(210, 180);
	glVertex2f(210, 360);
	glVertex2f(120, 360);
	glEnd();

	//Draw Button 2
	glBegin(GL_POLYGON);
	glColor3f(0.58, 0, 0.83);
	glVertex2f(210, 180);
	glVertex2f(300, 180);
	glVertex2f(300, 360);
	glVertex2f(210, 360);
	glEnd();

	//Draw Button 3
	glBegin(GL_POLYGON);
	glColor3f(0, 0, 1);
	glVertex2f(300, 180);
	glVertex2f(390, 180);
	glVertex2f(390, 360);
	glVertex2f(300, 360);
	glEnd();

	//Draw Button 4
	glBegin(GL_POLYGON);
	glColor3f(1, 0.75, 0.8);
	glVertex2f(390, 180);
	glVertex2f(480, 180);
	glVertex2f(480, 360);
	glVertex2f(390, 360);
	glEnd();
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
	gluOrtho2D(0, GRID_SIZE * GAMEBOARD_WIDTH, 0, GRID_SIZE * (GAMEBOARD_HEIGTH + GAMESTORE_HEIGTH));
}

void display() {
	glClearColor(0.5, 0.5, 0.5, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear Screen and Depth Buffer
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	for (list<Tower*>::iterator it = TowerList->begin(); it != TowerList->end(); ++it) {
		(*it)->DrawBaseTower();
	}

	//Draw UI
	glColor3f(0, 0, 0);
	glRasterPos2f(5, 270);
	string money_UI = "Money:" + to_string(money);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)money_UI.c_str());
	Draw_UI();						//Button only

	DrawGameBoard();

	glutSwapBuffers();
}

void update(int value) {

	glutPostRedisplay();
	glutTimerFunc(30, update, 0);
}

int main(int argc, char **argv) {
	srand(time(0));

	cout << "Programmer: <Lau Chin Ho 190034501>\n";
	cout << "Compiled on " << __DATE__ << ", " << __TIME__ << std::endl << std::endl;

	// init GLUT and create Window
	glutInit(&argc, argv);                      // GLUT initialization
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(GRID_SIZE * GAMEBOARD_WIDTH, GRID_SIZE * (GAMEBOARD_HEIGTH + GAMESTORE_HEIGTH));               // set the window size

	// create the window
	glutCreateWindow("Tower Defence");
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
