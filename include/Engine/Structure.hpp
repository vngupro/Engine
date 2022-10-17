#pragma once
#include <memory>

class SDLppTexture;
class Sprite;

struct Drawable
{
	int width;
	int height;
	std::shared_ptr<SDLppTexture> texture;
	//Sprite sprite;
	//Transform 
};