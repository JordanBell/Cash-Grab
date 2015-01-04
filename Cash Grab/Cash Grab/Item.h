//
//  Item.h
//  Cash Grab
//
//  Created by Tristan Bell on 04/01/2015.
//  Copyright (c) 2015 Tristan Bell. All rights reserved.
//

#pragma once

#include <string>

using namespace std;

class Item {
protected:
    string m_Description;
    int m_Cost;
    
public:
    Item(const string description, int cost);
    
    int GetCost() const { return m_Cost; }
    string GetDescription() const { return m_Description; }
};