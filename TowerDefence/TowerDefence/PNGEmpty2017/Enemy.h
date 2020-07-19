
#pragma once

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
	void Damage(int d);

	void update(double dt);

public:
	float x, y;

	float hp, maxHP, perHP;
	int hpBar;

	int atk;
	float walkSpeed;

	bool isActive;
	bool isDead;
	bool isTouch;

	float damageTimer, damageTimerRate;

	float slowSpeed;
	float slowTimer, slowTimerRate;
	bool isSlow;
};

