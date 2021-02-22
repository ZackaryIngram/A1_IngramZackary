#include "Primitive.h"
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
