#include <iostream>
#include "GL/freeglut.h"
#include <string>
#include "Sprite.h"

using namespace std;

//User define
#include "Tower.h"
#include "Enemy.h"

#include <chrono>
#include <ctime>

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
#define MIN_MONEY 0
#define MAX_ENEMY_NUM 100

//User public
chrono::system_clock::time_point LastFrameTime;

GLuint BaseTowerImage;
GLuint SlowTowerImage;
GLuint BlockImage;
GLuint TrapImage;

int mouse_x;
int mouse_y;

int CurTower = 0;
bool isGameOver;

int GameBoard[GRID_SIZE * GAMEBOARD_WIDTH][GRID_SIZE * GAMEBOARD_HEIGTH];

int money;
int towerMoney = 0;
bool isBuild;

int CurScene = 2;
//CurScene = 0 //Title Scene
//CurScene = 1 //How To Play Scene
//CurScene = 2 //Game Scene
//CurScene = 3 //GameOverFunc

Tower t[MAX_TOWER_NUM];
list<Tower*> *TowerList;

Enemy e[MAX_ENEMY_NUM];

void TitleScene() {

	glColor3f(1, 0.89, 0.25);
	glBegin(GL_POLYGON);
	glVertex2f(0, 0);
	glVertex2f(0, GRID_SIZE * (GAMEBOARD_HEIGTH + GAMESTORE_HEIGTH));
	glVertex2f(GRID_SIZE * GAMEBOARD_WIDTH, GRID_SIZE * (GAMEBOARD_HEIGTH + GAMESTORE_HEIGTH));
	glVertex2f(GRID_SIZE * GAMEBOARD_WIDTH, 0);
	glEnd();
}

void HowToPlayScene() {
	//TODO: Show How To Play;
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

	if (CurScene == 0) {
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			//TODO: Create a button, press to go in how to play scene(CurScene 1)
			CurScene = 2;

			//TODO: Create a button, press to go in the game (CurScene 2)
		}
	}

	//Game Scene
	if (CurScene == 2) {
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			mouse_x = x;
			mouse_y = (GRID_SIZE * (GAMEBOARD_HEIGTH + GAMESTORE_HEIGTH)) - y;

			mouse_x = mouse_x / GRID_SIZE;
			mouse_y = mouse_y / GRID_SIZE;

			//cout << "Mouse Click: " << mouse_x << ", " << mouse_y << endl;   //debug

			if (mouse_x < GAMEBOARD_WIDTH - 3 && mouse_y < GAMEBOARD_HEIGTH) {
				if (GameBoard[mouse_x][mouse_y] != 0) {
					MessageBox(NULL, "Please choose other grid!", "Ops!", MB_OK | MB_ICONERROR);
					return;
				}

				Tower *newTower = new Tower();
				if (money >= towerMoney && CurTower != 0) {
					newTower->isActive = true;
					newTower->x = mouse_x;
					newTower->y = mouse_y;
					newTower->CurTower = CurTower;
					money -= towerMoney;

					TowerList->push_back(newTower);

					GameBoard[mouse_x][mouse_y] = 1;

				}
				else if (money <= towerMoney) {
					MessageBox(NULL, "You don't gave enough money!", "Ops!", MB_OK | MB_ICONEXCLAMATION);
					return;
				}
				//cout << newTower->x << " " << newTower->y << endl; //debug
			}
		}
		if (mouse_x < GAMEBOARD_WIDTH && mouse_y <= (GAMEBOARD_HEIGTH + GAMESTORE_HEIGTH) && mouse_y > GAMEBOARD_HEIGTH) {
			//store area

			if (mouse_x >= 4 && mouse_x <= 6 && mouse_y >= 6 && mouse_y <= 9) {
				//Base Tower
				CurTower = 1;
				towerMoney = 20;
			}
			if (mouse_x >= 8 && mouse_x <= 10 && mouse_y >= 6 && mouse_y <= 9) {
				//SlowTower
				CurTower = 2;
				towerMoney = 30;
			}
			if (mouse_x >= 12 && mouse_x <= 14 && mouse_y >= 6 && mouse_y <= 9) {
				//Block
				CurTower = 4;
				towerMoney = 10;
			}
			if (mouse_x >= 16 && mouse_x <= 18 && mouse_y >= 6 && mouse_y <= 9) {
				//Trap
				CurTower = 3;
				towerMoney = 30;
			}
		}
	}
}

void Draw_UI() {
	string towerName[5] = { "Base Tower", "Slow Tower", "Road Block", "Trap" , "Not Select"};

	glColor3f(1, 1, 0);
	glRasterPos2f(5, 270);
	string money_UI = "Money:" + to_string(money);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)money_UI.c_str());

	glColor3f(0, 0, 0);
	glRasterPos2f(5, 220);
	string selectTower = "SelectTower: ";
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)selectTower.c_str());

	glRasterPos2f(5, 200);
	if (CurTower == 1) {
		string selectTower_UI = towerName[0];
		glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)selectTower_UI.c_str());
	}	
	if (CurTower == 2) {
		glColor3f(0.43, 1, 0.91);
		string selectTower_UI = towerName[1];
		glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)selectTower_UI.c_str());
	}	
	if (CurTower == 3) {
		glColor3f(0.77, 0.32, 1);
		string selectTower_UI = towerName[3];
		glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)selectTower_UI.c_str());
	}	
	if (CurTower == 4) {
		glColor3f(1, 0.55, 0.6);
		string selectTower_UI = towerName[2];
		glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)selectTower_UI.c_str());
	}
	if(CurTower == 0){
		string selectTower_UI = towerName[4];
		glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)selectTower_UI.c_str());
	}


	//Draw Base Tower Button
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, BaseTowerImage);
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0); glVertex2f(120, 180);
	glTexCoord2f(1, 0); glVertex2f(210, 180);
	glTexCoord2f(1, 1.5); glVertex2f(210, 360);
	glTexCoord2f(0, 1.5); glVertex2f(120, 360);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	//Draw SlowTowerButton
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, SlowTowerImage);
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0); glVertex2f(240, 180);
	glTexCoord2f(1, 0); glVertex2f(330, 180);
	glTexCoord2f(1, 1.5); glVertex2f(330, 360);
	glTexCoord2f(0, 1.5); glVertex2f(240, 360);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	//Draw Block Button
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, BlockImage);
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0); glVertex2f(360, 180);
	glTexCoord2f(1, 0); glVertex2f(450, 180);
	glTexCoord2f(1, 1.5); glVertex2f(450, 360);
	glTexCoord2f(0, 1.5); glVertex2f(360, 360);
	glEnd();
	glDisable(GL_TEXTURE_2D);


	//Draw Trap
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, TrapImage);
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0); glVertex2f(480, 180);
	glTexCoord2f(1, 0); glVertex2f(580, 180);
	glTexCoord2f(1, 1.5); glVertex2f(580, 360);
	glTexCoord2f(0, 1.5); glVertex2f(480, 360);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void SpawnEnemy(int value) {
	for (int i = 0; i < MAX_ENEMY_NUM; i++) {
		if (!e[i].isActive) {
			e[i].isDead = false;
			e[i].x = GAMEBOARD_WIDTH;
			e[i].y = rand() % GAMEBOARD_HEIGTH;
			e[i].walkSpeed = rand() % 2 + 1;
			e[i].isActive = true;
			break;
		}
	}
	glutTimerFunc(5000, SpawnEnemy, 0);
}

void GameInit() {
	SpawnEnemy(0);

	isGameOver = false;

	CurTower = 0;

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

	Sprite BaseID("Image/BaseTower.png");
	BaseTowerImage = BaseID.GenTexture();

	Sprite SlowID("Image/SlowTower.png");
	SlowTowerImage = SlowID.GenTexture();

	Sprite TrapID("Image/Trap.png");
	TrapImage = TrapID.GenTexture();

	Sprite BlockID("Image/Block.png");
	BlockImage = BlockID.GenTexture();
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

	// Auto resize window if user change the size 
	//glutReshapeWindow(GRID_SIZE * GAMEBOARD_WIDTH, GRID_SIZE * (GAMEBOARD_HEIGTH + GAMESTORE_HEIGTH));
}

void display() {
	glClearColor(0.5, 0.5, 0.5, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear Screen and Depth Buffer
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//ShowTitleScene
	if (CurScene == 0) {
		TitleScene();
	}
	if (CurScene == 1) {
		//TODO: How to play Scene func;
	}

	//ShowGameScene
	if (CurScene == 2) {
		Draw_UI();

		for (list<Tower*>::iterator it = TowerList->begin(); it != TowerList->end(); ++it) {
			(*it)->DrawBaseTower();
		}

		for (int i = 0; i < MAX_ENEMY_NUM; i++) {
			e[i].DrawEnemy();
		}


		DrawGameBoard();
	}

	glutSwapBuffers();
}

void update(int value) {
	if (CurScene == 2) {
		for (int i = 0; i < MAX_ENEMY_NUM; i++) {
			e[i].update(30.0 / 1000.0);
		}

		for (int i = 0; i < MAX_ENEMY_NUM; i++) {
			if (e[i].x <= -1) {
				CurScene = 3;
			}
		}
	}

	glutPostRedisplay();
	glutTimerFunc(30, update, 0);
}

void FixWindowSize() {
	HWND hwnd = FindWindow(NULL, "Tower Defence");    // Get window HWND
	if (hwnd)
	{
		LONG style;
		style = GetWindowLong(hwnd, GWL_STYLE);              // Get window style
		style &= ~WS_THICKFRAME;                                       // Disable window resizable border
		style &= ~WS_MINIMIZEBOX;                                     // Disable window minimum button
		style &= ~WS_MAXIMIZEBOX;                                    // Disable window maximum button
		SetWindowLong(hwnd, GWL_STYLE, style);                 // Set window style
	}
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

	//Title Scene
	CurScene = 2;
	GameInit();

	// Disable Window Resizing
	FixWindowSize();

	glutMainLoop();                             // run GLUT mainloop
	return(0);                                  // this line is never reached
}
