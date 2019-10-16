#include "../include/main.h"

Image::Image()
{
	rect.h = 0;
	rect.w = 0;
	rect.x = 0;
	rect.y = 0;
}

void Image::setSize(int width, int height) {
	rect.w = width;
	rect.h = height;
}

void Image::setCords(int x, int y) {
	rect.x = x;
	rect.y = y;
}

int Image::getWidth() {
	return rect.w;
}

int Image::getHeight() {
	return rect.h;
}

SDL_Rect Image::getRect() {
	return rect;
}

void Image::setImgPath(std::string path) {
	this->path = path;
}

SDL_Texture* Image::LoadImage(SDL_Renderer* render) {
	SDL_Texture* temp = NULL;
	SDL_Surface* surface = NULL;
	surface = IMG_Load(this->path.c_str());
	if (surface == NULL) {
		logSDLError("Unable to load image");
	}
	else {
		temp = SDL_CreateTextureFromSurface(render, surface);
		if (temp == NULL) {
			logSDLError("Unable to create texture from image");
		}
		SDL_FreeSurface(surface);
		surface = NULL;
	}
	return temp;
}

void Image::renderTexture(SDL_Texture *tex, SDL_Renderer *ren) {
	//Setup the destination rectangle to be at the position we want
	//Query the texture to get its width and height to use
	SDL_QueryTexture(tex, NULL, NULL, &rect.w, &rect.h);
	SDL_RenderCopy(ren, tex, NULL, &rect);
}

bool Image::ClickedOn(SDL_Event e)
{
	bool pass = true;
	if (e.type == SDL_MOUSEBUTTONDOWN) {
		bool inside = true;
		int x, y;
		SDL_GetMouseState(&x, &y);
		if (x < rect.x || y < rect.y) inside = false;
		if (x > rect.x+rect.w || y > rect.y+rect.h) inside = false;
		if (!inside) pass = false;
	}
	else {
		pass = false;
	}
	return pass;
}
