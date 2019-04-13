#pragma once
#include "RenderManager.h"

class RP_DrawSquare : public RenderProcessObject
{
	public:
		struct Options{
			GLuint texture;
			GLuint size;
			glm::vec2 pos;
			float angelRotate;
			float time;
			int countFrame;
		};
		std::vector<Options> options;
	public:
		RP_DrawSquare() {};
		~RP_DrawSquare() {};
		void init();
		void render(Layer* layer);
	private:
		struct{
			GLuint VAO;
			GLuint pos;
			Shader shader;
		}square;
};