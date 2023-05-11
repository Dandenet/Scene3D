#pragma once

#include <cstdint>

namespace graphics 
{

	class Texture
	{
	public:
		Texture();
		~Texture();

		Texture(const Texture& other) = delete;
		Texture(Texture&& other) noexcept;

		Texture& operator= (const Texture& other) = delete;
		Texture& operator= (Texture&& other) noexcept;

		bool create(uint32_t width, uint32_t height, bool hasAlpha);
		bool update(const uint8_t* buffer);

		void bind();

	private:
		uint32_t m_texture;
		uint32_t m_width;
		uint32_t m_height;
		bool     m_hasAlpha;
	};

}
