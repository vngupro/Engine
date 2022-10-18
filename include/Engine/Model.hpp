#pragma once

#include <Engine/Export.hpp>
#include <SDL.h>
#include <vector>
#include <memory>
//#include <Engine/SDLppTexture.hpp> // why error incomplete type ??
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class SDLppRenderer;
class Transform;
class SDLppTexture;

class ENGINE_API Model
{
private:
	std::string m_name;
	std::vector<SDL_Vertex> m_vertices;
	std::vector<int> m_indices;
	std::shared_ptr<SDLppTexture> m_texture;
	//std::string m_texture;
public:
	Model();
	Model(const std::string& name, const std::vector<SDL_Vertex>& vertices, const std::vector<int>& indices, const std::shared_ptr<SDLppTexture> texture);

	void Draw(const SDLppRenderer& renderer, const Transform& transform);
	json ExportToJson();
	void ExportToCbor();
	void ExportToBinary();
	static Model LoadModelFromJson(const std::string& filepath);
	//static Model LoadModelFromCbor(const std::string& filepath);
	//static Model LoadModelFromBinary(const std::string& filepath);
};