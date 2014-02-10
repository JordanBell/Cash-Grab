#include <vector>
#include "KeyCode.h"
#include "Entity.h"
#include "Player.h"

#pragma once
class Game
{
	KeyCode keys;

	//Entities
	Player *player;
	Coin *coin;
	Environment *environment;
	Machine *machine;
	Prompt *prompt;
	
public:
	Game(SDL_Surface* p_image, SDL_Surface* c_image, SDL_Surface* e_image, SDL_Surface* m_image, SDL_Surface* pr_image);
	~Game(void) {}
	void run();

private:
	bool running;
	std::vector<Entity*> entities;

	void init();

	void update();
		void handle_keys();
		void check_collisions();
	void render();

	void poll();
};

