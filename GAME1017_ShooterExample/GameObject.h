#pragma once
#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#include <iostream>

#include "SDL.h"
#include "Engine.h"
#include "EventManager.h"
#include "TextureManager.h"
using namespace std;

class GameObject
{
public: 
	virtual ~GameObject() {};
	virtual void Update() = 0;
	virtual void Render() = 0;
	//Getter
	SDL_FRect* GetDst() { return &m_dst; }
	const bool GetEnabled() const { return m_enabled; }
	//Setter
	void SetEnabled(const bool e) { m_enabled = e; }
protected: 
	SDL_FRect m_dst;
	bool m_enabled;
protected: 
	GameObject() :m_dst({ 0,0,0,0 }), m_enabled(true) {}
	GameObject(const SDL_FRect d) :m_dst(d), m_enabled(true) {}
};


class SpriteObject : public GameObject
{
public:

	virtual void Render() = 0;
	SDL_Rect* GetSrc() { return &m_src; }

protected: 
	SDL_Rect m_src;

protected: 
	SpriteObject(const SDL_Rect s, const SDL_FRect d) :GameObject(d), m_src(s) {}
};

class AnimatedSpriteObject : public SpriteObject
{
public:
	virtual void Render() = 0;
protected: 
	unsigned short m_frame, m_frameMax, m_sprite, m_spriteMin, m_spriteMax;

	
};

class Sprite
{
public:
	SDL_Rect m_src; 
	SDL_Rect m_dst; 
	SDL_Rect m_playerDst;

	void SetRekts(const SDL_Rect s, const SDL_Rect d) //non default construcotr
	{
		m_src = s;
		m_dst = d;
	}

	SDL_Rect* GetSrc() { return &m_src; }
	SDL_Rect* GetDst() { return &m_dst; }
	SDL_Rect* GetPlayerDst() { return &m_playerDst; }
};

class Enemies
{
private:

	SDL_Rect m_pEnemyDst;
	SDL_Rect m_pEnemycoDst;
public:

	Enemies(SDL_Point spawnLoc = { 1024, 500 })
	{
		cout << "Creating Enemy \n";
		this->m_pEnemyDst.x = spawnLoc.x;
		this->m_pEnemyDst.y = spawnLoc.y;
		this->m_pEnemyDst.w = 86;
		this->m_pEnemyDst.h = 102;

		this->m_pEnemycoDst.x = spawnLoc.x + 15;
		this->m_pEnemycoDst.y = spawnLoc.y + 10;
		this->m_pEnemycoDst.w = 86 - 15;
		this->m_pEnemycoDst.h = 102 - 10;

	}
	~Enemies() // Destructor
	{
		cout << "De-Allocating Enemy at " << &(*this) << endl;

	}
	void UpdateEnemies()
	{
		this->m_pEnemyDst.x -= 3;
		this->m_pEnemycoDst.x -= 3;
	}
	void Render(SDL_Renderer* rend, SDL_Texture* text, const SDL_Rect* src)
	{
		SDL_RenderCopy(rend, text, src, &m_pEnemyDst);
	}
	SDL_Rect* GetRekt() { return &m_pEnemyDst; }
	SDL_Rect* GetEnemycoRekt()
	{
		return &m_pEnemycoDst;
	}
};


class Enemy
{
private:
	SDL_Rect m_enemyDst;
	SDL_Rect m_enemycoDst;
public:

	Enemy(SDL_Point spawnLoc = { 1020, 200 })
	{
		cout << "Creating Enemy \n";
		this->m_enemyDst.x = spawnLoc.x;
		this->m_enemyDst.y = 0;
		this->m_enemyDst.w = 95 / 3 * 2;
		this->m_enemyDst.h = 96 * 2;

		this->m_enemycoDst.x = spawnLoc.x;
		this->m_enemycoDst.y = 0;
		this->m_enemycoDst.w = 95 / 3 * 2;
		this->m_enemycoDst.h = 96 * 2 - 10;
	}
	~Enemy() // Destructor
	{
		cout << "De-Allocating Enemy at " << &(*this) << endl;

	}
	void UpdateEnemy()
	{
		this->m_enemyDst.x -= 3;
		this->m_enemycoDst.x -= 3;
	}
	void Render(SDL_Renderer* rend, SDL_Texture* text, const SDL_Rect* src)
	{
		SDL_RenderCopy(rend, text, src, &m_enemyDst);
	}
	SDL_Rect* GetRekt() { return &m_enemyDst; }
	SDL_Rect* GetEnemycoRekt() { return &m_enemycoDst; }
};

#endif

