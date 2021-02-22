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
public: // Methods.
	virtual ~GameObject() {};
	virtual void Update() = 0;
	virtual void Render() = 0;
	SDL_FRect* GetDst() { return &m_dst; }
	const bool GetEnabled() const { return m_enabled; }
	void SetEnabled(const bool e) { m_enabled = e; }
protected: // Attributes.
	SDL_FRect m_dst;
	bool m_enabled;
protected: // Methods.
	GameObject() :m_dst({ 0,0,0,0 }), m_enabled(true) {}
	GameObject(const SDL_FRect d) :m_dst(d), m_enabled(true) {}
};

class SpriteObject : public GameObject
{
public:
	virtual void Render() = 0;
	SDL_Rect* GetSrc() { return &m_src; }
protected: // Attributes.
	SDL_Rect m_src;
protected: // Methods.
	SpriteObject(const SDL_Rect s, const SDL_FRect d) :GameObject(d), m_src(s) {}
};

class AnimatedSpriteObject : public SpriteObject
{
public:
	virtual void Render() = 0;
protected: // Attributes.
	unsigned short m_frame, m_frameMax, m_sprite, m_spriteMin, m_spriteMax;
protected: // Methods.
	//AnimatedSpriteObject(const SDL_Rect s, const SDL_FRect d) :SpriteObject(s, d),
	//	m_frame(0), m_frameMax(0), m_sprite(0), m_spriteMin(0), m_spriteMax(0) {}
	//void SetAnimation(const unsigned short fMax, const unsigned short sMin, const unsigned short sMax,
	//	const int srcY = 0)
	//{
	//	m_frame = 0;
	//	m_frameMax = fMax;
	//	m_sprite = m_spriteMin = sMin;
	//	m_spriteMax = sMax;
	//	m_src.x = m_src.w * m_sprite;
	//	m_src.y = srcY;
	//}
	//void Animate()
	//{
	//	if (m_frame++ == m_frameMax)
	//	{
	//		m_frame = 0;
	//		if (++m_sprite == m_spriteMax)
	//			m_sprite = m_spriteMin; 
	//		m_src.x = m_src.w * m_sprite; 
	//	}
	//}
};

class Sprite
{
public:
	SDL_Rect m_src; // Source rectangle.
	SDL_Rect m_dst; // Destination rectangle.
	SDL_Rect m_playercoDst;

	void SetRekts(const SDL_Rect s, const SDL_Rect d) //non default construcotr
	{
		m_src = s;
		m_dst = d;
	}
	SDL_Rect* GetSrc() { return &m_src; }
	SDL_Rect* GetDst() { return &m_dst; }
	SDL_Rect* GetPlayercoDst() { return &m_playercoDst; }

	
};

class Bullet
{
private:

	SDL_Rect m_pFireDst;

public:

	Bullet(SDL_Point spawnLoc = { 1024, 384 })
	{
		cout << "CONSTRUCTING Bullet \n";
		this->m_pFireDst.x = spawnLoc.x;
		this->m_pFireDst.y = spawnLoc.y;
		this->m_pFireDst.w = 14;
		this->m_pFireDst.h = 7;

	}
	~Bullet() // Destructor
	{
		cout << "De-Allocating Bullet at " << &(*this) << endl;

	}
	//void SetLoc(SDL_Point newloc)
	//{
	//	m_pFireDst.x = newloc.x;
	//	m_pFireDst.y = newloc.y;
	//}
	void Update()
	{
		this->m_pFireDst.x +=5;
	}
	void Render(SDL_Renderer* rend, SDL_Texture* text, const SDL_Rect* src)
	{
		SDL_RenderCopy(rend, text, src, &m_pFireDst);
	}
	SDL_Rect* GetRekt() { return &m_pFireDst; }
};

//class EnemyBullet
//{
//private:
//
//	SDL_Rect m_pWaterDst;
//	Mix_Chunk* waterball = nullptr;
//public:
//
//
//	EnemyBullet(SDL_Point spawnLoc = { 1024, 384 })
//	{
//		cout << "CONSTRUCTING Enemy Bullet\n";
//		this->m_pWaterDst.x = spawnLoc.x;
//		this->m_pWaterDst.y = spawnLoc.y;
//		this->m_pWaterDst.w = 8;
//		this->m_pWaterDst.h = 8;
//
//	}
//	~EnemyBullet() // Destructor
//	{
//		cout << "De-Allocating Enemy Bullet at " << &(*this) << endl;
//
//	}
//	void UpdateEnemyB()
//	{
//		this->m_pWaterDst.x -= 5;
//	}
//	void Render(SDL_Renderer* rend, SDL_Texture* text, const SDL_Rect* src)
//	{
//		SDL_RenderCopy(rend, text, src, &m_pWaterDst);
//	}
//
//	SDL_Rect* GetRekt() { return &m_pWaterDst; }
//
//};

class Enemies
{
private:

	SDL_Rect m_pEnemyDst;
	SDL_Rect m_pEnemycoDst;
public:

	Enemies(SDL_Point spawnLoc = { 1024, 500 })
	{
		cout << "CONSTRUCTING Enemy \n";
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

	Enemy(SDL_Point spawnLoc = { 1024, 500 })
	{
		cout << "CONSTRUCTING Bird1 \n";
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
		cout << "De-Allocating bird1 at " << &(*this) << endl;

	}
	void UpdateEnemy()
	{
		this->m_enemyDst.x -= 5;
		this->m_enemycoDst.x -= 5;
	}
	void Render(SDL_Renderer* rend, SDL_Texture* text, const SDL_Rect* src)
	{
		SDL_RenderCopy(rend, text, src, &m_enemyDst);
	}
	SDL_Rect* GetRekt() { return &m_enemyDst; }
	SDL_Rect* GetEnemycoRekt() { return &m_enemycoDst; }
};

#endif

