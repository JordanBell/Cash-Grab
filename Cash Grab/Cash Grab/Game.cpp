#include "Game.h"
#include "SDL.h"
#include "CollisionManager.h"
#include "Machine.h"
#include "Resources.h"
#include "UI.h"
#include <time.h>
#include <sstream>
#include "Wallet.h"
#include "EffectMagnetism.h"
#include "ParticleSimple.h"

using namespace std;

Game* g_game = nullptr;

Game::Game() : running(true), consoleCooldownCounter(0), m_muted(false), m_transitionDirection(Player::Direction::NULLDIR)
{
    delta = 0;
	srand((unsigned int)time(nullptr));

	// Initialise all ENTITIES
	machine = new Machine((7*TILE_SIZE), (TILE_SIZE));
	g_machine = machine;
	player = new Player((9.5*TILE_SIZE), (8*TILE_SIZE));
    g_player = player;
	prompt = new Prompt(machine);
    
    m_EffectManager = new EffectManager();

    // Add persisting magnetism effect (should only be one of this throughout the duration of the game)
    AddEffect(new EffectMagnetism(nullptr));
    
	m_CollisionManager = new CollisionManager(this);
	
    addCollidable(machine);
	m_GameObjects.push_back(player);

	// Set up the key responses
	keys = KeyCode(player, machine);
}

Game::~Game(void)
{
	// Delete all entities
    for (list<GameObject*>::iterator it = m_GameObjects.begin(); it != m_GameObjects.end(); ++it)
    {
        delete *it;
    }
    
    delete m_EffectManager;
    delete m_CollisionManager;
}

void Game::run()
{    
	InitEnvironment();
    
    //Mix_PlayMusic(g_resources->GetMusic(), -1);
    
    m_FPSTimer.start();
    lastUpdate = m_FPSTimer.get_ticks();
    
	while (running)
	{
		// Triumvirate Game loop processes
		Update();
		Render();
		Poll();
        
        // Handle any deletions that need to take place after updating
        DeleteGameObjects();

		// Regulate the framerate, and save the delta time.
		RegulateFrameRate();
	}
    
    Mix_HaltMusic();
}

void Game::InitEnvironment(void)
{
	// Environment stuff has a few steps
	g_environment = new Environment(0, 0);
	g_environmentUpper = new EnvironmentUpper(0, 0);
	environment = g_environment;
	m_GameObjects.push_front(environment);
	m_GameObjects.push_front(g_environmentUpper);

	// Add the prompt now, to layer it over everything
	m_GameObjects.push_back(prompt);
}

// Regulate the frame rate, and return the time (ms) since the last call
void Game::RegulateFrameRate()
{
	// Regulate FrameRate
	int ticks				= m_FPSTimer.get_ticks();
	int gap_between_frames	= ticks - lastUpdate;
	int minimum_gap_between_frames	= 1000 / FRAME_RATE;

	if(gap_between_frames < minimum_gap_between_frames)
    {
        //Sleep the remaining frame time
        SDL_Delay(minimum_gap_between_frames - gap_between_frames);
		delta = gap_between_frames;
//        return;
    }
	
	delta = ticks - lastUpdate;
    lastUpdate = ticks;

	//g_UI->SetTotalCoins(1000/delta);
}

void Game::HandleKeys()
{
	//Get the keystates
	Uint8 *keystates = SDL_GetKeyState(nullptr);

	if (!testingConsole.IsActive())
	{
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
		if (keystates[SDLK_1])		keys._1();

		// Screen Formatting
		if (keystates[SDLK_f]) toggleScreenFormat();
		if (keystates[SDLK_ESCAPE]) running = false;
	}

	// Testing console toggle
	if ((keystates[SDLK_BACKQUOTE]) && (consoleCooldownCounter == 0)) 
	{ 
		// Reset cooldown
		consoleCooldownCounter = CONSOLE_COOLDOWN;
		// Toggle it
		testingConsole.Toggle(); 
	}
}

void Game::Update()
{
	// Decrement the cooldown for console activation
	if (consoleCooldownCounter > 0) consoleCooldownCounter--;

	// Increment the screen transition
	if (m_transitionDirection != Player::Direction::NULLDIR)
	{
		if (m_transitionDirection == Player::Direction::UP)
		{
			if (s_renderingOffset_y != screen->h)
				s_renderingOffset_y += TRANSITION_SPEED;
			else
				m_transitionDirection = Player::Direction::NULLDIR;
		}
        if (m_transitionDirection == Player::Direction::DOWN)
		{
			if (s_renderingOffset_y != 0)
				s_renderingOffset_y -= TRANSITION_SPEED;
			else
				m_transitionDirection = Player::Direction::NULLDIR;
		}
        if (m_transitionDirection == Player::Direction::LEFT)
		{
			if (s_renderingOffset_x != 0)
				s_renderingOffset_x += TRANSITION_SPEED;
			else
				m_transitionDirection = Player::Direction::NULLDIR;
		}
        if (m_transitionDirection == Player::Direction::RIGHT)
		{
			if (s_renderingOffset_x != -screen->w)
				s_renderingOffset_x -= TRANSITION_SPEED;
			else
				m_transitionDirection = Player::Direction::NULLDIR;
        }
	}


//    if (consoleCooldownCounter == 0) g_player->Smash(50);
	HandleKeys();
	
	for (GameObject* e : m_GameObjects)
        e->Update(delta);
    
    // Efficiency!
    m_GameObjects.sort(GameObject_Compare);
    
	m_CollisionManager->Update(delta);
    m_EffectManager->Update(delta);
    
    g_UI->SetCollectedCoins(Wallet::GetCoins());
    g_UI->SetRequiredCoins(machine->coinCost);
    g_UI->SetTotalCoins(Wallet::GetTotalCoins());
}

void Game::Render()
{
    // Clear the screen
    SDL_FillRect(screen,NULL,0x000000);
    
	// Render all of the entities
	for (GameObject* go : m_GameObjects) 
		go->Render();

	// Render the UI above everything
    g_UI->Render();

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
		
		if( event.type == SDL_KEYDOWN )
		{
			if (testingConsole.IsActive())
				testingConsole.KeyIn(event.key.keysym);
		}
	}
}

void Game::addGameObject(GameObject* gameObject, bool toFront)
{
    if (toFront)
    {
        m_GameObjects.push_front(gameObject);
    }
    else
    {
        m_GameObjects.push_back(gameObject);
    }
    
//    m_GameObjects.sort(GameObject_Compare);
}

void Game::addCollidable(Collidable* collidable, bool toFront)
{
	// Check if the collidable is a game object. If so, add it to the game object list
	GameObject* collidableGameObject = dynamic_cast<GameObject*>(collidable);

	if (collidableGameObject)
		addGameObject(collidableGameObject, toFront);

	// Add this collidable to the collidables list
    m_CollisionManager->AddCollidable(collidable, toFront);
}

void Game::AddEffect(Effect *effect)
{
    m_EffectManager->AddEffect(effect);
}

void Game::removeGameObject(GameObject* gameObject)
{
    m_GameObjectDeleteQueue.emplace_back(unique_ptr<GameObject>(gameObject)); // Warning: Will this in-line declaration delete the pointer when out of scope?
}

void Game::removeCollidable(Collidable *collidable)
{
	// Check if the collidable is a game object. If so, add it to the game object list
	GameObject* collidableGameObject = dynamic_cast<GameObject*>(collidable);

	if (collidableGameObject)
		removeGameObject(collidableGameObject);

	// Remove this collidable to the collidables list
    m_CollisionManager->RemoveCollidable(collidable);
}

void Game::DeleteGameObjects()
{
    for (unique_ptr<GameObject>& gameObject_ptr : m_GameObjectDeleteQueue)
    {
        m_GameObjects.remove(gameObject_ptr.get());
    }
    
    m_GameObjectDeleteQueue.clear(); // Thus deleting the entities being pointed to
}