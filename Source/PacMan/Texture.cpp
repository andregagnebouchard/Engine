#include "stdafx.h"
#include "Texture.h"
//=================================================================================================
Texture::Texture(std::string fichierImage) : m_id(0), m_fichierImage(fichierImage)
{
}
//=================================================================================================
Texture::~Texture()
{
}
//=================================================================================================
bool Texture::charger()
{
	SDL_Surface *imageSDL = IMG_Load(m_fichierImage.c_str());

	if (imageSDL == 0)
	{
		std::cout << "Erreur : " << SDL_GetError() << std::endl;
		return false;
	}
}
//=================================================================================================
GLuint Texture::getID() const
{
	return m_id;
}
//=================================================================================================
void Texture::setFichierImage(const std::string &fichierImage)
{
	m_fichierImage = fichierImage;
}
//=================================================================================================