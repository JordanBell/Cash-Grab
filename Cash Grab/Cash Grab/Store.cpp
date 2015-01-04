//
//  Store.cpp
//  Cash Grab
//
//  Created by Tristan Bell on 04/01/2015.
//  Copyright (c) 2015 Tristan Bell. All rights reserved.
//

#include "Store.h"

Store::Store(int x, int y) : GameObject(x, y)
{
    m_Items.push_back(Item("A", 100));
    m_Items.push_back(Item("Item!", 170));
    m_Items.push_back(Item("Boo!", 5));
    m_Items.push_back(Item("Nothing.....", 1));
    m_Items.push_back(Item("Aaaaahhhhhhhhh", 10000));
}