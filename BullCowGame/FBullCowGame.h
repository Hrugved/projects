#pragma once
#include <string>

using FString = std::string;
using int32 = int;
using uint32 = unsigned int;

void Seperator(char sep, int n);

struct FBullCowCount {
	int32 bulls = 0;
	int32 cows = 0;
};

enum class EGuessStatus {
	Invalid_Status,
	AskingForHint,
	Ok,
	Not_Isogram,
	Wrong_length,
	Not_lowercase
};

class FBullCowGame {
public:


	int32 GetMaxTries() const;
	void GetValidHiddenWord(FBullCowGame& Player, int32 WordLimit);
	int32 GetCurrentTry() const;
	bool IsGameWon() const;
	int32 GetHiddenWordLength() const;
	int32 GetEnergyPoints() const;
	FString GetPlayerName() const;
	void SetHiddenWord(FString);
	void DisplayHint();
	EGuessStatus CheckGuessValidity(FString);
	FBullCowCount SubmitValidGuess(FString);
	void UpdateEnergyPoints(FBullCowCount);
	void Reset(FBullCowGame& OpponentPlayer, int32 HiddenWordLength, int32 MaxTries);
	void HintPenalty();
	FString GetHiddenWord() const;
	void GetHintForOpponent(FBullCowGame& Player);
	void SetHint(FString);
	bool ValidCharsInString(FString);

private:
	FString MyName;
	int32 MyCurrentTry;
	int32 MyMaxTry;
	FString MyHiddenWord;
	int32 EnergyPoints;
	FString MyHint;
	uint32 HintsTaken;
	bool bIsGameWon;
	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
};