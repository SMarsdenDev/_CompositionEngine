#include "../../../stdafx.h"
#include "glad/glad.h"
#include "ArrayBuffer.h"

namespace _CompositionEngine
{
	unsigned GetSizeFromType(BufferLayoutType type)
	{
		if (type == BufferLayoutType::FLOAT)
			return sizeof(float);
		else if (type == BufferLayoutType::INT)
			return sizeof(int);
		else if (type == BufferLayoutType::CHAR)
			return sizeof(char);
		else if (type == BufferLayoutType::DOUBLE)
			return sizeof(double);
		return 0;
	}

	GLenum GetGLTypeFromEnumType(BufferLayoutType type)
	{
		if (type == BufferLayoutType::FLOAT)
			return GL_FLOAT;
		else if (type == BufferLayoutType::INT)
			return GL_INT;
		else if (type == BufferLayoutType::CHAR)
			return GL_BYTE;
		else if (type == BufferLayoutType::DOUBLE)
			return GL_DOUBLE;
		return -1;
	}

	ArrayBuffer::ArrayBuffer(GLenum type)
	{
		if (type == GL_ARRAY_BUFFER)
		{
			GL_CALL(glGenBuffers(1, &m_ID));
		}
		else if (type == GL_VERTEX_ARRAY)
		{
			GL_CALL(glGenVertexArrays(1, &m_ID));
		}
	}
	VertexArray::VertexArray()
		: ArrayBuffer(GL_VERTEX_ARRAY)
	{
		Bind();
	}
	void VertexArray::Bind()
	{
		GL_CALL(glBindVertexArray(ID()));
	}
	VertexBuffer::VertexBuffer(float* verts, unsigned size)
		: ArrayBuffer(GL_ARRAY_BUFFER)
	{
		Bind();
		for (unsigned i = 0; i < size / sizeof(unsigned); ++i)
			m_Vertices.push_back(verts[i]);
		GL_CALL(glBufferData(GL_ARRAY_BUFFER, size, verts, GL_STATIC_DRAW));
	}
	void VertexBuffer::AssignLayout(VertexBufferLayout& layout)
	{
		unsigned numAttributes = unsigned(layout.m_Offsets.size());
		for (unsigned i = 0; i < numAttributes; ++i)
		{
			GLint size = layout.m_Offsets[i] / GetSizeFromType(layout.m_Types[i]);
			GL_CALL(glVertexAttribPointer(i, layout.m_AttribCounts[i], GetGLTypeFromEnumType(layout.m_Types[i]), GL_FALSE, 
				layout.m_VertexSize, (void*)layout.m_Offsets[i]));
			GL_CALL(glEnableVertexAttribArray(i));
		}
	}
	void VertexBuffer::Bind()
	{
		GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, ID()));
	}
	void VertexBufferLayout::AddAttribute(unsigned count, BufferLayoutType type)
	{
		m_Types.push_back(type);
		m_Offsets.push_back(m_VertexSize);
		m_AttribCounts.push_back(count);
		m_VertexSize += (GetSizeFromType(type) * count);
	}
	IndexBuffer::IndexBuffer(unsigned* indices, unsigned size)
		: ArrayBuffer(GL_ELEMENT_ARRAY_BUFFER)
	{
		GL_CALL(glGenBuffers(1, &m_ID));
		LOG_INFO(m_ID);
		Bind();
		for (unsigned i = 0; i < size / sizeof(unsigned); ++i)
			m_Indices.push_back(indices[i]);
		GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW));
	}
	void IndexBuffer::Bind()
	{
		GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID));
	}
}