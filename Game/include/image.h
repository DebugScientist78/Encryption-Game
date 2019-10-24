//The macros below with Image_H, are protective guards. That prevent the file to be implemented more than once
#ifndef IMAGE_H
#define IMAGE_H

/*
* Program name: image.h
* Date: 10/23/2019
* Purpose: This header file initlizes the Image class that is defined in image.cpp
* Author: Chency W
*/

//main.h ties in the project files in a simple include file and can be called easily
#include "main.h"

/*
The Image class is a wrapper for SDL texture and its image support
The class stores the image path, the area and position of the image. 
The area and position are store in a simple SDL_Rect object
*/
class Image {
	//These data members, can only be accessed by the class' get functions
private:
	std::string path;
	SDL_Rect rect;

//These functions can be accessed by the developer outside the class implementation
public:
	//constructor that sets all the values to NULL/0
	Image();

	//Set functions that size, position and image
	void setSize(int width, int height);
	void setCords(int x, int y);
	void setImgPath(std::string path);

	//get functions that return the data members
	int getWidth();
	int getHeight();
	SDL_Rect getRect();

	//Appliable functions that loads the image into a texture, render the texture and verify if is clicked on
	SDL_Texture* LoadImage(SDL_Renderer* render);
	void renderTexture(SDL_Texture *tex, SDL_Renderer *ren);
	bool ClickedOn(SDL_Event e);
};

#endif // !IMAGE_H

