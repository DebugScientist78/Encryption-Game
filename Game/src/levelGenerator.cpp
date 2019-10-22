#include "../include/main.h"

const std::string easy_msgs[15] = {
	"Jerry",
	"Justin",
	"Dogs and Cats",
	"Templmen",
	"Param",
	"cookies",
	"James",
	"Computer",
	"laptop",
	"Birds",
	"Block",
	"hundred",
	"Chocolate Milk",
	"Carsten",
	"Anmol"
};

const std::string med_msgs[10] = {
	"Jerry has cake",
	"Justin is here",
	"Milk and Cookies",
	"random numbers",
	"Anmol does CAD",
	"Red birds", 
	"two blocks",
	"is Carsten here?", 
	"Personal Computer", 
	"tiny cats"
};

const std::string hard_msgs[5] = {
	"Carsten likes to play games",
	"the Dell laptop is small",
	"This game is quite bad", 
	"A lot of birds sing", 
	"JoJo's Bizzare Adventure"
};

std::string Scramble(std::string input, int diff) {
	std::string new_str;
	std::string temp;
	temp = input;
	int r;
	if (diff == EASY) {
		//EASY scramble algorithm
		while (temp == input) {
			r = (rand() % input.length() - 1)+1;
			std::reverse(temp.begin(), temp.begin() + r);
			std::reverse(temp.begin() + r, temp.end());
			std::reverse(temp.begin(), temp.end());
		}
		new_str = temp;
	}
	else if (diff == MEDIUM) {
		//MEDIUM scramble algorithm
		while (temp == input) {
			for (int i = 0; i < 4; i++) {
				r = rand() % input.length();
				std::reverse(temp.begin(), temp.begin() + r);
				std::reverse(temp.begin() + r, temp.end());
				std::reverse(temp.begin(), temp.end());
				std::random_shuffle(temp.begin(), temp.end());
			}
		}
		new_str = temp;
	}
	else {
		while (temp == input) {
			for (int i = 0; i < 16; i++) {
				if (std::next_permutation(temp.begin(), temp.end())) {
					r = rand() % 4;
					for (int f = 0; f < r; f++) {
						std::random_shuffle(temp.begin(), temp.end());
						std::random_shuffle(temp.begin(), temp.end());
					}
				}
			}
		}
		new_str = temp;
	}
	return new_str;
}

void generate(int& diff, std::string& msg, int day) {
	int c;
	if (day < 10) {
		c = rand() % 3;
		if (c != 0) {
			diff = EASY;
			c = rand() % 15;
			msg = easy_msgs[c];
		}
		else {
			diff = MEDIUM;
			c = rand() % 10;
			msg = med_msgs[c];
		}
	}
	else if (day < 15) {
		c = rand() % 4;
		if (c != 0) {
			diff = MEDIUM;
			c = rand() % 10;
			msg = med_msgs[c];
		}
		else {
			diff = HARD;
			c = rand() % 5;
			msg = hard_msgs[c];
		}
	}
	else {
		diff = HARD;
		c = rand() % 5;
		msg = hard_msgs[c];
	}
	return;
}