#pragma once
#include "DLLDefine.hpp"
#include <SDL.h>

class SDLppTexture;

class ENGINE_API ResourceManager
{
public:
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;
	ResourceManager(ResourceManager&&) = delete;
	ResourceManager& operator=(ResourceManager&&) = delete;

	static ResourceManager& Get()
	{
		static ResourceManager instance;
		return instance;
	}

	static SDLppTexture* GetTexture();
	static void Purge();

private:
	ResourceManager(){}

	SDLppTexture* GetTexture_Impl();
	void Purge_Impl();
};