#pragma once
#include "MemoryManager.h"
#include "Engine.h"

class ShadowMap : public GameObject
{
	public:
		ShadowMap() {};
		~ShadowMap() {};
		void init();
		void draw();
		void update() {};
		void logic() {};
	private:

		GLuint framebuffer;
		GLuint textureColorbuffer;
		GLuint rbo;
		GLuint quad_texture;
		struct
		{
			GLuint VAO;
			GLuint pos;
			Shader shader;
		}square;
		void draw_quad();
		void draw_fans(float size,glm::vec2 pos,glm::vec2 center);
		struct
		{
			GLuint VAO;
			GLuint pos;
			Shader shader;
		}triangle;
		Shader gauss_shader;
		void draw_triangle(glm::vec2* v,float color);
};