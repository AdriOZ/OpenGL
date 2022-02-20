#pragma once

#include <GL/glew.h>
#include <vector>

struct VertexBufferElement
{
	uint32_t type;
	uint32_t count;
	uint32_t normalized;

	static uint32_t GetSizeOfType(uint32_t type)
	{
		switch (type)
		{
		case GL_FLOAT:
			return sizeof(float);
		case GL_UNSIGNED_INT:
			return sizeof(uint32_t);
		case GL_UNSIGNED_BYTE:
			return sizeof(uint8_t);
		}
		return 0;
	}
};

class VertexBufferLayout
{
public:
	VertexBufferLayout() : m_Stride(0)
	{
	}

	template<typename T>
	void Push(uint32_t count)
	{
	}

	template <>
	void Push<float>(uint32_t count)
	{
		m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
	}

	template <>
	void Push<uint32_t>(uint32_t count)
	{
		m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
	}

	template <>
	void Push<uint8_t>(uint32_t count)
	{
		m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
	}

	inline uint32_t GetStride() const
	{
		return m_Stride;
	}

	inline const std::vector<VertexBufferElement>& GetElements() const
	{
		return m_Elements;
	}

private:
	std::vector<VertexBufferElement> m_Elements;
	uint32_t m_Stride;
};