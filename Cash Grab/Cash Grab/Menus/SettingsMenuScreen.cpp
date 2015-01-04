//
//  SettingsMenuScreen.cpp
//  Cash Grab
//
//  Created by Tristan Bell on 28/12/2014.
//  Copyright (c) 2014 Tristan Bell. All rights reserved.
//

#include "SettingsMenuScreen.h"
#include "Resources.h"
#include "Menu.h"
#include "TextButton.h"
#include "ImageButton.h"

#include <string>

using namespace std;

SettingsMenuScreen::SettingsMenuScreen(Menu* parent) : MenuScreen(parent), initialised(false)
{
    UpdateVolumes();
    
    // TODO: remove code duplication
    SDL_Color color;
    color.r = 255;
    color.g = 255;
    color.b = 255;
    
    m_MusicVolumeLabel = new Label(0, 100, "Music Volume", color);
    m_SFXVolumeLabel = new Label(0, 170, "SFX Volume", color);
    
    m_MusicVolumeDisplay = new Label(0, 125, to_string(m_MusicVolumeLevel), color);
    m_SFXVolumeDisplay = new Label(0, 195, to_string(m_SFXVolumeLevel), color);
    
    m_MusicVolumeLabel->Center(parent->m_Background.w);
    m_MusicVolumeDisplay->Center(parent->m_Background.w);
    m_SFXVolumeLabel->Center(parent->m_Background.w);
    m_SFXVolumeDisplay->Center(parent->m_Background.w);
    
    ClickHandler backHandler = [this] {
        m_ParentMenu->Back();
    };
    m_BackButton = new TextButton(10, 10, backHandler, "Back");
    
    SDL_Surface *leftArrow = load_image("LeftArrow.png");
    SDL_Surface *rightArrow = load_image("RightArrow.png");
    
    ClickHandler leftMusicArrowCH = [this] {
        if (m_MusicVolumeLevel > 0) {
            m_MusicVolumeLevel -= 1;
            SetMusicVolume();
            
            if (m_MusicVolumeLevel == 9 || m_MusicVolumeLevel == 1) {
                m_MusicVolumeDisplay->x += 5;
            }
        }
    };
    Button *leftMusicButton = new ImageButton((parent->m_Background.w / 2) - 35, 126, leftArrow, leftMusicArrowCH, true);
    
    ClickHandler leftSFXArrowCH = [this] {
        if (m_SFXVolumeLevel > 0) {
            m_SFXVolumeLevel -= 1;
            SetSFXVolume();
            
            if (m_SFXVolumeLevel == 9 || m_SFXVolumeLevel == 1) {
                m_SFXVolumeDisplay->x += 5;
            }
        }
    };
    Button *leftSFXButton = new ImageButton((parent->m_Background.w / 2) - 35, 196, leftArrow, leftSFXArrowCH, true);
    
    ClickHandler rightMusicArrowCH = [this] {
        if (m_MusicVolumeLevel < 10) {
            m_MusicVolumeLevel += 1;
            SetMusicVolume();
            
            if (m_MusicVolumeLevel == 100 || m_MusicVolumeLevel == 10) {
                m_MusicVolumeDisplay->x -= 5;
            }
        }
    };
    Button *rightMusicButton = new ImageButton((parent->m_Background.w / 2) + 19, 126, rightArrow, rightMusicArrowCH, true);
    
    ClickHandler rightSFXArrowCH = [this] {
        if (m_SFXVolumeLevel < 10) {
            m_SFXVolumeLevel += 1;
            SetSFXVolume();
            
            if (m_SFXVolumeLevel == 100 || m_SFXVolumeLevel == 10) {
                m_SFXVolumeDisplay->x -= 5;
            }
        }
    };
    Button *rightSFXButton = new ImageButton((parent->m_Background.w / 2) + 19, 196, rightArrow, rightSFXArrowCH, true);
    
    AddUIElement(m_MusicVolumeLabel);
    AddUIElement(m_MusicVolumeDisplay);
    AddUIElement(m_SFXVolumeLabel);
    AddUIElement(m_SFXVolumeDisplay);
    
    AddButton(m_BackButton);
    AddButton(leftMusicButton);
    AddButton(leftSFXButton);
    AddButton(rightMusicButton);
    AddButton(rightSFXButton);
}

void SettingsMenuScreen::Update(int delta)
{
    MenuScreen::Update(delta);
    
    if (!initialised) {
        UpdateVolumes();
        initialised = true;
    }
    
    m_MusicVolumeDisplay->SetText(to_string(m_MusicVolumeLevel));
    m_SFXVolumeDisplay->SetText(to_string(m_SFXVolumeLevel));
    
    m_MusicVolumeDisplay->Update(delta);
    m_SFXVolumeDisplay->Update(delta);
}

void SettingsMenuScreen::UpdateVolumes()
{
    int musicVolume = (float)Mix_VolumeMusic(-1) / MIX_MAX_VOLUME * 10;
    int sfxVolume = (float)Mix_Volume(-1, -1) / MIX_MAX_VOLUME * 10;
    m_MusicVolumeLevel = (int)musicVolume;
    m_SFXVolumeLevel = (int)sfxVolume;
}

void SettingsMenuScreen::SetMusicVolume()
{
    int musicVolume = (float)m_MusicVolumeLevel / 10 * MIX_MAX_VOLUME;
    
    Mix_VolumeMusic(musicVolume);
}

void SettingsMenuScreen::SetSFXVolume()
{
    int sfxVolume = (float)m_SFXVolumeLevel / 10 * MIX_MAX_VOLUME;
    
    Mix_Volume(-1, sfxVolume); // Set volume of all channels
}