#include <Engine/Model.hpp>
#include <Engine/SDLppRenderer.hpp>
#include <Engine/ResourceManager.hpp>
#include <Engine/Vector2.hpp>
#include <Engine/Transform.hpp>
#include <Engine/SDLppTexture.hpp>
#include <fstream>
#include <iostream>

//Model::Model() :
//	m_vertices(),
//	m_indices()
//{
//}

Model::Model(const std::string& name, const std::vector<SDL_Vertex>& vertices, const std::vector<int>& indices, const std::shared_ptr<SDLppTexture> texture) :
	m_name(name),
    m_vertices(vertices),
	m_indices(indices),
	m_texture(texture)
{
}

void Model::Draw(const SDLppRenderer& renderer, const Transform& transform)
{
	SDL_RenderGeometry(renderer.GetHandle(), m_texture.get()->GetHandle(), &m_vertices[0], m_vertices.size(), &m_indices[0], m_indices.size());
	//(SDL_Renderer * renderer,
	//	SDL_Texture * texture,
	//	const SDL_Vertex * vertices, int num_vertices,
	//	const int* indices, int num_indices);
}


void Model::ExportToJson()
{
    json j =
    {
        {"texture", ResourceManager::Instance().GetPath(m_texture) },
        {"indices", m_indices }
    };

    j["vertices"] = json::array();
    for (int i = 0; i < m_vertices.size(); i++)
    {
        j["vertices"][i]["position"] = { m_vertices[i].position.x, m_vertices[i].position.y};
        j["vertices"][i]["color"] = { m_vertices[i].color.r, m_vertices[i].color.g, m_vertices[i].color.b, m_vertices[i].color.a };
        j["vertices"][i]["tex_coord"] = { m_vertices[i].tex_coord.x, m_vertices[i].tex_coord.y };
    }

    //// count elements
    //auto s = j.size();
    //j["size"] = s;

    // for debug purpose
    //std::cout << std::setw(4) << j << '\n';

    // Write to file
    std::ofstream fichier{ "assets/" + m_name + ".model"};
    fichier << std::setw(4) << j << "\n";
}

Model Model::LoadModel(const std::string& filepath)
{
    json j =
    {
        {"texture"},
        {"indices"},
        {"vertices"}
    };

    // check if file opening
    std::ifstream fichier(filepath);
    fichier >> j;
    //std::cout << std::setw(4) << j << "\n";

    std::string name;
    std::vector<SDL_Vertex> vertices;
    std::vector<int> indices;
    std::shared_ptr<SDLppTexture> texture = ResourceManager::Instance().GetTexture(j.at("texture"));
    j.at("indices").get_to(indices);

    for (int i = 0; i < j.at("vertices").size(); i++)
    {
        SDL_Vertex vertex;
        j.at("vertices")[i].at("color")[0].get_to(vertex.color.r);
        j.at("vertices")[i].at("color")[1].get_to(vertex.color.g);
        j.at("vertices")[i].at("color")[2].get_to(vertex.color.b);
        j.at("vertices")[i].at("color")[3].get_to(vertex.color.a);
        j.at("vertices")[i].at("position")[0].get_to(vertex.position.x);
        j.at("vertices")[i].at("position")[1].get_to(vertex.position.y);
        j.at("vertices")[i].at("tex_coord")[0].get_to(vertex.tex_coord.x);
        j.at("vertices")[i].at("tex_coord")[1].get_to(vertex.tex_coord.y);
        vertices.push_back(vertex);
    }

    return Model("name", vertices, indices, texture);
}