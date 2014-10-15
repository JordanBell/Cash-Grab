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
#include "SEConsole.h"
#include <memory>

using namespace std;

#define TILE_SIZE 32
#define FRAME_RATE 60
#define START_MONEY 100

class CollisionManager;
class Machine;
class Prompt;

#define CONSOLE_COOLDOWN 10

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
	bool IsMuted(void) { return m_muted; }
	void Mute(void) { m_muted = true; }
	void Unmute(void) { m_muted = false; }

	// Money Stuff
	void collectCoin();
	void IncWallet(void) { wallet++; totalCollected++; }
	void IncWalletBy(int n) { wallet += n; totalCollected += n; }

private:
	SEConsole testingConsole;
	int consoleCooldownCounter;
	KeyCode keys;
    CollisionManager* m_CollisionManager;
	Timer m_FPSTimer;
	int delta; // The time since the last frame
    int lastUpdate; // Time of last update for delta tracking
	bool m_muted;

	//Entities
	Environment *environment;
	Machine *machine;
	Prompt *prompt;
	list<Entity*> m_Entities;
    list<unique_ptr<Entity>> m_EntityDeleteQueue;
	bool running;

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