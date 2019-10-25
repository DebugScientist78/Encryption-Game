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
	//variable that represents the Events that SDL2 records
	SDL_Event e;

	//loops until user leaves screen or exits game
	while (!quit_flag) {
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
		SDL_Delay(15);
	}
	//deallocates textures upon exit
	SDL_DestroyTexture(titleText);
	titleText = NULL;
	SDL_DestroyTexture(startBlockText);
	startBlockText = NULL;
	SDL_DestroyTexture(lectureText);
	lectureText = NULL;
	SDL_DestroyTexture(HelpText);
	HelpText = NULL;
	SDL_DestroyTexture(backText);
	backText = NULL;
	return;
}

/*
This is more of a pop up, rather than a screen, it only loads the pause box texture, and stops the main screen
This is done since, the program is ran sequentially, meaning the main loop isn't able to refresh/update as the 
program is stuck in the pause's while loop

NOTE: this may cause RAM use to jump, I haven't tested though
*/
void loadPause(bool& mainQuit) {

	//sets up pause box size, position and image
	// loads it into the pause box texture
	SDL_Texture* pausebText;
	Image pauseB = Image();
	pauseB.setSize(120, 80);
	//middle of the screen
	pauseB.setCords((WIDTH / 2) - (pauseB.getWidth() / 2), (HEIGHT / 2) - (pauseB.getHeight() / 2));
	pauseB.setImgPath("graphics/Pausebox.bmp");
	pausebText = pauseB.LoadImage(gRender);


	bool quit = false;
	SDL_Event e;

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
				}
			}
		}
		//renders the pause box texture but not clearing the main screen texture
		pauseB.renderTexture(pausebText, gRender);
		SDL_RenderPresent(gRender);
	}
	//deallocates texture
	SDL_DestroyTexture(pausebText);
	pausebText = NULL;
	return;
}

void LoseLevel() {
	static const std::string questions[15] = {
		"What is encryption?",//1
		"What is a symmetric key?",//2
		"What is today's strongest encryption key?",//3
		"What does the Asymmetric key mean?",//4
		"How should a person handle information?",//5
		"What does SP-network mean?",
		"What level of information does encryption change?",
		"When did encryption in the US go public?",
		"What does the Symmetric key mean?",
		"What was the Enigma?",
		"How is encryption relevent?",
		"How does a computer struggle with encryption?",
		"What is the purpose of encryption?",
		"What does SSL mean?",
		"Why is it encryption hard to break?"
	};

	static const std::vector<std::vector< std::string> > answers = {
		{
			{//1
				"A) The process of scrambling messages and securing it",
				"B) Creating algorithms for a machine",
				"C) Making a computer run",
				"D) Installing anti-virus programs"
			}
		},
		{
			{//2
				"A) A key when drawn, looks symmetric",
				"B) A key that is used for both encrypting and decrypting",
				"C) A key that shows the message before and after encrypting",
				"D) A key with only one function"
			}
		},
		{
			{//3
				"A) DES",
				"B) MD5",
				"C) Blowfish",
				"D) AES"
			}
		},
		{
			{//4
				"A) A key when drawn, looks aysmmetric",
				"B) A key that is different from a symmetric key",
				"C) A key that has two different keys for encryprting and decrypting",
				"D) A key that has two keys for the client and server"
			}
		},
		{
			{//5
				"A) Show everybody and gain trust"
				"B) Give anyone they know the information",
				"C) secure it with encryption",
				"D) Sell the information"
			}
		}
	};

	static const bool answerValues[15][4] = {
		{//1
			true,false,false,false
		},
		{//2
			false,true,false,false
		}
	};

	static const std::string hardQuestions[5] = {
		"What is the principles of modern encryption?",
		"How can encryption keys be exploited?",
		"Why can quantum computers break encryption?",
		"What does permutation mean?",
		"Why is encryption a political concern?",
	};

	static const std::vector<std::vector<std::string>  > hardAnswers = {
	};

	static const bool hardAnswersValues[5][4] = {
	};

	std::string question;
	std::vector<std::string> anwsersIn;
	int r;
	r = rand();
	question = question[r];
	anwsersIn[0] = answers[r].at(0);
	SDL_SetRenderDrawColor(gRender, 245, 138, 66, 0);
	SDL_Rect backdrop = { WIDTH / 3, HEIGHT / 3, WIDTH / 2, HEIGHT / 2 };
	SDL_RenderFillRect(gRender, &backdrop);

	SDL_Texture* questionTexture = NULL;
	SDL_Rect questionRect = { question.length() * 2,90,backdrop.x,backdrop.y + 10 };
	TTF_Font* questionFont = TTF_OpenFont("fonts/m5x7.ttf", 16);
	questionTexture = LoadFont(questionTexture, question, { 0,0,0 }, questionFont, questionRect.w);

	bool quit = false;
	SDL_Event e;
	while (!quit) {
		const Uint8 *state = SDL_GetKeyboardState(NULL);
		if (SDL_WaitEvent(&e) != 0) {
		}
		SDL_RenderCopy(gRender, questionTexture, NULL, &questionRect);
		SDL_RenderPresent(gRender);
		SDL_Delay(10);
	}

	SDL_SetRenderDrawColor(gRender, 0, 0, 0, 0);
	backdrop = { 0,0,0,0 };
	SDL_RenderFillRect(gRender, &backdrop);
	SDL_RenderPresent(gRender);

	return;
}



/*
This function loads the main game screen and the logic in the game.
Where it calls upon the generate and scramble function, in a loop to give constant user feed back
The user input is also displayed below the message needed to be scrambled
*/
void loadMain() {

	//variables for the game, difficulty, life and messages
	int diff;
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
	SDL_Texture* lifeCounterTexture = NULL;
	TTF_Font* lifefont = TTF_OpenFont("fonts/m5x7.ttf",30);
	SDL_Rect lifetextRect;
	lifetextRect.h = 63;
	lifetextRect.w = 80;
	lifetextRect.x = lifeImg.getWidth() + lifeImg.getRect().x + 10;
	lifetextRect.y = lifeImg.getRect().y;
	std::string life_str = "x " + std::to_string(life);
	lifeCounterTexture = LoadFont(lifeCounterTexture, life_str, { 0,0,0 }, lifefont, lifetextRect.w);

	//sets up day counter
	SDL_Texture* dayCounterTexture = NULL;
	SDL_Rect daytextRect;
	daytextRect.h = 63;
	daytextRect.w = 90;
	daytextRect.x = lifetextRect.w + lifetextRect.x + 40;
	daytextRect.y = lifetextRect.y;
	std::string day_str = "Day: " + std::to_string(day);
	dayCounterTexture = LoadFont(dayCounterTexture, day_str, { 0,0,0 }, lifefont, daytextRect.w);

	//sets up prompt message
	SDL_Texture* promptTexture = NULL;
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
	SDL_Texture* userInputTexture = NULL;
	SDL_Rect userInputRect;
	userInputRect.h = 70;
	userInputRect.w = 100;
	userInputRect.x = (WIDTH / 2) - (userInputRect.w / 2);
	userInputRect.y = promptRect.y + 100;
	TTF_Font* inputfont = TTF_OpenFont("fonts/m5x7.ttf", 30);
	std::string userDisplay_str = "Input: ";
	userInputTexture = LoadFont(userInputTexture, userDisplay_str, { 0,0,0 }, inputfont, userInputRect.w);

	//sets up typing feedback
	SDL_Texture* TypeTexture = NULL;
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

	SDL_Event e;
	//starts text input
	SDL_StartTextInput();
	while (!quit) {
		//get key state for typing
		const Uint8 *state = SDL_GetKeyboardState(NULL);
		if (SDL_WaitEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				gExit = true;
				quit = true;
				scrMode = 0;
			}
			//pause game
			if (pause.ClickedOn(e)) {
				loadPause(quit);
			}
			//backspace for typing input
			if (state[SDL_SCANCODE_BACKSPACE] && input.length() > 0) {
				input.pop_back();
			}
			//appends text input to input string
			else if (e.type == SDL_TEXTINPUT) {
				std::cout << "text added" << std::endl;
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
					LoseLevel();
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
		SDL_RenderCopy(gRender, lifeCounterTexture, NULL, &lifetextRect);
		
		//updates day counter string
		day_str = "Day: " + std::to_string(day);
		dayCounterTexture = LoadFont(dayCounterTexture, day_str, { 255,255,255 }, lifefont, daytextRect.w);
		SDL_RenderCopy(gRender, dayCounterTexture, NULL, &daytextRect);
		
		//updates prompt message
		promptDisplay_str = "Unscramble: " + raw_string;
		promptTexture = LoadFont(promptTexture, promptDisplay_str, { 0,0,0 }, promptfont, promptRect.w);
		SDL_RenderCopy(gRender, promptTexture, NULL, &promptRect);
		
		SDL_RenderCopy(gRender, userInputTexture, NULL, &userInputRect);

		typeRect.w = input.length() * 10;
		TypeTexture = LoadFont(TypeTexture, input, { 0,0,0 }, typefont, 1000);
		SDL_RenderCopy(gRender, TypeTexture, NULL, &typeRect);

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
			SDL_Delay(5000);
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
			SDL_Delay(5000);
		}
		//generates level
		if (!levelComplete) {
			generate(diff, ans_string, day);
			raw_string = Scramble(ans_string, diff);
			levelComplete = true;
		}
	}
	//stops text input and deallocate textures
	SDL_StopTextInput();
	SDL_DestroyTexture(pauseText);
	pauseText = NULL;
	SDL_DestroyTexture(lifeTexture);
	lifeTexture = NULL;
	SDL_DestroyTexture(lifeCounterTexture);
	lifeCounterTexture = NULL;
	SDL_DestroyTexture(userInputTexture);
	userInputTexture = NULL;
	SDL_DestroyTexture(promptTexture);
	promptTexture = NULL;
	SDL_DestroyTexture(TypeTexture);
	TypeTexture = NULL;
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

	//sets up back button and sets texture
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
	TTF_Font* maintxt = NULL;
	SDL_Texture* txtTexture = NULL;
	SDL_Rect txtRect;
	txtRect.h = 600;
	txtRect.w = 900;
	txtRect.x = ((WIDTH / 2) - (txtRect.w / 2))-100;
	txtRect.y = 60;

	maintxt = TTF_OpenFont("fonts/m5x7.ttf", 24);
	SDL_Color colorText = { 0,0,0 };
	//loads texture
	txtTexture = LoadFont(txtTexture, msg, colorText, maintxt,txtRect.w);

	SDL_Event e;
	bool quit = false;

	while (!quit) {
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
		}
		//renders changed background and text
		SDL_RenderClear(gRender);
		Background.renderTexture(backText, gRender);
		backButton.renderTexture(bButtonText, gRender);
		SDL_RenderCopy(gRender, txtTexture, NULL, &txtRect);
		SDL_RenderPresent(gRender);
		SDL_Delay(15);
	}
	//deallocates texture
	SDL_DestroyTexture(txtTexture);
	txtTexture = NULL;
	SDL_DestroyTexture(bButtonText);
	bButtonText = NULL;
	SDL_DestroyTexture(backText);
	backText = NULL;
	SDL_RenderClear(gRender);
	return;
}

/*
The 'lecture' screen, is simply a screen full of tips and information regarding the game and encryption
It can be accessed through the title screen or losing the game
*/
void loadLecture() {
	//12 premade tips to be loaded at random
	std::string tips[12] = {
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
	SDL_Texture* bodyTexture = NULL;
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
	SDL_Texture* tipTexture = NULL;
	//loads tip texture
	tipTexture = LoadFont(tipTexture, tips[r], { 0,0,0 }, tipFont, tipRect.w);

	bool quit = false;
	SDL_Event e;
	while (!quit) {
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
		}
		//Render text
		SDL_RenderClear(gRender);
		Background.renderTexture(backText, gRender);
		SDL_RenderCopy(gRender, bodyTexture, NULL, &bodyRect);
		SDL_RenderCopy(gRender, tipTexture, NULL, &tipRect);
		SDL_RenderPresent(gRender);
	}
	//deallocates textures
	SDL_DestroyTexture(backText);
	backText = NULL;
	SDL_DestroyTexture(bodyTexture);
	bodyTexture = NULL;
	SDL_DestroyTexture(tipTexture);
	tipTexture = NULL;
	return;
}