#include "MemoryManager.h"
#include <soil.h>
#include <fstream>
#include <sstream>
#include <iostream>



GLuint MemoryManager::getVAO()
{
	GLuint vao;
	glGenVertexArrays(1, &vao);
	VAOS.insert(vao);
	return vao;
}

void MemoryManager::delVAO(GLuint vao)
{
	VAOS.erase(vao);
}

GLuint MemoryManager::getVBO()
{
	GLuint vbo;
	glGenBuffers(1, &vbo);
	VBOS.insert(vbo);
	return vbo;
}

void MemoryManager::delVBO(GLuint vbo)
{
	VBOS.erase(vbo);
}

static GLuint loadShaderFromFile(std::string file_path, GLenum type_shader)
{
	switch (type_shader)
	{
		case GL_VERTEX_SHADER:						file_path += "_VS.glsl"; break;
		case GL_FRAGMENT_SHADER:					file_path += "_FS.glsl"; break;
		case GL_TESS_CONTROL_SHADER:				file_path += "_TC.glsl"; break;
		case GL_TESS_EVALUATION_SHADER:				file_path += "_TE.glsl"; break;
		case GL_GEOMETRY_SHADER:					file_path += "_GS.glsl"; break;
		case GL_COMPUTE_SHADER:						file_path += "_CS.glsl"; break;
		default: return 0;
	}

	std::string shaderCode;
	std::ifstream shaderStream(file_path, std::ios::in);
	if (shaderStream.is_open())
	{
		std::stringstream sstr;
		sstr << shaderStream.rdbuf();
		shaderCode = sstr.str();
		shaderStream.close();
	}
	else
	{
		return -1;
	}

	GLuint shader_ID = glCreateShader(type_shader);


	// Compile Vertex Shader
	printf("Compiling shader : %s\n", file_path.c_str());
	char const * sourcePointer = shaderCode.c_str();

	glShaderSource(shader_ID, 1, &sourcePointer, NULL);
	glCompileShader(shader_ID);

	// Check Vertex Shader
	GLint Result = GL_FALSE;
	int InfoLogLength;

	glGetShaderiv(shader_ID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(shader_ID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0)
	{
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(shader_ID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
		return 0;
	}

	return shader_ID;
}

GLuint MemoryManager::loadShader(std::string file_path)
{
	std::vector<GLuint> shaderID;
	GLenum shaderType[] = { GL_VERTEX_SHADER, GL_FRAGMENT_SHADER, GL_TESS_CONTROL_SHADER, GL_TESS_EVALUATION_SHADER, GL_GEOMETRY_SHADER, GL_COMPUTE_SHADER };
	for (int i = 0; i < 6; i++)
	{
		GLuint result = loadShaderFromFile(file_path, shaderType[i]);
		if (result == -1) { continue; }
		if (result == 0) { return 0; };
		shaderID.push_back(result);
	}

	if (shaderID.size() == 0) return 0;

	// Link the program
	printf("Linking program\n");
	GLuint ProgramID = glCreateProgram();
	for (int i = 0; i < shaderID.size(); i++)
		glAttachShader(ProgramID, shaderID[i]);
	glLinkProgram(ProgramID);

	// Check the program
	GLint Result = 0;
	GLint InfoLogLength;
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0)
	{
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
		return 0;
	}


	for (int i = 0; i < shaderID.size(); i++)
	{
		glDetachShader(ProgramID, shaderID[i]);
		glDeleteShader(shaderID[i]);
	}

	Shaders.insert(ProgramID);
	return ProgramID;
};

void MemoryManager::delShader(GLuint shader)
{
	if (Shaders.count(shader))
	{
		Shaders.erase(shader);
		glDeleteProgram(shader);
	}
}


GLuint MemoryManager::loadTexture(std::string file,bool repeat)
{
	GLenum image_format = GL_RGBA;
	GLint internal_format = GL_RGBA;
	GLint level = 0;
	GLint border = 0;
	GLuint gl_texID;
	int* width = new int;
	int* height = new int;
	*width = 0;
	*height = 0;
	glGenTextures(1, &gl_texID);
	Textures.insert(gl_texID);
	glBindTexture(GL_TEXTURE_2D, gl_texID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT*repeat + GL_CLAMP_TO_EDGE*(1 - repeat));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT*repeat + GL_CLAMP_TO_EDGE*(1 - repeat));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -0.5);
	unsigned char* image = SOIL_load_image(file.c_str(), width, height, 0, SOIL_LOAD_RGBA);
	glTexImage2D(GL_TEXTURE_2D, level, internal_format, *width, *height, border, image_format, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
	delete width;
	delete height;
	return gl_texID;
}

void MemoryManager::delTexture(GLuint texture)
{
	glDeleteTextures(1, &texture);
	Textures.erase(texture);
}

