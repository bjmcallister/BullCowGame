/*
Created by:Billy McAllister with help of 
youtube videos and Udemy course by Ben Tristem

This game was a way for me to learn C++
It uses multiple different programming techniques
which was extremely useful.

Something I would like to add later is a way to 
randomize a group of words. It's on my TODO list ;)
*/

#include <iostream>
#include <string>
#include "FBullCowGame.h"
#pragma once

using FText = std::string;
using int32 = int;

void PrintInfo();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame;

int main(){
	bool bPlayAgain = false;

	do {
		PrintInfo();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} while (bPlayAgain==true);

	return 0; 

}



//-----------------------------------Functions-----------------------------------------\\

void PrintInfo() {
	 
	
	std::cout << "Welcome to Bulls and Cows!" << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?\n\n";
	std::cout << "You have " << BCGame.GetMaxTries() << " tries.\n";
	return;
}

void PlayGame() {
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	//loop asking for guesses while the game is 
	//NOT won and there are still tries remaining
	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries){

		FText Guess = GetValidGuess();
		
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls << std::endl;
		std::cout << "Cows = " << BullCowCount.Cows << std::endl << std::endl;
	}
	PrintGameSummary();
	return;
}

FText GetValidGuess() {
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do {
			int32 CurrentTry = BCGame.GetCurrentTry();
			std::cout << "Try " << CurrentTry << ". Enter your guess: ";
			
			std::getline(std::cin, Guess);

			Status = BCGame.CheckGuessValidity(Guess);
			switch (Status) {
			case EGuessStatus::Wrong_Length:
				std::cout << "Please Enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
				break;

			case EGuessStatus::Not_Isogram:
				std::cout << "Please Enter a word without repeating letters\n";
				break;

			case EGuessStatus::Not_Lowercase:
				std::cout << "Please Enter an all lowercase word\n";

			default:
				break;
			}
			std::cout << std::endl;
		}	 while (Status != EGuessStatus::OK);
		return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again with the same hidden word? (y/n)  \n";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintGameSummary() 
{
	if (BCGame.IsGameWon())
	{
		std::cout << "WELL DONE - YOU WIN!\n";
	}
	else
	{
		std::cout << "Better luck next time!\n";
	}
}