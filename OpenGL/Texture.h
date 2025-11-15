#ifndef TEXTURE_H
#define	TEXTURE_H

#include "StandardIncludes.h"
class Texture
{
public:
	// Constructors / Destructors Texture();
	Texture();
	virtual ~Texture() {}
	
	// Accessors
	GLuint GetTexture() { return m_texture; }

	// Methods
	void LoadTexture(string _fileName);
	void LoadCubeMap(vector<string> _faces);
	void LoadTexture(string _fileName, GLint _wrappermethod);
	void Cleanup();

private:
	// Members
	int m_width;
	int m_height; int m_channels;
	GLuint m_texture;

	//Methods
	bool EndsWith(const std::string& str, const std::string& suffix);
};
#endif