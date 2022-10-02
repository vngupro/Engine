#include "ResourceManager.hpp"
#include "SDLppTexture.hpp"
#include "SDLppRenderer.hpp"
#include <utility>
#include <iostream>

std::shared_ptr<SDLppTexture> ResourceManager::GetTexture(SDLppRenderer& renderer, const const std::string& texturePath)
{
	return Get().GetTexture_Impl(renderer, texturePath);
}

std::shared_ptr<SDLppTexture> ResourceManager::GetTexture_Impl(SDLppRenderer& renderer, const std::string& texturePath)
{
	if (textureMap.find(texturePath) == textureMap.end())
	{
		std::shared_ptr<SDLppTexture> texture = std::make_shared<SDLppTexture>(SDLppTexture::LoadFromFile(renderer, texturePath));
		textureMap.emplace(texturePath, texture);
	}

	return textureMap.find(texturePath)->second;
}

void ResourceManager::Purge()
{
	return Get().Purge_Impl();
}

void ResourceManager::Purge_Impl()
{
	for (auto it = textureMap.begin(); it != textureMap.end(); it++)
	{
		if (it->second.use_count() <= 1)
		{
			it->second.reset();
			textureMap.erase(it->first);
			if (textureMap.size() > 0)
			{
				it--;
			}
		}
	}

	std::cout << "Purge success" << std::endl;
}