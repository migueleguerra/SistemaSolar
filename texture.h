#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <OpenGL/gl3.h>
#include <OpenGL/gl3ext.h>

class Texture
{
public:
	Texture(const std::string& fileName);

	void Bind();

	virtual ~Texture();
protected:
private:
	Texture(const Texture& texture) {}
	void operator=(const Texture& texture) {}

	GLuint m_texture;
};

#endif
