#pragma once
#ifndef _PRIMITIVES_H_
#define _PRIMITIVES_H_

#include "GameObject.h"

class Image : public SpriteObject
{
public:
	Image(SDL_Rect s, SDL_FRect d, const char* k) :SpriteObject(s, d), m_key(k) {}
	void Update() {}
	void Render();
private:
	std::string m_key;
};

class Line : public GameObject
{
public:
	Line(SDL_FPoint start, SDL_FPoint end, SDL_Color col = { 255, 255, 255, 255 }) :
		GameObject({ 0,0,0,0 }), m_start(start), m_end(end), m_color(col) {}
	void Update() {};
	void Render();
private:
	SDL_FPoint m_start, m_end;
	SDL_Color m_color;
};

class Rectangle : public GameObject
{
public:
	Rectangle(SDL_FRect d, bool fill = true, SDL_Color col = { 255, 255, 255, 255 }) :
		GameObject(d), m_fill(fill), m_color(col) {}
	void Update() {};
	void Render();
private:
	bool m_fill;
	SDL_Color m_color;
};
//
//class Bullet : public SpriteObject
//{
//public:
//	Bullet(SDL_Rect s, SDL_FRect d, const char* key, const double angle);
//	void Update();
//	void Render();
//	const SDL_FPoint& GetCenter() { return m_center; }
//	const double& GetRadius() { return m_radius; }
//private:
//	SDL_FPoint m_center;
//	int m_ctr, m_ctrMax;
//	double m_angle,
//		m_dx, m_dy,
//		m_radius;
//	std::string m_key;
//};
//
//class Dragon : public SpriteObject
//{
//public: // Methods.
//	Dragon(SDL_Rect s, SDL_FRect d, const char* k) :SpriteObject(s, d), m_key(k) {}
//	~Dragon();
//	void Update();
//	void Render();
//	const SDL_FPoint& GetCenter() { return m_center; }
//	const double& GetRadius() { return m_radius; }
//	std::vector<Bullet*>& GetBullets() { return m_bullets; }
//private: // Properties.
//	SDL_FPoint m_center;
//	double m_angle,
//		m_velX, m_velY,
//		m_velMax,
//		m_radius,
//		m_rotSpeed,
//		m_thrust;
//	std::vector<Bullet*> m_bullets;
//	std::string m_key;
//};
//class Enemy : public SpriteObject
//{
//public:
//	Enemy(SDL_Rect s, SDL_FRect d);
//	void Update();
//	void Render();
//	const SDL_FPoint& GetCenter() { return m_center; }
//	const double& GetRadius() { return m_radius; }
//	void SetColMods(Uint8 r, Uint8 g, Uint8 b);
//private:
//	SDL_FPoint m_center;
//	double m_angle,
//		m_dx, m_dy,
//		m_radius,
//		m_rotSpeed;
//	Uint8 m_rMod, m_gMod, m_bMod;
//};
//
//class EnemyField : public GameObject
//{ // Manager class for the individual asteroids.
//public:
//	EnemyField(unsigned int sz = 6);
//	~EnemyField();
//	void Update();
//	void Render();
//	std::vector<Enemy*>& GetAsteroids() { return m_enemies; }
//	const unsigned int GetSize() { return m_size; }
//private:
//	std::vector<Enemy*> m_enemies;
//	int m_size;
//};

#endif