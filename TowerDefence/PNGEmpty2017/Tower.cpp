#include "Tower.h"

Tower::Tower()
{
	isActive = true;
	radius = 13;
}
Tower::~Tower()
{
}

void Tower::DrawBaseTower()
{
	if (!isActive) {
		return;
	}

	if (CurTower == 0) {
		return;
	}


	if (CurTower == 1) { //BaseTower
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
		glColor3f(0, 1, 0);
		for (int i = 0; i < 360; i++) {
			glVertex2f((radius * cos(i * M_PI / 180.0f)) + (((x * GRID_SIZE) + ((x + 1) * GRID_SIZE)) / 2), (radius * sin(i * M_PI / 180.0f)) + (((y * GRID_SIZE) + ((y + 1) * GRID_SIZE + 1)) / 2));
		}
		glEnd();
	}
	else if (CurTower == 2) { //SlowTower
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
		glColor3f(0.43, 1, 0.91);
		for (int i = 0; i < 360; i++) {
			glVertex2f((radius * cos(i * M_PI / 180.0f)) + (((x * GRID_SIZE) + ((x + 1) * GRID_SIZE)) / 2), (radius * sin(i * M_PI / 180.0f)) + (((y * GRID_SIZE) + ((y + 1) * GRID_SIZE + 1)) / 2));
		}
		glEnd();
	}
	else if (CurTower == 3) { //Trap
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
		glColor3f(1, 0.55, 0.6);
		for (int i = 0; i < 360; i+=90) {
			glVertex2f((radius * cos(i * M_PI / 180.0f)) + (((x * GRID_SIZE) + ((x + 1) * GRID_SIZE)) / 2), (radius * sin(i * M_PI / 180.0f)) + (((y * GRID_SIZE) + ((y + 1) * GRID_SIZE + 1)) / 2));
		}
		glEnd();
	}
	else if (CurTower == 4) { //Block
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
		glColor3f(0.77, 0.32, 1);
		for (int i = 0; i < 360; i += 72) {
			glVertex2f((radius * cos(i * M_PI / 180.0f)) + (((x * GRID_SIZE) + ((x + 1) * GRID_SIZE)) / 2), (radius * sin(i * M_PI / 180.0f)) + (((y * GRID_SIZE) + ((y + 1) * GRID_SIZE + 1)) / 2));
		}		
		glEnd();
	}
}


void Tower::Damage(int d)
{
	if (damageTime <= 0) {
		hp -= d;
		damageTime = damageTimeRate;
	}
}

void Tower::update(double dt)
{
	if (!isActive) {
		return;
	}
	if (hp <= 0) {
		isActive = false;
	}

	perHP = hp / MaxHP;

	hpBar = (x * GRID_SIZE) + (GRID_SIZE * perHP);

	if (damageTime > 0) {
		damageTime -= dt;
	}

	//TODO: SHOT BULLET
}
