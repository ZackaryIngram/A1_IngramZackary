#pragma once
#ifndef _STATES_
#define  _STATES_
#include <SDL.h>
#include <vector>
#include "GameObject.h"
#include <iostream>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
class State 
{

public:
	virtual void Enter() = 0;
	virtual void Update() = 0;
	virtual void Render();
	virtual void Exit() = 0;
	virtual void Resume();
	virtual ~State() = default; 
	GameObject* GetGameobject(const std::string& s);
	auto GetIt(const std::string& s);

protected:
	State() {};
	std::vector<std::pair<std::string, GameObject*>> m_objects;
	vector<Enemy*> m_enemyNumber;
	vector<Enemy*> m_enemy;
};

class TitleState : public State
{
public:
	TitleState();
	virtual void Enter();
	virtual void Update();
	virtual void Render();
	virtual void Exit();
	
};
class PauseState : public State
{
private:
	SDL_Texture* m_pPBGTexture;

public:
	PauseState();
	virtual void Enter();
	virtual void Update();
	virtual void Render();
	virtual void Exit();

	Sprite m_pbg;

};

class GameState : public State
{
private:
	SDL_Renderer* m_pRenderer;
	SDL_Texture* m_pEnemyTexture;
	SDL_Texture* m_pTexture;
	SDL_Texture* m_pRules;
	SDL_Texture* m_pBGTexture;
	Mix_Music* m_backgroundMusic = nullptr;
	
	Sprite m_player, m_bg1, m_bg2, m_enemy;
	int m_speed = 2; 
	int m_dstWidth = 500, m_dstHeight = 550;
	int m_srcWidth = 500, m_srcHeight = 550 , m_srcy = 0;
	int m_time = 0, m_timerE = 0,  m_enemyTimer = 0;
	bool m_playerSpawned = true, m_plose;

	int m_counter;
	
public:
	GameState();
	virtual void Enter();
	virtual void Update();
	virtual void Render();
	virtual void Resume();
	virtual void Exit();
	

};

class LoseState : public State
{

public:
	LoseState();
	virtual void Enter();
	virtual void Update();
	virtual void Render();
	virtual void Exit();
};

#endif
