#ifndef game_h
#define game_h

#include <list>
#include "KeyCode.h"
#include "Entity.h"
#include "Player.h"
#include "Coin.h"
#include "Environment.h"
#include "Prompt.h"
#include "Timer.h"

using namespace std;

#define TILE_SIZE 32
#define FRAME_RATE 60
#define START_MONEY 10

class CollisionManager;
class Machine;

class Game
{	
public:
	Player *player;
	int wallet;
    
	Game();
	~Game(void);
	void run();
    void addEntity(Entity* entity);
    void addCollidable(Collidable* collidable);
    void removeEntity(Entity* entity);
    void removeCollidable(Collidable* collidable);
	void addABunchOfCoins();

	// Money Stuff
	void collectCoin() { wallet++; }

private:
	//
	/// Fields
	//
	KeyCode keys;
    CollisionManager* m_CollisionManager;
	Timer m_FPSTimer;
	int delta; // The time since the last frame

	//Entities
	Environment *environment;
	Machine *machine;
	Prompt *prompt;
	list<Entity*> m_Entities;
    list<Entity*> m_EntityDeleteQueue;
	bool running;

	//
	/// Functions
	//
    void InitEnvironment();
	void Update();
	void HandleKeys();
	void Render();
	void Poll();

    void DeleteEntities();
	int RegulateFrameRate();
};

extern Game* g_game;

#endif