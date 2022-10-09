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

    for (const SDL_Vertex& vertex : m_vertices)
    {
        j["vertices"]["position"] = {vertex.position.x, vertex.position.y};
        j["vertices"]["color"] = {vertex.color.r, vertex.color.g, vertex.color.b, vertex.color.a };
        j["vertices"]["tex_coord"] = { vertex.tex_coord.x, vertex.tex_coord.y };
    }

    //// count elements
    //auto s = j.size();
    //j["size"] = s;

    // for debug purpose
    //std::cout << std::setw(4) << j << '\n';

    // Write to file
    std::ofstream fichier{ "assets/" + m_name + ".model"};
    fichier << std::setw(4) << j << '\n';
}

void Model::LoadJson(const std::string& filepath)
{
    json j;
    std::ifstream fichier(filepath);
    std::string line{ "" };

    while (std::getline(fichier, line))
    {
        std::cout << line << std::endl;
        int index;
        if ((index = line.find("texture")) != std::string::npos)
        {
            std::cout << "Found line texture at " << index << std::endl;
        }
        if ((index = line.find("vertices")) != std::string::npos)
        {
            std::cout << "Found line vertices at " << index << std::endl;
        }
        if ((index = line.find("color")) != std::string::npos)
        {
            std::cout << "Found line color at " << index << std::endl;
        }
    }
    // parse it DONE
    // if texture DONE
    // texture
    // if color DONE
    // color
    // if position DONE
    // position
    // create model with texture color position
    // return model
}