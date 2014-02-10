#ifndef Game_h
#define Game_h

#include <vector>
#include "KeyCode.h"
#include "Entity.h"
#include "Player.h"
#include "Coin.h"
#include "Environment.h"

class Game
{
	
public:
	Game(SDL_Surface* p_image, SDL_Surface* c_image, SDL_Surface* e_image, SDL_Surface* m_image, SDL_Surface* pr_image);
	~Game(void) {}
	void run();

private:
	KeyCode keys;
    
	//Entities
	Player *player;
	Coin *coin;
	Environment *environment;
	Machine *machine;
	Prompt *prompt;
    
	bool running;
	std::vector<Entity*> entities;

	void update();
	void handle_keys();
	void render();
	void poll();
};

#endif

