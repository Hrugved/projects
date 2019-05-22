//Bull-Cow game which can be played by two players

#pragma once
#include<iostream>
#include<string>
#include<conio.h>
#include"FBullCowGame.h"


using FText = std::string;
using int32 = int;

void printIntro();
void PrintDetails();
void GameSetup();
void playGame(FBullCowGame&);
FText GetValidGuess(FBullCowGame&);
void Display(int);
void PrintSummary(FBullCowGame&);
void PrintResult();  
bool askToPlayAgain();

//intializing two instances of class
FBullCowGame Player1;
FBullCowGame Player2;


//GAME CONTROLLER STARTS HERE
int main(void) {
	do {
		printIntro(); //print all the details
		GameSetup();  //setting up game by asking player`s their names, hidden word length, max tries, and setting each other`s hidden word
		std::cout << " " << Player1.GetPlayerName() << " will go first. Best of luck!\n" <<
			                                           " You have to guess hidden word given by "<<Player2.GetPlayerName()<<" in "<<Player1.GetMaxTries()<<" guesses\n"<<
			                                           " No. of COWS = no.of letters(in guess) which are also present in hidden word but are NOT in same position.\n"<<
			                                           " No. of BULLS = no.of letters(in guess) which are also present in hidden word and are in same position.\n"<<
			                                           " Remember you could always use hint (by typing ??), but at cost of few Energy-points\n"<<
			                                           " Best Of Luck"<<std::endl; 
		Seperator('-', 150);
		playGame(Player1);//player1 plays the game 
		std::cout << " " << Player2.GetPlayerName() << " will go now. Best of luck!\n" <<  
		                                               " You have to guess hidden word given by " << Player1.GetPlayerName() << " in " << Player1.GetMaxTries() << " guesses\n"<<
			                                           " No. of COWS = no.of letters(in guess) which are also present in hidden word but are NOT in same position.\n" <<
			                                           " No. of BULLS = no.of letters(in guess) which are also present in hidden word and are in same position.\n" <<
			                                           " Remember you could always use hint (by typing ??), but at cost of few Energy-points\n" << 
			                                           " Best Of Luck" << std::endl; 
		Seperator('-', 150);
		playGame(Player2); //player2 plays the game 
		PrintResult(); //compare scores of both player and declare winner or tie
	} while (askToPlayAgain());
}

void printIntro() {
	std::cout<< R"(
                      oooooo   oooooo     oooo           oooo                                                       ooooooooooooo           
                      `888.    `888.     .8'            `888                                                       8'   888   `8           
w                       `888.   .8888.   .8'    .ooooo.   888   .ooooo.   .ooooo.  ooo. .oo.  .oo.    .ooooo.            888       .ooooo.  
                        `888  .8'`888. .8'    d88' `88b  888  d88' `"Y8 d88' `88b `888P"Y88bP"Y88b  d88' `88b           888      d88' `88b 
                         `888.8'  `888.8'     888ooo888  888  888       888   888  888   888   888  888ooo888           888      888   888 
                          `888'    `888'      888    .o  888  888   .o8 888   888  888   888   888  888    .o           888      888   888 
                           `8'      `8'       `Y8bod8P' o888o `Y8bod8P' `Y8bod8P' o888o o888o o888o `Y8bod8P'          o888o     `Y8bod8P' 
                                 ______  _   _  _      _      _____       ___   _   _ ______       _____  _____  _    _  _____ 
                                 | ___ \| | | || |    | |    /  ___|     / _ \ | \ | ||  _  \     /  __ \|  _  || |  | |/  ___|
                                 | |_/ /| | | || |    | |    \ `--.     / /_\ \|  \| || | | |     | /  \/| | | || |  | |\ `--. 
                                 | ___ \| | | || |    | |     `--. \    |  _  || . ` || | | |     | |    | | | || |/\| | `--. \
                                 | |_/ /| |_| || |____| |____/\__/ /    | | | || |\  || |/ /      | \__/\\ \_/ /\  /\  //\__/ /
                                 \____/  \___/ \_____/\_____/\____/     \_| |_/\_| \_/|___/        \____/ \___/  \/  \/ \____/ 

					                               !!! A FUN WORD GAME !!!
)" << "\n";
	PrintDetails();
}

void PrintDetails()
{
	system("PAUSE");//freeze the output scren till any key is entered
	std::cout
		<< "  GUIDELINES TO PLAY:\n"
		<< " 		1.  Two players can play this game.\n"
		<< " 		2.  Each player will enter a hidden word for other player to guess.\n"
		<< " 		3.  Next each player will have to guessed opponent`s hidden word.\n"
		<< " 		4.  Each guess will be evaluated and count of BULLS and COWS will be displayed.\n"
		<< " 		5.  No. of COWS = no. of letters(in guess) which are also present in hidden word but are NOT in same position.\n"
		<< " 		6.  No. of BULLS = no. of letters(in guess) which are also present in hidden word and are in same position.\n"
		<< "		7.  Player may opt for hint by typing ' ?? ' (without quotes) instead of guess.\n\n";
	system("PAUSE");
std::cout<< "  -------------------------------------------------------    ADDITIONAL POINTS    -------------------------------------------------------\n"
		<< "  POINTS TO KEEP IN MIND:\n"
		<< " 		8.  Only certain no. of tries are allowed for guessing(Max no. of tries will be agreed upon by both players before the start of the game)\n"
		<< "  RULES FOR ENTERING GUESS:\n"
		<< " 		9.  Make sure guess entered is *all lowercase, *is isogram, *same length as hidden word.\n"
		<< " 		10. ?? will be interpreted as asking for hint.\n\n"
		<< "  HOW WINNER WILL BE DECIDED: \n"
		<< " 		11. Winner will be the one with least no. of tries taken to guessed opponent`s hidden word.\n"
		<< " 		12. In case of equal no. of tries, winner will be the one with highest Energy-Points.\n\n"
		<< "  ENERGY POINTS:\n"
		<< " 		13. For each bull more than previous guess, player will get 10 Energy-points and\n"
		<< "                14. for each cow more than previous guess, player will get 5 Energy-points.\n"
		<< " 		15. similarly for each less bull and cow from previous guess, 10 and 5 energypoints each will be deducted respectively.\n\n"
		<< "  WARNING:\n"
		<< " 		16. Hint will cost you some Energy-points so please think before asking.\n\n";
system("PAUSE");
system("CLS");//clear the comsole screen
}

void GameSetup() {
	int32 HiddenWordLength, MaxTries;
	std::cout << " For fair play, both players will have to will agree upon length of hidden words and number of max tries allowed!\n\n";
	Seperator('-', 150);
	std::cout << " Select Length of Hidden Word: "; std::cin >> HiddenWordLength;
	Seperator('-', 150);
	std::cout << " Select maximum allowed tries to guess each other`s hidden word: "; std::cin >> MaxTries; std::cin.ignore();
	Seperator('-', 150);
	Player1.Reset(Player2, HiddenWordLength, MaxTries);// update`s player1`s name, reset private variables and gets hidden word and hint for player2 
	std::cout << "\n"; Seperator('$', 150); 
	Player2.Reset(Player1, HiddenWordLength, MaxTries);// update`s player12`s name, reset private variables and gets hidden word and hint for player1 
	Seperator('$', 150);
	std::cout << R"( 
                                _              _     _           ____                   _      _ 
                               | |       ___  | |_  ( )  ___    |  _ \    ___     ___  | | __ | |
                               | |      / _ \ | __|  \| / __|   | |_) |  / _ \   / __| | |/ / | |
                               | |___  |  __/ | |_      \__ \   |  _ <  | (_) | | (__  |   <  |_|
                               |_____|  \___|  \__|     |___/   |_| \_\  \___/   \___| |_|\_\ (_)

)";
	Seperator('$', 150);
	system("PAUSE");
	system("CLS");
}

void playGame(FBullCowGame& BCGame) { //passing object by reference for obvious reasons
	
	int32 MaxTries = BCGame.GetMaxTries();

	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {
		FText guess = GetValidGuess(BCGame);
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(guess);
		BCGame.UpdateEnergyPoints(BullCowCount);
		std::cout << " BULLS = "; Display(BullCowCount.bulls); std::cout<<"\n"
				  << " COWS  = "; Display(BullCowCount.cows); std::cout << "\n\n";
		Seperator('-', 150);
	}
	PrintSummary(BCGame);
	system("PAUSE");
	system("CLS");
}

FText GetValidGuess(FBullCowGame& BCGame) {
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	FText guess = "";
	do {
		//take input and store it in guess
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << " Try " << CurrentTry << " of " << BCGame.GetMaxTries() << ",Enter your guess: ";
		std::getline(std::cin, guess);
		//keep looping and error-checking till we get a valid guess from user
		Status = BCGame.CheckGuessValidity(guess);
		switch (Status) {
		case EGuessStatus::AskingForHint:
			BCGame.DisplayHint();
			BCGame.HintPenalty();
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << " Please enter a valid isogram(no repetating letters).\n\n";
			break;
		case EGuessStatus::Not_lowercase:
			std::cout << " Please enter all lowercase letters.\n\n";
			break;
		case EGuessStatus::Wrong_length:
			std::cout << " Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		default:
			//assuming its a valid guess
			break;
		}
	} while (Status != EGuessStatus::Ok);
	return guess;
}

void PrintSummary(FBullCowGame& BCGame) {
	if (BCGame.IsGameWon()) {
		std::cout << " Well Done - You Guessed it in " << BCGame.GetCurrentTry()-1 <<" tries!\n\n\n";
	}
	else {
		std::cout << " phew that was tough one!\n\n\n";
	}
}

void PrintResult() {

	std::cout << R"(
       ____                                 ___                          
      / ___|   __ _   _ __ ___     ___     / _ \  __   __   ___   _ __   
     | |  _   / _` | | '_ ` _ \   / _ \   | | | | \ \ / /  / _ \ | '__|  
     | |_| | | (_| | | | | | | | |  __/   | |_| |  \ V /  |  __/ | |     
      \____|  \__,_| |_| |_| |_|  \___|    \___/    \_/    \___| |_|     
                                                                    
     __        __         _   _     ____    _                              _ _ 
     \ \      / /   ___  | | | |   |  _ \  | |   __ _   _   _    ___    __| | |
      \ \ /\ / /   / _ \ | | | |   | |_) | | |  / _` | | | | |  / _ \  / _` | |
       \ V  V /   |  __/ | | | |   |  __/  | | | (_| | | |_| | |  __/ | (_| |_|
        \_/\_/     \___| |_| |_|   |_|     |_|  \__,_|  \__, |  \___|  \__,_(_)
                                                        |___/                  


)";
	if (Player1.GetCurrentTry() == Player2.GetCurrentTry()) { //if both players took same no. of guesses, compare Energy-Points
		if (Player1.GetEnergyPoints() > Player2.GetEnergyPoints()) { //player with more Energy-Points is winner 
			std::cout << " The Winner Is " << Player1.GetPlayerName() << "\n\n";
		}
		else if (Player1.GetEnergyPoints() < Player2.GetEnergyPoints()) {
			std::cout << " The Winner Is " << Player2.GetPlayerName() << "\n\n";
		}
		else {
			std::cout << " Wow! That`s a Tie!\n\n";
		}
	}
	else if (Player1.GetCurrentTry() < Player2.GetCurrentTry()) {   //player with least no. of guesses taken is winner 
		std::cout <<" The Winner Is " << Player1.GetPlayerName() <<"\n\n";
	}
	else {
		std::cout << " The Winner Is " << Player2.GetPlayerName() << "\n\n";
	}
	
}

bool askToPlayAgain() {
	std::cout << " Do you want to play again? (yes/no) : ";
	FText Response = "";
	std::getline(std::cin, Response);
	return ((Response[0] == 'y') || (Response[0] == 'Y'));
}

//displays two whiteboxes for each 1 unit 
void Display(int n) {
	for (int i = 0; i < 2*n; i++) {
		std::cout << (char)178u; //extended ascii for whitebox
	};
	std::cout <<" "<<n;
}

//prints char 'sep' n times
void Seperator(char sep, int n)
{
	for (int i = 0; i < n; i++) {
		std::cout << sep;
	}
	std::cout << "\n";
}
