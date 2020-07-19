#include "Sprite.h"
#include <fstream>
#include <iostream>
#include "GL\freeglut.h"
#include "png.h"

using namespace std;

Sprite::Sprite()
{
}


Sprite::~Sprite()
{
}


Sprite::Sprite(const char* fileName) {
	initWithFile(fileName);
}

int Sprite::GenTexture() {
	GLuint textureID;

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	glTexImage2D(GL_TEXTURE_2D, 0, hasAlpha ? 4 : 3, width, height, 0, hasAlpha ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);

	return textureID;
}

void Sprite::initWithFile(const char* fileName) {
	FILE *fp;
	png_structp png_ptr;
	png_infop info_ptr;
	unsigned int sig_read = 0;
	int color_type, interlace_type;

	fopen_s(&fp, fileName, "rb");
	if (!fp) {
		cout << "File not found." << endl;
		return;
	}

	png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING,
		NULL, NULL, NULL);

	info_ptr = png_create_info_struct(png_ptr);

	png_init_io(png_ptr, fp);
	png_set_sig_bytes(png_ptr, sig_read);

	png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_STRIP_16 | PNG_TRANSFORM_PACKING | PNG_TRANSFORM_EXPAND, NULL);

	int bit_depth;
	png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type,
		&interlace_type, NULL, NULL);

	hasAlpha = (color_type == PNG_COLOR_TYPE_RGBA);

	unsigned int row_bytes = png_get_rowbytes(png_ptr, info_ptr);
	data = (unsigned char*)malloc(row_bytes * height);

	png_bytepp row_pointers = png_get_rows(png_ptr, info_ptr);

	for (int i = 0; i < (int)height; i++) {
		memcpy(data + (row_bytes * (height - 1 - i)), row_pointers[i], row_bytes);
	}

	png_destroy_read_struct(&png_ptr, &info_ptr, NULL);

	fclose(fp);
}


