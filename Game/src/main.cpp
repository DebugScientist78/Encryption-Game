#include "../include/main.h"
const int numOfImages = 1;

int main(int argc, char *args[]) {
	if (!init()) {
		printf("Failed to initlize window \n");
	}
	else {
		std::vector<Image> totalImgs;
		SDL_Texture* titleText;
		SDL_Texture* backText;
		SDL_Rect backPos;
		backPos.h = 720;
		backPos.w = 1280;
		backPos.x = 0;
		backPos.y = 0;
		SDL_Rect titlePos;
		titlePos.h = 200;
		titlePos.w = 620;
		titlePos.x = 600;
		titlePos.y = 0;

		Image Background = Image();
		Background.setSize(WIDTH, HEIGHT);
		Background.setImgPath("graphics/Title Background.png");
		backText = Background.LoadImage(gRender);

		Image title = Image();
		title.setSize(680, 200);
		title.setImgPath("graphics/titleblock.png");
		titleText = title.LoadImage(gRender);

		/*bool imgPass = true;
		for (int i = 0; i < numOfImages; i++) {
			if (!totalImgs[i].LoadImage()) {
				imgPass = false;
				break;
			}
		}*/
		if (backText == NULL  && titleText == NULL) {
			printf("Failed to load the images \n");
		}
		else {
			bool quit_flag = false;
			SDL_Event e;
			while (!quit_flag) {
				while (SDL_PollEvent(&e) != 0) {
					if (e.type == SDL_QUIT) {
						quit_flag = true;
					}
					if (e.type == SDL_MOUSEBUTTONDOWN) {
						if (title.ClickedOn(e)) std::cout << "clicked" << std::endl;
					}
				}
				SDL_RenderClear(gRender);
				SDL_RenderCopy(gRender, backText, NULL, &backPos);
				SDL_RenderCopy(gRender, titleText, NULL, &titlePos);
				SDL_RenderPresent(gRender);
			}
		}
	}
	clean();
	return 0;
}