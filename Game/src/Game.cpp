#include "../include/main.h"

void loadTitle() {
	SDL_Texture* titleText;
	SDL_Texture* startBlockText;

	Background.setSize(WIDTH, HEIGHT);
	Background.setCords(0, 0);
	Background.setImgPath("graphics/Title Background.png");
	backText = Background.LoadImage(gRender);

	Image title = Image();
	title.setSize(680, 200);
	title.setCords((WIDTH / 2) - (title.getWidth() / 2), 10);
	title.setImgPath("graphics/titleblock.bmp");
	titleText = title.LoadImage(gRender);

	Image startBlock = Image();
	startBlock.setSize(364, 120);
	startBlock.setCords((WIDTH / 2) - (startBlock.getWidth() / 2), (title.getHeight() + title.getRect().y) + 50);
	startBlock.setImgPath("graphics/Title-Start.png");
	startBlockText = startBlock.LoadImage(gRender);

	bool quit_flag = false;
	SDL_Event e;
	while (!quit_flag) {
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				gExit = true;
				quit_flag = true;
				scrMode = 0;
			}
			if (e.type == SDL_MOUSEBUTTONDOWN) {
				if (title.ClickedOn(e)) std::cout << "clicked" << std::endl;
				if (startBlock.ClickedOn(e)) {
					scrMode = MAIN;
					quit_flag = true;
				}
			}
			if (e.type == SDL_KEYDOWN) {
				switch (e.key.keysym.sym)
						case SDLK_w:
							Background.setImgPath("graphics/HUD Text Box Green.bmp");
							backText = Background.LoadImage(gRender);
							break;
			}
		}
		SDL_RenderClear(gRender);
		Background.renderTexture(backText, gRender);
		title.renderTexture(titleText, gRender);
		startBlock.renderTexture(startBlockText, gRender);
		SDL_RenderPresent(gRender);
	}
	SDL_DestroyTexture(titleText);
	SDL_DestroyTexture(startBlockText);
}

void loadMain() {
	Background.setImgPath("graphics/MainScreen.bmp");
	Background.LoadImage(gRender);

	bool quit = false;
	SDL_Event e;
	while (!quit) {
		while (SDL_PollEvent(&e) != 0) {

		}

	}

}

void loadHelp() {

}

void loadOptions() {

}