//main.h ties in the project files in a simple include file and can be called easily
#include "../include/main.h"

/*
* Program name: main.cpp
* Date: 10/23/2019
* Purpose: This source file is where the main method is located,
* It runs procedurally with the initilizing and then loads into a loop of screens that are running
* Author: Chency W
*/

int main(int argc, char *args[]) {
	//Sets the screen mode to the title screen
	scrMode = TITLE;
	if (!init()) {
		printf("Failed to initlize window \n");
	}
	else {
		//window exit that ends the program
		gExit = false;

		//the function gives random set of numbers dependent on runtime
		srand((int)time(0));
		while (!gExit) {
			//Check cases for which screen to load
			if (scrMode == TITLE) {
				loadTitle();
			}
			else if (scrMode == MAIN) {
				loadMain();
			}
			else if (scrMode == HELP) {
				loadHelp();
			}
			else if (scrMode == LECTURE) {
				loadLecture();
			}
			else {
				std::cout << "Transition failed" << std::endl;
			}
		}
	}
	//ends the program
	clean();
	return 0;
}