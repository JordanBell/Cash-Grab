//
//  UI.cpp
//  SustainableEconomy
//
//  Created by Tristan Bell on 28/04/2014.
//  Copyright (c) 2014 Tristan Bell. All rights reserved.
//

#include "UI.h"
#include "toolkit.h"
#include <sstream>

UI* g_UI = nullptr;

UI::UI()
{
    m_TotalCoinsLabel = nullptr;
    m_CollectedCoinsLabel = nullptr;
    m_RequiredCoinsLabel = nullptr;
    
    collectedX = requiredX = totalX = 0;
    collectedY = 0;
    requiredY = 30;
    totalY = 60;
    
    SetTotalCoins(0);
    SetCollectedCoins(0);
    SetRequiredCoins(0);
}

UI::~UI()
{
    SDL_FreeSurface(m_RequiredCoinsLabel);
    SDL_FreeSurface(m_TotalCoinsLabel);
    SDL_FreeSurface(m_CollectedCoinsLabel);
}

void UI::Render()
{
    SDL_FreeSurface(m_CollectedCoinsLabel);
    SDL_FreeSurface(m_RequiredCoinsLabel);
    SDL_FreeSurface(m_TotalCoinsLabel);
    
    m_CollectedCoinsLabel = TTF_RenderText_Solid(g_resources->GetFont(), m_CollectedCoins.c_str(), textColor);
    m_RequiredCoinsLabel = TTF_RenderText_Solid(g_resources->GetFont(), m_RequiredCoins.c_str(), textColor);
    m_TotalCoinsLabel = TTF_RenderText_Solid(g_resources->GetFont(), m_TotalCoins.c_str(), textColor);
    
    apply_surface(collectedX, collectedY, m_CollectedCoinsLabel, screen);
    apply_surface(requiredX, requiredY, m_RequiredCoinsLabel, screen);
    apply_surface(totalX, totalY, m_TotalCoinsLabel, screen);
}

void UI::SetTotalCoins(int coins)
{
    ostringstream sStream;
    sStream << "Total: ";
    sStream << coins;
    m_TotalCoins = sStream.str();
}

void UI::SetCollectedCoins(int coins)
{
    ostringstream sStream;
    sStream << "Collected: ";
    sStream << coins;
    m_CollectedCoins = sStream.str();
}

void UI::SetRequiredCoins(int coins)
{
    ostringstream sStream;
    sStream << "Cost: ";
    sStream << coins;
    m_RequiredCoins = sStream.str();
}