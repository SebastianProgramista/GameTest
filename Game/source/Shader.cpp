//+++++++++++++++++++++++++++++++++++++++++++++++
// Projekt : Gra 2D
// Tech    : 
//           OpenGL 3.3/ GLSL 330, 
//           Glew 1.6, 
//           GLFW 3 
//           GLM 0.9.1.1
// http://www.sworek.acsoftware.pl   
//
//+++++++++++++++++++++++++++++++++++++++++++++++
#include "Shader.h"
//-----------------------------------------------
// Name:
// Desc:
//
ShaderTech::ShaderTech()
{
}
//-----------------------------------------------
// Name:
// Desc:
//
bool ShaderTech::Init()
{
    if (!Tech::Init())
	{
        return false;
    }

    if (!AddShader(GL_VERTEX_SHADER, "shader/shader.vert")) 
	{
        return false;
    }

    if (!AddShader(GL_FRAGMENT_SHADER, "shader/shader.frag"))
	{
        return false;
    }

    if (!Finalize()) 
	{
        return false;
    }

	m_WVPLocation       = GetUniformLocation("gWVP");
    m_samplerLocation	= GetUniformLocation("gSampler");	

	return true;
}

//-----------------------------------------------
// Name:
// Desc:
//
void ShaderTech::SetTextureUnit(unsigned int uiTextureUnit)
{
	glActiveTexture(GL_TEXTURE0+uiTextureUnit);
    glUniform1i(m_samplerLocation, uiTextureUnit);
}

//-----------------------------------------------
// Name:
// Desc:
//
void ShaderTech::set(glm::mat4 &m4World)
{
	glUniformMatrix4fv(m_WVPLocation, 1, GL_FALSE, glm::value_ptr(m4World));    
}