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
protected:
    const char *m_text;
    
public:
    TextButton(int x, int y, ClickHandler clickHandler, const char *text, bool repeatClick = false);
    
    virtual void SetHighlight(bool highlight);
};

#endif /* defined(__Cash_Grab__TextButton__) */
