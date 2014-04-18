//
//  CollisionManager.h
//  SustainableEconomy
//
//  Created by Tristan Bell on 18/04/2014.
//  Copyright (c) 2014 Tristan Bell. All rights reserved.
//

#ifndef __SustainableEconomy__CollisionManager__
#define __SustainableEconomy__CollisionManager__

#include <list>
#include "Collidable.h"
#include "Player.h"
#include "Game.h"

using namespace std;

class Game;

class CollisionManager {
protected:
    list<Collidable*> m_Collidables;
    Player* m_Player;
    Game* m_Game;
    
public:
    CollisionManager(Game* game);
    
    void Update(int delta);
    
    void AddCollidable(Collidable* collidable) { m_Collidables.push_back(collidable); }
    void RemoveCollidable(Collidable* collidable) { m_Collidables.remove(collidable); }
    
    void MovableCollision(Collidable* collidable);
    void ImmovableCollision(Collidable* collidable);
};

#endif /* defined(__SustainableEconomy__CollisionManager__) */
