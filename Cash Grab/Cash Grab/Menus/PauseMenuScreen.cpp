//
//  PauseMenuScreen.cpp
//  Cash Grab
//
//  Created by Tristan Bell on 28/12/2014.
//  Copyright (c) 2014 Tristan Bell. All rights reserved.
//

#include "PauseMenuScreen.h"
#include "TextButton.h"
#include "MenuManager.h"

TTF_Font *PauseMenuScreen::s_Font = TTF_OpenFont("joystix monospace.ttf", 24);

PauseMenuScreen::PauseMenuScreen(Menu* parent) : MenuScreen(parent)
{
    SDL_Color color;
    color.r = 255;
    color.g = 255;
    color.b = 255;
    
    ClickHandler resumeHandler = [] { g_menuManager->SetActive(false); };
    ClickHandler settingsHandler = [this] { m_ParentMenu->GoToScreen(SETTINGS); };
    
    Button *resumeButton = new TextButton(0, 200, resumeHandler, "Resume");
    Button *settingsButton = new TextButton(0, 250, settingsHandler, "Settings");
    
    TTF_Font *font = TTF_OpenFont("joystix monospace.ttf", 24);
    m_TitleLabel = new Label(0, 100, "Paused", color, font);
    
    m_TitleLabel->Center(parent->m_Background.w);
    resumeButton->Center(parent->m_Background.w);
    settingsButton->Center(parent->m_Background.w);
    
    m_Buttons.push_back(resumeButton);
    m_Buttons.push_back(settingsButton);
}

void PauseMenuScreen::Render()
{
    MenuScreen::Render();
    
    m_TitleLabel->Render();
}