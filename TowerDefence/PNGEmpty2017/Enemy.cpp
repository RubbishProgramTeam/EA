#include "Enemy.h"

Enemy::Enemy()
{
	hp = 1;
	atk = 1;

	walkSpeed = 1;
	isActive = true;
	isDead = false;
}


Enemy::~Enemy()
{
}

void Enemy::DrawEnemy()
{
	if (!isActive) return;

	glBegin(GL_POLYGON);
	glColor3f(1, 0, 0);
	for (int i = 0; i < 360; i++) {
		glVertex2f((13 * cos(i * M_PI / 180.0f)) + (((x * GRID_SIZE) + ((x + 1) * GRID_SIZE)) / 2), (13 * sin(i * M_PI / 180.0f)) + (((y * GRID_SIZE) + ((y + 1) * GRID_SIZE + 1)) / 2));
	}
	glEnd();

}

void Enemy::update(double dt)
{
	if (!isActive) return;

	if (!isDead) {
		if (x > -1) 
			x = x - (walkSpeed * dt);
	}
	else {
		isActive = false;
	}
}
