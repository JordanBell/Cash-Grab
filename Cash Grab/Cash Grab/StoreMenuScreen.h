//
//  StoreMenuScreen.h
//  Cash Grab
//
//  Created by Tristan Bell on 04/01/2015.
//  Copyright (c) 2015 Tristan Bell. All rights reserved.
//

#pragma once

#include "MenuScreen.h"
#include "Store.h"

class StoreMenuScreen : public MenuScreen {
private:
    const static int k_ItemPanelWidth;
    
public:
    StoreMenuScreen(const Store *store, Menu *parent);
    
};