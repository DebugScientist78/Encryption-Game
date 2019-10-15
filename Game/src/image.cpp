#include "../include/main.h"

Image::Image()
{
	width = 0;
	height = 0;
	texture = nullptr;
}

Image::~Image() {
	SDL_DestroyTexture(texture);
}

void Image::setSize(int width, int height) {
	this->width = width;
	this->height = height;
}

int* Image::getWidth() {
	return &width;
}

int* Image::getHeight() {
	return &height;
}

SDL_Texture* Image::getTexture() {
	return texture;
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

/**
* Draw an SDL_Texture to an SDL_Renderer at position x, y, preserving
* the texture's width and height
* @param tex The source texture we want to draw
* @param ren The renderer we want to draw to
* @param x The x coordinate to draw to
* @param y The y coordinate to draw to
*/
void Image::renderTexture(SDL_Renderer *ren, int x, int y) {
	//Setup the destination rectangle to be at the position we want
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	this->x = x;
	this->y = y;
	//Query the texture to get its width and height to use
	SDL_QueryTexture(texture, NULL, NULL, &dst.w, &dst.h);
	SDL_RenderCopy(ren, texture, NULL, &dst);
}

bool Image::ClickedOn(SDL_Event e)
{
	bool pass = true;
	if (e.type == SDL_MOUSEBUTTONDOWN) {
		bool inside = true;
		int x, y;
		SDL_GetMouseState(&x, &y);
		if (x < this->x || y < this->y) inside = false;
		if (x > this->x+this->width || y > this->y+this->height) inside = false;
		if (!inside) pass = false;
	}
	else {
		pass = false;
	}
	return pass;
}
