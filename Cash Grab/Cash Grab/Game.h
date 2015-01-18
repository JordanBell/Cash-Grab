#ifndef game_h
#define game_h

#define TILE_SIZE 32
#define FRAME_RATE 60

#define CONSOLE_COOLDOWN 10
#define LAYER_ENV_LOWER 0
#define LAYER_GROUND 1
#define LAYER_PLAYER 2
#define LAYER_ENV_UPPER 3
#define LAYER_AIR 4
#define LAYER_UI 10
#define GAME_TYPE "testing"

#include <list>
#include "KeyCode.h"
#include "Sprite.h"
#include "Player.h"
#include "Coin.h"
#include "Timer.h"
#include "CGConsole.h"
#include "EffectManager.h"
#include "MenuManager.h"
#include "EventHandler.h"

#include <memory>
#include <map>

using namespace std;

class CollisionManager;
class Machine;

enum Element {
	NORMAL, ICE, FIRE
};

class Game
{	
public:
	Player *player;
    
	Game();
	~Game(void);
    
    void NewGame();
	void run();
    void addGameObject(GameObject* gameObject, bool toFront = false);
    void addCollidable(Collidable* collidable, bool toFront = false);
    void AddEffect(Effect* effect);
    void removeGameObject(GameObject* gameObject);
    void removeCollidable(Collidable* collidable);
    
	void Mute(void) { /*m_muted = true;*/ }
	void Unmute(void) { /*m_muted = false;*/ }

private:
    CollisionManager* m_CollisionManager;
    EffectManager* m_EffectManager;
    MenuManager* m_MenuManager;
    
	CGConsole testingConsole;
	int consoleCooldownCounter;
	KeyCode keys;
	Timer m_FPSTimer;
	int delta; // The time since the last frame
    int lastUpdate; // Time of last update for delta tracking
	int m_InteractCooldown;

	// The number of frames until an interaction can be called again.
	static const unsigned int k_InteractCooldown = 20;

	//GameObjects
	list<GameObject*> m_GameObjects;
    list<unique_ptr<GameObject>> m_GameObjectDeleteQueue;
    list<EventHandler*> m_EventHandlers;
	bool running;
    
    // Render list
    map<int, GameObject*> m_RenderList;

	void InitEnvironment(void);
	void Update(void);
	void HandleKeys(void);
	void Render(void);
	void Poll(void);

    void DeleteGameObjects(void);
	void RegulateFrameRate(void);
};

extern Game* g_game;

#endif