//
//  SettingsMenuScreen.h
//  Cash Grab
//
//  Created by Tristan Bell on 28/12/2014.
//  Copyright (c) 2014 Tristan Bell. All rights reserved.
//

#pragma once

#include "MenuScreen.h"
#include "Label.h"
#include "Button.h"

class SettingsMenuScreen : public MenuScreen {
private:
    Uint8 m_MusicVolumeLevel;
    Uint8 m_SFXVolumeLevel;
    
    Label *m_MusicVolumeLabel;
    Label *m_MusicVolumeDisplay;
    Label *m_SFXVolumeLabel;
    Label *m_SFXVolumeDisplay;
    
    Button *m_BackButton;
    
public:
    SettingsMenuScreen(Menu* parent);
    
    void Update(int delta) override;
    void Render() override;
};
