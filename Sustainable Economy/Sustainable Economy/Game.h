#ifndef game_h
#define game_h

#define TILE_SIZE 32
#define FRAME_RATE 60

#define CONSOLE_COOLDOWN 10
#define TRANSITION_SPEED 10

#include <list>
#include "KeyCode.h"
#include "Sprite.h"
#include "Player.h"
#include "Coin.h"
#include "EnvironmentUpper.h"
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

	void TransitionScreen(Player::Direction direction) { m_transitionDirection = direction; }

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
	Player::Direction m_transitionDirection;

	//GameObjects
	Environment *environment;
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