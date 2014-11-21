//
//  UI.h
//  SustainableEconomy
//
//  Created by Tristan Bell on 28/04/2014.
//  Copyright (c) 2014 Tristan Bell. All rights reserved.
//

#ifndef __SustainableEconomy__UI__
#define __SustainableEconomy__UI__

#include "SDL.h"
#include "Resources.h"
#include <string>

using namespace std;

class UI 
{
protected:
    int collectedX, collectedY;
    int requiredX, requiredY;
    int totalX, totalY;
    
    string m_TotalCoins;
    string m_CollectedCoins;
    string m_RequiredCoins;
    
    SDL_Surface* m_TotalCoinsLabel;
    SDL_Surface* m_CollectedCoinsLabel;
    SDL_Surface* m_RequiredCoinsLabel;
    
public:
    UI();
    ~UI();
    
    void Render();
    
    void SetTotalCoins(int coins);
    void SetCollectedCoins(int coins);
    void SetRequiredCoins(int coins);
};

extern UI* g_UI;

#endif /* defined(__SustainableEconomy__UI__) */
