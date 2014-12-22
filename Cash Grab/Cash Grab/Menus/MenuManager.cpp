//
//  MenuManager.cpp
//  Cash Grab
//
//  Created by Tristan Bell on 17/12/2014.
//  Copyright (c) 2014 Tristan Bell. All rights reserved.
//

#include "MenuManager.h"
#include "Menu.h"

MenuManager::MenuManager()
{
    
    
//    m_menus[START] = startMenu;
//    m_menus[PAUSE] = pauseMenu;
}

MenuManager::~MenuManager()
{
    for (auto p : m_menus) {
        delete p.second;
    }
}

void MenuManager::GoToMenu(MenuType menuName)
{
    m_currentMenu = m_menus.at(menuName);
}

void MenuManager::Update(int delta)
{
    if (IsActive()) {
        m_currentMenu->Update(delta);
    }
}

void MenuManager::Render()
{
    if (IsActive()) {
        m_currentMenu->Render();
    }
}