//
//  Menu.cpp
//  Cash Grab
//
//  Created by Tristan Bell on 17/12/2014.
//  Copyright (c) 2014 Tristan Bell. All rights reserved.
//

#include "Menu.h"
#include "MenuScreen.h"
#include "MenuManager.h"
#include "toolkit.h"

Menu::Menu() : prev(nullptr)
{
    Init();
}

Menu::Menu(Menu* previous) : prev(previous)
{
    Init();
}

void Menu::Init()
{
    int wOffset = 0;
    int hOffset = 0;
    
    m_Background.x = wOffset;
    m_Background.y = hOffset;
    m_Background.w = SCREEN_WIDTH - (wOffset * 2);
    m_Background.h = SCREEN_HEIGHT - (hOffset * 2);
}

void Menu::Update(int delta)
{
//    currentMenu->m_screen->Update(delta);
    m_screen->Update(delta);
}

void Menu::Render()
{
    SDL_FillRect(screen, &m_Background, 0);
    
//    currentMenu->m_screen->Render();
    m_screen->Render();
}

void Menu::GoToScreen(MenuName screenName)
{
//    prev = currentMenu;
//    currentMenu = currentMenu->next.at(screenName);
    
    g_menuManager->m_currentMenu = next.at(screenName);
}

void Menu::Back()
{
    if (prev) {
        g_menuManager->m_currentMenu = prev;
    }
}

void Menu::OnEvent(SDL_Event event)
{
//    currentMenu->m_screen->OnEvent(event);
    m_screen->OnEvent(event);
}