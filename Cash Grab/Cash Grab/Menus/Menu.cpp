//
//  Menu.cpp
//  Cash Grab
//
//  Created by Tristan Bell on 17/12/2014.
//  Copyright (c) 2014 Tristan Bell. All rights reserved.
//

#include "Menu.h"
#include "MenuScreen.h"

void Menu::Update(int delta)
{
    currentMenu->m_screen->Update(delta);
}

void Menu::Render()
{
    currentMenu->m_screen->Render();
}

void Menu::GoToScreen(string screenName)
{
    prev = currentMenu;
    currentMenu = next.at(screenName);
}

void Menu::Back()
{
    if (prev) {
        currentMenu = prev;
    }
    else {
        printf("No previous menu!\n");
    }
}