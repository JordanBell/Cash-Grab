//
//  CollisionManager.cpp
//  SustainableEconomy
//
//  Created by Tristan Bell on 18/04/2014.
//  Copyright (c) 2014 Tristan Bell. All rights reserved.
//

#include "CollisionManager.h"
#include "Game.h"

using namespace std;

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
    
    DeleteCollidables();
}

void CollisionManager::MovableCollision(Collidable* collidable)
{
    m_Game->removeCollidable(collidable);
}

void CollisionManager::ImmovableCollision(Collidable* collidable)
{
    
}

void CollisionManager::DeleteCollidables()
{
    for (Collidable* c : m_DeleteQueue)
    {
        m_Collidables.remove(c);
    }
    
    m_DeleteQueue.clear();
}