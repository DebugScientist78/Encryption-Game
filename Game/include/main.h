#ifndef MAIN_H
#define MAIN_H

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>

#include "image.h"

const int WIDTH = 1280;
const int HEIGHT = 720;

extern SDL_Window* gWindow;
extern SDL_Renderer* gRender;

void logSDLError(std::string msg);

bool init();

void clean();

#endif // !MAIN_H
