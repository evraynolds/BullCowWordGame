//
//  main.cpp
//  BullCowGame
//
//  Created by evan_localadmin on 16/10/2017.
//  Copyright © 2017 evan_localadmin. All rights reserved.
//


/*
 This is the console exectuable that makes use of the BUllCowClass
 This acts as the view in a MVC pattern and is responsible for all user interaction.  For game logi see the
 FBullCowgame class
 */

//  Preprocessor directive
#include <iostream>
#include <string>
#include "FBullCowGame.hpp"

using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetValidGuessAndPrint();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; // Instantiate a new game

// entry point for application
int main(int argc, const char * argv[])
{
    bool continueGame = false;
    do{
        PrintIntro();
        PlayGame();
        //TODO add a game summary
        continueGame = AskToPlayAgain();
    }while(continueGame);
    
    return 0;
}

void PrintIntro()
{
    // introduce the game
   
    std::cout << "\n\nWelcome to Bulls and Cows, a fun word game!\n";
    std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of? \n";
    std::cout << std::endl;
    return;
}

void PlayGame()
{
    BCGame.Reset();
    int32 MaxTries = BCGame.GetMaxTries();
    
    // loop for the number of turns asking for guesses
    
    while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries ){ //TODO make loop checking valid guesses
        FText Guess = GetValidGuessAndPrint();
        
        // print guess back to user
        std::cout << std::endl;
        std::cout << "Your guess was: " << Guess << std::endl;
        
        FBullCowCount BullCowCount = BCGame.SubmitGuess(Guess);
        
        std::cout << "Bulls = " << BullCowCount.Bulls << " ";
        std::cout << "Cows = " << BullCowCount.Cows << "\n\n";
    }
    return;
}


// loop continually until the user enters valid guess
FText GetValidGuessAndPrint()
{
    FText sGuess = "";
    EGuessStatus Status = EGuessStatus::Invalid_Status;
    do{
        int32 currentTry = BCGame.GetCurrentTry();
        // get a guess from the player
        std::cout << "Try " << currentTry << " of " << BCGame.GetMaxTries();
        std::cout << ". Enter your guess: ";
        std::getline(std::cin, sGuess);
    
        Status = BCGame.CheckGuessValidity(sGuess);
    
        switch(Status){
            case EGuessStatus::Wrong_Length:
                std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
                break;
            case EGuessStatus::Not_Lowercase:
                std::cout << "Please enter a word in lowercase.\n";
                break;
            case EGuessStatus::Not_Isogram:
                std::cout << "Please enter a word without repeating any letters.\n";
                break;
            default:
                break;
        }
    }while(Status != EGuessStatus::OK ); // Keep looping until we get valid input
   
    return sGuess;
}

bool AskToPlayAgain()
{
     PrintGameSummary();
    std::cout << "\nDo you want to play again (y/n)? ";
    FText Response = "";
    getline(std::cin, Response);
    std::cout << std::endl;

    return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintGameSummary()
{
    if(BCGame.IsGameWon()){
        std::cout << "WELL DONE - YOU WIN!!!!";
    }else{
        std::cout << "Better luck next time!\n";
    }
}
