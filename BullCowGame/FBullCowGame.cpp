#pragma once
#include<iostream>
#include "FBullCowGame.h"
#include <map>
#include<string>
#include<conio.h>
#define TMap std::map

using int32 = int;
using uint32 = unsigned int;


int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
int32 FBullCowGame::GetEnergyPoints() const { return EnergyPoints; }
FString FBullCowGame::GetPlayerName() const { return MyName;}
int32 FBullCowGame::GetMaxTries() const {return MyMaxTry;}
bool FBullCowGame::IsGameWon() const {return bIsGameWon;}
FString FBullCowGame::GetHiddenWord() const {return MyHiddenWord;}

//updates MyhiddenWord with provided string
void FBullCowGame::SetHiddenWord(FString HiddenWord)
{
	MyHiddenWord = HiddenWord;
}

//checks if player is allowed to take hint, if yes then let player choose hinttypes 1 or 2 (or 3 if opponent leaves a custom hint) and displays as suits 
void FBullCowGame::DisplayHint()
{
	if (HintsTaken > 2*MyHiddenWord.length()/3) { std::cout << " Sorry you can`t take more than two hints. You are on your own!\n\n"; return; } //limited hints allowed
	
	int32 HintType;
	std::cout << " Types of Hints to ask for: " << std::endl;
	std::cout << " 1 : Enter letter to know its position." << std::endl;
	std::cout << " 2 : Enter position(index starting from 1) to know letter present there." << std::endl;
	bool CustomHintPresent = false;
	if (MyHint != "") { //is opponent left a custom hint which is equivalent to say if MyHint is non-empty
		std::cout << " 3 : Enter 3 for custom hint." << std::endl;
		CustomHintPresent = true;
	}
	do {
		std::cout << " Enter Hint-type: ";
		std::cin >> HintType;
	} while (HintType != 1 && HintType != 2 && CustomHintPresent && HintType!=3 );

	if (HintType == 1) {
		char Letter;
		std::cout << " Enter Letter: "; std::cin >> Letter;
		for (uint32 Position = 0; Position < MyHiddenWord.length(); Position++) {
			if (Letter == MyHiddenWord[Position]) {
				std::cout << " " << Letter << " is at position " << Position + 1 << " in hidden word.\n\n" << std::endl;
				std::cin.ignore();//to ignore '\n' left by cin  in stream, which creates a bug with getline registering '\n' as a input
				return;
			}
		}
		std::cout << Letter << " is not present in the hidden word.\n\n";
	}

	else if(HintType == 2) {
		uint32 Position;
		std::cout << " Enter Position(1-" << MyHiddenWord.length() << ") :"; std::cin >> Position;
		if (1 <= Position && Position <= MyHiddenWord.length() + 1) { 
			std::cout << " Letter " << MyHiddenWord[Position - 1] << " is present at position " << Position << ".\n" << std::endl;
		}
		else {
			std::cout << Position << " is invalid position.\n" << std::endl;
		}
	}

	else if(HintType == 3){
		std::cout << " Hint: " << MyHint << "\n\n";
	}

	std::cin.ignore();//to ignore '\n' which creates a bug with getline registering '\n' as a input
	return;
}

//sets the word entered by player as MyHiddenWord of other player 
void FBullCowGame::GetValidHiddenWord(FBullCowGame& Player, int32 WordLimit)
{
	FString Word;
	int32 WordChar;
	std::cout << " Please enter the hidden word of length "<< WordLimit <<" for other player to guess,";
	while(true) {
		std::cout << " Please ensure it`s an valid isogram(no repeating letters) only: ";
		Word = "";
		//to let player input hidden word with secreacy (displays * instead of actual chars on console screen)!
		for (WordChar = 0; WordChar < WordLimit; WordChar++) {
			Word.push_back(tolower(_getch()));  //changes char to lowercase and adds the char to string
			std::cout << "*";
		}
		while (_getch() != 13); //to ignore all keystrokes instead of enter. It ensures player enters hidden word only of agreed upon length.
		std::cout << "\n";
		if (ValidCharsInString(Word) && IsIsogram(Word)) {  //to check if its all alphabets and an isogram
			std::cout << " Hit Enter to CONTINUE , else hit any other key to RE-ENTER hidden word... ";//just to confirm if player wants to change hidden word
			if (_getch() == 13) { break; } 
		}
		std::cout << "\n";
	}
	Player.SetHiddenWord(Word);//update opponent`s hidden word
	std::cout << "\n";
}

// update`s player`s name, gets hidden word and hint for other player, reset private variables
void FBullCowGame::Reset(FBullCowGame& OpponentPlayer, int32 HiddenWordLength, int32 MaxTries)
{
	
	std::cout << " Please enter your name: "; std::getline(std::cin, MyName);       Seperator('-', 150);
	GetValidHiddenWord(OpponentPlayer,HiddenWordLength);                           Seperator('-', 150);
	GetHintForOpponent(OpponentPlayer);                                            
	MyCurrentTry = 1;
	MyMaxTry = MaxTries;
	bIsGameWon = false;
	EnergyPoints = 0;
	HintsTaken = 0;
	return;
}

//checks recieved guess on parameters of EGuesssStatus
EGuessStatus FBullCowGame::CheckGuessValidity(FString guess) {
	if (guess == "??") { HintsTaken++ ; return  EGuessStatus::AskingForHint; }
	else if (!IsIsogram(guess)) { return EGuessStatus::Not_Isogram; }
	else if (!IsLowercase(guess)) { return EGuessStatus::Not_lowercase; }
	else if (guess.length() != GetHiddenWordLength()) { return EGuessStatus::Wrong_length; }
	else { return EGuessStatus::Ok; }
}

//recieves a VALID guess, increments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount; //all values intialized to zero
	int32 WordLength = MyHiddenWord.length(); //valid guess has same length as that of hidden word
	//loop through all letters in guess
	for (int GuessChar = 0; GuessChar < WordLength; GuessChar++) {
		//compare against letters of hidden word
		for (int32 HWchar = 0; HWchar < WordLength; HWchar++) {
			if (Guess[GuessChar] == MyHiddenWord[HWchar]) { //if they match
				if (GuessChar == HWchar) BullCowCount.bulls++; //if they are in same place->increment bulls
				else BullCowCount.cows++; //otherwise must incrememnt cows
			}
		}
		bIsGameWon = (BullCowCount.bulls == GetHiddenWordLength()) ? true : false;
	}
	
	return BullCowCount;
}

//compares provided FBUllCowCount with previous and updates Energy-Points accordingly
void FBullCowGame::UpdateEnergyPoints(FBullCowCount CurrentBullCowCount)
{
	static FBullCowCount PreviousBullCowCount; //preserves value between all function calls
	EnergyPoints += (CurrentBullCowCount.bulls - PreviousBullCowCount.bulls) * 10 + (CurrentBullCowCount.cows - PreviousBullCowCount.cows) * 5;
	PreviousBullCowCount = CurrentBullCowCount;
	// when game is won reset PreviousBullCOwCount since all objects of same class access same function (and we dont want static variable to create problems)
	if (IsGameWon()) { PreviousBullCowCount.bulls = 0; PreviousBullCowCount.cows = 0; } 
}

//deducts 10 Energy-Points for asking hint
void FBullCowGame::HintPenalty()
{
	EnergyPoints += -10;
}

//let player(if he chooses to) enter hint for opponent and then updates opponent`s MyHint
void FBullCowGame::GetHintForOpponent(FBullCowGame& Player)
{
	FString Hint = "";
	std::cout << " Do you wish to leave a custom hint for your opponent? (yes/no) :";
	FString Response = "";
	std::getline(std::cin, Response);
	if ((Response[0] == 'y') || (Response[0] == 'Y')) {
		std::cout << " Enter your hint statement: ";
		char WordChar;
		while ((WordChar = _getch()) != 13) { //appends chars to word till enter is press
			if (WordChar == 8) { //if backspace is entered 
				std::cout << '\b';  //moves cursor back by one
				Hint.pop_back(); //removes last char off the string
			}
			else {
				Hint.push_back(WordChar); //adds char to string
				std::cout << '*'; 
			}
		}
	}
	Player.SetHint(Hint);
	std::cout << "\n";
}

//updates MyHint to provided string 
void FBullCowGame::SetHint(FString Hint)
{MyHint = Hint;}

//return true if all chars of provided string are alpahbets
bool FBullCowGame::ValidCharsInString(FString word)
{
	for (uint32 i = 0; i < word.length(); i++) {
		if(tolower(word[i])<='a' || 'z'<=tolower(word[i]) ) {return false;}
	}
	return true;
}

//returns true if provided string is isogram
bool FBullCowGame::IsIsogram(FString word) const
{
	if (word.length() <= 1) {
		return true;
	}

	TMap <char, bool> LetterSeen;

	for (auto Letter : word) {
		Letter = tolower(Letter);
		if (LetterSeen[Letter]) {
			return false;
		}
		else {
			LetterSeen[Letter] = true;
		}
	}

	return true;
}

//returns true if provided string is all lowercase 
bool FBullCowGame::IsLowercase(FString word) const
{
	for (auto Letter : word) {
		if (!islower(Letter)) return false;
	}
	return true;
}


