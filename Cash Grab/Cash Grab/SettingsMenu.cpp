//
//  SettingsMenu.cpp
//  Cash Grab
//
//  Created by Tristan Bell on 28/12/2014.
//  Copyright (c) 2014 Tristan Bell. All rights reserved.
//

#include "SettingsMenu.h"
#include "SettingsMenuScreen.h"

SettingsMenu::SettingsMenu() : Menu()
{
    m_screen = new SettingsMenuScreen(this);
}

SettingsMenu::SettingsMenu(Menu* previous) : Menu(previous)
{
    m_screen = new SettingsMenuScreen(this);
}