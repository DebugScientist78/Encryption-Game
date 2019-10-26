//include main.h as it links everything together
#include "../include/main.h"

/*
* Program name: Game.cpp
* Date: 10/23/2019
* Purpose: loads the 'screens' of the game, each screen has render initlizing and destroying to save memory
* Author: Chency W
*/


/*
The function loads the title screen of the game.
The background texture is initlized and set to an image in the graphics folder.
Three other textures are loaded, the start, 
*/
void loadTitle() {

	//textures for the title, start button, lecture button and help button
	SDL_Texture* titleText;
	SDL_Texture* startBlockText;
	SDL_Texture* lectureText;
	SDL_Texture* HelpText;

	//audio initilize
	Mix_Music* music = nullptr;
	music = Mix_LoadMUS("audio/title_music.mp3");

	//setup Background size, position and image
	//loads it into the background texture
	Background.setSize(WIDTH, HEIGHT);
	Background.setCords(0, 0);
	Background.setImgPath("graphics/Title Background.png");
	backText = Background.LoadImage(gRender);

	//Setup title size, position and image
	//loads it into the title texture
	Image title = Image();
	title.setSize(680, 200);
	title.setCords((WIDTH / 2) - (title.getWidth() / 2), 10);
	title.setImgPath("graphics/titleblock.bmp");
	titleText = title.LoadImage(gRender);

	//sets up the start button size, position and image
	//loads it into the start button texture
	Image startBlock = Image();
	startBlock.setSize(364, 120);
	startBlock.setCords((WIDTH / 2) - (startBlock.getWidth() / 2), (title.getHeight() + title.getRect().y) + 50);
	startBlock.setImgPath("graphics/Title-Start.png");
	startBlockText = startBlock.LoadImage(gRender);

	//sets up the lecture/tips button, size, position and image
	//loads it into the lecture/tips texture
	Image lecture = Image();
	lecture.setSize(364, 120);
	lecture.setCords((WIDTH / 2) - (lecture.getWidth() / 2), (startBlock.getHeight() + startBlock.getRect().y) + 20);
	lecture.setImgPath("graphics/Title-info.png");
	lectureText = lecture.LoadImage(gRender);

	//Sets up the help button, size, position and image
	//loads it into the help button texture
	Image Help = Image();
	Help.setSize(364, 120);
	Help.setCords((WIDTH / 2) - (Help.getWidth() / 2), (lecture.getHeight() + lecture.getRect().y) + 20);
	Help.setImgPath("graphics/Title-Help.png");
	HelpText = Help.LoadImage(gRender);

	//quit condition, changes to true upon exit of program or screen
	bool quit_flag = false;

	//mute flag
	bool muted = false;

	//variable that represents the Events that SDL2 records
	SDL_Event e;

	//loops until user leaves screen or exits game
	Mix_PlayMusic(music, -1);
	while (!quit_flag) {
		const Uint8* state = SDL_GetKeyboardState(nullptr);
		//verifies vaild event input
		if (SDL_WaitEvent(&e) != 0) {
			// exits the game
			if (e.type == SDL_QUIT) {
				gExit = true;
				quit_flag = true;
				scrMode = 0;
			}
			if (e.type == SDL_MOUSEBUTTONDOWN) {
				//checks if buttons are clicked, then changes screen mode into their respective choices
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
			//Mutes and unmute
			if (state[SDL_SCANCODE_M] && e.type == SDL_KEYDOWN) {
				muted = !muted;
				if (muted) {
					Mix_VolumeMusic(128);
				}
				else {
					Mix_VolumeMusic(0);
				}
			}
		}
		//constantly renders and updates the window
		SDL_RenderClear(gRender);
		Background.renderTexture(backText, gRender);
		title.renderTexture(titleText, gRender);
		startBlock.renderTexture(startBlockText, gRender);
		lecture.renderTexture(lectureText, gRender);
		Help.renderTexture(HelpText, gRender);
		SDL_RenderPresent(gRender);
		//relief for the CPU
		SDL_Delay(10);
	}
	//deallocates textures upon exit
	SDL_DestroyTexture(titleText);
	titleText = nullptr;
	SDL_DestroyTexture(startBlockText);
	startBlockText = nullptr;
	SDL_DestroyTexture(lectureText);
	lectureText = nullptr;
	SDL_DestroyTexture(HelpText);
	HelpText = nullptr;
	SDL_DestroyTexture(backText);
	backText = nullptr;
	
	//deallocate audio
	Mix_HaltMusic();
	Mix_FreeMusic(music);
	music = nullptr;

	return;
}

/*
This is more of a pop up, rather than a screen, it only loads the pause box texture, and stops the main screen
This is done since, the program is ran sequentially, meaning the main loop isn't able to refresh/update as the 
program is stuck in the pause's while loop

NOTE: this may cause RAM use to jump, I haven't tested though
*/
void loadPause(bool& mainQuit, bool& mute) {

	//sets up pause box size, position and image
	// loads it into the pause box texture
	SDL_Texture* pausebText;
	Image pauseB = Image();
	pauseB.setSize(120, 80);
	//middle of the screen
	pauseB.setCords((WIDTH / 2) - (pauseB.getWidth() / 2), (HEIGHT / 2) - (pauseB.getHeight() / 2));
	pauseB.setImgPath("graphics/Pausebox.bmp");
	pausebText = pauseB.LoadImage(gRender);

	//quit flag
	bool quit = false;
	//
	SDL_Event e;
	pauseB.renderTexture(pausebText, gRender);
	SDL_RenderPresent(gRender);
	while (!quit) {
		if (SDL_WaitEvent(&e) != 0) {
			if (e.type == SDL_KEYDOWN) {
				switch (e.key.keysym.sym) {
					//if q is pressed, exit to title
					//if p is pressed, unpauses the game
				case SDLK_q:
					quit = true;
					scrMode = TITLE;
					mainQuit = true;
					break;

				case SDLK_p:
					quit = true;
					break;
				case SDLK_m:
					mute = !mute;
					break;
				}
			}
		}
		//renders the pause box texture but not clearing the main screen texture
	}
	//deallocates texture
	SDL_DestroyTexture(pausebText);
	pausebText = nullptr;
	return;
}

/*
Loads a question, if answered correctly, they get to see the correct answer from the level
otherwise, they get the correct answer for the question.
Then it returns back to the game
*/
void LoseLevel(std::string ans) {

	//setup music for questions
	Mix_Music* music = Mix_LoadMUS("audio/question.mp3");

	//Answer collection to questions;
	//refer to the images for context
	static const std::vector<std::vector<bool>> answerValues = {
		{//1
			true,false,false,false
		},
		{//2
			false,true,false,false
		},
		{//3
			false,false,false,true
		}, 
		{//4
			false,true,false,false
		},
		{//5
			false,false,true,false
		},
		{//6
			false,false,false,true
		},
		{//7
			true,false,false,false
		},
		{//8
			false,true,false,false
		},
		{//9
			false,false,true,false
		},
		{//10
			true,false,false,false
		},
		{//11
			false,true,false,false
		},
		{//12
			false,false,false,true
		},
		{//13
			false,true,false,false
		},
		{//14
			true,false,false,false
		},
		{//15
			false,false,false,true
		}
	};

	//select random quesiton
	int r;
	r = rand()%15;
	std::vector<bool> answerARR;
	answerARR = answerValues[r];
	//std::cout << answerARR[0] << answerARR[1] << answerARR[2] << answerARR[3] << std::endl;

	//create image to display question
	Image text = Image();
	SDL_Texture* txtTexture;
	text.setSize(845, 475);
	text.setCords((WIDTH / 2)-(text.getWidth()/2), (HEIGHT / 2)-(text.getHeight()/2));
	text.setImgPath("graphics/Questions and Answers/Question_" + std::to_string(r+1) + ".bmp");
	txtTexture = text.LoadImage(gRender);

	SDL_Texture* ansText = nullptr;
	TTF_Font* ansfont = TTF_OpenFont("fonts/m5x7.ttf", 50);
	SDL_Rect ansRect;
	
	//flags to prevent spam and ensure proper flow of function
	bool quit = false;
	bool correct = false;
	bool pressed = false;

	bool muted = false;

	SDL_Event ev;

	Mix_PlayMusic(music, -1);
	while (!quit) {
		text.renderTexture(txtTexture, gRender);
		SDL_RenderPresent(gRender);

		//array of keyboard states
		const Uint8 *state = SDL_GetKeyboardState(nullptr);
		if (SDL_WaitEvent(&ev) != 0) {
			//mute music or not
			if (state[SDL_SCANCODE_M]) {
				muted = !muted;
				if (muted) {
					Mix_VolumeMusic(128);
				}
				else {
					Mix_VolumeMusic(0);
				}
			}

			//read user input while allowed
			if (state[SDL_SCANCODE_A] && !pressed) {
				correct = answerARR[0];
				pressed = true;
			}
			else if (state[SDL_SCANCODE_B] && !pressed) {
				correct = answerARR[1];
				pressed = true;
			}
			else if (state[SDL_SCANCODE_C] && !pressed) {
				correct = answerARR[2];
				pressed = true;
			}
			else if (state[SDL_SCANCODE_D] && !pressed) {
				correct = answerARR[3];
				pressed = true;
			}

			if (pressed) {
				if (correct) {//load correct answer for the level
					text.setImgPath("graphics/Questions and Answers/correct.bmp");
					txtTexture = text.LoadImage(gRender);
					text.renderTexture(txtTexture, gRender);
					ansRect.h = (ans.length() / 1.5)*10;
					ansRect.w = (ans.length() * 1.5)*10;
					ansRect.x = text.getRect().x +150;
					ansRect.y = text.getRect().y + 300;
					ansText = LoadFont(ansText, ans, { 0,0,0 }, ansfont, text.getWidth()-50);
					SDL_RenderCopy(gRender, ansText, nullptr, &ansRect);
					SDL_RenderPresent(gRender);
				}
				else {//load the correct answer for the question
					text.setImgPath("graphics/Questions and Answers/incorrect.bmp");
					txtTexture = text.LoadImage(gRender);
					text.renderTexture(txtTexture, gRender);
					std::string correctLetter;
					if (answerARR[0]) {
						correctLetter = "A)";
					}
					else if (answerARR[1]) {
						correctLetter = "B)";
					}
					else if (answerARR[2]) {
						correctLetter = "C)";
					}
					else if (answerARR[3]) {
						correctLetter = "D)";
					}

					ansRect.h = 200;
					ansRect.w = 100;
					ansRect.x = text.getRect().x + 100;
					ansRect.y = text.getRect().y + 100;
					ansText = LoadFont(ansText, correctLetter, { 0,0,0 }, ansfont, 50);
					SDL_RenderCopy(gRender, ansText, nullptr, &ansRect);
					SDL_RenderPresent(gRender);
					SDL_RenderPresent(gRender);
				}
				quit = true;
			}
		}
		SDL_Delay(10);
	}
	SDL_Delay(10);
	//waits until the user hits backspace to quit
	while (1) {
		const Uint8 *state = SDL_GetKeyboardState(nullptr);
		if (SDL_WaitEvent(&ev) != 0) {
			if (state[SDL_SCANCODE_BACKSPACE]) {
				break;
			}
		}
		SDL_RenderPresent(gRender);
	}
	
	SDL_DestroyTexture(txtTexture);
	SDL_DestroyTexture(ansText);
	ansText = nullptr;
	txtTexture = nullptr;

	TTF_CloseFont(ansfont);
	ansfont = nullptr;

	Mix_HaltMusic();
	Mix_FreeMusic(music);
	music = nullptr;

	return;
}


/*
This function loads the main game screen and the logic in the game.
Where it calls upon the generate and scramble function, in a loop to give constant user feed back
The user input is also displayed below the message needed to be scrambled
*/
void loadMain() {

	//setup music
	Mix_Music* music = Mix_LoadMUS("audio/main_music.mp3");

	//variables for the game, difficulty, life and messages
	int diff;
	int day = 0;
	std::string ans_string;
	std::string raw_string = "";
	std::string input = "";
	int life = 3;

	Background.setImgPath("graphics/MainScreen.bmp");
	backText = Background.LoadImage(gRender);

	//sets up pause button
	SDL_Texture* pauseText;
	Image pause = Image();
	pause.setCords(60, 60);
	pause.setCords(WIDTH - pause.getWidth() - 130, HEIGHT-pause.getHeight()-110);
	pause.setImgPath("graphics/pause.bmp");
	pauseText = pause.LoadImage(gRender);

	//sets up life counter
	SDL_Texture* lifeTexture;
	Image lifeImg = Image();
	lifeImg.setSize(63, 63);
	lifeImg.setCords(lifeImg.getWidth() + lifeImg.getRect().x + 10, pause.getRect().y);
	lifeImg.setImgPath("graphics/heart.png");
	lifeTexture = lifeImg.LoadImage(gRender);

	//sets up life counter text
	SDL_Texture* lifeCounterTexture = nullptr;
	TTF_Font* lifefont = TTF_OpenFont("fonts/m5x7.ttf",30);
	SDL_Rect lifetextRect;
	lifetextRect.h = 63;
	lifetextRect.w = 80;
	lifetextRect.x = lifeImg.getWidth() + lifeImg.getRect().x + 10;
	lifetextRect.y = lifeImg.getRect().y;
	std::string life_str = "x " + std::to_string(life);
	lifeCounterTexture = LoadFont(lifeCounterTexture, life_str, { 0,0,0 }, lifefont, lifetextRect.w);

	//sets up day counter
	SDL_Texture* dayCounterTexture = nullptr;
	SDL_Rect daytextRect;
	daytextRect.h = 63;
	daytextRect.w = 90;
	daytextRect.x = lifetextRect.w + lifetextRect.x + 40;
	daytextRect.y = lifetextRect.y;
	std::string day_str = "Day: " + std::to_string(day);
	dayCounterTexture = LoadFont(dayCounterTexture, day_str, { 0,0,0 }, lifefont, daytextRect.w);

	//sets up prompt message
	SDL_Texture* promptTexture = nullptr;
	SDL_Rect promptRect;
	promptRect.h = 80;
	promptRect.w = 600;
	promptRect.x = (WIDTH/2) - (promptRect.w/2);
	promptRect.y = 20;
	//sets font
	TTF_Font* promptfont = TTF_OpenFont("fonts/m5x7.ttf", 40);
	std::string promptDisplay_str = "Unscramble: " + raw_string;
	//set texture from font, string and color
	promptTexture = LoadFont(promptTexture, promptDisplay_str, { 0,0,0 }, promptfont, promptRect.w);

	//sets up user input
	SDL_Texture* userInputTexture = nullptr;
	SDL_Rect userInputRect;
	userInputRect.h = 70;
	userInputRect.w = 100;
	userInputRect.x = (WIDTH / 2) - (userInputRect.w / 2);
	userInputRect.y = promptRect.y + 100;
	TTF_Font* inputfont = TTF_OpenFont("fonts/m5x7.ttf", 30);
	std::string userDisplay_str = "Input: ";
	userInputTexture = LoadFont(userInputTexture, userDisplay_str, { 0,0,0 }, inputfont, userInputRect.w);

	//sets up typing feedback
	SDL_Texture* TypeTexture = nullptr;
	SDL_Rect typeRect;
	typeRect.h = 60;
	typeRect.w = 10;
	typeRect.x = (WIDTH / 2) - (typeRect.w/2)-100;
	typeRect.y = userInputRect.y + 100;
	TTF_Font* typefont = TTF_OpenFont("fonts/m5x7.ttf", 25);
	TypeTexture = LoadFont(TypeTexture, input, { 0,0,0 }, typefont, typeRect.w);

	bool quit = false;
	//prevents level change from spamming
	bool levelComplete = false;

	bool muted = false;

	SDL_Event e;
	//starts text input
	SDL_StartTextInput();

	Mix_PlayMusic(music, -1);
	while (!quit) {
		if (muted) {
			Mix_VolumeMusic(128);
		}
		else {
			Mix_VolumeMusic(0);
		}

		//get key state for typing
		const Uint8 *state = SDL_GetKeyboardState(nullptr);
		if (SDL_WaitEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				gExit = true;
				quit = true;
				scrMode = 0;
			}
			//pause game
			if (pause.ClickedOn(e)) {
				SDL_StopTextInput();
				loadPause(quit,muted);
				SDL_StartTextInput();
			}
			//backspace for typing input
			if (state[SDL_SCANCODE_BACKSPACE] && input.length() > 0) {
				input.pop_back();
			}
			//appends text input to input string
			else if (e.type == SDL_TEXTINPUT) {
				input += e.text.text;
			}
			//checks if the input is correct
			else if (state[SDL_SCANCODE_RETURN] && levelComplete == true && e.key.repeat == 0) {
				if (input == ans_string) {
					//continue the day
					levelComplete = false;
					day++;
				}
				else {
					//day stays the same, life is deducted
					life--;
					levelComplete = false;
					SDL_StopTextInput();
					Mix_PauseMusic();
					LoseLevel(ans_string);
					SDL_StartTextInput();
					Mix_ResumeMusic();
					Mix_PlayMusic(music, -1);
					input.pop_back();
				}
				//clears input and anwser
				input = "";
				ans_string = "";
			}
		}
		//renders texture and updates them
		SDL_RenderClear(gRender);
		Background.renderTexture(backText, gRender);
		pause.renderTexture(pauseText, gRender);

		lifeImg.renderTexture(lifeTexture, gRender);
		//updates string for life counter
		life_str = "x " + std::to_string(life);
		lifeCounterTexture = LoadFont(lifeCounterTexture, life_str, { 255,255,255 }, lifefont, lifetextRect.w);
		SDL_RenderCopy(gRender, lifeCounterTexture, nullptr, &lifetextRect);
		
		//updates day counter string
		day_str = "Day: " + std::to_string(day);
		dayCounterTexture = LoadFont(dayCounterTexture, day_str, { 255,255,255 }, lifefont, daytextRect.w);
		SDL_RenderCopy(gRender, dayCounterTexture, nullptr, &daytextRect);
		
		//updates prompt message
		promptDisplay_str = "Unscramble: " + raw_string;
		promptTexture = LoadFont(promptTexture, promptDisplay_str, { 0,0,0 }, promptfont, promptRect.w);
		SDL_RenderCopy(gRender, promptTexture, nullptr, &promptRect);
		
		SDL_RenderCopy(gRender, userInputTexture, nullptr, &userInputRect);

		typeRect.w = input.length() * 10;
		TypeTexture = LoadFont(TypeTexture, input, { 0,0,0 }, typefont, 1000);
		SDL_RenderCopy(gRender, TypeTexture, nullptr, &typeRect);

		SDL_RenderPresent(gRender);

		//if player reaches day 20, he wins and game exits to the title
		if (day == 20) {
			quit = true;
			scrMode = TITLE;

			SDL_RenderClear(gRender);
			Background.setImgPath("graphics/winBG.png");
			backText = Background.LoadImage(gRender);
			Background.renderTexture(backText, gRender);
			SDL_RenderPresent(gRender);
			SDL_Delay(3000);
		}
		//if player has no lives left, player loses then goes to tips/lecture screen
		if (life <= 0) {
			quit = true;
			scrMode = LECTURE;

			SDL_RenderClear(gRender);
			Background.setImgPath("graphics/loseBG.png");
			backText = Background.LoadImage(gRender);
			Background.renderTexture(backText, gRender);
			SDL_RenderPresent(gRender);
			SDL_Delay(3000);
		}
		//generates level
		if (!levelComplete) {
			generate(diff, ans_string, day);
			raw_string = Scramble(ans_string, diff);
			levelComplete = true;
		}
		SDL_Delay(10);
	}
	//stops text input and deallocate textures
	SDL_StopTextInput();

	SDL_DestroyTexture(backText);
	backText = nullptr;

	SDL_DestroyTexture(pauseText);
	pauseText = nullptr;
	SDL_DestroyTexture(lifeTexture);
	lifeTexture = nullptr;
	SDL_DestroyTexture(dayCounterTexture);
	dayCounterTexture = nullptr;
	SDL_DestroyTexture(lifeCounterTexture);
	lifeCounterTexture = nullptr;
	SDL_DestroyTexture(userInputTexture);
	userInputTexture = nullptr;
	SDL_DestroyTexture(promptTexture);
	promptTexture = nullptr;
	SDL_DestroyTexture(TypeTexture);
	TypeTexture = nullptr;

	TTF_CloseFont(inputfont);
	inputfont = nullptr;
	TTF_CloseFont(lifefont);
	lifefont = nullptr;
	TTF_CloseFont(promptfont);
	promptfont = nullptr;
	TTF_CloseFont(typefont);
	typefont = nullptr;

	Mix_HaltMusic();
	Mix_FreeMusic(music);
	music = nullptr;

	return;
}

/*
The help screen simply displays information about the game and the rules around it
It renders the text from a .txt file in the dialog folder for organizations sake
*/
void loadHelp() {
	//updates background image
	Background.setImgPath("graphics/MainScreen.bmp");
	backText = Background.LoadImage(gRender);

	//music
	Mix_Music* music = Mix_LoadMUS("audio/help.mp3");

	//sets up back button and sets texture
	SDL_Texture* bButtonText;
	Image backButton;
	backButton.setSize(182, 60);
	backButton.setCords((WIDTH - backButton.getWidth())-70, 50);
	backButton.setImgPath("graphics/GoBackButton.png");
	bButtonText = backButton.LoadImage(gRender);
	
	//message to text texture
	std::string msg;
	//in file stream, reads file
	std::ifstream in;

	//reads the help text file
	in.open("dialog/Help.txt");
	//explit conversion to string from text document
	msg = (static_cast<std::stringstream const&>(std::stringstream() << in.rdbuf()).str());

	//Sets up text size, position, font and color
	TTF_Font* mainFont = nullptr;
	SDL_Texture* txtTexture = nullptr;
	SDL_Rect txtRect;
	txtRect.h = 600;
	txtRect.w = 900;
	txtRect.x = ((WIDTH / 2) - (txtRect.w / 2))-100;
	txtRect.y = 60;

	mainFont = TTF_OpenFont("fonts/m5x7.ttf", 24);
	SDL_Color colorText = { 0,0,0 };
	//loads texture
	txtTexture = LoadFont(txtTexture, msg, colorText, mainFont,txtRect.w);

	SDL_Event e;
	bool quit = false;

	bool muted = false;

	Mix_PlayMusic(music, -1);
	while (!quit) {
		const Uint8* state = SDL_GetKeyboardState(nullptr);
		if (SDL_WaitEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				quit = true;
				gExit = true;
			}
			//back button, sends user to title screen
			if (backButton.ClickedOn(e)) {
				scrMode = TITLE;
				quit = true;
			}
			if (state[SDL_SCANCODE_M]) {
				muted = !muted;
				if (muted) {
					Mix_VolumeMusic(128);
				}
				else {
					Mix_VolumeMusic(0);
				}
			}
		}
		//renders changed background and text
		SDL_RenderClear(gRender);
		Background.renderTexture(backText, gRender);
		backButton.renderTexture(bButtonText, gRender);
		SDL_RenderCopy(gRender, txtTexture, nullptr, &txtRect);
		SDL_RenderPresent(gRender);
		SDL_Delay(15);
	}
	//deallocates texture
	SDL_DestroyTexture(backText);
	backText = nullptr;

	SDL_DestroyTexture(txtTexture);
	txtTexture = nullptr;
	SDL_DestroyTexture(bButtonText);
	bButtonText = nullptr;
	SDL_DestroyTexture(backText);
	backText = nullptr;
	SDL_RenderClear(gRender);

	TTF_CloseFont(mainFont);
	mainFont = nullptr;

	//deallocate music
	Mix_FreeMusic(music);
	music = nullptr;
	return;
}

/*
The 'lecture' screen, is simply a screen full of tips and information regarding the game and encryption
It can be accessed through the title screen or losing the game
*/
void loadLecture() {
	//music
	Mix_Music* music = Mix_LoadMUS("audio/lecture.mp3");

	//12 premade tips to be loaded at random
	const static std::string tips[12] = {
		"The more days you survive, the harder the levels become. The harder scrambling algorithms, use permutations to shuffle the text. Most encryption keys, use a form a permutation, called Substitutation-permutation network",
		"The first 10 days have a chance of 66% giving and easy scramble, the trick is, the characters are simply shifted. Digital encryption was used during WW2 called the Engima.",
		"Encryption for the internet was originially setup by the US government, encryption didn't go public till the 1970s.",
		"A lot of effective encryption algorithms manipulate data on a binary level.",
		"The internet, has many standareds for encryption such as SSL and SSH.",
		"A common part of encryption, is the key. The key takes the text and can scramble/unscramble it.", 
		"After 9 days in game, the difficulty will shift from a 75% chance of medium messages and 25% of hard messages.",
		"Popular encyption keys, are AES, RSA and Twofish. Many keys also have key sizes, determining the amount of bits being used.",
		"There are two distinct types of encryption keys; symmetric and asymmetric. symmetric keys mean the key is used for both encrypting and decrypting. While asymmetric keys use two diferent keys to encrypt and decrypt.",
		"The hardest difficulty in this game, is the closet to actual encryption algorithms. Where the string is permutated and shuffled. Though actual algorithms use more mathematically complex methods.",
		"You can play around with encryption yourself! Many programming languages, have a crytography API to use. They include encryption keys used in industry.",
		"Encryption may be obselete thanks to quantum computing. Encryption is intended to be unbreakable by clasical computers, quantum computers could break them in hours."
	};

	//updates background
	Background.setImgPath("graphics/Lecture.bmp");
	backText = Background.LoadImage(gRender);

	//reads lecture templete text file
	std::ifstream in;
	in.open("dialog/Lecture Templete.txt");
	std::string templete = (static_cast<std::stringstream const&>(std::stringstream() << in.rdbuf()).str()); 

	//sets body text size, posiion, font and color
	TTF_Font* bodyFont = TTF_OpenFont("fonts/m5x7.ttf", 24);
	SDL_Rect bodyRect;
	bodyRect.h = 150;
	bodyRect.w = 1100;
	bodyRect.x = (WIDTH / 2) - (bodyRect.w / 2);
	bodyRect.y = 110;
	SDL_Texture* bodyTexture = nullptr;
	//loads into texture
	bodyTexture = LoadFont(bodyTexture, templete, { 0,0,0 },bodyFont,bodyRect.w);

	//generates a number from 0 - 12
	int r = rand() % 12;

	//sets up tip size, positon, font and color
	TTF_Font* tipFont = TTF_OpenFont("fonts/m5x7.ttf", 22);
	SDL_Rect tipRect;
	tipRect.h = 150;
	tipRect.w = tips[r].length()*2.8;
	tipRect.x = (WIDTH / 2) - (tipRect.w / 2);
	tipRect.y = 20 + bodyRect.h + bodyRect.y;
	SDL_Texture* tipTexture = nullptr;
	//loads tip texture
	tipTexture = LoadFont(tipTexture, tips[r], { 0,0,0 }, tipFont, tipRect.w);

	bool quit = false;
	bool muted = false;
	SDL_Event e;

	Mix_PlayMusic(music, -1);
	while (!quit) {
		const Uint8* state = SDL_GetKeyboardState(nullptr);
		if (SDL_WaitEvent(&e) != 0) {
			if (e.type == SDL_KEYDOWN) {
				//hitting q, exits to title screen
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
			if (state[SDL_SCANCODE_M]) {
				muted = !muted;
				if (muted) {
					Mix_VolumeMusic(128);
				}
				else {
					Mix_VolumeMusic(0);
				}
			}
		}
		//Render text
		SDL_RenderClear(gRender);
		Background.renderTexture(backText, gRender);
		SDL_RenderCopy(gRender, bodyTexture, nullptr, &bodyRect);
		SDL_RenderCopy(gRender, tipTexture, nullptr, &tipRect);
		SDL_RenderPresent(gRender);
		SDL_Delay(10);
	}
	//deallocates textures
	SDL_DestroyTexture(backText);
	backText = nullptr;

	SDL_DestroyTexture(bodyTexture);
	bodyTexture = nullptr;
	SDL_DestroyTexture(tipTexture);
	tipTexture = nullptr;

	TTF_CloseFont(bodyFont);
	bodyFont = nullptr;

	//deallocate music
	Mix_FreeMusic(music);
	music = nullptr;

	return;
}