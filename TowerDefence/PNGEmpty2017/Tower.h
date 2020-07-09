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
	void DrawBaseTower(int x, int y);

public:
	bool isActive;
	int radius;
};
