#pragma once
#include "RenderManager.h"
#include "Map.h"

class RP_DrawShadows : public RenderProcessObject
{
	public:
		struct
		{
			glm::vec2 light_pos;
			Map* map;
			Layer* current_layer;
		}options;
	public:
		RP_DrawShadows() {};
		~RP_DrawShadows() {};
		void init();
		void run();
	private:
		void draw_triangle(glm::vec2* v, float color,GLuint texture = 0,GLuint brightness_map = 0);
		void draw_fans(float size, glm::vec2 pos, glm::vec2 center);
		Layer shadow_map_layer;
		Layer result_layer;
		std::vector<glm::vec2> positions;
		struct
		{
			GLuint VAO;
			GLuint pos;
			Shader shader;
		}triangle;
};