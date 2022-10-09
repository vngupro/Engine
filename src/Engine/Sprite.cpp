#include <Engine/Sprite.hpp>
#include <Engine/SDLppRenderer.hpp>
#include <Engine/SDLppTexture.hpp>
#include <Engine/Transform.hpp>

Sprite::Sprite(std::shared_ptr<const SDLppTexture> texture) :
Sprite(std::move(texture), texture->GetRect())
{
}

Sprite::Sprite(std::shared_ptr<const SDLppTexture> texture, const SDL_Rect& rect) :
m_texture(std::move(texture)),
m_rect(rect),
m_width(rect.w),
m_height(rect.h)
{
}

void Sprite::Draw(SDLppRenderer& renderer, const Transform& transform)
{
	SDL_Rect texRect = m_texture->GetRect();

	Vector2f topLeftCorner = transform.TransformPoint(Vector2f(0.f, 0.f));
	Vector2f topRightCorner = transform.TransformPoint(Vector2f(m_width, 0.f));
	Vector2f bottomLeftCorner = transform.TransformPoint(Vector2f(0.f, m_height));
	Vector2f bottomRightCorner = transform.TransformPoint(Vector2f(m_width, m_height));

	float invWidth = 1.f / texRect.w;
	float invHeight = 1.f / texRect.h;

	SDL_Vertex vertices[4];
	vertices[0].color = SDL_Color{ 255, 255, 255, 255 };
	vertices[0].position = SDL_FPoint{ topLeftCorner.x, topLeftCorner.y };
	vertices[0].tex_coord = SDL_FPoint{ m_rect.x * invWidth, m_rect.y * invHeight };

	vertices[1].color = SDL_Color{ 255, 255, 255, 255 };
	vertices[1].position = SDL_FPoint{ topRightCorner.x, topRightCorner.y };
	vertices[1].tex_coord = SDL_FPoint{ (m_rect.x + m_rect.w) * invWidth, m_rect.y * invHeight };

	vertices[2].color = SDL_Color{ 255, 255, 255, 255 };
	vertices[2].position = SDL_FPoint{ bottomLeftCorner.x, bottomLeftCorner.y };
	vertices[2].tex_coord = SDL_FPoint{ m_rect.x * invWidth, (m_rect.y + m_rect.h) * invHeight };

	vertices[3].color = SDL_Color{ 255, 255, 255, 255 };
	vertices[3].position = SDL_FPoint{ bottomRightCorner.x, bottomRightCorner.y };
	vertices[3].tex_coord = SDL_FPoint{ (m_rect.x + m_rect.w) * invWidth, (m_rect.y + m_rect.h) * invHeight };

	int indices[6] = { 0, 1, 2, 2, 1, 3 };

	SDL_RenderGeometry(renderer.GetHandle(),
		m_texture->GetHandle(),
		vertices, 4,
		indices, 6);
}

int Sprite::GetHeight() const
{
	return m_height;
}

int Sprite::GetWidth() const
{
	return m_width;
}

void Sprite::Resize(int width, int height)
{
	m_width = width;
	m_height = height;
}

void Sprite::SetRect(SDL_Rect rect)
{
	m_rect = rect;
}
