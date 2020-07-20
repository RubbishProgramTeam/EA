#include <iostream>
#include "GL/freeglut.h"
#include <string>
#include "Sprite.h"

using namespace std;

//User define
#include "Tower.h"
#include "Enemy.h"
#include "Bullet.h"
#include <playsoundapi.h>

#include <chrono>
#include <ctime>

#include <list>
#include <stdlib.h>
#include <time.h>

#include <playsoundapi.h>

#define _USE_MATH_DEFINES
#include <math.h>
#define GRID_SIZE 30
#define GAMESTORE_HEIGTH 4
#define GAMEBOARD_WIDTH 22
#define GAMEBOARD_HEIGTH 6
#define MAX_TOWER_NUM 114
#define MIN_MONEY 0
#define MAX_ENEMY_NUM 100
#define MAX_BULLET_NUM 999
#define SPACEBAR 32

//User public

GLuint BaseTowerImage;
GLuint SlowTowerImage;
GLuint BlockImage;
GLuint TrapImage;
GLuint FlowerImage;
GLuint ClearImage;
GLuint GameOverImage;

int mouse_x;
int mouse_y;

int CurTower = 0;

int GameBoard[GRID_SIZE * GAMEBOARD_WIDTH][GRID_SIZE * GAMEBOARD_HEIGTH];

int money;
float autoAddMoney, AddMoneyRate;

int towerMoney;

bool isFirst = true;
bool isClear;
bool isInside;

int CurScene;

float gameStart;

int enemySpawnTime;

int score;
//CurScene = 0 //Title Scene
//CurScene = 1 //How To Play Scene
//CurScene = 2 //Game Scene
//CurScene = 3 //GameOver Scene

Tower t[MAX_TOWER_NUM];
list<Tower*> *TowerList;

Enemy e[MAX_ENEMY_NUM];
list<Enemy*> *EnemyList;

void GameInit() {

	isClear = false;

	gameStart = 0;

	score = 0;

	CurTower = 0;

	towerMoney = 0;

	money = 75;

	autoAddMoney = 10.0;
	AddMoneyRate = 10.0;
	autoAddMoney = AddMoneyRate;

	TowerList = new list<Tower*>();

	EnemyList = new list<Enemy*>();

	for (int i = 0; i < MAX_TOWER_NUM; i++) {
		t[i].isActive = false;
		for (int j = 0; j < GAMEBOARD_HEIGTH; j++) {
			GameBoard[i][j] = 0;
			//GameBoard[i][j] = 0; emtry
			//GameBoard[i][j] = 1; HaveThing
		}
	}

	for (int i = 0; i < MAX_ENEMY_NUM; i++) {
		e[i].isActive = false;
	}

	Sprite BaseID("Image/BaseTower.png");
	BaseTowerImage = BaseID.GenTexture();

	Sprite SlowID("Image/SlowTower.png");
	SlowTowerImage = SlowID.GenTexture();

	Sprite TrapID("Image/Trap.png");
	TrapImage = TrapID.GenTexture();

	Sprite BlockID("Image/Block.png");
	BlockImage = BlockID.GenTexture();

	Sprite FlowerID("Image/sunflower.png");
	FlowerImage = FlowerID.GenTexture();

	Sprite ClearID("Image/Del.png");
	ClearImage = ClearID.GenTexture();

	Sprite GameOverID("Image/GameOver.png");
	GameOverImage = GameOverID.GenTexture();
}

void TitleScene() {
	// Title
	glColor3f(1, 0, 0);
	glRasterPos2f(250, 200);
	string TitleStr = "Tower Defense";
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)TitleStr.c_str());

	// Press space key to start string 
	glColor3f(0, 0, 0);
	glRasterPos2f( 220, 100);
	string StartStr = "Press space key to start";
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)StartStr.c_str());

	// Press h key to see how to play string
	glColor3f(0, 0, 0);
	glRasterPos2f(200, 50);
	string HowToPlayStr = "Press H key to see how to play";
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)HowToPlayStr.c_str());
	
	// Background
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, BaseTowerImage);
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0); glVertex2f(80, 150);
	glTexCoord2f(1, 0); glVertex2f(170, 150);
	glTexCoord2f(1, 1); glVertex2f(170, 250);
	glTexCoord2f(0, 1); glVertex2f(80, 250);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, BlockImage);
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0); glVertex2f(480, 150);
	glTexCoord2f(1, 0); glVertex2f(570, 150);
	glTexCoord2f(1, 1); glVertex2f(570, 250);
	glTexCoord2f(0, 1); glVertex2f(480, 250);
	glEnd();
	glDisable(GL_TEXTURE_2D);

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
	glColor3f(0, 0, 0);
	glRasterPos2f(260, 270);
	string HowToPlay = "How To Play";
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)HowToPlay.c_str());
	glRasterPos2f(5, 250);
	string HowToPlay_Content = "At the beginning of the game the player will have 75 dollars. Players can \nuse money to buy plants and choose where these plants appear in their own \nland (The yellow area is your own land). These plants will assist the player \nagainst the enemy. The enemy will appear to the right of the interface, attacking \nfrom right to left. The more the player successfully resists, the higher the score \nwill be. The game will end when the player can't resist the enemy's attack.";
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)HowToPlay_Content.c_str());
	glRasterPos2f(230, 44);
	string BackToTitle = "Back to title scene";
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)BackToTitle.c_str());

	if (isInside) {
		glColor3f(1, 0, 0);
	}
	else {
		glColor3f(0, 1, 0);
	}
	glBegin(GL_POLYGON);
	glVertex2f(225, 70);
	glVertex2f(387, 70);
	glVertex2f(387, 30);
	glVertex2f(225, 30);
	glEnd();

	glColor3f(1, 0.89, 0.25);
	glBegin(GL_POLYGON);
	glVertex2f(0, 0);
	glVertex2f(0, GRID_SIZE * (GAMEBOARD_HEIGTH + GAMESTORE_HEIGTH));
	glVertex2f(GRID_SIZE * GAMEBOARD_WIDTH, GRID_SIZE * (GAMEBOARD_HEIGTH + GAMESTORE_HEIGTH));
	glVertex2f(GRID_SIZE * GAMEBOARD_WIDTH, 0);
	glEnd();
}

void GameOverScene() {
	glColor3f(1, 1, 0);
	glRasterPos2f(195, 150);
	string GameTimeUI = "Game Finish Time: " + to_string(gameStart);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)GameTimeUI.c_str());

	glColor3f(1, 0.5, 0.25);
	glRasterPos2f(285, 120);
	string ScoreUI = "Score: " + to_string(score);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)ScoreUI.c_str());

	glColor3f(0, 0, 0);
	glRasterPos2f(245, 20);
	string BackToTitle = "Back to title scene";
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)BackToTitle.c_str());

	if (isInside) {
		glColor3f(0, 1, 1);
	}
	else {
		glColor3f(0, 1, 0);
	}
	glBegin(GL_POLYGON);
	glVertex2f(240, 45);
	glVertex2f(402, 45);
	glVertex2f(402, 5);
	glVertex2f(240, 5);
	glEnd();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, GameOverImage);
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0); glVertex2f(0, 0);
	glTexCoord2f(0, 1); glVertex2f(0, GRID_SIZE * (GAMEBOARD_HEIGTH + GAMESTORE_HEIGTH));
	glTexCoord2f(1, 1); glVertex2f(GRID_SIZE * GAMEBOARD_WIDTH, GRID_SIZE * (GAMEBOARD_HEIGTH + GAMESTORE_HEIGTH));
	glTexCoord2f(1, 0); glVertex2f(GRID_SIZE * GAMEBOARD_WIDTH, 0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
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

void Draw_UI() {
	//What Tower Selected
	string towerName[7] = { "Base Tower", "Slow Tower", "Road Block", "Trap" , "Not Select", "Money Tower", "Clear Plant" };

	glColor3f(1, 1, 0);
	glRasterPos2f(5, 270);
	string money_UI = "Money:" + to_string(money);
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)money_UI.c_str());

	glColor3f(0, 0, 0);
	glRasterPos2f(5, 240);
	string selectTower = "Selection: ";
	glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)selectTower.c_str());

	glRasterPos2f(5, 220);
	if (CurTower == 1) {
		string selectTower_UI = towerName[0];
		glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)selectTower_UI.c_str());
	}
	if (CurTower == 2) {
		string selectTower_UI = towerName[1];
		glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)selectTower_UI.c_str());
	}
	if (CurTower == 3) {
		string selectTower_UI = towerName[3];
		glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)selectTower_UI.c_str());
	}
	if (CurTower == 4) {
		string selectTower_UI = towerName[2];
		glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)selectTower_UI.c_str());
	}
	if (CurTower == 5) {
		string selectTower_UI = towerName[5];
		glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)selectTower_UI.c_str());
	}
	if (CurTower == 6) {
		string selectTower_UI = towerName[6];
		glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)selectTower_UI.c_str());
	}
	if (CurTower == 0) {
		string selectTower_UI = towerName[4];
		glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)selectTower_UI.c_str());
	}

	//Tower Money
	glRasterPos2f(5, 200);
	if (CurTower == 1) {
		string selectTowerMoney_UI = "$ " + to_string(towerMoney);
		glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)selectTowerMoney_UI.c_str());
	}
	if (CurTower == 2) {
		string selectTowerMoney_UI = "$ " + to_string(towerMoney);
		glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)selectTowerMoney_UI.c_str());
	}
	if (CurTower == 3) {
		string selectTowerMoney_UI = "$ " + to_string(towerMoney);
		glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)selectTowerMoney_UI.c_str());
	}
	if (CurTower == 4) {
		string selectTowerMoney_UI = "$ " + to_string(towerMoney);
		glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)selectTowerMoney_UI.c_str());
	}
	if (CurTower == 5) {
		string selectTowerMoney_UI = "$ " + to_string(towerMoney);
		glutBitmapString(GLUT_BITMAP_HELVETICA_18, (const unsigned char*)selectTowerMoney_UI.c_str());
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
	glTexCoord2f(0, 0); glVertex2f(210, 180);
	glTexCoord2f(1, 0); glVertex2f(300, 180);
	glTexCoord2f(1, 1.5); glVertex2f(300, 360);
	glTexCoord2f(0, 1.5); glVertex2f(210, 360);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	//Draw Block Button
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, BlockImage);
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0); glVertex2f(300, 180);
	glTexCoord2f(1, 0); glVertex2f(390, 180);
	glTexCoord2f(1, 1.5); glVertex2f(390, 360);
	glTexCoord2f(0, 1.5); glVertex2f(300, 360);
	glEnd();
	glDisable(GL_TEXTURE_2D);


	//Draw Trap
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, TrapImage);
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0); glVertex2f(390, 180);
	glTexCoord2f(1, 0); glVertex2f(480, 180);
	glTexCoord2f(1, 1.5); glVertex2f(480, 360);
	glTexCoord2f(0, 1.5); glVertex2f(390, 360);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	//Add Money Tower
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, FlowerImage);
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0); glVertex2f(480, 180);
	glTexCoord2f(1, 0); glVertex2f(570, 180);
	glTexCoord2f(1, 1.5); glVertex2f(570, 360);
	glTexCoord2f(0, 1.5); glVertex2f(480, 360);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, ClearImage);
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0); glVertex2f(570, 180);
	glTexCoord2f(1, 0); glVertex2f(670, 180);
	glTexCoord2f(1, 1); glVertex2f(670, 265);
	glTexCoord2f(0, 1); glVertex2f(570, 265);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

double fRand(float fMin, float fMax)
{
	float f = (float)rand() / RAND_MAX;
	return fMin + f * (fMax - fMin);
}

void SpawnEnemy(int value) {
	Enemy *newEnemy = new Enemy();

	newEnemy->isDead = false;
	newEnemy->isTouch = false;
	newEnemy->isSlow = false;

	newEnemy->slowTimerRate = 5;
	newEnemy->slowSpeed = 0.5;

	newEnemy->hp = rand() % 10 + 8;
	newEnemy->maxHP = newEnemy->hp;

	newEnemy->perHP = newEnemy->hp / newEnemy->maxHP;

	newEnemy->atk = 1;

	newEnemy->damageTimer = 0;
	newEnemy->damageTimerRate = 1;

	newEnemy->x = GAMEBOARD_WIDTH;
	newEnemy->y = rand() % GAMEBOARD_HEIGTH;
	newEnemy->walkSpeed = fRand(0.8, 1);
	newEnemy->isActive = true;

	EnemyList->push_back(newEnemy);

	glutTimerFunc(enemySpawnTime, SpawnEnemy, 0);
}

void mouseClick(int button, int state, int x, int y) {

	if (CurScene == 0) {

	}
	//HowToPlayScene
	if (CurScene == 1) {
		if (x >= 225 && x <= 387 && y >= 230 && y <= 268) {
			//Back to title scene button
			CurScene = 0;
		}
	}

	if (CurScene == 3) {
		if (x >= 225 && x <= 387 && y >= 253 && y <= 289) {
			//Back to title scene button
			CurScene = 0;
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
				if (!isClear && GameBoard[mouse_x][mouse_y] != 0) {
					MessageBox(NULL, "Please choose other grid!", "Ops!", MB_OK | MB_ICONERROR);
					return;
				}

				Tower *newTower = new Tower();

				if (money >= towerMoney && CurTower != 0) {
					newTower->x = mouse_x;
					newTower->y = mouse_y;

					newTower->perHP = newTower->hp / newTower->MaxHP;

					newTower->CurTower = CurTower;
					if (CurTower == 1) {
						//Base Tower
						newTower->hp = 5.0;
						newTower->atk = 2;
						newTower->fire = 1;
						newTower->fireRate = 5;
						newTower->addMoney = NULL;
						newTower->MaxHP = newTower->hp;
					}
					else if (CurTower == 2) {
						//SlowTower
						newTower->hp = 5.0;
						newTower->atk = 1;
						newTower->fire = 1;
						newTower->fireRate = 3;
						newTower->addMoney = NULL;
						newTower->MaxHP = newTower->hp;
					}
					else if (CurTower == 3) {
						//Trap
						newTower->hp = 1.0;
						newTower->atk = 7;
						newTower->addMoney = NULL;
						newTower->MaxHP = newTower->hp;
					}
					else if (CurTower == 4) {
						//Road Block
						newTower->hp = 15.0;
						newTower->atk = 0;
						newTower->addMoney = NULL;
						newTower->MaxHP = newTower->hp;
					}
					else if (CurTower == 5) {
						//Add Money Tower
						newTower->hp = 5.0;
						newTower->atk = 0;
						newTower->MaxHP = newTower->hp;
						newTower->addMoney = 8;
						newTower->addMoneyRate = newTower->addMoney;
					}

					newTower->damageTimeRate = 2;
					newTower->damageTime = 0;

					money -= towerMoney;

					newTower->isActive = true;

					TowerList->push_back(newTower);

					GameBoard[mouse_x][mouse_y] = 1;

					if (isClear && GameBoard[mouse_x][mouse_y] != 0) {
						GameBoard[mouse_x][mouse_y] = 0;
						isClear = false;
						CurTower = 0;
						return;
					}
				}
				else if (money <= towerMoney) {
					MessageBox(NULL, "You don't gave enough money!", "Ops!", MB_OK | MB_ICONEXCLAMATION);
					return;
				}
			}
		}


		if (mouse_x < GAMEBOARD_WIDTH && mouse_y <= (GAMEBOARD_HEIGTH + GAMESTORE_HEIGTH) && mouse_y > GAMEBOARD_HEIGTH) {
			//store area

			if (mouse_x >= 4 && mouse_x <= 6 && mouse_y >= 6 && mouse_y <= 9) {
				//Base Tower
				CurTower = 1;
				towerMoney = 100;
			}
			if (mouse_x >= 7 && mouse_x <= 9 && mouse_y >= 6 && mouse_y <= 9) {
				//SlowTower
				CurTower = 2;
				towerMoney = 160;
			}
			if (mouse_x >= 10 && mouse_x <= 12 && mouse_y >= 6 && mouse_y <= 9) {
				//Block
				CurTower = 4;
				towerMoney = 50;
			}
			if (mouse_x >= 13 && mouse_x <= 15 && mouse_y >= 6 && mouse_y <= 9) {
				//Trap
				CurTower = 3;
				towerMoney = 95;
			}			
			if (mouse_x >= 16 && mouse_x <= 18 && mouse_y >= 6 && mouse_y <= 9) {
				//SunFlower
				CurTower = 5;
				towerMoney = 25;
			}			
			if (mouse_x >= 19 && mouse_x <= 21 && mouse_y >= 6 && mouse_y <= 9) {
				//DelPlant
				CurTower = 6;
				towerMoney = 0;
				isClear = true;
			}
		}
	}
}

void keyboardClick(unsigned char key, int x, int y) {
	if (CurScene == 0) {
		if (key == SPACEBAR) {
			CurScene = 2;
			if (isFirst) {
				glutTimerFunc(10000, SpawnEnemy, 0);
				isFirst = false;
			}
			else {
				SpawnEnemy(0);
			}
		}
		else if (key == 'h') {
			CurScene = 1;
		}
	}
}

void AutoAddMoney(double dt) {
	if (autoAddMoney > 0) {
		autoAddMoney -= dt;
	}
	else if (autoAddMoney <= 0) {
		money += 25;
		autoAddMoney = AddMoneyRate;
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
	// Show How to play scene
	if (CurScene == 1) {
		//TODO: How to play Scene func;
		HowToPlayScene();
	}

	//ShowGameScene
	if (CurScene == 2) {
		Draw_UI();

		for (list<Tower*>::iterator it = TowerList->begin(); it != TowerList->end(); ++it) {
			(*it)->DrawBullet();
		}

		for (list<Tower*>::iterator it = TowerList->begin(); it != TowerList->end(); ++it) {
			if (GameBoard[(*it)->x][(*it)->y] != 0) {
				(*it)->DrawBaseTower();
			}
			else {
				(*it)->isActive = false;
			}
		}

		for (list<Enemy*>::iterator it = EnemyList->begin(); it != EnemyList->end(); ++it) {
			(*it)->DrawEnemy();
		}

		DrawGameBoard();
	}
	if (CurScene == 3) {
		GameOverScene();
	}
	glutSwapBuffers();
}

void update(int value) {

	if (CurScene == 0) {
		GameInit();
	}

	if (CurScene == 2) {
		gameStart += (30.0 / 1000.0);
		if (gameStart >= 90) {
			enemySpawnTime = 3000;
		}		
		else if (gameStart >= 50) {
			enemySpawnTime = 5000;
		}		
		else if (gameStart >= 30) {
			enemySpawnTime = 7000;
		}
		else if (gameStart < 30) {
			enemySpawnTime = 10000;
		}
		AutoAddMoney(30.0 / 1000.0);
		bool isCon = false;

		for (list<Enemy*>::iterator it = EnemyList->begin(); it != EnemyList->end(); ++it) {
			(*it)->update(30.0/1000.0);
			if ((*it)->x <= -1) {
				//GameOver
				CurScene = 3;
			}

			if ((*it)->hp <= 0) {
				(*it)->isDead = true;
				isCon = false;
				EnemyList->remove(*it);
				score += 10;
				break;
			}
		}

		for (list<Enemy*>::iterator eit = EnemyList->begin(); eit != EnemyList->end(); ++eit) {
			isCon = false;
			for (list<Tower*>::iterator tit = TowerList->begin(); tit != TowerList->end(); ++tit) {
				if ((*tit)->y == (*eit)->y && (*eit)->x > (*tit)->x) {
					//Tower distance		
					//(*tit)->d = sqrtf((((*eit)->x - (*tit)->x) * ((*eit)->x - (*tit)->x)) + (((*eit)->y - (*tit)->y) * ((*eit)->y - (*tit)->y)));
					(*tit)->d = (*eit)->x - (*tit)->x;

					//Bullet distance
					(*tit)->d2 = (*eit)->x - (*tit)->bPos_x;

					if ((*tit)->d2 <= 1) {
						(*eit)->Damage((*tit)->atk);
						(*tit)->bPos_x = (*tit)->x;
						if ((*tit)->CurTower == 2) {
							(*eit)->isSlow = true;
						}
						(*tit)->DestroyBullet();
					}

					if ((*tit)->d <= 1) {
						isCon = true;
						(*eit)->isTouch = true;
						if ((*tit)->CurTower == 3) {
							(*eit)->isDead = true;
						}					
						(*tit)->Damage((*eit)->atk);					
					}
				}
			}
			if (!isCon) {
				(*eit)->isTouch = false;
			}
		}

		for (list<Tower*>::iterator tit = TowerList->begin(); tit != TowerList->end(); ++tit) {
			(*tit)->update(30.0 / 1000.0);

			if ((*tit)->addMoney != NULL) {
				if ((*tit)->addMoney <= 0) {
					money += 25;
					(*tit)->addMoney = (*tit)->addMoneyRate;
				}
			}

			if ((*tit)->x > GAMEBOARD_WIDTH) {
				(*tit)->DestroyBullet();
			}

			if ((*tit)->hp == 0) {
				GameBoard[(*tit)->x][(*tit)->y] = 0;
				TowerList->remove((*tit));
				break;
			}
		}
	}

	glutPostRedisplay();
	glutTimerFunc(25, update, 0);
}
void mouseMove(int x, int y) {
	if (CurScene == 1) {
		if (x >= 225 && x <= 387 && y >= 230 && y <= 268) {
			//Back to title scene button
			isInside = true;
		}
		else {
			isInside = false;
		}
	}

	if (CurScene == 3) {
		cout << x << " " << y << endl;
		if (x >= 240 && x <= 402 && y >= 253 && y <= 289) {
			//Back to title scene button
			isInside = true;
		}
		else {
			isInside = false;
		}
	}

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
	cout << "Programmer: <Tower Defence>\n";
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
	glutTimerFunc(25, update, 0);
	glutDisplayFunc(display);                   // Display function

	glutMouseFunc(mouseClick);
	glutPassiveMotionFunc(mouseMove);
	glutKeyboardFunc(keyboardClick);

	//Title Scene 
	CurScene = 0;

	// BGM Player (audio must be .wav format)
	PlaySound("media/Markvard - Perfect Day", NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);

	// Disable Window Resizing
	FixWindowSize();

	glutMainLoop();                             // run GLUT mainloop
	return(0);                                  // this line is never reached
}
