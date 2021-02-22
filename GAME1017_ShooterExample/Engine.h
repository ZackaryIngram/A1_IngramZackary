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
private: 
	bool m_bRunning; 
	const Uint8* m_iKeystates; 
	Uint32 m_start, m_end, m_delta, m_fps, m_startLast; 
	SDL_Window* m_pWindow; 
	SDL_Renderer* m_pRenderer; 
	double m_deltaTime;

private: 
	Engine() {}
	bool Init(const char* title, int xpos, int ypos, int width, int height, int flags);
	void Wake();
	void Sleep();
	void HandleEvents();
	void Update();
	void Render();
	void Clean();
	
public:

	int Run();
	static Engine& Instace(); 
	SDL_Renderer* GetRenderer() { return m_pRenderer; }
	double GetDeltaTime() const { return m_deltaTime; }
	bool& Running();
	void SetRunning(const bool b);
};

