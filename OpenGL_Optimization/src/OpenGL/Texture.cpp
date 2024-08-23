#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

enum FileFormats {
	JPG,
	PNG,
};

enum GLTExtureDataPlace {
	INTERNAL,
	NORMAL,
};

struct TextureFile {
	FileFormats format;

	TextureFile(const std::string& path) {
		std::string formatString;
		bool writeFormat = false;
		for (unsigned int i = 0; i < path.size(); i++) {
			if (writeFormat) formatString += path[i];
			if (path[i] == '.') {
				writeFormat = true;
			}
		}
		SetFormatEnum(formatString);
	}

	void SetFormatEnum(const std::string& formatString) {
		if (formatString == "png") format = FileFormats::PNG;
		if (formatString == "jpg") format = FileFormats::JPG;
	}

	unsigned int GetGLType(GLTExtureDataPlace dataPlace) const {
		switch (format)
		{
		case JPG:
			return (GLTExtureDataPlace::INTERNAL ? GL_RGB8 : GL_RGB);
		case PNG:
			return (GLTExtureDataPlace::INTERNAL ? GL_RGBA8 : GL_RGBA);
		default:
			break;
		}
	}
};


Texture::Texture(const std::string& path)
	:m_FilePath(path), m_LocalBuffer(nullptr), 
	m_Width(0), m_Height(0), m_BPP(0)
{
	TextureFile fileFormat(path);

	glGenTextures(1, &m_RendererID);
	glBindTexture(GL_TEXTURE_2D, m_RendererID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	stbi_set_flip_vertically_on_load(1);
	unsigned char* m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 0);
	if (m_LocalBuffer)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, fileFormat.GetGLType(GLTExtureDataPlace::INTERNAL), m_Width, m_Height, 0, 
										fileFormat.GetGLType(GLTExtureDataPlace::NORMAL), GL_UNSIGNED_BYTE, m_LocalBuffer);

		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(m_LocalBuffer);
	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_RendererID);
}

void Texture::Bind(unsigned int slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, m_RendererID);
}

void Texture::Unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
