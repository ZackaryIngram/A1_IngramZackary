#pragma once
#ifndef _TEXTURE_MANAGER_
#define  _TEXTURE_MANAGER_
#include <map>
#include <string>
#include "SDL.h"
#include "SDL_image.h"
class TextureManager
{
public://Public Methods
  	static void Init();
	static void Load(const char* path, const std::string key); 
	static void UnLoad(const std::string key);
	static SDL_Texture* GetTexture(const std::string key);
	static void Quit();


private://Private properties

	static std::map<std::string, SDL_Texture*> s_textures;

private://Private Methods
	TextureManager();

};

typedef TextureManager TEMA;
#endif
