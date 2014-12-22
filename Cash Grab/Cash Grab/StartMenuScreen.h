//
//  StartMenu.h
//  Cash Grab
//
//  Created by Tristan Bell on 15/12/2014.
//  Copyright (c) 2014 Tristan Bell. All rights reserved.
//

#pragma once

#include "MenuScreen.h"

class StartMenuScreen : public MenuScreen {
private:
    void NewGame();
    void Continue();
    
public:
    StartMenuScreen(Menu* parent);
    
    void Update(int delta) override final;
};
