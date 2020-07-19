#pragma once

class BaseTower
{
public:
	BaseTower();
	~BaseTower();

public:
	void DrawBaseTower(int x, int y);
	void DrawSlowTower(int x, int y);
	void DrawBlock(int x, int y);
	void DrawTrap(int x, int y);

};

