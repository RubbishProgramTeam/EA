#pragma once
class Sprite
{
public:
	Sprite();
	~Sprite();
	Sprite(const char* fileName);

public:
	unsigned char *data;
	unsigned int width, height;
	bool hasAlpha;

public:
	int GenTexture();
	void initWithFile(const char* fileName);
};

