#pragma once
#include "DLLDefine.hpp"
#include <SDL.h>
#include <string>
#include <map>
#include <memory>

class SDLppTexture;
class SDLppRenderer;

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
	
	static std::shared_ptr<SDLppTexture> GetTexture(SDLppRenderer& renderer, const std::string& texturePath);
	static void Purge();
	//static void Register(const std::shared_ptr<SDLppTexture>);

private:
	// Constructor
	ResourceManager(){}

	// Variables
	std::map<const std::string, std::shared_ptr<SDLppTexture>> textureMap;

	// Functions
	std::shared_ptr<SDLppTexture> GetTexture_Impl(SDLppRenderer& renderer, const std::string& texturePath);
	void Purge_Impl();
	//static void Register_Impl(const std::shared_ptr<SDLppTexture>);
};