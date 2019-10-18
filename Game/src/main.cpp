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
		while (!gExit) {
			if (scrMode == TITLE) {
				loadTitle();
			}
			else if (scrMode == MAIN) {
				loadMain();
			}
			else if (scrMode == HELP) {
				loadHelp();
			}
			else if (scrMode == OPTITIONS) {
				loadOptions();
			}
			else {
				std::cout << "Transition failed" << std::endl;
			}
		}
	}
	clean();
	return 0;
}