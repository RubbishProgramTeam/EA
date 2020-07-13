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
