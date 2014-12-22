//
//  StartMenu.cpp
//  Cash Grab
//
//  Created by Tristan Bell on 15/12/2014.
//  Copyright (c) 2014 Tristan Bell. All rights reserved.
//

#include "StartMenuScreen.h"
#include "TextButton.h"
#include "Menu.h"

StartMenuScreen::StartMenuScreen(Menu* parent) : MenuScreen(parent)
{
    ClickHandler newGameHandler = [this] { NewGame(); };
    ClickHandler continueHandler = [this] { Continue(); };
    ClickHandler settingsHandler = [this] { m_ParentMenu->GoToScreen("settings"); };
    
    Button *newGameButton = new TextButton(0, 100, newGameHandler, "New Game");
    Button *continueButton = new TextButton(0, 150, continueHandler, "Continue");
    Button *settingsButton = new TextButton(0, 200, settingsHandler, "Settings");
    
    m_Buttons.push_back(newGameButton);
    m_Buttons.push_back(continueButton);
    m_Buttons.push_back(settingsButton);
}

void StartMenuScreen::Update(int delta)
{
    MenuScreen::Update(delta);
}

void StartMenuScreen::NewGame()
{
    printf("New game\n");
}

void StartMenuScreen::Continue()
{
    printf("Continue\n");
}