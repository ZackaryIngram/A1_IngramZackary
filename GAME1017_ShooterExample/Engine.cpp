#include "Engine.h"
#include "Utilities.h"
#include "StateManager.h"
#include "TextureManager.h"
#include "SoundManager.h"
#include "EventManager.h"
#include "States.h"
#include <iostream>
#include <ctime>
#include <iomanip>
#define WIDTH 1024
#define HEIGHT 768
#define FPS 60
#define BGSCROLL 2 // Could these scroll/speed values be handled in the class? Yes. Consider it!
#define PSPEED 6
using namespace std;
//Engine::Engine() :m_iESpawn(0), m_iESpawnMax(60), m_pivot({ 0,0 })
//{	// Again showing a mix of either initializers or in-body initialization. Initializers happen first.
//	m_bRunning = m_bEBNull = m_bENull = m_bPBNull = false; // Setting all to false.
//	m_bCanShoot = true;
//	cout << "Engine class constructed!" << endl; 
//}
bool Engine::Init(const char* title, int xpos, int ypos, int width, int height, int flags)
{
	cout << "Initializing game." << endl;
	srand((unsigned)time(NULL));
	// Attempt to initialize SDL.
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		// Create the window.
		m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (m_pWindow != nullptr) // Window init success.
		{
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
			if (m_pRenderer != nullptr) // Renderer init success.
			{

				TEMA::Init(); // Initialize Image subsystem 
				EVMA::Init();
				SOMA::Init();
			}
			else return false; // Renderer init fail.
		}
		else return false; // Window init fail.
	}
	else return false; // SDL init fail.
	m_fps = (Uint32)round((1 / (double)FPS) * 1000); // Sets FPS in milliseconds and rounds.
	m_iKeystates = SDL_GetKeyboardState(nullptr);
	m_startLast = SDL_GetTicks();

	STMA::PushState(new TitleState());

	m_bRunning = true; // Everything is okay, start the engine.
	cout << "Initialization!" << endl;
	return true;
}

void Engine::Wake()
{
	m_start = SDL_GetTicks();
	//New stuff for Delta Time
	m_deltaTime = (m_start - m_startLast) / 1000.0f;
	m_startLast = m_start;

}

void Engine::HandleEvents()
{
	EVMA::HandleEvents();
}

void Engine::Update()
{
	StateManager::Update();
	
}

void Engine::Render()
{
	STMA::Render();
	
}

void Engine::Sleep()
{
	m_end = SDL_GetTicks();
	m_delta = m_end - m_start;
	if (m_delta < m_fps) // Engine has to sleep.
		SDL_Delay(m_fps - m_delta);
}

int Engine::Run()
{
	if (m_bRunning == true)
	{
		return 1;
	}
	if (Init("GAME1017_A1_IngramZackary", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0) == false)
		return 1;
	while (m_bRunning)
	{
		Wake();
		HandleEvents();
		Update();
		Render();
		if (m_bRunning)
			Sleep();
	}
	Clean();
	return 0;
}

Engine& Engine::Instace()
{
	static Engine instance;
	return instance;
	
}
void Engine::Clean()
{
	cout << "Cleaning..." << endl;
	STMA::Quit();
	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyWindow(m_pWindow);
	TEMA::Quit();
	EVMA::Quit();
	SOMA::Quit();
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}

bool& Engine::Running() { return m_bRunning; } // Getter.
void Engine::SetRunning(const bool b) { m_bRunning = b; }