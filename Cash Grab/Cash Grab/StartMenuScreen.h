//
//  StartMenu.h
//  Cash Grab
//
//  Created by Tristan Bell on 15/12/2014.
//  Copyright (c) 2014 Tristan Bell. All rights reserved.
//

#ifndef __Cash_Grab__StartMenu__
#define __Cash_Grab__StartMenu__

#include "MenuScreen.h"

class StartMenuScreen : public MenuScreen {
    
public:
    StartMenuScreen(Menu* parent);
    
    void Update(int delta) override final;
};

#endif /* defined(__Cash_Grab__StartMenu__) */
