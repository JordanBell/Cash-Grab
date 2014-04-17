#ifndef game_h
#define game_h

#include <vector>
#include "KeyCode.h"
#include "Entity.h"
#include "Player.h"
#include "Coin.h"
#include "Environment.h"
#include "Prompt.h"
#include "Machine.h"

#define TILE_SIZE 32
class Game
{	
public:
	Game();
	~Game(void) {}
	void run();
    void addEntity(Entity* entity);

private:
	//
	/// Fields
	//
	KeyCode keys;

	//Entities
	Player *player;
	Coin *coin;
	Environment *environment;
	Machine *machine;
	Prompt *prompt;
	std::vector<Entity*> m_Entities;
	bool running;

	//
	/// Functions
	//
	void Update();
		void HandleKeys();
		void CheckCollisions();
	void Render();

	void Poll();
};

extern Game* g_game;

#endif