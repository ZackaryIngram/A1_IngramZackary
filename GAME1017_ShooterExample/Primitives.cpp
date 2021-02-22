#include "Primitives.h"
#include "Engine.h"
#include "EventManager.h"
#include "SoundManager.h"
#include "MathManager.h"

void Image::Render()
{
	SDL_RenderCopyF(Engine::Instace().GetRenderer(), TEMA::GetTexture(m_key), &m_src, &m_dst);
}

void Line::Render()
{
	SDL_SetRenderDrawColor(Engine::Instace().GetRenderer(), m_color.r, m_color.g, m_color.b, m_color.a);
	SDL_RenderDrawLineF(Engine::Instace().GetRenderer(), m_start.x, m_start.y, m_end.x, m_end.y);
}

void Rectangle::Render()
{
	SDL_SetRenderDrawColor(Engine::Instace().GetRenderer(), m_color.r, m_color.g, m_color.b, m_color.a);
	if (m_fill)
		SDL_RenderFillRectF(Engine::Instace().GetRenderer(), &m_dst);
	else
		SDL_RenderDrawRectF(Engine::Instace().GetRenderer(), &m_dst);
}
//Bullet::Bullet(SDL_Rect s, SDL_FRect d, const char* key, const double angle) :
//	SpriteObject(s, d), m_key(key), m_angle(angle), m_radius(10),
//	m_ctr(0), m_ctrMax(60)
//{
//	m_center = { (m_dst.x + m_dst.w / 2.0f), (m_dst.y + m_dst.h / 2.0f) };
//	MAMA::SetDeltas(MAMA::Deg2Rad(m_angle), m_dx, m_dy, 5.0f, 10.0f);
//}
//
//void Bullet::Update()
//{
//	 Move object.
//	m_center.x += (float)m_dx;
//	m_center.y += (float)m_dy;
//	 Wrap on screen.
//	if (m_center.x < -m_dst.w) m_center.x = WIDTH + m_dst.w / 2;
//	else if (m_center.x > WIDTH + m_dst.w) m_center.x = 0 - m_dst.w / 2;
//	else if (m_center.y < -m_dst.h) m_center.y = HEIGHT + m_dst.h / 2;
//	else if (m_center.y > HEIGHT + m_dst.h) m_center.y = 0 - m_dst.h / 2;
//	 Update dest rectangle.
//	m_dst.x = m_center.x - m_dst.w / 2;
//	m_dst.y = m_center.y - m_dst.h / 2;
//	 Set bullet to be disabled.
//	if (m_ctr++ >= m_ctrMax)
//		m_enabled = false;
//}
//
//void Bullet::Render()
//{
//	SDL_RenderCopyExF(Engine::Instace().GetRenderer(), TEMA::GetTexture(m_key),
//		&m_src, &m_dst, m_angle, nullptr, SDL_FLIP_NONE);
//}
//
//Dragon::~Dragon()
//{
//	SOMA::StopSound(15);
//	for (auto a : m_bullets)
//	{
//		delete a;
//		a = nullptr; // ;)
//	}
//	m_bullets.clear();
//}
//
//void Dragon::Update()
//{
//	m_velMax = (6.0), m_radius = (38); m_angle = 0;
//	m_center = { (m_dst.x + m_dst.w / 2.0f), (m_dst.y + m_dst.h / 2.0f) };
//	Bullet Spawn
//	if (EVMA::MousePressed(1))
//	{
//		m_bullets.push_back(new Bullet({ 0, 0, 146, 72 },
//			{ m_center.x - 9, m_center.y - 12, 50, 50 },
//			"bullet", m_angle));
//		m_bullets.shrink_to_fit();
//	}
//	 Checking animation states.
//	Movement
//	if (EVMA::KeyHeld(SDL_SCANCODE_W))
//	{
//		 m_velY = -4;
//		m_center.y += (float)m_velY;
//		
//	}
//	/*else if(EVMA::KeyHeld(SDL_SCANCODE_S))
//	{
//		m_velY = 4;
//		m_center.y += (float)m_velY;
//		
//	}*/
//	else if (EVMA::KeyHeld(SDL_SCANCODE_A))
//	{
//		m_velX = -4;
//		m_center.x += (float)m_velX;
//
//	}
//	else if (EVMA::KeyHeld(SDL_SCANCODE_D))
//	{
//		m_velX = 4;
//		m_center.x += (float)m_velX;
//
//	}
//	else
//	{
//		m_velX = 0;
//		m_velY = 3;
//		m_center.y += (float)m_velY;
//		m_center.x += (float)m_velX;	
//	}
//		 Wrap on screen.
//		if (m_center.x < -m_dst.w / 2) m_center.x = WIDTH + m_dst.w / 2;
//		else if (m_center.x > WIDTH + m_dst.w / 2) m_center.x = 0 - m_dst.w / 2;
//		if (m_center.y < -m_dst.h / 2) m_center.y = HEIGHT + m_dst.h / 2;
//		else if (m_center.y > HEIGHT + m_dst.h / 2) m_center.y = 0 - m_dst.h / 2;
//		 Update dest rectangle.
//		m_dst.x = m_center.x - m_dst.w / 2;
//		m_dst.y = m_center.y - m_dst.h / 2;
//	
//		 Invoke the animation.
//		Animate();
//		 Update bullets.
//		for (unsigned int i = 0; i < m_bullets.size(); i++)
//		{
//			m_bullets[i]->Update();
//			if (!m_bullets[i]->GetEnabled())
//			{
//				delete m_bullets[i];
//				m_bullets[i] = nullptr;
//				m_bullets.erase(m_bullets.begin() + i);
//				m_bullets.shrink_to_fit();
//			}
//
//		}
//}
//
//void Dragon::Render()
//{
//	for (const auto b : m_bullets)
//		b->Render();
//	SDL_RenderCopyExF(Engine::Instace().GetRenderer(), TEMA::GetTexture("player"),
//		&m_src, &m_dst, m_angle, nullptr, SDL_FLIP_NONE);
//}
//
//Enemy::Enemy(SDL_Rect s, SDL_FRect d) : SpriteObject(s, d),
//m_angle(0.0), m_radius(33.0)
//{
//	m_center = { (m_dst.x + m_dst.w / 2.0f), (m_dst.y + m_dst.h / 2.0f) };
//	m_rotSpeed = (1.0 + rand() % 5) * (rand() % 2 * 2.0 - 1.0); // -1 or 1
//	MAMA::SetDeltas(MAMA::Deg2Rad((rand() % 360) - 90.0), m_dx, m_dy, -2.0f, 2.0f);
//}
//
//void Enemy::Update()
//{
//	 Rotate and move object.
//	m_angle += m_rotSpeed;
//	m_center.x += -2*(float)m_dx;
//	/*m_center.y += (float)m_dy;*/
//	 Wrap on screen.
//	if (m_center.x < -m_dst.w / 2) m_center.x = WIDTH + m_dst.w / 2;
//	else if (m_center.x > WIDTH + m_dst.w / 2) m_center.x = 0 - m_dst.w / 2;
//	else if (m_center.y < -m_dst.h / 2) m_center.y = HEIGHT + m_dst.h / 2;
//	else if (m_center.y > HEIGHT + m_dst.h / 2) m_center.y = 0 - m_dst.h / 2;
//	 Update dest rectangle.
//	m_dst.x = m_center.x - m_dst.w / 2;
//	m_dst.y = m_center.y - m_dst.h / 2;
//}
//
//void Enemy::Render()
//{
//	SDL_SetTextureColorMod(TEMA::GetTexture("enemy"), 255 - m_rMod, 255 - m_gMod, 255 - m_bMod);
//	SDL_RenderCopyExF(Engine::Instace().GetRenderer(), TEMA::GetTexture("enemy"),
//		&m_src, &m_dst, m_angle, nullptr, SDL_FLIP_NONE);
//	SDL_SetTextureColorMod(TEMA::GetTexture("enemy"), 255, 255, 255); // Resetting it so not all sprites are tinted this way.
//}
//
//void Enemy::SetColMods(Uint8 r, Uint8 g, Uint8 b)
//{
//	m_rMod = r; m_gMod = g; m_bMod = b;
//}
//EnemyField::EnemyField(unsigned int sz) :GameObject({ 0,0,0,0 }), m_size(sz)
//{
//	for (int i = 0; i < m_size; i++)
//	{
//		m_enemies.push_back(new Enemy({ 0, 0, 400, 358 },
//			{ (i % 2 == 0 ? 1000.0f : 1220 + (rand() % 800)), (i % 2 == 0 ? 40.0f:-44) + (rand() %800),
//			121.0f, 121.0f }));
//		m_enemies.back()->SetColMods((rand() % 129), (rand() % 129), (rand() % 129));
//	}
//	m_enemies.shrink_to_fit();
//}
//
//EnemyField::~EnemyField()
//{
//	for (auto a : m_enemies)
//	{
//		delete a;
//		a = nullptr; // ;)
//	}
//	m_enemies.clear();
//}
//
//void EnemyField::Update()
//{
//	for (const auto a : m_enemies)
//		a->Update();
//}
//
//void EnemyField::Render()
//{
//	for (const auto a : m_enemies)
//		a->Render();
//}