//
//  StoreMenuScreen.cpp
//  Cash Grab
//
//  Created by Tristan Bell on 04/01/2015.
//  Copyright (c) 2015 Tristan Bell. All rights reserved.
//

#include "StoreMenuScreen.h"
#include "Label.h"

const int StoreMenuScreen::k_ItemPanelWidth = 300;

StoreMenuScreen::StoreMenuScreen(const Store *store, Menu *parent) : MenuScreen(parent)
{
    std::list<Item> storeItems = store->GetItems();
    
    int labelX = 30;
    int labelY = 15;
    
    SDL_Color white;
    white.r = 255;
    white.g = 255;
    white.b = 255;
    
    for (Item item : storeItems) {
        Label *label = new Label(labelX, labelY, item.GetDescription(), white);
        Label *priceLabel = new Label(0, labelY + label->GetHeight() + 5, to_string(item.GetCost()), white);
        priceLabel->Center(label);
        
        if (labelX + label->GetWidth() > k_ItemPanelWidth) {
            labelX = 30;
            labelY += label->GetHeight() + priceLabel->GetHeight() + 20;
            
            int xDiff = labelX - label->x;
            int yDiff = labelY - label->y;
            
            label->x += xDiff;
            priceLabel->x += xDiff;
            label->y += yDiff;
            priceLabel->y += yDiff;
        }
        
        labelX += label->GetWidth() + 20;
        
        AddUIElement(label);
        AddUIElement(priceLabel);
    }
}