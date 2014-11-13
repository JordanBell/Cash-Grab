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
#include "EffectManager.h"
#include <memory>

using namespace std;

#define TILE_SIZE 32
#define FRAME_RATE 60

class CollisionManager;
class Machine;
class Prompt;

#define CONSOLE_COOLDOWN 10

class Game
{	
public:
	Player *player;
    
	Game();
	~Game(void);
	void run();
    void addEntity(Entity* entity, bool toFront = false);
    void addCollidable(Collidable* collidable, bool toFront = false);
    void AddEffect(Effect* effect);
    void removeEntity(Entity* entity);
    void removeCollidable(Collidable* collidable);
	bool IsMuted(void) { return m_muted; }
	void Mute(void) { m_muted = true; }
	void Unmute(void) { m_muted = false; }

private:
	SEConsole testingConsole;
	int consoleCooldownCounter;
	KeyCode keys;
    CollisionManager* m_CollisionManager;
    EffectManager* m_EffectManager;
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