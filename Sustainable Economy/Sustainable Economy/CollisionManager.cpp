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
        if (c->m_IsMoveable) // Coin collisions
        {
            if (m_Player->CollidesWith(c))
            {
                // I know it's bad design but whatever
                Coin* coin = dynamic_cast<Coin*>(c);
                if (coin && !coin->moving)
                {
                    MovableCollision(c);
                }
            }
        }
        else
        {
            if (m_Player->CollidesWith(c))
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

void CollisionManager::AddCollidable(Collidable* collidable, bool toFront)
{
    if (toFront) m_Collidables.push_front(collidable);
    else m_Collidables.push_back(collidable);
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
        m_Player->SetCanMove(false);
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