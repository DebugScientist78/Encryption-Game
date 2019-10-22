#ifndef LEVEL_GENERATOR_H
#define LEVEL_GENERATOR_H
#include "main.h"

enum difficulty {EASY = 0,MEDIUM = 1, HARD = 2};

void generate(int& diff, std::string& msg, int day);
std::string Scramble(std::string input, int diff);

#endif // !LEVEL_GENERATOR_H

