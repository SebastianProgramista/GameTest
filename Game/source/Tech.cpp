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
#include "Tech.h"

static const char* pVSName = "VS";
static const char* pFSName = "FS";

//-----------------------------------------------
// Name:
// Desc: 
//
const char* ShaderType2ShaderName(GLuint Type)
{
    switch (Type) 
	{
        case GL_VERTEX_SHADER:
            return pVSName;
        case GL_FRAGMENT_SHADER:
            return pFSName;
        default:
            assert(0);
    }

    return NULL;
}

//-----------------------------------------------
// Name:
// Desc: 
//
Tech::Tech()
{
    m_shaderProg = 0;
	
}

//-----------------------------------------------
// Name:
// Desc: 
//
char *Tech::textFileRead(char *fn) 
{
	FILE *fp;
	char *content = NULL;

	int count=0;

	if (fn != NULL) {
		fopen_s(&fp,fn,"rt");

		if (fp != NULL) {
      
      fseek(fp, 0, SEEK_END);
      count = ftell(fp);
      rewind(fp);

			if (count > 0) {
				content = new char[count+1];
				count = fread(content,sizeof(char),count,fp);
				content[count] = '\0';
			}
			fclose(fp);
		}
	}
	return content;
}
//-----------------------------------------------
// Name:
// Desc:
//
Tech::~Tech()
{

    if (m_shaderProg != 0)
    {
        glDeleteProgram(m_shaderProg);
        m_shaderProg = 0;
    }
}

//-----------------------------------------------
// Name:
// Desc:
//
bool Tech::Init()
{
    m_shaderProg = glCreateProgram();

    if (m_shaderProg == 0) 
	{
        return false;
    }

    return true;
}

//-----------------------------------------------
// Name:
// Desc:
//
bool Tech::AddShader(GLenum ShaderType, char* pShaderText)
{
    GLuint ShaderObj = glCreateShader(ShaderType);

    if (ShaderObj == 0) 
	{
        return false;
    }

	const char *pShader = NULL;

	pShader = textFileRead(pShaderText);

    const GLchar* p[1];
	GLint Lengths[1];


    p[0]       = pShader;
    Lengths[0] = strlen(pShader);

    glShaderSource(ShaderObj, 1, p, Lengths);

    glCompileShader(ShaderObj);

    GLint success;
    glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &success);

    if (!success)
	{
        GLchar InfoLog[1024];
        glGetShaderInfoLog(ShaderObj, 1024, NULL, InfoLog);
        return false;
    }

    glAttachShader(m_shaderProg, ShaderObj);

	if(pShader)
	{
		SAFE_DELETE( pShader);
	}

    return true;
}

//-----------------------------------------------
// Name:
// Desc: 
//
bool Tech::Finalize()
{
    GLint Success = 0;
    GLchar ErrorLog[1024] = { 0 };

    glLinkProgram(m_shaderProg);
	

    glGetProgramiv(m_shaderProg, GL_LINK_STATUS, &Success);
	if (Success == 0) {
		glGetProgramInfoLog(m_shaderProg, sizeof(ErrorLog), NULL, ErrorLog);
        return false;
	}

    glValidateProgram(m_shaderProg);
    glGetProgramiv(m_shaderProg, GL_VALIDATE_STATUS, &Success);
    if (!Success) {
        glGetProgramInfoLog(m_shaderProg, sizeof(ErrorLog), NULL, ErrorLog);
        return false;
    }

	printProgramInfoLog(m_shaderProg);

    return true;
}

//-----------------------------------------------
// Name:
// Desc: 
//
void Tech::Enable()
{
    glUseProgram(m_shaderProg);
	glBindFragDataLocation(m_shaderProg, 0, "FragColor");
}

//-----------------------------------------------
// Name:
// Desc: 
//
GLuint Tech::getShaderProg()
{
	return m_shaderProg;
}

//-----------------------------------------------
// Name:
// Desc: 
//
void Tech::Disable()
{
    glUseProgram(0);
}

//-----------------------------------------------
// Name:
// Desc: 
//
GLint Tech::GetUniformLocation(const char* pUniformName)
{
    GLint Location = glGetUniformLocation(m_shaderProg, pUniformName);

    if (Location == INVALID_UNIFORM_LOCATION)
    {
		
    }

    return Location;
}

//-----------------------------------------------
// Name:
// Desc: 
//
void Tech::printProgramInfoLog(GLuint shader)
{
	int infoLogLen   = 0;
	int charsWritten = 0;
	char *infoLog;
                      
	glGetProgramiv(shader, GL_INFO_LOG_LENGTH, &infoLogLen);
 
	if (infoLogLen > 0)
	{
		infoLog = new char[infoLogLen];
		glGetProgramInfoLog(shader, infoLogLen, &charsWritten, infoLog);
		delete [] infoLog;
	}
}