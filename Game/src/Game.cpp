#include "../include/main.h"

void loadTitle() {

	SDL_Texture* titleText;
	SDL_Texture* startBlockText;
	SDL_Texture* OptionsText;
	SDL_Texture* HelpText;

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

	Image Options = Image();
	Options.setSize(364, 120);
	Options.setCords((WIDTH / 2) - (Options.getWidth() / 2), (startBlock.getHeight() + startBlock.getRect().y) + 20);
	Options.setImgPath("graphics/Title-Options.png");
	OptionsText = Options.LoadImage(gRender);

	Image Help = Image();
	Help.setSize(364, 120);
	Help.setCords((WIDTH / 2) - (Help.getWidth() / 2), (Options.getHeight() + Options.getRect().y) + 20);
	Help.setImgPath("graphics/Title-Help.png");
	HelpText = Help.LoadImage(gRender);

	bool quit_flag = false;
	SDL_Event e;

	while (!quit_flag) {
		if (SDL_WaitEvent(&e) != 0) {
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
				if (Options.ClickedOn(e)) {
					scrMode = OPTITIONS;
					quit_flag = true;
				}
				if (Help.ClickedOn(e)) {
					scrMode = HELP;
					quit_flag = true;
				}
			}
			/*if (e.type == SDL_KEYDOWN) {
				if (e.key.keysym.sym == SDLK_w) {
					Background.setImgPath("graphics/HUD Text Box Green.bmp");
					backText = Background.LoadImage(gRender);
				}
			}*/
		}
		SDL_RenderClear(gRender);
		Background.renderTexture(backText, gRender);
		title.renderTexture(titleText, gRender);
		startBlock.renderTexture(startBlockText, gRender);
		Options.renderTexture(OptionsText, gRender);
		Help.renderTexture(HelpText, gRender);
		SDL_RenderPresent(gRender);
		SDL_Delay(15);
	}
	SDL_DestroyTexture(titleText);
	titleText = NULL;
	SDL_DestroyTexture(startBlockText);
	startBlockText = NULL;
	SDL_DestroyTexture(OptionsText);
	OptionsText = NULL;
	SDL_DestroyTexture(HelpText);
	HelpText = NULL;
	SDL_DestroyTexture(backText);
	backText = NULL;
	return;
}

void loadMain() {
	Background.setImgPath("graphics/MainScreen.bmp");
	backText = Background.LoadImage(gRender);

	bool quit = false;
	SDL_Event e;
	while (!quit) {
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				gExit = true;
				quit = true;
				scrMode = 0;
			}
		}
		SDL_RenderClear(gRender);
		Background.renderTexture(backText, gRender);
		SDL_RenderPresent(gRender);
	}
	SDL_DestroyTexture(backText);
	return;
}

void loadHelp() {
	Background.setImgPath("graphics/MainScreen.bmp");
	backText = Background.LoadImage(gRender);

	backButton.setSize(182, 60);
	backButton.setCords((WIDTH - backButton.getWidth())-70, 50);
	backButton.setImgPath("graphics/GoBackButton.png");
	bButtonText = backButton.LoadImage(gRender);

	std::string msg;
	std::ifstream in;

	in.open("dialog/Help.txt");
	msg = (static_cast<std::stringstream const&>(std::stringstream() << in.rdbuf()).str());

	TTF_Font* maintxt = NULL;
	SDL_Texture* txtTexture = NULL;
	Image textImg = Image();
	SDL_Rect txtRect;
	txtRect.h = 70;
	txtRect.w = 800;
	txtRect.x = ((WIDTH / 2) - (txtRect.w / 2))-120;
	txtRect.y = 100;

	maintxt = TTF_OpenFont("fonts/m5x7.ttf", 20);
	SDL_Color colorText = { 0,0,0 };
	txtTexture = LoadFont(txtTexture, msg, colorText, maintxt,txtRect.w);

	SDL_Event e;
	bool quit = false;

	while (!quit) {
		if (SDL_WaitEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				quit = true;
				gExit = true;
			}
			if (backButton.ClickedOn(e)) {
				scrMode = TITLE;
				quit = true;
			}
		}
		SDL_RenderClear(gRender);
		Background.renderTexture(backText, gRender);
		backButton.renderTexture(bButtonText, gRender);
		SDL_RenderCopy(gRender, txtTexture, NULL, &txtRect);
		SDL_RenderPresent(gRender);
		SDL_Delay(15);
	}

	SDL_DestroyTexture(txtTexture);
	txtTexture = NULL;
	SDL_DestroyTexture(bButtonText);
	bButtonText = NULL;
	SDL_DestroyTexture(backText);
	backText = NULL;
	SDL_RenderClear(gRender);
	return;
}


void loadOptions() {

}