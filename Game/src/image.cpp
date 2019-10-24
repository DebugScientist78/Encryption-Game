//main.h ties in the project files in a simple include file and can be called easily
#include "../include/main.h"

/*
* Program name: image.cpp
* Date: 10/23/2019
* Purpose: This source file defines the functions of the Image class
* Author: Chency W
*/

//constructer setting the Rect values to 0
Image::Image()
{
	rect.h = 0;
	rect.w = 0;
	rect.x = 0;
	rect.y = 0;
}

//Sets the size of the image in the Rect member from references
void Image::setSize(int width, int height) {
	rect.w = width;
	rect.h = height;
}

//Sets the position of the image in the Rect member from references
void Image::setCords(int x, int y) {
	rect.x = x;
	rect.y = y;
}

//returns the width stored
int Image::getWidth() {
	return rect.w;
}

//returns the height stored
int Image::getHeight() {
	return rect.h;
}

//returns the Rect data type
SDL_Rect Image::getRect() {
	return rect;
}

//sets the string value to the path of the image
void Image::setImgPath(std::string path) {
	this->path = path;
}

//returns a texture containing the image
SDL_Texture* Image::LoadImage(SDL_Renderer* render) {

	//temp is the texture being returned
	//surface is a temporary rendering type that is need to convert to texture type
	SDL_Texture* temp = NULL;
	SDL_Surface* surface = NULL;

	//sets the surface to the image by loading it
	surface = IMG_Load(this->path.c_str());

	//checks if it was successful
	if (surface == NULL) {
		logSDLError("Unable to load image");
	}
	else {
		//surface's data is converted into temp, texture
		temp = SDL_CreateTextureFromSurface(render, surface);

		//checks for failure
		if (temp == NULL) {
			logSDLError("Unable to create texture from image");
		}

		//deallocates the surface
		SDL_FreeSurface(surface);
		surface = NULL;
	}
	return temp;
}

//Renders the texture with the Rect's specifications
void Image::renderTexture(SDL_Texture *tex, SDL_Renderer *ren) {
	//Setup the destination rectangle to be at the position we want
	//Query the texture to get its width and height to use
	SDL_QueryTexture(tex, NULL, NULL, &rect.w, &rect.h);
	SDL_RenderCopy(ren, tex, NULL, &rect);
}

// returns true or false, if the image is clicked on
bool Image::ClickedOn(SDL_Event e)
{
	//a pass flag, that changes to false upon a unsatisfied condition
	bool pass = true;

	//checks if mouse was clicked
	if (e.type == SDL_MOUSEBUTTONDOWN) {
		//another flag for wither the mouse is in the image field
		bool inside = true;
		int x, y;

		//gets postion of the mouse
		SDL_GetMouseState(&x, &y);

		//checks if outside of the boundaries
		if (x < rect.x || y < rect.y) inside = false;
		if (x > rect.x+rect.w || y > rect.y+rect.h) inside = false;
		if (!inside) pass = false;
	}
	else {
		pass = false;
	}
	return pass;
}
