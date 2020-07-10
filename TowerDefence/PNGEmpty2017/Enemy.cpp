#include "Enemy.h"

Enemy::Enemy()
{
	isActive = true;
	hp = 1;
	atk = 1;
	x = 2;
	y = rand() % GAMEBOARD_HEIGTH;

	walkSpeed = 1;
}


Enemy::~Enemy()
{
}

void Enemy::DrawEnemy()
{
	if (!isActive) {
		return;
	}
	glBegin(GL_POLYGON);
	glColor3f(1, 0, 0);
	for (int i = 0; i < 360; i++) {
		glVertex2f((13 * cos(i * M_PI / 180.0f)) + (((x * GRID_SIZE) + ((x + 1) * GRID_SIZE)) / 2), (13 * sin(i * M_PI / 180.0f)) + (((y * GRID_SIZE) + ((y + 1) * GRID_SIZE + 1)) / 2));
	}
	glEnd();

}

void Enemy::update(double dt)
{
	if (!isActive) {
		return;
	}

	if (x > -1) {
		x = x - (walkSpeed * dt);
	}
	else {
		walkSpeed = 0;
		isActive = false;
	}
}
