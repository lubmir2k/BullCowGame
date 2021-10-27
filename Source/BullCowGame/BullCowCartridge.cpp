// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "Console/HiddenWordList.h"

void UBullCowCartridge::BeginPlay()
{
    Super::BeginPlay();

    
    
    SetupGame();

    PrintLine(TEXT("The number of possible words is %i."), Words.Num());
    PrintLine(TEXT("The number of valid words is %i."), GetValidWords(Words).Num());
    PrintLine(TEXT("The HiddenWord is: %s."), *HiddenWord);// Debug Line   
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{ 
    if (bGameOver)
    {
        ClearScreen();
        SetupGame();
    }
    else // Checking PlayerGuess
    {
        ProcessGuess(Input);
    }
    
}

void UBullCowCartridge::SetupGame()
{
    // Welcoming The Player
    PrintLine(TEXT("Welcome to Bull Cows!"));
    
    HiddenWord = TEXT("cakes");
    Lives = HiddenWord.Len();
    bGameOver = false;

    PrintLine(TEXT("Guess the %i letter word!"), HiddenWord.Len());
    PrintLine(TEXT("You have %i lives."), Lives);
    PrintLine(TEXT("Type in your guess and \npress enter to continue...")); // Prompt Player For Guess
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("Press enter to play again."));
}

void UBullCowCartridge::ProcessGuess(FString Guess)
{
    if (Guess.Len() != HiddenWord.Len())
    {
        PrintLine(TEXT("Sorry wrong number of characters, try guessing again!"));
        PrintLine(TEXT("The word is %i characters long"), HiddenWord.Len());
        PrintLine(TEXT("You have %i lives remaining"), Lives);
        return;
    }

    if (Guess == HiddenWord)
    {
        PrintLine(TEXT("You have won!"));
        EndGame();
        return;
    }

    if (!IsIsogram(Guess))
    {
        PrintLine(TEXT("No repeating letters, guess again"));
        return;
    }

    PrintLine(TEXT("Lost a life!"));
    PrintLine(TEXT("%i"), --Lives);

    if (Lives <= 0)
    {
        PrintLine(TEXT("You have no lives left!"));
        PrintLine(TEXT("The hidden word was: %s"), *HiddenWord);
        EndGame();
        return;   
    }
    
    // Show number of Bulls and Cows
    PrintLine(TEXT("Trying guessing again, you have %i lives left"), Lives);
}

bool UBullCowCartridge::IsIsogram(FString Word) const
{
    for(int32 Index = 0; Index < Word.Len(); Index++)
    {
        for (int32 Comparison = Index + 1; Comparison < Word.Len(); Comparison++)
        {
            if(Word[Index] == Word[Comparison])
            {
                return false;
            }
        }
    }
    return true;
}

TArray<FString> UBullCowCartridge::GetValidWords(TArray<FString> WordList) const
{
    TArray<FString> ValidWords;

    for(int32 Index = 0; Index < WordList.Num(); Index++)
    {
        if(WordList[Index].Len() >= 4 && WordList[Index].Len() <= 8 && IsIsogram((WordList[Index])))
        {
            ValidWords.Emplace(WordList[Index]);
        }
    }
    return ValidWords;
}
