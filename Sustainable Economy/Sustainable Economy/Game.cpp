#include "Game.h"
#include "SDL.h"

Game::Game(SDL_Surface* p_image, SDL_Surface* c_image, SDL_Surface* e_image, SDL_Surface* m_image, SDL_Surface* pr_image)
{
	//Initialise all ENTITIES
	player = new Player(p_image);		  
	coin = new Coin(c_image);
	environment = new Environment(e_image);	
	machine = new Machine(m_image);
	prompt = new Prompt(pr_image);
	
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
}

void Game::handle_keys()
{
	//Get the keystates
	Uint8 *keystates = SDL_GetKeyState(NULL);
	
	//If WASD, move player
	if (keystates[SDLK_UP])		keys.up();
	if (keystates[SDLK_DOWN])	keys.down();
	if (keystates[SDLK_LEFT])	keys.left();             //ERROR
	if (keystates[SDLK_RIGHT])	keys.right();
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