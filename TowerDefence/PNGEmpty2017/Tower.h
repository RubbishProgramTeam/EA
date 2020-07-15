#pragma once

#include <iostream>
#include "GL/freeglut.h"
#include <string>
#include "Sprite.h"
#include "Bullet.h"
#include "Enemy.h"

#include <list>
#define _USE_MATH_DEFINES
#include <math.h>
#define GRID_SIZE 30
#define GAMEBOARD_WIDTH 22
#define GAMEBOARD_HEIGTH 6
#define MAX_BULLET_NUM 100

using namespace std;

class Tower
{
public:
	Tower();
	~Tower();

public:
	void DrawBaseTower();
	void Damage(int d);

	void DrawBullet();
	void DestroyBullet();

	void update(double dt);
public:
	//Tower
	bool isActive;
	bool canDamage;
	float damageTime;
	float damageTimeRate;

	int radius;

	int x, y;
	int CurTower;

	float hp;
	float MaxHP;
	int hpBar;
	float perHP;
	int atk;

	float addMoney, addMoneyRate;

	float d, d2;

	//Bullet
	Bullet b[MAX_BULLET_NUM];
	list<Bullet*> *BulletList;

	float bPos_x;
	float bPos_y;

	float fire;
	float fireRate;
};
