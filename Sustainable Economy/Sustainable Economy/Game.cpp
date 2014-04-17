#include "Game.h"
#include "SDL.h"
Game* g_game = NULL;

Game::Game() : running(true)
{
	// Initialise all ENTITIES
	g_environment = new Environment(0, 0);
	environment = g_environment;

	// Change this later
	/*player = new Player(0, 0);
	coin = new Coin(0, 0);
	machine = new Machine(0, 0);
	prompt = new Prompt(0, 0);*/
	
	m_Entities.push_back(environment);
	/*m_Entities.push_back(machine);
	m_Entities.push_back(coin);
	m_Entities.push_back(player);
	m_Entities.push_back(prompt);*/

	// Set up the key responses
	//keys = KeyCode(player, machine);
}

void Game::run()
{	
	while (running)
	{
		Update();
		Render();
		Poll();
	}
}

void Game::Update()
{
	//HandleKeys();
	
	for (Entity* e : m_Entities) { e->update(); }
	CheckCollisions();
}

void Game::CheckCollisions()
{
	//Player/Coin collisions
}

void Game::HandleKeys()
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

void Game::Render()
{
	//For all entities, render images
		//Change sprites
			//Change player sprite
			//Change coin sprite
		//Update animations
			//Remove touched coins
			//If coins are non-stationary, animate them along trajectory

	for (Entity* e : m_Entities) { e->render(); }
	SDL_Flip(screen);
}

void Game::Poll()
{
	SDL_Event event;
	while(SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			running = false;
		}
	}
}

void Game::addEntity(Entity* entity)
{
    m_Entities.push_back(entity);
}