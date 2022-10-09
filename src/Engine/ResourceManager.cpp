#include <Engine/ResourceManager.hpp>
#include <Engine/SDLppSurface.hpp>
#include <Engine/SDLppTexture.hpp>
#include <stdexcept>

ResourceManager::ResourceManager(SDLppRenderer& renderer) :
m_renderer(renderer)
{
	if (s_instance != nullptr)
		throw std::runtime_error("only one ResourceManager can be created");

	s_instance = this;
}

ResourceManager::~ResourceManager()
{
	s_instance = nullptr;
}

void ResourceManager::Clear()
{
	m_missingTexture.reset();
	m_textures.clear();
}

const std::shared_ptr<SDLppTexture>& ResourceManager::GetTexture(const std::string& texturePath)
{
	// Avons-nous d�j� cette texture en stock ?
	auto it = m_textures.find(texturePath);
	if (it != m_textures.end())
		return it->second; // Oui, on peut la renvoyer

	// Non, essayons de la charger
	SDLppSurface surface = SDLppSurface::LoadFromFile(texturePath);
	if (!surface.IsValid())
	{
		// On a pas pu charger la surface, utilisons une texture "manquante"
		if (!m_missingTexture)
		{
			// On cr�� la texture la premi�re fois qu'on en a besoin
			surface = SDLppSurface(64, 64);
			surface.FillRect(SDL_Rect{ 0, 0, 16, 16 }, 255, 0, 255, 255);
			surface.FillRect(SDL_Rect{ 16, 0, 16, 16 }, 0, 0, 0, 255);
			surface.FillRect(SDL_Rect{ 0, 16, 16, 16 }, 0, 0, 0, 255);
			surface.FillRect(SDL_Rect{ 16, 16, 16, 16 }, 255, 0, 255, 255);

			m_missingTexture = std::make_shared<SDLppTexture>(SDLppTexture::LoadFromSurface(m_renderer, surface));
		}
		
		// On enregistre cette texture comme une texture manquante (pour ne pas essayer de la charger � chaque fois)
		m_textures.emplace(texturePath, m_missingTexture);
		return m_missingTexture;
	}

	// On a r�ussi � charger la surface, on la transforme en texture et on l'enregistre
	std::shared_ptr<SDLppTexture> texture = std::make_shared<SDLppTexture>(SDLppTexture::LoadFromSurface(m_renderer, surface));

	// .emplace et .insert renvoient un std::pair<iterator, bool>, le bool�en indiquant si la texture a �t� ins�r�e dans la map (ce qu'on sait d�j� ici)
	it = m_textures.emplace(texturePath, std::move(texture)).first;

	// Attention, on ne peut pas renvoyer texture directement (m�me sans std::move) car on renvoie une r�f�rence constante
	// qui serait alors une r�f�rence constante sur une variable temporaire d�truite � la fin de la fonction (texture)

	return it->second;
}

void ResourceManager::Purge()
{
	// On va it�rer sur le conteneur tout en enlevant certains �l�ments pendant l'it�ration, cela demande un peu de pratique
	for (auto it = m_textures.begin(); it != m_textures.end(); ) //< pas d'incr�mentation de it
	{
		// On v�rifie le compteur pour v�rifier si la texture est utilis�e ailleurs ou non
		if (!it->second.unique())
		{
			++it; // la texture est utilis�e, on la garde et on passe � la suivante
		}
		else
		{
			// la texture n'est plus utilis�e, on peut l'enlever avec .erase(it), qui renvoie un nouvel it�rateur sur l'�l�ment *suivant*
			// (celui du prochain tour de boucle = pas d'incr�mentation dans ce cas)
			it = m_textures.erase(it);
		}
	}
}

ResourceManager& ResourceManager::Instance()
{
	if (s_instance == nullptr)
		throw std::runtime_error("ResourceManager hasn't been instantied");

	return *s_instance; 
}

std::string ResourceManager::GetPath(const std::shared_ptr<SDLppTexture>& texture)
{
	for (auto it = m_textures.begin(); it != m_textures.end(); ++it)
		if (it->second == texture)
			return it->first;
	return "Path not found";
}

ResourceManager* ResourceManager::s_instance = nullptr;
