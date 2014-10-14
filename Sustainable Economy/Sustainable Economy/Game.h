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
#define START_MONEY 1000

class CollisionManager;
class Machine;
class Prompt;

class Game
{	
public:
	Player *player;
	int wallet;
    int totalCollected;
    
	Game();
	~Game(void);
	void run();
    void addEntity(Entity* entity, bool toFront = false);
    void addCollidable(Collidable* collidable, bool toFront = false);
    void removeEntity(Entity* entity);
    void removeCollidable(Collidable* collidable);
	void addABunchOfCoins();

	// Money Stuff
	void collectCoin();
	void IncWallet(void) { wallet++; totalCollected++; }
	void IncWalletBy(int n) { wallet += n; totalCollected += n; }

private:
	//
	/// Fields
	//
	KeyCode keys;
    CollisionManager* m_CollisionManager;
	Timer m_FPSTimer;
	int delta; // The time since the last frame
    int lastUpdate; // Time of last update for delta tracking

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
	void RegulateFrameRate();
};

extern Game* g_game;

#endif