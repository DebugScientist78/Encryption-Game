//The macros below with LEVL_GENERATOR_H, are protective guards. That prevent the file to be implemented more than once
#ifndef LEVEL_GENERATOR_H
#define LEVEL_GENERATOR_H

/*
* Program name: levelGenerator.h
* Date: 10/23/2019
* Purpose: This header file initlizes the difficulty enum data type
* and initlizes the generate and scramble funcions
* Author: Chency W
*/

//main.h ties in the project files in a simple include file and can be called easily
#include "main.h"

//another enum data type for difficulty of level
enum difficulty {EASY = 0,MEDIUM = 1, HARD = 2};

//updates the msg, by using the reference of the string, day and difficulty
//updating without returning a data type
void generate(int& diff, std::string& msg, int day);

//returns a scrambled string/message
std::string Scramble(std::string input, int diff);

#endif // !LEVEL_GENERATOR_H

