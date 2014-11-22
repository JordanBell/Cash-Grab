//
//  UI.cpp
//  CashGrab
//
//  Created by Tristan Bell on 28/04/2014.
//  Copyright (c) 2014 Tristan Bell. All rights reserved.
//

#include "UI.h"
#include "toolkit.h"
#include <sstream>
#include "Machine.h"

UI* g_UI = nullptr;

UI::UI()
{
	m_TotalCoinsLabel = nullptr;
    m_CollectedCoinsLabel = nullptr;
    m_RequiredCoinsLabel = nullptr;
    
	// Some UI is relative to the machine's position
	int machineX = (7*TILE_SIZE); // I'm so sorry
	int machineY = (TILE_SIZE); // It's hard coded, pls forgive

    totalX = machineX + TILE_SIZE + 16;
    totalY = TILE_SIZE/4;

	collectedX = requiredX = machineX + (TILE_SIZE * 3) - 3;
	collectedY = machineY + 13;
	requiredY = machineY + 37;
    
    SetTotalCoins(0);
    SetCollectedCoins(0);
    SetRequiredCoins(0);
}

UI::~UI()
{
	// Free all surfaces
    SDL_FreeSurface(m_RequiredCoinsLabel);
    SDL_FreeSurface(m_TotalCoinsLabel);
    SDL_FreeSurface(m_CollectedCoinsLabel);
}

void UI::Render()
{
	// Free the surfaces to the blitted anew
    SDL_FreeSurface(m_CollectedCoinsLabel);
    SDL_FreeSurface(m_RequiredCoinsLabel);
    SDL_FreeSurface(m_TotalCoinsLabel);
    
	// Set all the text labels to their new (or unchanged) values
    m_CollectedCoinsLabel = TTF_RenderText_Solid(g_resources->GetFont(), m_CollectedCoins.c_str(), machineTextColor);
    m_RequiredCoinsLabel = TTF_RenderText_Solid(g_resources->GetFont(), m_RequiredCoins.c_str(), machineTextColor);
    m_TotalCoinsLabel = TTF_RenderText_Solid(g_resources->GetFont(), m_TotalCoins.c_str(), textColor);
    
	// Blit the new fonts onto the label
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
	// Note: I've commented out the string label, as it is rendered on the machine graphic
    ostringstream sStream;
    //sStream << "Collected: ";
    sStream << coins;
    m_CollectedCoins = sStream.str();
}

void UI::SetRequiredCoins(int coins)
{
	// Note: I've commented out the string label, as it is rendered on the machine graphic
    ostringstream sStream;
    //sStream << "Cost: ";
    sStream << coins;
    m_RequiredCoins = sStream.str();
}