#pragma once
#include "RenderManager.h"

class RP_DrawSquare : public RenderProcessObject
{
	public:
		struct{
			GLuint texture;
			GLuint size;
			glm::vec2 pos;
			float angelRotate;
		}options;
	public:
		RP_DrawSquare() {};
		~RP_DrawSquare() {};
		void init();
		void run();
	private:
		struct{
			GLuint VAO;
			GLuint pos;
			Shader shader;
		}square;
};