#pragma once
#include "stdafx.h"
#include "IShaderProgram.h"
#include <GL/glew.h>
//=================================================================================================
class OpenGLShaderProgram : public IShaderProgram
{
  public:
		OpenGLShaderProgram(const std::string &vertexShaderFilepath, const std::string &fragmentShaderFilepath);
    ~OpenGLShaderProgram();

		// IShader
		virtual void Bind() override;
		virtual void Unbind() override;

		// IMPL
		void Init();

  private:
		void CompileShaders(GLuint &shader, GLenum type, std::string const &fichierSource);

    GLuint m_vertexShaderId;
    GLuint m_fragmentShaderId;
    GLuint m_id;
    std::string m_vertexShaderFilepath;
    std::string m_fragmentShaderFilepath;
};
//=================================================================================================