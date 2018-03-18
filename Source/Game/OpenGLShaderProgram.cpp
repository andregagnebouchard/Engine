#include "stdafx.h"
#include "OpenGLShaderProgram.h"
#include <iostream>
#include <string>
#include <fstream>
//=================================================================================================
OpenGLShaderProgram::OpenGLShaderProgram(const std::string &vertexShaderFilepath, const std::string &fragmentShaderFilepath) :
	m_vertexShaderId(0), 
	m_fragmentShaderId(0), 
	m_id(0),
	m_vertexShaderFilepath(vertexShaderFilepath),
	m_fragmentShaderFilepath(fragmentShaderFilepath)
{
}
//=================================================================================================
OpenGLShaderProgram::~OpenGLShaderProgram()
{
    glDeleteShader(m_vertexShaderId);
    glDeleteShader(m_fragmentShaderId);
    glDeleteProgram(m_id);
}
//=================================================================================================
void OpenGLShaderProgram::Init()
{
    // Destruction d'un éventuel ancien Shader
    if(glIsShader(m_vertexShaderId) == GL_TRUE)
        glDeleteShader(m_vertexShaderId);

    if(glIsShader(m_fragmentShaderId) == GL_TRUE)
        glDeleteShader(m_fragmentShaderId);

    if(glIsProgram(m_id) == GL_TRUE)
        glDeleteProgram(m_id);

    // Compilation des shaders
		CompileShaders(m_vertexShaderId, GL_VERTEX_SHADER, m_vertexShaderFilepath);
		CompileShaders(m_fragmentShaderId, GL_FRAGMENT_SHADER, m_fragmentShaderFilepath);

    // Création du programme
		m_id = glCreateProgram();

    // Association des shaders
    glAttachShader(m_id, m_vertexShaderId);
    glAttachShader(m_id, m_fragmentShaderId);

    // Verrouillage des entrées shader
    glBindAttribLocation(m_id, 0, "in_Vertex");
    glBindAttribLocation(m_id, 1, "in_Color");
    glBindAttribLocation(m_id, 2, "in_TexCoord0");

    // Linkage du programme
    glLinkProgram(m_id);

    // Vérification du linkage
    GLint erreurLink(0);
    glGetProgramiv(m_id, GL_LINK_STATUS, &erreurLink);

    // S'il y a eu une erreur
    if(erreurLink != GL_TRUE)
				throw std::exception("Shader initialisation error");
}
//=================================================================================================
void OpenGLShaderProgram::CompileShaders(GLuint &shader, GLenum type, std::string const &fichierSource)
{
    // Création du shader
    shader = glCreateShader(type);

    // Vérification du shader
    if(shader == 0)
				throw std::exception("Shader initialisation error");

    // Flux de lecture
    std::ifstream fichier(fichierSource.c_str());

    // Test d'ouverture
    if(!fichier)
    {
        glDeleteShader(shader);
				throw std::exception("Shader initialisation error");
    }

    // Strings permettant de lire le code source
    std::string ligne;
    std::string codeSource;

    // Lecture
    while(getline(fichier, ligne))
        codeSource += ligne + '\n';


    // Fermeture du fichier
    fichier.close();

    // Récupération de la chaine C du code source
    const GLchar* chaineCodeSource = codeSource.c_str();

    // Envoi du code source au shader
    glShaderSource(shader, 1, &chaineCodeSource, 0);

    // Compilation du shader
    glCompileShader(shader);

    // Vérification de la compilation
    GLint erreurCompilation(0);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &erreurCompilation);

    // S'il y a eu une erreur
    if(erreurCompilation != GL_TRUE)
				throw std::exception("Shader initialisation error");
}
//=================================================================================================
void OpenGLShaderProgram::Bind()
{
	glUseProgram(m_id);
}
//=================================================================================================
void OpenGLShaderProgram::Unbind()
{
	glUseProgram(0);
}
//=================================================================================================