//
//  CollisionManager.cpp
//  SustainableEconomy
//
//  Created by Tristan Bell on 18/04/2014.
//  Copyright (c) 2014 Tristan Bell. All rights reserved.
//

#include "CollisionManager.h"

CollisionManager::CollisionManager(Game* game)
{
    m_Game = game;
    m_Player = game->player;
}

void CollisionManager::Update(int delta)
{
    for (Collidable* c : m_Collidables)
    {
        if (m_Player->CollidesWith(c))
        {
            printf("Collision!\n");
            
            if (c->m_IsMoveable)
            {
                MovableCollision(c);
            }
            else
            {
                ImmovableCollision(c);
            }
        }
    }
}

void CollisionManager::MovableCollision(Collidable* collidable)
{
    m_Game->removeCollidable(collidable);
}

void CollisionManager::ImmovableCollision(Collidable* collidable)
{
    
}