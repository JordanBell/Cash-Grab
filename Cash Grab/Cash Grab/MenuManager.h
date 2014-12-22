//
//  MenuManager.h
//  Cash Grab
//
//  Created by Tristan Bell on 17/12/2014.
//  Copyright (c) 2014 Tristan Bell. All rights reserved.
//

#ifndef __Cash_Grab__MenuManager__
#define __Cash_Grab__MenuManager__

#include "Menu.h"
#include <map>
#include <string>

using namespace std;

typedef enum {
    START,
    PAUSE
} MenuType;

class MenuManager {
protected:
    map<MenuType, Menu*> m_menus;
    Menu* m_currentMenu;
    
    bool m_active;
    
public:
    MenuManager();
    ~MenuManager();
    
    void GoToMenu(MenuType menuName);
    
    void Update(int delta);
    void Render();
    
    void SetActive(bool active) { m_active = active; }
    bool IsActive() { return m_active; }
};

#endif /* defined(__Cash_Grab__MenuManager__) */
