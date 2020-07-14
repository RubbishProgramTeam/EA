#include "Bullet.h"

Bullet::Bullet()
{
	isCon = false;
}


Bullet::~Bullet()
{
}

void Bullet::Draw()
{
	if (bPos_x <= GAMEBOARD_WIDTH && !isCon) {
		glBegin(GL_POLYGON);
		if (getCurTower == 1) {
			glColor3f(0, 1, 0);
			bulletType = 1;
			atk = 2;
		}
		else if (getCurTower == 2) {
			glColor3f(0.43, 1, 0.91);
			bulletType = 2;
			atk = 1;
		}
		else {
			return;
		}
		for (int i = 0; i < 360; i++) {
			glVertex2f((5 * cos(i * M_PI / 180.0f)) + (((bPos_x * GRID_SIZE) + ((bPos_x + 1) * GRID_SIZE)) / 2), (5 * sin(i * M_PI / 180.0f)) + (((bPos_y * GRID_SIZE) + ((bPos_y + 1) * GRID_SIZE + 1)) / 2));
		}
		glEnd();
	}
}

void Bullet::update(double dt)
{
	bool isShot;

	//fireTime -= dt;
	bPos_x = bPos_x + (bulletSpeed * dt);

	for (int i = 0; i < 360; i++) {
		glVertex2f((5 * cos(i * M_PI / 180.0f)) + (((bPos_x * GRID_SIZE) + ((bPos_x + 1) * GRID_SIZE)) / 2), (5 * sin(i * M_PI / 180.0f)) + (((bPos_y * GRID_SIZE) + ((bPos_y + 1) * GRID_SIZE + 1)) / 2));
	}
	/*if (fireTime <= 0) {
		isActive = true;
		fireTime = fireTimeRate;
	}*/
}
