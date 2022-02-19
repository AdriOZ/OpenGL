#pragma once

#include <iostream>

class IndexBuffer
{
public:
	IndexBuffer(const uint32_t* data, uint32_t count);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

	inline int32_t GetCount() const;
private:
	uint32_t m_RendererID;
	uint32_t m_Count;
};