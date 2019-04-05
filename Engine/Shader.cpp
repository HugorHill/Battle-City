#pragma once

#include "Shader.h"
#include "Engine.h"
#include "Defines.h"

Shader::Shader(std::string file)
{
	shader_program = engine->mm.loadShader(file);
}

void Shader::start()
{
	glUseProgram(shader_program);
}

void Shader::stop()
{
	glUseProgram(0);
}

void Shader::load_f(std::string name, float val)
{
	GLuint loc = glGetUniformLocation(shader_program, name.data());
	glUniform1f(loc, val);
}

void Shader::load_i(std::string name, int val)
{
	GLuint loc = glGetUniformLocation(shader_program, name.data());
	glUniform1i(loc, val);
}

void Shader::load_vec(std::string name, glm::vec2 val)
{
	GLuint loc = glGetUniformLocation(shader_program, name.data());
	glUniform2f(loc, val.x,val.y);
}

void Shader::load_vec(std::string name, glm::vec3 val)
{
	GLuint loc = glGetUniformLocation(shader_program, name.data());
	glUniform3f(loc, val.x, val.y, val.z);
}

void Shader::load_mat(std::string name, glm::mat2 val)
{
	GLuint loc = glGetUniformLocation(shader_program, name.data());
	glUniformMatrix2fv(loc, 1, GL_FALSE, glm::value_ptr(val));
}

void Shader::load_mat(std::string name, glm::mat3 val)
{
	GLuint loc = glGetUniformLocation(shader_program, name.data());
	glUniformMatrix3fv(loc, 1, GL_FALSE, glm::value_ptr(val));
}

void Shader::load_mat(std::string name, glm::mat4 val)
{
	GLuint loc = glGetUniformLocation(shader_program, name.data());
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(val));
}