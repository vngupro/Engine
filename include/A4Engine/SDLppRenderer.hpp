#pragma once

#include <A4Engine/Export.hpp>
#include <SDL.h>
#include <string_view>

class SDLppTexture;
class SDLppWindow;

class A4ENGINE_API SDLppRenderer
{
	public:
		SDLppRenderer(SDLppWindow& window, std::string_view rendererName = "", Uint32 flags = 0);
		SDLppRenderer(const SDLppRenderer&) = delete; // constructeur par copie
		SDLppRenderer(SDLppRenderer&& renderer) noexcept; // constructeur par mouvement
		~SDLppRenderer();

		void Clear();
		
		void DrawLines(const SDL_FPoint* points, std::size_t count);
		void DrawTriangles(const SDL_Vertex* vertices, std::size_t count);
		void DrawTriangles(const SDL_Vertex* vertices, std::size_t vertCount, int* indices, std::size_t indexCount);
		void DrawTriangles(const SDLppTexture& texture, const SDL_Vertex* vertices, std::size_t count);
		void DrawTriangles(const SDLppTexture& texture, const SDL_Vertex* vertices, std::size_t vertCount, int* indices, std::size_t indexCount);

		SDL_Renderer* GetHandle() const;
		
		void Present();
		
		void RenderCopy(const SDLppTexture& texture);
		void RenderCopy(const SDLppTexture& texture, const SDL_Rect& dst);
		void RenderCopy(const SDLppTexture& texture, const SDL_Rect& src, const SDL_Rect& dst);
		
		void SetDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

		SDLppRenderer& operator=(const SDLppRenderer&) = delete; // op�rateur d'assignation par copie
		SDLppRenderer& operator=(SDLppRenderer&&) noexcept; // op�rateur d'assignation par copie

	private:
		SDL_Renderer* m_renderer;
};