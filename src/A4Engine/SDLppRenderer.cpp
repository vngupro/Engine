#include <A4Engine/SDLppRenderer.hpp>
#include <A4Engine/SDLppTexture.hpp>
#include <A4Engine/SDLppWindow.hpp>
#include <SDL.h>

SDLppRenderer::SDLppRenderer(SDLppWindow& window, std::string_view rendererName, Uint32 flags)
{
	int choosenDriver = -1;

	int numDrivers = SDL_GetNumRenderDrivers();
	for (int i = 0; i < numDrivers; ++i)
	{
		SDL_RendererInfo info;
		SDL_GetRenderDriverInfo(i, &info);

		if (info.name == rendererName)
			choosenDriver = i;
	}

	m_renderer = SDL_CreateRenderer(window.GetHandle(), choosenDriver, flags);
}

SDLppRenderer::SDLppRenderer(SDLppRenderer&& renderer) noexcept
{
	m_renderer = renderer.m_renderer;
	renderer.m_renderer = nullptr;
}

SDLppRenderer::~SDLppRenderer()
{
	SDL_DestroyRenderer(m_renderer);
}

void SDLppRenderer::Clear()
{
	SDL_RenderClear(m_renderer);
}

void SDLppRenderer::DrawLines(const SDL_FPoint* points, std::size_t count)
{
	SDL_RenderDrawLinesF(m_renderer, points, static_cast<int>(count));
}

void SDLppRenderer::DrawTriangles(const SDL_Vertex* vertices, std::size_t count)
{
	SDL_RenderGeometry(m_renderer, nullptr, vertices, static_cast<int>(count), nullptr, 0);
}

void SDLppRenderer::DrawTriangles(const SDL_Vertex* vertices, std::size_t vertCount, int* indices, std::size_t indexCount)
{
	SDL_RenderGeometry(m_renderer, nullptr, vertices, static_cast<int>(vertCount), indices, static_cast<int>(indexCount));
}

void SDLppRenderer::DrawTriangles(const SDLppTexture& texture, const SDL_Vertex* vertices, std::size_t count)
{
	SDL_RenderGeometry(m_renderer, texture.GetHandle(), vertices, static_cast<int>(count), nullptr, 0);
}

void SDLppRenderer::DrawTriangles(const SDLppTexture& texture, const SDL_Vertex* vertices, std::size_t vertCount, int* indices, std::size_t indexCount)
{
	SDL_RenderGeometry(m_renderer, texture.GetHandle(), vertices, static_cast<int>(vertCount), indices, static_cast<int>(indexCount));
}

SDL_Renderer* SDLppRenderer::GetHandle() const
{
	return m_renderer;
}

void SDLppRenderer::Present()
{
	SDL_RenderPresent(m_renderer);
}

void SDLppRenderer::RenderCopy(const SDLppTexture& texture)
{
	SDL_RenderCopy(m_renderer, texture.GetHandle(), nullptr, nullptr);
}

void SDLppRenderer::RenderCopy(const SDLppTexture& texture, const SDL_Rect& dst)
{
	SDL_RenderCopy(m_renderer, texture.GetHandle(), nullptr, &dst);
}

void SDLppRenderer::RenderCopy(const SDLppTexture& texture, const SDL_Rect& src, const SDL_Rect& dst)
{
	SDL_RenderCopy(m_renderer, texture.GetHandle(), &src, &dst);
}

void SDLppRenderer::SetDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	SDL_SetRenderDrawColor(m_renderer, r, g, b, a);
}

SDLppRenderer& SDLppRenderer::operator=(SDLppRenderer&& renderer) noexcept
{
	std::swap(m_renderer, renderer.m_renderer);
	return *this;
}
