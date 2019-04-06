#pragma once
#include "RenderManager.h"

class RP_DrawText : public RenderProcessObject
{
	public:
		struct{
			std::string text;
			glm::vec2 pos;
			bool atCenter;
			glm::vec3 color;
			float scale;
			GLuint bgTexture;
		}options;

	public:
		RP_DrawText() {};
		~RP_DrawText() {};
		void init();
		void render(Layer* layer);

	private:
		struct{
			GLuint VAO;
			GLuint VBO;
			Shader glyph_shader;
			glm::mat4 projection;
		}glyph;
		struct Character{
			GLuint     TextureID;
			glm::ivec2 Size;
			glm::ivec2 Bearing;
			GLuint     Advance;
		};
		std::map<GLchar, Character> Characters;
};