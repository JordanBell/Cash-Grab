//
//  CollisionManager.cpp
//  SustainableEconomy
//
//  Created by Tristan Bell on 18/04/2014.
//  Copyright (c) 2014 Tristan Bell. All rights reserved.
//

#include "CollisionManager.h"
#include "Game.h"
#include "Resources.h"

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
        if (c->m_IsMoveable) // Throwable collisions
        {
            int collisionOverlap;
            if (m_Player->CollidesWith(c, collisionOverlap))
            {
                // I know it's bad design but whatever
                Throwable* throwable = dynamic_cast<Throwable*>(c);
                if (throwable && !throwable->IsAirborne())
                {
                    MovableCollision(c);
                }
            }
        }
        else
        {
            int collisionOverlap;
            if (m_Player->WillCollideWith(c, collisionOverlap))
            {   
                // If we're not right next to a wall
                if (collisionOverlap > 0)
                {
                    // Slow down by overlap amount
                    if (m_Player->m_yVel > 0)
                    {
                        m_Player->m_yVel -= collisionOverlap;
                        
                        if (m_Player->m_yVel < 0)
                        {
                            m_Player->m_yVel = 0;
                        }
                    }
                    else if (m_Player->m_yVel < 0)
                    {
                        m_Player->m_yVel += collisionOverlap;
                        
                        if (m_Player->m_yVel > 0)
                        {
                            m_Player->m_yVel = 0;
                        }
                    }
                    
                    if (m_Player->m_xVel > 0)
                    {
                        m_Player->m_xVel -= collisionOverlap;
                        
                        if (m_Player->m_xVel < 0)
                        {
                            m_Player->m_xVel = 0;
                        }
                    }
                    else if (m_Player->m_xVel < 0)
                    {
                        m_Player->m_xVel += collisionOverlap;
                        
                        if (m_Player->m_xVel > 0)
                        {
                            m_Player->m_xVel = 0;
                        }
                    }
                    
                    // Do this movement before stopping player from moving
                    m_Player->DoMove();
                }
                
                shouldMove = false;
                
                ImmovableCollision(c);
            }
        }
    }
    
    if (shouldMove)
    {
        if (!m_Player->m_CanMove) {
            m_Player->SetCanMove(true);
        }
        
        m_Player->DoMove();
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
    ((Throwable*)collidable)->OnCollect();
    
    m_Game->removeCollidable(collidable);
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