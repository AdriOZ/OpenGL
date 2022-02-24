#pragma once

#include <string>

class Texture
{
public:
	Texture(const std::string& filePath);
	~Texture();

	void Bind(uint32_t slot = 0) const;
	void Unbind() const;

	inline uint32_t GetWidth() const { return m_Width; }
	inline uint32_t GetHeight() const { return m_Height; }
	inline uint32_t GetBPP() const { return m_BPP; }
private:
	std::string m_FilePath;
	uint8_t* m_LocalBuffer;
	uint32_t m_RendererID;
	int32_t m_Width;
	int32_t m_Height;
	int32_t m_BPP;
};

