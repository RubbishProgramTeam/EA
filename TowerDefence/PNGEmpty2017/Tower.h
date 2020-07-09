#include "GL/freeglut.h"
#define _USE_MATH_DEFINES
#include <math.h>
#define GRID_SIZE 30

class Tower
{
public:
	Tower();
	~Tower();

public:
	void DrawBaseTower(int x, int y, float hp, int atk);
	void DrawSlowTower(int x, int y, float hp, int atk);
	void DrawBlock(int x, int y, float hp, int atk);
	void DrawTrap(int x, int y, float hp, int atk);

	void Damage(int d, float hp);
public:
	bool isActive;
	int radius;
	float hp;
	int atk;
};
