// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

	SetupGame();

	PrintLine(TEXT("The HiddenWord is: %s \nIt is %i characters long"), *HiddenWord, HiddenWord.Len());
	
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    if(bGameOver)
    {
    	ClearScreen();
    	SetupGame();
    }
	else
	{
		ProcessGuess(Input, Lives);
	}
}

void UBullCowCartridge::SetupGame()
{
	PrintLine(TEXT("Welcome to Bull Cows!"));

	HiddenWord = TEXT("windows");
	Lives = HiddenWord.Len();
	bGameOver = false;
	
	PrintLine(TEXT("Guess the %i letter word!"), HiddenWord.Len());
	PrintLine(TEXT("You have %i Lives"), Lives);
	PrintLine(TEXT("Type in your guess \nand press Enter."));
}

void UBullCowCartridge::EndGame()
{
	bGameOver = true;
	PrintLine(TEXT("Press enter to play again."));
}

void UBullCowCartridge::ProcessGuess(FString Guess, int32 Counter)
{
	if(Guess == HiddenWord)
	{
		PrintLine(TEXT("You have won!"));
		EndGame();
	}
	else
	{
		if(Lives > 0)
		{
			if(Guess.Len() != HiddenWord.Len())
			{
				PrintLine(TEXT("Sorry, try guessing again, \nyou have %i lives remaining"), --Lives);
			}
		}
		else
		{
			PrintLine(TEXT("You have no lives left. \nYou have lost!"), HiddenWord.Len());
			EndGame();
		}
	}	
}
