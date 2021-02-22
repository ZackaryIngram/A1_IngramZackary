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
class State // THis is the base abstract base class for all states
{

public:
	virtual void Enter() = 0;// = 0 means Pure virtual - must be defined in subclass
	virtual void Update() = 0;
	virtual void Render();
	virtual void Exit() = 0;
	virtual void Resume();
	virtual ~State() = default; // Modern alternative to = {};
	GameObject* GetGo(const std::string& s);
	auto GetIt(const std::string& s);

protected:// Private but inherited... Prevents instantiation outside the class
	State() {};
	std::vector<std::pair<std::string, GameObject*>> m_objects;
	vector<Bullet*> m_bullet;
	//vector<EnemyBullet*> m_enemyBullet;
	vector<Enemy*> m_enemyNumber;
	//vector<ObstaclesTree*> m_treeNumber;
	vector<Enemy*> m_enemy;
	//vector<ObstaclesBird2*> m_bird2Number;
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
public:
	PauseState();
	virtual void Enter();
	virtual void Update();
	virtual void Render();
	virtual void Exit();

};

class GameState : public State
{
private:
	SDL_Renderer* m_pRenderer;
	SDL_Texture* m_pEnemyTexture;
	SDL_Texture* m_pTexture;
	SDL_Texture* m_pBGTexture;
	SDL_Texture* m_pShootTexture/*m_pFireballTexture*/;
	//SDL_Texture* m_pWaterballTexture;
	//SDL_Texture* m_explodeTexture;
	//SDL_Texture* m_pTreeTexture;
	//SDL_Texture* m_pEnemyTexture;
	//SDL_Texture* m_bird2Texture;
	Mix_Music* m_bgm = nullptr;
	Mix_Chunk* shoot = nullptr;
	//Mix_Chunk* waterball = nullptr;
	//Mix_Chunk* explosion = nullptr;
	Sprite m_player, m_bg1, m_bg2, m_enemy, m_shoot;
	int m_speed = 5; // In-class initialization. Not normal.
	int m_dstWidth = 432, m_dstHeight = 512;
	int m_srcWidth = m_dstWidth / 3, m_srcHeight = m_dstHeight / 4, m_srcy = 0;
	int m_time = 0, m_timerE = 0, m_timerB = 0, m_timerPE = 0, m_timerEE = 0, m_timerTree = 0, m_enemyTimer = 0;
	bool m_playerOn = true, m_pExploOn = false, m_eExploOn = false,  m_plose;
	int m_explodeSrcW = 1226 / 11, m_explodeSrcH = 440 / 4;

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
