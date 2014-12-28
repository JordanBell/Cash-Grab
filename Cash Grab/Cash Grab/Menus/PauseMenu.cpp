//
//  PauseMenu.cpp
//  Cash Grab
//
//  Created by Tristan Bell on 28/12/2014.
//  Copyright (c) 2014 Tristan Bell. All rights reserved.
//

#include "PauseMenu.h"
#include "SettingsMenu.h"
#include "PauseMenuScreen.h"

PauseMenu::PauseMenu()
{
    m_screen = new PauseMenuScreen(this);
    
    next[SETTINGS] = new SettingsMenu(this);
}