#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <vector>
#define FPS 60
#define WIDTH 1024
#define HEIGHT 768

class Engine
{
private: // Private properties.
	bool m_bRunning; // Loop control flag.
		//m_bENull, // These three flags check if we need to clear the respective vectors of nullptrs.
		//m_bPBNull,
		//m_bEBNull,
		//m_bCanShoot; // This restricts the player from firing again unless they release the Spacebar.
	const Uint8* m_iKeystates; // Keyboard state container.
	Uint32 m_start, m_end, m_delta, m_fps, m_startLast; // Fixed timestep variables.
	SDL_Window* m_pWindow; // This represents the SDL window.
	SDL_Renderer* m_pRenderer; // This represents the buffer to draw to.
	double m_deltaTime;

	//SDL_Texture* m_pBGText; // For the bg.
	//Sprite bgArray[2];
	//SDL_Texture* m_pSprText; // For the sprites.
	//Player* m_player;
	//int m_iESpawn, // The enemy spawn frame timer properties.
	//	m_iESpawnMax;
	//vector<Enemy*> m_vEnemies;
	//vector<Bullet*> m_vPBullets;
	//vector<Bullet*> m_vEBullets;
	//SDL_Point m_pivot;
	//Mix_Music* m_pMusic;
	//vector<Mix_Chunk*> m_vSounds;

private: // Private methods.
	Engine() {}
	bool Init(const char* title, int xpos, int ypos, int width, int height, int flags);
	void Wake();
	void Sleep();
	void HandleEvents();
	void Update();
	void Render();
	void Clean();
	
public: // Public methods.

	int Run();
	static Engine& Instace(); // static method fo object access.
	SDL_Renderer* GetRenderer() { return m_pRenderer; }
	double GetDeltaTime() const { return m_deltaTime; }
	bool& Running();
	void SetRunning(const bool b);
};

// reminder: you can only have declarations in your headers, not logical code.
