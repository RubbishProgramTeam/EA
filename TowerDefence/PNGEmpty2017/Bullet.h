#pragma once

#include <iostream>
#include "GL/freeglut.h"

#define _USE_MATH_DEFINES
#include <math.h>
#define GRID_SIZE 30
#define GAMEBOARD_WIDTH 22
#define GAMEBOARD_HEIGTH 6

class Bullet{
public:
	Bullet();
	~Bullet();

public:
	void Draw();

	void update(double dt);

public:
	int bulletType;

	float bulletSpeed;
	float fireTime, fireTimeRate;
	float bPos_x, bPos_y;

	int atk;

	int getCurTower;
};

