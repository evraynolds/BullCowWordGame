//
//  FBullCowGame.cpp
//  BullCowGame
//
//  Created by evan_localadmin on 17/10/2017.
//  Copyright © 2017 evan_localadmin. All rights reserved.
//

#include "FBullCowGame.hpp"
#include <map>
#define TMap std::map

using FString  = std::string;
using int32 = int;

FBullCowGame::FBullCowGame(){ Reset(); }


int FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; } 

int FBullCowGame::GetMaxTries() const {
    TMap<int32, int32> wordLengthToMaxTries{ {3,4}, {4,7}, {5,10}, {6,16} };
    return wordLengthToMaxTries[MyHiddenWord.length()];
}

void FBullCowGame::Reset()
{
    constexpr int32 MAX_TRIES = 8;
    MyCurrentTry = 1;
   
    const FString HIDDEN_WORD = "planet";
    MyHiddenWord = HIDDEN_WORD;
    bGameIsWon = false;
    return;
}

bool FBullCowGame::IsIsogram(FString word) const
{
    //Map guess
    if(word.length() <=1 ) { return true; }
    
    TMap<char, bool> letterSeen;
    for(auto letter : word)
    {
        letter = tolower(letter);
        if(letterSeen[letter]){
            return false;
        } else {
            letterSeen[letter] = true;
        }
    }
    //Check if values exceed one
    return true;
}

bool FBullCowGame::IsLowercase(FString word) const{
    
    for(auto letter : word)
    {
        if(!islower(letter)){
            return false;
        }
    }
    return true;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
    // if the guess isn't an isogram, return error
    
    if(!IsIsogram(Guess))
    {
        return EGuessStatus::Not_Isogram;
    }
    else if(!IsLowercase(Guess))
    {
        return EGuessStatus::Not_Lowercase;
    }
    else if(Guess.length() != GetHiddenWordLength())
    {
        return EGuessStatus::Wrong_Length;
    }
    else
    {
        return EGuessStatus::OK;
    }
   
}

FBullCowCount FBullCowGame::SubmitGuess(FString Guess)
{
    MyCurrentTry++;
    FBullCowCount BullCowCount;
    
    int32 wordLength = MyHiddenWord.length();
    for(int32 HWChar = 0; HWChar < wordLength; HWChar++)
    {
        for(int32 MWChar = 0; MWChar < wordLength; MWChar++)
        {
            if(Guess[MWChar] == MyHiddenWord[HWChar])
            {
                if(HWChar == MWChar)
                {
                    BullCowCount.Bulls++;
                }
                else
                {
                    BullCowCount.Cows++;
                }
            }
        }
    }
    if(BullCowCount.Bulls == wordLength)
    {
        bGameIsWon = true;
    }
    else
    {
        bGameIsWon = false;
    }
    return BullCowCount;
}

