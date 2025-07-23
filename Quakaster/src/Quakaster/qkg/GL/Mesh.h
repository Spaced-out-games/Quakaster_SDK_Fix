#pragma once
#include "../../Core.h"
#include <vector>
#include <initializer_list>
#include <memory>
namespace qkg
{
	template <class vertex_t>
	struct Mesh
	{
		std::unique_ptr<std::vector<vertex_t>> m_Vertices = nullptr;
		std::unique_ptr<std::vector<uint32_t>> m_Indices = nullptr;

		public:

			Mesh();
			~Mesh();
			void upload_vertices(std::vector<vertex_t>&& vertices);
			void upload_vertices(const std::initializer_list<vertex_t> vertices);


			void upload_indices(std::vector<uint32_t>&& indices);
			void upload_indices(const std::initializer_list<uint32_t> vertices);

	};


	template <class vertex_t>
	Mesh<vertex_t>::Mesh() = default;

	template <class vertex_t>
	Mesh<vertex_t>::~Mesh() = default;

	template <class vertex_t>
	void Mesh<vertex_t>::upload_vertices(std::vector<vertex_t>&& vertices)
	{
		m_Vertices = std::make_unique<std::vector<vertex_t>>(std::move(vertices));
	}

	template <class vertex_t>
	void Mesh<vertex_t>::upload_vertices(std::initializer_list<vertex_t> vertices)
	{
		m_Vertices = std::make_unique<std::vector<vertex_t>>(vertices);
	}

	template <class vertex_t>
	void Mesh<vertex_t>::upload_indices(std::vector<uint32_t>&& indices)
	{
		m_Indices = std::make_unique<std::vector<uint32_t>>(std::move(indices));
	}

	template <class vertex_t>
	void Mesh<vertex_t>::upload_indices(std::initializer_list<uint32_t> indices)
	{
		m_Indices = std::make_unique<std::vector<uint32_t>>(indices);
	}
}