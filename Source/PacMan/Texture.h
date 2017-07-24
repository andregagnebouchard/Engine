#ifndef DEF_TEXTURE
#define DEF_TEXTURE
// Include
#ifdef _WIN32
#include <GL/glew.h>
#else
#define GL3_PROTOTYPES 1
#include <GL3/gl3.h>
#endif

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
class Texture
{
public:

	Texture(std::string fichierImage);
	~Texture();
	bool charger();
	GLuint getID() const;
	void setFichierImage(const std::string &fichierImage);


private:

	GLuint m_id;
	std::string m_fichierImage;
};

#endif