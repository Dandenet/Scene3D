#pragma once

#include "Vertex.hpp"
#include <cstdint>

namespace graphics 
{

	class Mesh
	{
	public:
		Mesh();
		~Mesh();

		Mesh(const Mesh& other) = delete;
		Mesh(Mesh&& other) noexcept;

		Mesh& operator= (const Mesh& other) = delete;
		Mesh& operator= (Mesh&& other) noexcept;

		bool create(size_t vertexCount);
		bool update(const Vertex* vertices);

		void draw(uint32_t primitive);

	private:
		uint32_t m_vbo;
		uint32_t m_vao;

		size_t m_size;

	};

}
