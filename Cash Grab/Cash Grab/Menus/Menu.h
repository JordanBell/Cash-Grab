//
//  Menu.h
//  Cash Grab
//
//  Created by Tristan Bell on 17/12/2014.
//  Copyright (c) 2014 Tristan Bell. All rights reserved.
//

#ifndef __Cash_Grab__Menu__
#define __Cash_Grab__Menu__

#include "MenuScreen.h"
#include <map>
#include <string>

using namespace std;

class Menu {
protected:
    MenuScreen* m_screen;
    
    // Menu tree structure
    Menu* currentMenu;
    map<string, Menu*> next;
    Menu* prev;
    
public:
    virtual ~Menu() { }
    
    virtual void Update(int delta);
    virtual void Render();
    
    void GoToScreen(string screenName);
    void Back();
};

#endif /* defined(__Cash_Grab__Menu__) */
