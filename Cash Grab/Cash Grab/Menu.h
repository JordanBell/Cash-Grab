//
//  Menu.h
//  Cash Grab
//
//  Base class for menus.
//
//  Created by Tristan Bell on 15/12/2014.
//  Copyright (c) 2014 Tristan Bell. All rights reserved.
//

#ifndef Cash_Grab_Menu_h
#define Cash_Grab_Menu_h

class Menu {
    std::vector<Button*> m_Buttons;
    
public:
    Menu();
    
    virtual ~Menu() {
        for (Button* b : m_Buttons) {
            delete b;
        }
    }
};

#endif
