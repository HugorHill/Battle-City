#pragma once

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <map>
#include <string>
#include <vector>
#include <set>


//����������� ����� ��� ������� ��������
class Engine;
class GameObject
{
	friend class Engine;
	public:
		virtual void init() = 0;
		virtual void draw() = 0;
		virtual void logic() = 0;
		virtual void update() = 0;
	protected:
		static Engine* engine;
};

class MemoryManager
{
	public:
		MemoryManager() {};
		~MemoryManager() {};
		
		GLuint getVAO();
		void delVAO(GLuint vao);
		
		GLuint getVBO();
		void delVBO(GLuint vbo);

		GLuint loadShader(std::string file);
		void delShader(GLuint shader);

		GLuint loadTexture(std::string file,bool repeat = false);
		void delTexture(GLuint texture);

private:
	std::set<GLuint> VAOS;
	std::set<GLuint> VBOS;
	std::set<GLuint> Shaders;
	std::set<GLuint> Textures;
};