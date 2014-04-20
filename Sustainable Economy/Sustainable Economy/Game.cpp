#include "Game.h"
#include "SDL.h"
#include "CollisionManager.h"
#include "Prompt.h"
#include "Machine.h"
#include <time.h>

using namespace std;

Game* g_game = NULL;

Game::Game() : running(true), wallet(START_MONEY)
{
    delta = 0;
	srand(time(NULL));

	// Initialise all ENTITIES
	player = new Player((9*32)-1, (8*32)-3);
	machine = new Machine((7*32), (32));
	prompt = new Prompt(0, 0);
    
	m_CollisionManager = new CollisionManager(this);
	
	// Add this later
	//prompt = new Prompt(0, 0);
	
	m_Entities.push_back(player);
	m_Entities.push_back(machine);
	m_Entities.push_back(prompt);

	// Set up the key responses
	keys = KeyCode(player, machine);
}

Game::~Game(void)
{
	// Delete all entities
}

void Game::run()
{
    // Must be initialised after Game is constructed
    InitEnvironment();
    
	while (running)
	{
		m_FPSTimer.start();

		// Triumvirate Game loop processes
		Update();
		Render();
		Poll();
        
        // Handle any deletions that need to take place after updating
        DeleteEntities();

		// Regulate the framerate, and save the delta time.
		delta = RegulateFrameRate();
	}
}

void Game::InitEnvironment()
{
	g_environment = new Environment(0, 0);
	environment = g_environment;
	//m_Entities.push_back(environment);
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

void Game::Update()
{
	HandleKeys();
	
	for (Entity* e : m_Entities) { e->update(delta); }
	m_CollisionManager->Update(delta);
}

void Game::Render()
{
    // Clear the screen
    SDL_FillRect(screen,NULL,0x000000);
    
    environment->render();
    
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

void Game::addCollidable(Collidable* collidable)
{
    addEntity(collidable);
    m_CollisionManager->AddCollidable(collidable);
}

void Game::removeEntity(Entity* entity)
{
    m_EntityDeleteQueue.push_back(entity);
}

void Game::removeCollidable(Collidable *collidable)
{
    m_CollisionManager->RemoveCollidable(collidable);
    removeEntity(collidable);
}

void Game::DeleteEntities()
{
    for (Entity* entity : m_EntityDeleteQueue)
    {
        m_Entities.remove(entity);
        //delete entity;
    }
    
    m_EntityDeleteQueue.clear();
}