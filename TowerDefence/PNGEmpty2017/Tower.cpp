#include "Tower.h"

Tower::Tower()
{
	isActive = true;
	radius = 13;
	hp = 1;
	atk = 1;
}

Tower::~Tower()
{
}

void Tower::DrawBaseTower(int x, int y, float hp, int atk)
{
	if (!isActive) {
		return;
	}

	glBegin(GL_POLYGON);
	glColor3f(0, 1, 0);
	for (int i = 0; i < 360; i++) {
		glVertex2f((radius * cos(i * M_PI / 180.0f)) + (((x * GRID_SIZE) + ((x + 1) * GRID_SIZE)) / 2), (radius * sin(i * M_PI / 180.0f)) + (((y * GRID_SIZE) + ((y + 1) * GRID_SIZE + 1)) / 2));
	}
	glEnd();
}

void Tower::DrawSlowTower(int x, int y, float hp, int atk)
{
	if (!isActive) {
		return;
	}

	glBegin(GL_POLYGON);
	glColor3f(0.5, 0.5, 1);
	for (int i = 0; i < 360; i++) {
		glVertex2f((radius * cos(i * M_PI / 180.0f)) + (((x * GRID_SIZE) + ((x + 1) * GRID_SIZE)) / 2), (radius * sin(i * M_PI / 180.0f)) + (((y * GRID_SIZE) + ((y + 1) * GRID_SIZE + 1)) / 2));
	}
	glEnd();
}

void Tower::DrawBlock(int x, int y, float hp, int atk)
{
	if (!isActive) {
		return;
	}

	glBegin(GL_POLYGON);
	glColor3f(0, 1, 0);
	for (int i = 0; i < 360; i++) {
		glVertex2f((radius * cos(i * M_PI / 180.0f)) + (((x * GRID_SIZE) + ((x + 1) * GRID_SIZE)) / 2), (radius * sin(i * M_PI / 180.0f)) + (((y * GRID_SIZE) + ((y + 1) * GRID_SIZE + 1)) / 2));
	}
	glEnd();
}

void Tower::DrawTrap(int x, int y, float hp, int atk)
{
	if (!isActive) {
		return;
	}

	glBegin(GL_POLYGON);
	glColor3f(0, 1, 0);
	for (int i = 0; i < 360; i++) {
		glVertex2f((radius * cos(i * M_PI / 180.0f)) + (((x * GRID_SIZE) + ((x + 1) * GRID_SIZE)) / 2), (radius * sin(i * M_PI / 180.0f)) + (((y * GRID_SIZE) + ((y + 1) * GRID_SIZE + 1)) / 2));
	}
	glEnd();
}

void Tower::Damage(int d, float hp)
{
	hp -= d;
	
}
