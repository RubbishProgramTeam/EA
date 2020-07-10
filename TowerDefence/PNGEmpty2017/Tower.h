#include <iostream>
#include "GL/freeglut.h"
#define _USE_MATH_DEFINES
#include <math.h>
#define GRID_SIZE 30

class Tower
{
public:
	Tower();
	~Tower();

public:
	void DrawBaseTower();
	void Damage(int d);

	void update(double dt);
public:
	bool isActive;

	bool canDamage;
	float damageTime;
	float damageTimeRate;

	int radius;

	int x, y;
	int CurTower;

	int hp;
	int atk;
	int towerNum;
};
