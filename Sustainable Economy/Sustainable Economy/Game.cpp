#include "Game.h"
#include "SDL.h"

Game::Game(SDL_Surface* p_image, SDL_Surface* c_image, SDL_Surface* e_image, SDL_Surface* m_image, SDL_Surface* pr_image)
{
	//Set the sprite_sheets of each Entity
	Player.set_sheet(p_image);
	Coin.set_sheet(c_image);
	Environment.set_sheet(e_image);
	Machine.set_sheet(m_image);
	Prompt.set_sheet(pr_image);
	
	init();
}

void Game::init()
{
	//Initialise all ENTITIES
	player = new Player();		  
	coin = new Coin();
	environment = new Environment();	
	machine = new Machine();
	prompt = new Prompt();
	
	entities.push_back(environment);
	entities.push_back(machine);
	entities.push_back(coin);
	entities.push_back(player);
	entities.push_back(prompt);

	//Set up the key responses
	keys = KeyCode(player, machine);
}

void Game::run()
{
	init();
	
	while (running)
	{
		update();
		render();
		poll();
	}
}

void Game::update()
{
	handle_keys();
	
	for (Entity* e : entities) { e->update(); }
	check_collisions();
}

void Game::check_collisions()
{
	//Player/Coin collisions
}

void Game::handle_keys()
{
	//Get the keystates
	Uint8 *keystates = SDL_GetKeyState(NULL);
	
	//If WASD, move player
	if (keystates[SDLK_UP] || keystates[SDLK_DOWN] || keystates[SDLK_LEFT] || keystates[SDLK_RIGHT])
	{
		if (keystates[SDLK_UP])		keys.up();
		if (keystates[SDLK_DOWN])	keys.down();
		if (keystates[SDLK_LEFT])	keys.left();
		if (keystates[SDLK_RIGHT])	keys.right();
	}
	else keys.no_direction();

	if (keystates[SDLK_RETURN]) keys.enter();
}

void Game::render()
{
	//For all entities, render images
		//Change sprites
			//Change player sprite
			//Change coin sprite
		//Update animations
			//Remove touched coins
			//If coins are non-stationary, animate them along trajectory

	for (Entity* e : entities) { e->render(); }
}

void Game::poll()
{

}