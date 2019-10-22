#ifndef MAIN_H
#define MAIN_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <stdio.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

#include "image.h"
#include "levelGenerator.h"
  
enum screen {
	TITLE = 1,
	MAIN = 2,
	HELP = 3,
	OPTITIONS = 4,
	LECTURE = 5
};

const int WIDTH = 1280;
const int HEIGHT = 720;

extern SDL_Window* gWindow;
extern SDL_Renderer* gRender;
extern SDL_Texture* backText;
extern SDL_Texture* bButtonText;
extern Image Background;
extern Image backButton;
extern Image msgBox;
extern int scrMode;
extern bool gExit;
extern bool gTutorial;
extern int day;

void logSDLError(std::string msg);

bool init();

void clean();

void loadMain();
void loadTitle();
void loadHelp();
void loadOptions();
void loadLecture();

SDL_Texture* LoadFont(SDL_Texture* texture, std::string msg, SDL_Color color, TTF_Font* font, int wrapL);

#endif // !MAIN_H
