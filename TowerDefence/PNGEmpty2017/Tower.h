#include <iostream>
#include "GL/freeglut.h"

#define _USE_MATH_DEFINES
#include <math.h>
#define GRID_SIZE 30
#define GAMEBOARD_WIDTH 22
#define GAMEBOARD_HEIGTH 6

class Tower
{
public:
	Tower();
	~Tower();

public:
	void DrawBaseTower();
	void Damage(int d);
	void DrawBullet();

	void update(double dt);
public:
	bool isActive;
	bool isShot;

	bool canDamage;
	float damageTime;
	float damageTimeRate;

	int radius;

	int x, y;
	int CurTower;

	float hp;
	float MaxHP;

	int atk;
	int bulletType;
	float bulletSpeed;

	float fireTime, fireTimeRate;

	float bPos_x, bPos_y;

	int hpBar;
	float perHP;
};
