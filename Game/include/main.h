//The macros below with MAIN_H, are protective guards. That prevent the file to be implemented more than once
#ifndef MAIN_H
#define MAIN_H

/*
* Program name: main.h
* Date: 10/23/2019
* Purpose: This header file holds everything the other files would need to depend, simplifying the linking
* Author: Chency W
*/

/*
The includes for the SDL libraries and the extentions for PNG support and true type font
NOTE: depending if its ran on LINUX or WINDOWS, the directory; 'SDL2/' is to be place in front 
of the following include statements
*/
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

/*
Standard C++ and C libraries
Allowing for string support, algorithms, file access and random generatings
*/
#include <stdio.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

//class include of Image class that is a wrapper of Texture class, for images
#include "image.h"
// includes functions that generates a level and scrambles the information
#include "levelGenerator.h"
  
// enumerated data type for keeping track of current screen mode 
enum screen {
	TITLE = 1,
	MAIN = 2,
	HELP = 3,
	LECTURE = 4
};

//easy reference to the screen resolutions as global constants
const int WIDTH = 1280;
const int HEIGHT = 720;

// objects/variables that a repeatedly used or, needed outside of screen functions
extern SDL_Window* gWindow;
extern SDL_Renderer* gRender;
extern SDL_Texture* backText;
extern SDL_Texture* bButtonText;
extern Image Background;
extern Image backButton;
extern int scrMode;
extern bool gExit;
extern bool gTutorial;
extern int day;

//Wrapper for SDL's error logging tool
void logSDLError(std::string msg);

//The following functions are being initilized here, defined in cpp files
bool init();

void clean();

void loadMain();
void loadTitle();
void loadHelp();
void loadLecture();

SDL_Texture* LoadFont(SDL_Texture* texture, std::string msg, SDL_Color color, TTF_Font* font, int wrapL);

#endif // !MAIN_H
