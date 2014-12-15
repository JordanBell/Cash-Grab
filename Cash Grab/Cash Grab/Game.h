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

#include <list>
#include "KeyCode.h"
#include "Sprite.h"
#include "Player.h"
#include "Coin.h"
#include "Prompt.h"
#include "Timer.h"
#include "SEConsole.h"
#include "EffectManager.h"
#include <memory>

using namespace std;

class CollisionManager;
class Machine;
class Prompt;

class Game
{	
public:
	Player *player;
    
	Game();
	~Game(void);
	void run();
    void addGameObject(GameObject* gameObject, bool toFront = false);
    void addCollidable(Collidable* collidable, bool toFront = false);
    void AddEffect(Effect* effect);
    void removeGameObject(GameObject* gameObject);
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

	//GameObjects
	Machine *machine;
	Prompt *prompt;
	list<GameObject*> m_GameObjects;
    list<unique_ptr<GameObject>> m_GameObjectDeleteQueue;
	bool running;

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