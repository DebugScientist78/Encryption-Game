#include "../include/main.h"

SDL_Window* gWindow;
SDL_Renderer* gRender;

/**
* Log an SDL error with some error message to the output stream of our choice
* @param os The output stream to write the message to
* @param msg The error message to write, format will be msg error: SDL_GetError()
*/
void logSDLError(std::string msg) {
	std::cout << msg << " error: " << SDL_GetError() << std::endl;
}

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
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
			}
		}
	}
	return success;
}

void clean() {
	SDL_DestroyRenderer(gRender);
	gRender = NULL;
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	SDL_Quit();
}