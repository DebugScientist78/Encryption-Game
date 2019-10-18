#include "../include/main.h"

SDL_Window* gWindow;
SDL_Renderer* gRender;
SDL_Texture* backText;
SDL_Texture* bButtonText;
Image Background;
Image backButton;

int scrMode;
bool gExit;
bool gTutorial;

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

void clean() {
	SDL_DestroyRenderer(gRender);
	gRender = NULL;
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	SDL_Quit();
}

SDL_Texture* LoadFont(SDL_Texture* texture,std::string msg, SDL_Color color, TTF_Font* font, int wrapL) {
	SDL_Surface* temp = NULL;
	temp = TTF_RenderText_Blended_Wrapped(font,msg.c_str(),color,wrapL);
	if (temp == NULL) {
		logSDLError("Failed to load text");
	}
	else {
		texture = SDL_CreateTextureFromSurface(gRender, temp);
		if (texture == NULL) {
			logSDLError("Failed conversion");
		} 
		SDL_FreeSurface(temp);
		temp = NULL;
	}

	return texture;
}