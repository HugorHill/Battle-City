#include "RenderManager.h"
#include "Defines.h"
#include "Engine.h"
#include <stdio.h>
#include <string>
#include <ft2build.h>
#include <freetype\freetype.h>

namespace rendering
{
	namespace text
	{
		struct
		{
			GLuint VAO;
			GLuint VBO;
			Shader glyph_shader;
			glm::mat4 projection;
		}glyph;

		struct Character
		{
			GLuint     TextureID;
			glm::ivec2 Size;     
			glm::ivec2 Bearing;
			GLuint     Advance;
		};

		std::map<GLchar, Character> Characters;

		static void init(void* p)
		{

			//инициализация библиотеки
			FT_Library ft;
			if (FT_Init_FreeType(&ft))
				std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;

			FT_Face face;
			if (FT_New_Face(ft, "Retro Gaming.ttf", 0, &face))
				std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;

			FT_Set_Pixel_Sizes(face, 0, 48);

			glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction

			for (GLubyte c = 0; c < 128; c++)
			{
				// Load character glyph 
				if (FT_Load_Char(face, c, FT_LOAD_RENDER))
				{
					std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
					continue;
				}
				// Generate texture
				GLuint texture;
				glGenTextures(1, &texture);
				glBindTexture(GL_TEXTURE_2D, texture);
				glTexImage2D(
					GL_TEXTURE_2D,
					0,
					GL_RED,
					face->glyph->bitmap.width,
					face->glyph->bitmap.rows,
					0,
					GL_RED,
					GL_UNSIGNED_BYTE,
					face->glyph->bitmap.buffer
				);
				// Set texture options
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				// Now store character for later use
				Character character =
				{
					texture,
					glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
					glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
					face->glyph->advance.x
				};
				Characters.insert(std::pair<GLchar, Character>(c, character));
			}

			glyph.glyph_shader = Shader("glyph", p);
			glyph.projection = glm::ortho(-WINDOW_SIZE_UNITS / 2, WINDOW_SIZE_UNITS / 2, -WINDOW_SIZE_UNITS / 2, WINDOW_SIZE_UNITS / 2);

			glGenVertexArrays(1, &glyph.VAO);
			glGenBuffers(1, &glyph.VBO);
			glBindVertexArray(glyph.VAO);
			glBindBuffer(GL_ARRAY_BUFFER, glyph.VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);

			FT_Done_Face(face);
			FT_Done_FreeType(ft);
		}

		static void drawText(std::string text, glm::vec2 pos, bool atCenter, glm::vec3 color, float scale,GLuint bgTexture)
		{
			glyph.glyph_shader.start();
			glyph.glyph_shader.load_i("text", 0);
			glyph.glyph_shader.load_i("bgTexture", 1);
			glyph.glyph_shader.load_mat("projection", glyph.projection);
			glyph.glyph_shader.load_vec("textColor", color);
			glyph.glyph_shader.load_f("useBgTexture", 0);
			GLfloat len_text = 0;
			if (bgTexture)
			{
				glyph.glyph_shader.load_f("useBgTexture", 1);
				glActiveTexture(GL_TEXTURE1);
				glBindTexture(GL_TEXTURE_2D, bgTexture);
			}
			glActiveTexture(GL_TEXTURE0);
			glBindVertexArray(glyph.VAO);

			std::string::const_iterator c;
			for (c = text.begin(); c != text.end() && atCenter; c++)
			{
				Character ch = Characters[*c];
				len_text += (ch.Advance >> 6) * scale / 2.0;
			}
			pos.x -= len_text;

			
			for (c = text.begin(); c != text.end(); c++)
			{
				Character ch = Characters[*c];

				GLfloat xpos = pos.x + ch.Bearing.x * scale;
				GLfloat ypos = pos.y - (ch.Size.y - ch.Bearing.y) * scale;

				GLfloat w = ch.Size.x * scale;
				GLfloat h = ch.Size.y * scale;

				GLfloat vertices[6][4] = {
					{ xpos,     ypos + h,   0.0, 0.0 },
					{ xpos,     ypos,       0.0, 1.0 },
					{ xpos + w, ypos,       1.0, 1.0 },

					{ xpos,     ypos + h,   0.0, 0.0 },
					{ xpos + w, ypos,       1.0, 1.0 },
					{ xpos + w, ypos + h,   1.0, 0.0 }
				};
				glBindTexture(GL_TEXTURE_2D, ch.TextureID);

				glBindBuffer(GL_ARRAY_BUFFER, glyph.VBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
				glBindBuffer(GL_ARRAY_BUFFER, 0);

				glDrawArrays(GL_TRIANGLES, 0, 6);
				pos.x += (ch.Advance >> 6) * scale;
			}
			glBindVertexArray(0);
			glBindTexture(GL_TEXTURE_2D, 0);
		}

	}
}

void RenderManager::init(int w, int h, Engine* ptr)
{
	engine = ptr;
	std::string title = "";
	if (!glfwInit())
	{
		fprintf(stderr, "Ошибка при инициализации GLFW\n");
		return;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	engine->window = glfwCreateWindow(w, h, title.c_str(), NULL, NULL);
	if (engine->window == NULL)
	{
		fprintf(stderr, "Невозможно открыть окно GLFW\n");
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(engine->window);
	glfwSwapInterval(0);


	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		fprintf(stderr, "Невозможно инициализировать GLEW\n");
		return;
	}

	//glfwSetInputMode(engine->window, GLFW_STICKY_KEYS, GL_TRUE);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	rendering::text::init(engine);

	//init structure square
	square.VAO = engine->mm.getVAO();
	square.pos = engine->mm.getVBO();
	square.shader = Shader("static", engine);

	glBindVertexArray(square.pos);
	static const GLfloat pos[] =
	{
		-1,-1,0,
		1,-1,0,
		-1,1,0,
		-1,1,0,
		1,-1,0,
		1,1,0
	};
	glBindBuffer(GL_ARRAY_BUFFER, square.pos);
	glBufferData(GL_ARRAY_BUFFER, sizeof(pos), pos, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glDisableVertexAttribArray(0);

}

void RenderManager::updateScreen()
{
	glfwSwapBuffers(engine->window);
}

static glm::vec2* hero_pos = NULL;
//функция рисования квадратика: размеры и позиция указываются в юнитах, а угол в градусах
void RenderManager::drawSquare(GLuint texture, GLuint size, glm::vec2 pos, float angelRotate)
{
	if(!hero_pos) hero_pos = _ptr(engine->vm.getVar("hero position"), glm::vec2);

	square.shader.start();

	glm::vec2 light_pos = *hero_pos;
	light_pos /= WINDOW_SIZE_UNITS / 2.0;
	square.shader.load_vec("light_pos", light_pos);
	glm::mat4 transformation = glm::mat4(1);
	pos /= WINDOW_SIZE_UNITS/2.0;
	transformation = glm::translate(transformation, glm::vec3(pos, 0));
	transformation = glm::rotate(transformation, glm::radians(angelRotate), glm::vec3(0, 0, 1));
	transformation = glm::scale(transformation, glm::vec3((float)size / WINDOW_SIZE_UNITS));

	square.shader.load_mat("transf", transformation); //тут загружаеся преобразование
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glBindVertexArray(square.VAO);
	glEnableVertexAttribArray(0);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisableVertexAttribArray(0);
	square.shader.stop();
}

//поизиция указывается в юнитах
void RenderManager::drawText(std::string text, glm::vec2 pos, bool atCenter, glm::vec3 color, float scale, GLuint bgTexture)
{
	rendering::text::drawText(text, pos, atCenter, color, scale, bgTexture);
}