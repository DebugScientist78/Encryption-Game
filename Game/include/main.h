#ifndef MAIN_H
#define MAIN_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>

#include "image.h"
#include "keyinput.h"

enum screen {
	TITLE = 1,
	MAIN = 2,
	HELP = 3,
	OPTITIONS = 4
};

const int WIDTH = 1280;
const int HEIGHT = 720;

extern SDL_Window* gWindow;
extern SDL_Renderer* gRender;
extern SDL_Texture* backText;
extern Image Background;
extern int scrMode;
extern bool gExit;

void logSDLError(std::string msg);

bool init();

void clean();

void loadMain();
void loadTitle();
void loadHelp();
void loadOptions();

#endif // !MAIN_H
