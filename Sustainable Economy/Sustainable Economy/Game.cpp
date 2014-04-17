#include "Game.h"
#include "SDL.h"
#include <time.h>
Game* g_game = NULL;

Game::Game() : running(true)
{
	delta = 0;
	srand(time(NULL));

	// Initialise all ENTITIES
	g_environment = new Environment(0, 0);
	environment = g_environment;
	player = new Player((9*32)-1, (8*32)-3);
	machine = new Machine((7*32), (32));
	coin = new Coin((8*32), (8*32), (4*32), (12*32));
	
	// Add this later
	//prompt = new Prompt(0, 0);
	
	m_Entities.push_back(environment);
	m_Entities.push_back(player);
	m_Entities.push_back(machine);
	//m_Entities.push_back(coin);
	//m_Entities.push_back(prompt);

	
	addABunchOfCoins();

	// Set up the key responses
	keys = KeyCode(player, machine);
}

Game::~Game(void)
{
	// Delete all entities
}


void Game::addABunchOfCoins()
{
	m_Entities.push_back(new Coin((10*32), (8*32), (14*32), (12*32)));
	m_Entities.push_back(new Coin((8*32), (8*32), (4*32), (12*32)));
	m_Entities.push_back(new Coin(160, 160, 480, 160));
	m_Entities.push_back(new Coin(160, 160, 480, 160));
	m_Entities.push_back(new Coin(160, 160, 480, 160));
	m_Entities.push_back(new Coin(160, 160, 480, 160));
	m_Entities.push_back(new Coin(160, 160, 480, 160));
	m_Entities.push_back(new Coin(160, 160, 480, 160));
	m_Entities.push_back(new Coin(160, 160, 480, 160));
	m_Entities.push_back(new Coin(160, 160, 480, 160));
}

void Game::run()
{	
	while (running)
	{
		m_FPSTimer.start();

		// Triumvirate Game loop processes
		Update();
		Render();
		Poll();

		// Regulate the framerate, and save the delta time.
		delta = RegulateFrameRate();
	}
}

// Regulate the frame rate, and return the time (ms) since the last call
int Game::RegulateFrameRate()
{
	// Regulate FrameRate
	int ticks				= m_FPSTimer.get_ticks();
	int gap_between_frames	= 1000 / FRAME_RATE;

	if(ticks < gap_between_frames)
    {
        //Sleep the remaining frame time
        SDL_Delay(gap_between_frames - ticks);
		return gap_between_frames;
    }
	
	return 1000/ticks;
}

void Game::Update()
{
	HandleKeys();
	
	for (Entity* e : m_Entities) { e->update(delta); }
	CheckCollisions();
}

void Game::CheckCollisions()
{
	//Player/Coin Collisions
	//Player/Wall Collisions
}

void Game::HandleKeys()
{
	//Get the keystates
	Uint8 *keystates = SDL_GetKeyState(NULL);
	
	//If WASD, move player
	if (keystates[SDLK_w] || keystates[SDLK_s] || keystates[SDLK_a] || keystates[SDLK_d])
	{
		if (keystates[SDLK_a])	keys.left();
		if (keystates[SDLK_d])	keys.right();
		if (keystates[SDLK_w])	keys.up();
		if (keystates[SDLK_s])	keys.down();
	}
	else keys.no_direction();
	
	if (keystates[SDLK_RETURN]) keys.enter();

	// Screen Formatting
	if (keystates[SDLK_f]) toggleScreenFormat();
	if (keystates[SDLK_ESCAPE]) exitFullScreen();
}

void Game::Render()
{
	// Render all of the entities
	for (Entity* e : m_Entities) { e->render(); }
	// Flip (update) the screen
	SDL_Flip(screen);
}

void Game::Poll()
{
	// Respond to events
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