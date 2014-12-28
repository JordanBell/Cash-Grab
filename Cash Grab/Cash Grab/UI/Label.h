//
//  Label.h
//  Cash Grab
//
//  Created by Tristan Bell on 28/12/2014.
//  Copyright (c) 2014 Tristan Bell. All rights reserved.
//

#pragma once

#include "GameObject.h"

using namespace std;

class Label : public GameObject {
protected:
    string m_Text;
    SDL_Color m_Color;
    
public:
    Label(int x, int y, string text, SDL_Color color);
    
    void Update(int delta) override;
    void Render() override;
    
    void SetText(string text);
    
    void Center(int width);
};