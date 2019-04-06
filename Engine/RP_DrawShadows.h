#pragma once
#include "RenderManager.h"
#include "Map.h"

class RP_DrawShadows : public RenderProcessObject
{
	public:
		struct Options
		{
			glm::vec2 light_pos;
			glm::vec2 wall;
		};
		std::vector<Options> options;
	public:
		RP_DrawShadows() {};
		~RP_DrawShadows() {};
		void init();
		void render(Layer* layer);
	private:
		void draw_triangle(glm::vec2* v, float color,GLuint texture = 0,GLuint brightness_map = 0);
		void draw_fans(float size, glm::vec2 pos, glm::vec2 center);
		void draw_raw_square();
		Layer shadow_map_layer;
		Layer result_layer;
		Shader multiply_shader;
		Shader blur_shader;
		Shader light_shader;
		GLuint lightmap_texture;
		struct
		{
			GLuint VAO;
			GLuint pos;
			Shader shader;
		}triangle;
		struct
		{
			GLuint VAO;
			GLuint pos;
		}square;
};