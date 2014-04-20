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
    bool shouldMove = true;
    
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
                shouldMove = false;
            }
        }
    }
    
    if (shouldMove && !m_Player->m_CanMove)
    {
        m_Player->m_CanMove = true;
    }
    
    DeleteCollidables();
}

void CollisionManager::MovableCollision(Collidable* collidable)
{
    m_Game->removeCollidable(collidable);
	m_Game->collectCoin();
}

void CollisionManager::ImmovableCollision(Collidable* collidable)
{
    if (m_Player->m_CanMove)
    {
        m_Player->stop_moving();
    }
}

void CollisionManager::DeleteCollidables()
{
    for (Collidable* c : m_DeleteQueue)
    {
        m_Collidables.remove(c);
    }
    
    m_DeleteQueue.clear();
}