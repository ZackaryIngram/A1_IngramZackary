#include "TextureManager.h"
#include "Engine.h"
#include <iostream>

TextureManager::TextureManager(){}

void TextureManager::Init()
{
	//initialize SDL's Image subsystem
	if(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) != 0)
	{
		std::cout << "Image Initialized" << std::endl;
	}
	else // is 0
	{
		std::cout << "Image Init Failed: ERROR - " << IMG_GetError() << std::endl;
	}
}

void TextureManager::Load(const char* path, const std::string key)
{
	SDL_Texture* temp = IMG_LoadTexture(Engine::Instace().GetRenderer(), path);
	if(temp == nullptr)
	{
		std::cout << "Could not load Texture: ERROR - " << IMG_GetError() << std::endl;
	}
	else
	{
		s_textures.emplace(key, temp); //Add to map
		std::cout << "Successfully loaded Texture ' " << key << " '!" << std::endl;
	}
	

}

void TextureManager::UnLoad(const std::string key)
{
	if(s_textures.find(key) != s_textures.end())
	{
		SDL_DestroyTexture(s_textures[key]); //Dealocates Texture
		s_textures.erase(key); // Removes texture pointer from map
	}
	else
	{
		std::cout << "Could not unload ' " << key << " ' -  key not found! " << std::endl;
	}
	
}

SDL_Texture* TextureManager::GetTexture(const std::string key)
{
	return s_textures[key]; //Render textures at this key
}

void TextureManager::Quit()
{
	for (auto const& i : s_textures)
	{
		SDL_DestroyTexture(s_textures[i.first]);
	}
	s_textures.clear(); // Wrangle all the dangles
}

std::map<std::string, SDL_Texture*> TextureManager::s_textures;