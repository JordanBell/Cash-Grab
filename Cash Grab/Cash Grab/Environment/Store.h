//
//  Store.h
//  Cash Grab
//
//  Created by Tristan Bell on 04/01/2015.
//  Copyright (c) 2015 Tristan Bell. All rights reserved.
//

#pragma once

#include "GameObject.h"
#include "Item.h"

#include <list>

using namespace std;

class Store : public GameObject {
protected:
    list<Item> m_Items;
    
public:
    Store(int x, int y);
    virtual ~Store() { }
    
    list<Item> GetItems() const { return m_Items; }
};
