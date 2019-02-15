
#pragma once
#include "MemoryManager.h"
#include "Shader.h"


#define WINDOW_SIZE_UNITS 512

class Square
{
	public:
		Square() {};
		~Square() {};
		Square(float unit_size, void* engine);
		void draw(GLuint texture);

	private:
		float square_size;
		GLuint VAO;
		GLuint Positions;
		GLuint Texture_coords;
		Shader Shader_prog;
};


class Terrain : public GameObject
{
	public:
		Terrain(void* p) { init(p); }
		void init(void* p);
		void draw();
		void logic() {};
		void update() {};
	private:
		GLuint texture;
		Square sqr;
};

