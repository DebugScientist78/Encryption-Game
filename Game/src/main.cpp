#include "../include/main.h"
const int numOfImages = 1;

int main(int argc, char *args[]) {
	scrMode = TITLE;
	if (!init()) {
		printf("Failed to initlize window \n");
	}
	else {
		gExit = false;
		gTutorial = true;
		srand((int)time(0));
		while (!gExit) {
			if (scrMode == TITLE) {
				loadTitle();
			}
			else if (scrMode == MAIN) {
				day = 0;
				loadMain();
			}
			else if (scrMode == HELP) {
				loadHelp();
			}
			else if (scrMode == OPTITIONS) {
				loadOptions();
			}
			else if (scrMode == LECTURE) {
				loadLecture();
			}
			else {
				std::cout << "Transition failed" << std::endl;
			}
		}
	}
	clean();
	return 0;
}