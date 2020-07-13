#include "GL/freeglut.h"

#define _USE_MATH_DEFINES
#include <math.h>

#define GAMEBOARD_WIDTH 22
#define GAMEBOARD_HEIGTH 6
#define GRID_SIZE 30
#define MAX_ENEMY_NUM 20

class Enemy
{
public:
	Enemy();
	~Enemy();

public:
	void DrawEnemy();
	void update(double dt);

public:
	float x, y;

	int hp, atk;

	int walkSpeed;
	bool isActive;
	bool isDead;

	//Enemy list
	//cal distance tower to enemy to check is atk(2-point distance)
};

