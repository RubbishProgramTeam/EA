#include "Tower.h"

Tower::Tower()
{
	isActive = true;
	radius = 15;
}

Tower::~Tower()
{
}

void Tower::DrawBaseTower(int x, int y)
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
