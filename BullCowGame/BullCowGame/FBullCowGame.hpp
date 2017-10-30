//
//  FBullCowGame.hpp
//  BullCowGame
//
//  Created by evan_localadmin on 17/10/2017.
//  Copyright © 2017 evan_localadmin. All rights reserved.
//

#ifndef FBullCowGame_hpp
#define FBullCowGame_hpp

#include <stdio.h>

#endif /* FBullCowGame_hpp */
#include <string>

using FString  = std::string;
using int32 = int;

struct FBullCowCount
{
    int32 Bulls = 0;
    int32 Cows = 0;
};

enum class EGuessStatus
{
    Invalid_Status,
    OK,
    Not_Isogram,
    Wrong_Length,
    Not_Lowercase
};

enum class EResetStatus
{
    No_Hidden_Word,
    OK
};

class FBullCowGame
{
public:
    FBullCowGame();
    int32 GetMaxTries() const;
    int32 GetCurrentTry() const;
    int32 GetHiddenWordLength() const;
    bool IsGameWon() const;
    EGuessStatus CheckGuessValidity(FString) const;
    
    void Reset(); //TODO make a more rich return value.
     //TODO make a more rich return value.
    // Count Bulls and Cows
    FBullCowCount SubmitGuess(FString);
    // Please try and ignore this and focus on the interface above
private:
    // see constructor for initialization
    int32 MyCurrentTry;
    FString MyHiddenWord;
    bool bGameIsWon;
    bool IsIsogram(FString) const;
    bool IsLowercase(FString) const;
};
