//
//  PauseMenuScreen.h
//  Cash Grab
//
//  Created by Tristan Bell on 28/12/2014.
//  Copyright (c) 2014 Tristan Bell. All rights reserved.
//

#pragma once

#include "MenuScreen.h"
#include "Label.h"

class PauseMenuScreen : public MenuScreen {
private:
    static TTF_Font *s_Font;
    
    Label *m_TitleLabel;
    
public:
    PauseMenuScreen(Menu* parent);
    
    void Render() override;
};
