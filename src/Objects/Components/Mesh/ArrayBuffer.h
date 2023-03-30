#pragma once
#include <vector>
#include "GLFW/glfw3.h"

namespace _CompositionEngine
{
	enum BufferLayoutType
	{
		FLOAT,
		INT,
		DOUBLE,
		CHAR,
	};

	class ArrayBuffer
	{
	public:
		ArrayBuffer(GLenum type);
		virtual void Bind() = 0;

		inline GLuint& ID() { return m_ID; }

	private:
		GLuint m_ID;
	};

	class VertexArray : public ArrayBuffer
	{
	public:
		VertexArray();
		virtual void Bind();
	private:

	};
	class VertexBufferLayout
	{
	public:
		void AddAttribute(unsigned count, BufferLayoutType type);
		inline unsigned NumAttributes() const { return (unsigned)m_Offsets.size(); }

		friend class VertexBuffer;
	private:
		std::vector<unsigned> m_Offsets; //!< The "Stride" in bytes between attributes
		std::vector<BufferLayoutType> m_Types; //!< The type of the elements in each attribute
	    std::vector<unsigned> m_AttribCounts;
	    long int m_VertexSize = 0;
	};
	class VertexBuffer : public ArrayBuffer
	{
	public:
		VertexBuffer(float* verts, unsigned count);
		void AssignLayout(VertexBufferLayout& layout);

		inline unsigned GetVertexCount() const { return m_VertexCount; }

		virtual void Bind();

		void Serialize(std::ofstream& file);

	private:
		std::vector<float> m_Vertices;
		unsigned m_VertexCount;
	};

	class IndexBuffer : public ArrayBuffer
	{
	public:
		IndexBuffer(unsigned* indices, unsigned count);

		inline const unsigned* GetIndices() const { return &m_Indices.front(); }
		inline const unsigned Size() const { return unsigned(m_Indices.size()); }

		void Bind();

		void Serialize(std::ofstream& file);

	private:
		GLuint m_ID;
		std::vector<unsigned> m_Indices;
	};
}