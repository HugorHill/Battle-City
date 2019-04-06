#include "RenderManager.h"
#include "RP_DrawText.h"
#include <ft2build.h>
#include <freetype\freetype.h>
#include <iostream>

void RP_DrawText::init()
{
	FT_Library ft;
	if (FT_Init_FreeType(&ft))
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;

	FT_Face face;
	if (FT_New_Face(ft, "Retro Gaming.ttf", 0, &face))
		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;

	FT_Set_Pixel_Sizes(face, 0, 48);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	for (GLubyte c = 0; c < 128; c++)
	{
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
			continue;
		}
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
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		Character character =
		{
			texture,
			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			face->glyph->advance.x
		};
		Characters.insert(std::pair<GLchar, Character>(c, character));
	}

	glyph.glyph_shader = Shader("glyph");
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
};

void RP_DrawText::render(Layer* layer)
{
	layer->Use();
	glyph.glyph_shader.start();
	glyph.glyph_shader.load_i("text", 0);
	glyph.glyph_shader.load_i("bgTexture", 1);
	glyph.glyph_shader.load_mat("projection", glyph.projection);
	glyph.glyph_shader.load_vec("textColor", options.color);
	glyph.glyph_shader.load_f("useBgTexture", 0);
	GLfloat len_text = 0;
	if (options.bgTexture)
	{
		glyph.glyph_shader.load_f("useBgTexture", 1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, options.bgTexture);
	}
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(glyph.VAO);

	std::string::const_iterator c;
	for (c = options.text.begin(); c != options.text.end() && options.atCenter; c++)
	{
		Character ch = Characters[*c];
		len_text += (ch.Advance >> 6) * options.scale / 2.0;
	}
	options.pos.x -= len_text;


	for (c = options.text.begin(); c != options.text.end(); c++)
	{
		Character ch = Characters[*c];

		GLfloat xpos = options.pos.x + ch.Bearing.x * options.scale;
		GLfloat ypos = options.pos.y - (ch.Size.y - ch.Bearing.y) * options.scale;

		GLfloat w = ch.Size.x * options.scale;
		GLfloat h = ch.Size.y * options.scale;

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
		options.pos.x += (ch.Advance >> 6) * options.scale;
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	layer->Reset();
};