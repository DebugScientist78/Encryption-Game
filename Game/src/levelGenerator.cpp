//main.h ties in the project files in a simple include file and can be called easily
#include "../include/main.h"

/*
* Program name: levelGenerator.cpp
* Date: 10/23/2019
* Purpose: This source file defines the functions that generate the levels
* and scramble randomly chosen messages
* Author: Chency W
*/

//Set of simply messages
const std::string easy_msgs[15] = {
	"Jerry",
	"Justin",
	"Dogs and cats",
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

//set of medium level messages
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

//set of hard and complex messages
const std::string hard_msgs[5] = {
	"Carsten likes to play games",
	"the Dell laptop is small",
	"This game is quite bad", 
	"A lot of birds sing", 
	"JoJo's Bizzare Adventure"
};

//scrambles the message depending on its diffuclty
std::string Scramble(std::string input, int diff) {
	std::string new_str;
	std::string temp;
	temp = input;
	//to be used to generate random numbers
	int r;
	if (diff == EASY) {
		//EASY scramble algorithm
		while (temp == input) {
			//rand gives a random number, the modulos sets the max range of the number
			r = (rand() % input.length() - 1)+1;
			//the string is shifted randomly
			std::reverse(temp.begin(), temp.begin() + r);
			std::reverse(temp.begin() + r, temp.end());
			std::reverse(temp.begin(), temp.end());
		}
		new_str = temp;
	}
	else if (diff == MEDIUM) {
		//MEDIUM scramble algorithm
		while (temp == input) {
			//repeats 4 times instead of once
			for (int i = 0; i < 4; i++) {
				r = rand() % input.length();
				std::reverse(temp.begin(), temp.begin() + r);
				std::reverse(temp.begin() + r, temp.end());
				std::reverse(temp.begin(), temp.end());
				//Addtionally, the string's characters are now shuffled
				std::random_shuffle(temp.begin(), temp.end());
			}
		}
		new_str = temp;
	}
	else {
		//HARD scramble algorithm
		while (temp == input) {
			//repeats 16 times
			for (int i = 0; i < 16; i++) {
				//turns the string into a possible permutation of itself
				if (std::next_permutation(temp.begin(), temp.end())) {
					//randomly can loop once to 4 times
					r = rand() % 4;
					for (int f = 0; f < r; f++) {
						//shuffles the string
						std::random_shuffle(temp.begin(), temp.end());
					}
				}
			}
		}
		new_str = temp;
	}
	return new_str;
}

//generates the message upon defined list of messages for EASY, MEDIUM and HARD difficulty
void generate(int& diff, std::string& msg, int day) {
	//used for randomly generated numbers
	int r;

	//Difficulty is set to EASY or MEDIUM 
	if (day < 10) {
		r = rand() % 3;
		//A 66% chance of EASY message
		if (r != 0) {
			diff = EASY;
			//randomly picks the message from the array
			r = rand() % 15;
			msg = easy_msgs[r];
		}
		else {
			diff = MEDIUM;
			r = rand() % 10;
			msg = med_msgs[r];
		}
	}
	//Dfficulty can be MEDIUM or HARDs
	else if (day < 15) {
		//75% chance of MEDIUM message
		r = rand() % 4;
		if (r != 0) {
			diff = MEDIUM;
			r = rand() % 10;
			msg = med_msgs[r];
		}
		else {
			diff = HARD;
			r = rand() % 5;
			msg = hard_msgs[r];
		}
	}
	//after 15 days, only hard messages appear
	else {
		diff = HARD;
		r = rand() % 5;
		msg = hard_msgs[r];
	}
	return;
}