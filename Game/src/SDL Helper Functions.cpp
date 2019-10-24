//main.h ties in the project files in a simple include file and can be called easily
#include "../include/main.h"

/*
* Program name: SDL Helper Functions.cpp
* Date: 10/23/2019
* Purpose: This source file defines the functions that are meant to simplfy using SDL
* Author: Chency W
*/


// initlization of global variables
SDL_Window* gWindow;
SDL_Renderer* gRender;
SDL_Texture* backText;
SDL_Texture* bButtonText;
Image Background;
Image backButton;

int scrMode;
bool gExit;
bool gTutorial;
int day;

/**
* Log an SDL error with some error message to the output stream of our choice
* @param os The output stream to write the message to
* @param msg The error message to write, format will be msg error: SDL_GetError()
*/
void logSDLError(std::string msg) {
	std::cout << msg << " error: " << SDL_GetError() << std::endl;
}

//ran at the beginning of the program,
//sets up the window and render, and verifys PNG support and TTF supports
bool init() {
	bool success = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL is unable to load,  SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else {
		gWindow = SDL_CreateWindow("Decrypt", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL) {
			logSDLError("Window could not be created!");
			success = false;
		}
		else {
			gRender = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRender == NULL) {
				logSDLError("Renderer could not be created");
				success = false;
			}
			else {
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRender, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					logSDLError("SDL_image could not initialize!");
					success = false;
				}
				if (TTF_Init() == -1)
				{
					logSDLError("SDL_ttf could not initialize!");
					success = false;
				}
			}
		}
	}
	return success;
}

// deallocates the window and render variable and exits the SDL2 system
void clean() {
	SDL_DestroyRenderer(gRender);
	gRender = NULL;
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	TTF_Quit();
	SDL_Quit();
}

//Wrapper function that returns a texture for a string
SDL_Texture* LoadFont(SDL_Texture* texture,std::string msg, SDL_Color color, TTF_Font* font, int wrapL) {
	//needs a surface to convert into a texture temporarily
	SDL_Surface* temp = NULL;

	//turns text with font, scolor and wrap limit to a surface
	temp = TTF_RenderText_Blended_Wrapped(font,msg.c_str(),color,wrapL);
	if (temp == NULL) {
		logSDLError("Failed to load text");
	}
	else {
		//converts to texture
		texture = SDL_CreateTextureFromSurface(gRender, temp);
		if (texture == NULL) {
			logSDLError("Failed conversion");
		} 
		SDL_FreeSurface(temp);
		temp = NULL;
	}

	return texture;
}