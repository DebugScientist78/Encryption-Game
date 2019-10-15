#ifndef IMAGE_H
#define IMAGE_H
#include "main.h"

class Image {
private:
	int x,y;
	int width;
	int height;
	std::string path;
	SDL_Texture* texture;
public:
	Image();
	~Image();

	void setSize(int width, int height);
	void setImgPath(std::string path);
	int* getWidth();
	int* getHeight();
	SDL_Texture* getTexture();

	SDL_Texture* LoadImage(SDL_Renderer* render);
	void renderTexture(SDL_Renderer *ren, int x, int y);
	bool ClickedOn(SDL_Event e);
};

#endif // !IMAGE_H

