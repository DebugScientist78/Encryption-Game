#ifndef IMAGE_H
#define IMAGE_H
#include "main.h"

class Image {
private:
	std::string path;
	SDL_Rect rect;
public:
	Image();

	void setSize(int width, int height);
	void setCords(int x, int y);
	void setImgPath(std::string path);
	int getWidth();
	int getHeight();
	SDL_Rect getRect();

	SDL_Texture* LoadImage(SDL_Renderer* render);
	void renderTexture(SDL_Texture *tex, SDL_Renderer *ren);
	bool ClickedOn(SDL_Event e);
};

#endif // !IMAGE_H

