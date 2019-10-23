#include "../include/main.h"

SDL_Texture* msgBoxText;
Image msgBox = Image();

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

	Image lecture = Image();
	lecture.setSize(364, 120);
	lecture.setCords((WIDTH / 2) - (lecture.getWidth() / 2), (startBlock.getHeight() + startBlock.getRect().y) + 20);
	lecture.setImgPath("graphics/Title-info.png");
	OptionsText = lecture.LoadImage(gRender);

	Image Help = Image();
	Help.setSize(364, 120);
	Help.setCords((WIDTH / 2) - (Help.getWidth() / 2), (lecture.getHeight() + lecture.getRect().y) + 20);
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
				if (lecture.ClickedOn(e)) {
					scrMode = LECTURE;
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
		lecture.renderTexture(OptionsText, gRender);
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

void loadBatch(std::string& in_msg) {
	
}

void loadPause(bool& mainQuit) {
	SDL_Texture* pausebText;
	Image pauseB = Image();
	pauseB.setSize(120, 80);
	pauseB.setCords((WIDTH / 2) - (pauseB.getWidth() / 2), (HEIGHT / 2) - (pauseB.getHeight() / 2));
	pauseB.setImgPath("graphics/Pausebox.bmp");
	pausebText = pauseB.LoadImage(gRender);

	bool quit = false;
	SDL_Event e;
	while (!quit) {
		if (SDL_WaitEvent(&e) != 0) {
			if (e.type == SDL_KEYDOWN) {
				switch (e.key.keysym.sym) {
				case SDLK_q:
					quit = true;
					scrMode = TITLE;
					mainQuit = true;
					break;

				case SDLK_p:
					quit = true;
					break;
				}
			}
		}
		pauseB.renderTexture(pausebText, gRender);
		SDL_RenderPresent(gRender);
	}
	SDL_DestroyTexture(pausebText);
	pausebText = NULL;
	return;
}

void loadMain() {
	std::string msgTransfer;
	int diff;
	std::string ans_string;
	std::string raw_string = "";
	std::string input = "";
	int life = 3;

	Background.setImgPath("graphics/MainScreen.bmp");
	backText = Background.LoadImage(gRender);

	SDL_Texture* pauseText;
	Image pause = Image();
	pause.setCords(60, 60);
	pause.setCords(WIDTH - pause.getWidth() - 130, HEIGHT-pause.getHeight()-110);
	pause.setImgPath("graphics/pause.bmp");
	pauseText = pause.LoadImage(gRender);

	SDL_Texture* lifeTexture;
	Image lifeImg = Image();
	lifeImg.setSize(63, 63);
	lifeImg.setCords(lifeImg.getWidth() + lifeImg.getRect().x + 10, pause.getRect().y);
	lifeImg.setImgPath("graphics/heart.png");
	lifeTexture = lifeImg.LoadImage(gRender);
	SDL_Texture* lifeCounterTexture = NULL;
	TTF_Font* lifefont = TTF_OpenFont("fonts/m5x7.ttf",30);
	SDL_Rect lifetextRect;
	lifetextRect.h = 63;
	lifetextRect.w = 80;
	lifetextRect.x = lifeImg.getWidth() + lifeImg.getRect().x + 10;
	lifetextRect.y = lifeImg.getRect().y;
	std::string life_str = "x " + std::to_string(life);
	lifeCounterTexture = LoadFont(lifeCounterTexture, life_str, { 0,0,0 }, lifefont, lifetextRect.w);

	SDL_Texture* dayCounterTexture = NULL;
	SDL_Rect daytextRect;
	daytextRect.h = 63;
	daytextRect.w = 90;
	daytextRect.x = lifetextRect.w + lifetextRect.x + 40;
	daytextRect.y = lifetextRect.y;
	std::string day_str = "Day: " + std::to_string(day);
	dayCounterTexture = LoadFont(dayCounterTexture, day_str, { 0,0,0 }, lifefont, daytextRect.w);

	SDL_Texture* promptTexture = NULL;
	SDL_Rect promptRect;
	promptRect.h = 80;
	promptRect.w = 600;
	promptRect.x = (WIDTH/2) - (promptRect.w/2);
	promptRect.y = 20;
	TTF_Font* promptfont = TTF_OpenFont("fonts/m5x7.ttf", 40);
	std::string promptDisplay_str = "Unscramble: " + raw_string;
	promptTexture = LoadFont(promptTexture, promptDisplay_str, { 0,0,0 }, promptfont, promptRect.w);

	SDL_Texture* userInputTexture = NULL;
	SDL_Rect userInputRect;
	userInputRect.h = 70;
	userInputRect.w = 100;
	userInputRect.x = (WIDTH / 2) - (userInputRect.w / 2);
	userInputRect.y = promptRect.y + 100;
	TTF_Font* inputfont = TTF_OpenFont("fonts/m5x7.ttf", 30);
	std::string userDisplay_str = "Input: ";
	userInputTexture = LoadFont(userInputTexture, userDisplay_str, { 0,0,0 }, inputfont, userInputRect.w);

	SDL_Texture* TypeTexture = NULL;
	SDL_Rect typeRect;
	typeRect.h = 60;
	typeRect.w = 10;
	typeRect.x = (WIDTH / 2) - (typeRect.w/2)-100;
	typeRect.y = userInputRect.y + 100;
	TTF_Font* typefont = TTF_OpenFont("fonts/m5x7.ttf", 25);
	TypeTexture = LoadFont(TypeTexture, input, { 0,0,0 }, typefont, typeRect.w);

	bool quit = false;
	bool onPause = false;
	bool OneClickMsg = false;
	bool OneClickBat = false;
	bool levelComplete = false;

	SDL_Event e;
	SDL_StartTextInput();
	while (!quit) {
		const Uint8 *state = SDL_GetKeyboardState(NULL);
		if (SDL_WaitEvent(&e) != 0) {
			SDL_Delay(10);
			if (e.type == SDL_QUIT) {
				gExit = true;
				quit = true;
				scrMode = 0;
			}
			if (pause.ClickedOn(e)) {
				loadPause(quit);
			}
			if (state[SDL_SCANCODE_BACKSPACE] && input.length() > 0) {
				input.pop_back();
			}
			else if (e.type == SDL_TEXTINPUT) {
				std::cout << "text added" << std::endl;
				input += e.text.text;
			}
			else if (state[SDL_SCANCODE_RETURN] && levelComplete == true && e.key.repeat == 0) {
				std::cout << "space" << std::endl;
				std::cout << (input == ans_string) << std::endl;
				if (input == ans_string) {
					levelComplete = false;
					day++;
				}
				else {
					life--;
					levelComplete = false;
				}
				input = "";
				ans_string = "";
			}

			/*if (renderText) {
				if (input != "") {
					userDisplay_str = "Input: " + input;
					userInputTexture = LoadFont(userInputTexture, userDisplay_str, { 0,0,0 }, lifefont, userInputRect.w);
				}
				else {
					userInputTexture = LoadFont(userInputTexture, " ", { 0,0,0 }, lifefont, userInputRect.w);
				}
				SDL_RenderCopy(gRender, userInputTexture, NULL, &userInputRect);
			}*/
		}
		SDL_RenderClear(gRender);
		Background.renderTexture(backText, gRender);
		pause.renderTexture(pauseText, gRender);
		lifeImg.renderTexture(lifeTexture, gRender);
		life_str = "x " + std::to_string(life);
		lifeCounterTexture = LoadFont(lifeCounterTexture, life_str, { 255,255,255 }, lifefont, lifetextRect.w);
		SDL_RenderCopy(gRender, lifeCounterTexture, NULL, &lifetextRect);
		day_str = "Day: " + std::to_string(day);
		dayCounterTexture = LoadFont(dayCounterTexture, day_str, { 255,255,255 }, lifefont, daytextRect.w);
		SDL_RenderCopy(gRender, dayCounterTexture, NULL, &daytextRect);
		
		promptDisplay_str = "Unscramble: " + raw_string;
		promptTexture = LoadFont(promptTexture, promptDisplay_str, { 0,0,0 }, promptfont, promptRect.w);
		SDL_RenderCopy(gRender, promptTexture, NULL, &promptRect);
		
		SDL_RenderCopy(gRender, userInputTexture, NULL, &userInputRect);

		typeRect.w = input.length() * 10;
		TypeTexture = LoadFont(TypeTexture, input, { 0,0,0 }, typefont, 1000);
		SDL_RenderCopy(gRender, TypeTexture, NULL, &typeRect);

		SDL_RenderPresent(gRender);

		if (day == 20) {
			quit = true;
			scrMode = TITLE;

		}
		if (life <= 0) {
			quit = true;
			scrMode = LECTURE;
		}
		if (!levelComplete) {
			generate(diff, ans_string, day);
			raw_string = Scramble(ans_string, diff);
			levelComplete = true;
		}
	}
	SDL_StopTextInput();
	SDL_DestroyTexture(pauseText);
	pauseText = NULL;
	SDL_DestroyTexture(lifeTexture);
	lifeTexture = NULL;
	SDL_DestroyTexture(lifeCounterTexture);
	lifeCounterTexture = NULL;
	SDL_DestroyTexture(msgBoxText);
	msgBoxText = NULL;
	SDL_DestroyTexture(userInputTexture);
	userInputTexture = NULL;
	SDL_DestroyTexture(promptTexture);
	promptTexture = NULL;
	SDL_DestroyTexture(TypeTexture);
	TypeTexture = NULL;
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
	SDL_Rect txtRect;
	txtRect.h = 600;
	txtRect.w = 900;
	txtRect.x = ((WIDTH / 2) - (txtRect.w / 2))-100;
	txtRect.y = 60;

	maintxt = TTF_OpenFont("fonts/m5x7.ttf", 24);
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
	Background.setImgPath("graphics/MainScreen.bmp");
	backText = Background.LoadImage(gRender);

	backButton.setSize(182, 60);
	backButton.setCords((WIDTH - backButton.getWidth()) - 70, 50);
	backButton.setImgPath("graphics/GoBackButton.png");
	bButtonText = backButton.LoadImage(gRender);

	bool quit = false;
	SDL_Event e;
	while (!quit) {
		if (SDL_WaitEvent(&e) == 1) {
			if (backButton.ClickedOn(e)) {
				scrMode = TITLE;
				quit = true;
			}
			if (e.type == SDL_QUIT) {
				quit = true;
				gExit = true;
			}
		}
		SDL_RenderClear(gRender);
		Background.renderTexture(backText, gRender);
		backButton.renderTexture(bButtonText, gRender);
		SDL_RenderPresent(gRender);
		SDL_Delay(15);
	}
	SDL_DestroyTexture(backText);
	backText = NULL;
	SDL_DestroyTexture(bButtonText);
	bButtonText = NULL;
}

void loadLecture() {
	std::string tips[12] = {
		"The more days you survive, the harder the levels become. The harder scrambling algorithums, use permutations to shuffle the text. Most encryption keys, use a form a permutation, called Substitutation-permutation network",
		"The first 10 days have a chance of 66% giving and easy scramble, the trick is, the characters are simply shifted. Digital encryption was used during WW2 called the Engima.",
		"Encryption for the internet was originially setup by the US government, encryption didn't go public till the 1970s.",
		"A lot of effective encryption algorithums manipulate data on a binary level.",
		"The internet, has many standareds for encryption such as SSL and SSH.",
		"A common part of encryption, is the key. The key takes the text and can scramble/unscramble it.", 
		"After 9 days in game, the difficulty will shift from a 75% chance of medium messages and 25% of hard messages.",
		"Popular encyption keys, are AES, RSA and Twofish. Many keys also have key sizes, determining the amount of bits being used.",
		"There are two distinct types of encryption keys; symmetric and asymmetric. symmetric keys mean the key is used for both encrypting and decrypting. While asymmetric keys use two diferent keys to encrypt and decrypt.",
		"The hardest difficulty in this game, is the closet to actual encryption algorithums. Where the string is permutated and shuffled. Though actual algorithums use more mathematically complex methods.",
		"You can play around with encryption yourself! Many programming languages, have a crytography API to use. They include encryption keys used in industry.",
		"Encryption may be obselete thanks to quantum computing. Encryption is intended to be unbreakable by clasical computers, quantum computers could break them in hours."
	};
	Background.setImgPath("graphics/Lecture.bmp");
	backText = Background.LoadImage(gRender);

	std::ifstream in;
	in.open("dialog/Lecture Templete.txt");
	std::string templete = (static_cast<std::stringstream const&>(std::stringstream() << in.rdbuf()).str()); 

	TTF_Font* bodyFont = TTF_OpenFont("fonts/m5x7.ttf", 24);
	SDL_Rect bodyRect;
	bodyRect.h = 150;
	bodyRect.w = 1100;
	bodyRect.x = (WIDTH / 2) - (bodyRect.w / 2);
	bodyRect.y = 110;
	SDL_Texture* bodyTexture = NULL;
	bodyTexture = LoadFont(bodyTexture, templete, { 0,0,0 },bodyFont,bodyRect.w);

	int r = rand() % 12;

	TTF_Font* tipFont = TTF_OpenFont("fonts/m5x7.ttf", 22);
	SDL_Rect tipRect;
	tipRect.h = 150;
	tipRect.w = tips[r].length()*2.8;
	tipRect.x = (WIDTH / 2) - (tipRect.w / 2);
	tipRect.y = 20 + bodyRect.h + bodyRect.y;
	SDL_Texture* tipTexture = NULL;
	tipTexture = LoadFont(tipTexture, tips[r], { 0,0,0 }, tipFont, tipRect.w);

	bool quit = false;
	SDL_Event e;
	while (!quit) {
		if (SDL_WaitEvent(&e) != 0) {
			if (e.type == SDL_KEYDOWN) {
				switch (e.key.keysym.sym) {
				case SDLK_q:
					quit = true;
					scrMode = TITLE;
				}
			}
			if (e.type == SDL_QUIT) {
				quit = true;
				gExit = true;
				scrMode = 0;
			}
		}
		SDL_RenderClear(gRender);
		Background.renderTexture(backText, gRender);
		SDL_RenderCopy(gRender, bodyTexture, NULL, &bodyRect);
		SDL_RenderCopy(gRender, tipTexture, NULL, &tipRect);
		SDL_RenderPresent(gRender);
	}
	SDL_DestroyTexture(backText);
	backText = NULL;
	SDL_DestroyTexture(bodyTexture);
	bodyTexture = NULL;
	SDL_DestroyTexture(tipTexture);
	tipTexture = NULL;
	return;
}