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
		if (type == GL_ARRAY_BUFFER || type == GL_ELEMENT_ARRAY_BUFFER)
			GL_CALL(glGenBuffers(1, &m_ID));
		if (type == GL_VERTEX_ARRAY)
			GL_CALL(glGenVertexArrays(1, &m_ID));
	}
	VertexArray::VertexArray()
		: ArrayBuffer(GL_VERTEX_ARRAY)
	{
	}
	void VertexArray::Bind()
	{
		GL_CALL(glBindVertexArray(ID()));
	}
	VertexBuffer::VertexBuffer(float* verts, unsigned size)
		: ArrayBuffer(GL_ARRAY_BUFFER)
	{
		Bind();
		GL_CALL(glBufferData(GL_ARRAY_BUFFER, size, verts, GL_STATIC_DRAW));
	}
	void VertexBuffer::AssignLayout(VertexBufferLayout& layout)
	{
		unsigned numAttributes = unsigned(layout.m_Offsets.size());
		for (unsigned i = 0; i < numAttributes; ++i)
		{
			GL_CALL(glVertexAttribPointer(i, layout.m_Offsets[i] / GetSizeFromType(layout.m_Types[i]), 
				GetGLTypeFromEnumType(layout.m_Types[i]), GL_FALSE, layout.m_Offsets[i], NULL));
		}
	}
	void VertexBuffer::Bind()
	{
		GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, ID()));
	}
	void VertexBufferLayout::AddAttribute(unsigned count, BufferLayoutType type)
	{
		m_Types.push_back(type);
		m_Offsets.push_back(GetSizeFromType(type) * count);
	}
	IndexBuffer::IndexBuffer(unsigned* indices, unsigned count)
		: ArrayBuffer(GL_ELEMENT_ARRAY_BUFFER)
	{
		GL_CALL(glGenBuffers(GL_ELEMENT_ARRAY_BUFFER, &m_ID));
		Bind();

		GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned), indices, GL_STATIC_DRAW));
	}
	void IndexBuffer::Bind()
	{
		GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ID));
	}
}