#pragma once
#ifndef _BUTTON_H_
#define _BUTTON_H_

#include <string>
#include "SDL.h"
#include "GameObject.h"

class Button : public SpriteObject
{
public:
	Button(SDL_Rect s, SDL_FRect d, const char* key);
	void Update();
	void Render();

protected:
	std::string m_key;
	enum BtnState { STATE_UP, STATE_OVER, STATE_DOWN } m_state; // enum defined locally.
	virtual void Execute() = 0; // Button3 is an abstract base class.
};

class PauseButton : public Button
{
private:
	void Execute();

public:
	PauseButton(SDL_Rect s, SDL_FRect d, const char* k);
};

class PlayButton : public Button
{
private:
	void Execute();
public:
	PlayButton(SDL_Rect s, SDL_FRect d, const char* k);
};

class MainMenuButton : public Button
{
private:
	void Execute();
public:
	MainMenuButton(SDL_Rect s, SDL_FRect d, const char* k);
};

#endif

