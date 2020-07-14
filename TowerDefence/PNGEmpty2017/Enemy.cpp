#include "Enemy.h"

Enemy::Enemy()
{
}


Enemy::~Enemy()
{
}

void Enemy::DrawEnemy()
{
	if (!isActive) return;

	glColor3f(0, 1, 0);
	glBegin(GL_POLYGON);
	glVertex2f(x * GRID_SIZE, y * GRID_SIZE);
	glVertex2f(x * GRID_SIZE, y * GRID_SIZE + 5);
	glVertex2f(hpBar, y * GRID_SIZE + 5);
	glVertex2f(hpBar, y * GRID_SIZE);
	glEnd();

	glBegin(GL_POLYGON);
	glColor3f(1, 0, 0);
	glVertex2f(x * GRID_SIZE, y * GRID_SIZE);
	glVertex2f(x * GRID_SIZE, y * GRID_SIZE + 5);
	glVertex2f((x + 1) * GRID_SIZE, y * GRID_SIZE + 5);
	glVertex2f((x + 1) * GRID_SIZE, y * GRID_SIZE);
	glEnd();

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

	if (!isSlow) {
		slowTimer = slowTimerRate;
	}

	if (hp <= 0) {
		isDead = true;
	}

	if (!isDead) {
		perHP = hp / maxHP;

		hpBar = (x * GRID_SIZE) + (GRID_SIZE * perHP);

		if (x > -1 && !isTouch && !isSlow)
			x = x - (walkSpeed * dt);

		if (x > -1 && !isTouch && isSlow && slowTimer > 0) {
			slowTimer -= dt;
			x = x - (walkSpeed * slowSpeed * dt);
		}
	}
	else {
		isActive = false;
	}
}
