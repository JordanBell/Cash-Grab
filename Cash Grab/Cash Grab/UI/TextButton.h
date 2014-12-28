//
//  TextButton.h
//  Cash Grab
//
//  Created by Tristan Bell on 17/12/2014.
//  Copyright (c) 2014 Tristan Bell. All rights reserved.
//

#ifndef __Cash_Grab__TextButton__
#define __Cash_Grab__TextButton__

#include "Button.h"

class TextButton : public Button {
    
public:
    TextButton(int x, int y, ClickHandler clickHandler, const char *text, bool repeatClick = false);
};

#endif /* defined(__Cash_Grab__TextButton__) */
