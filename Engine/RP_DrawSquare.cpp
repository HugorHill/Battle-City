#include "Engine.h"
#include "RP_DrawSquare.h"
#include "RenderManager.h"
#include <glm\glm.hpp>

void RP_DrawSquare::init()
{
	//init square
	square.VAO = engine->mm.getVAO();
	square.pos = engine->mm.getVBO();
	square.shader = Shader("static");

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
};

void RP_DrawSquare::render(Layer* layer)
{
	layer->Use();
	square.shader.start();
	glm::mat4 transformation = glm::mat4(1);
	glBindVertexArray(square.VAO);
	glEnableVertexAttribArray(0);
	glActiveTexture(GL_TEXTURE0);
	for (auto &opt : options)
	{
		opt.pos /= WINDOW_SIZE_UNITS / 2.0;
		transformation = glm::mat4(1);
		transformation = glm::translate(transformation, glm::vec3(opt.pos, 0));
		transformation = glm::rotate(transformation, glm::radians(opt.angelRotate), glm::vec3(0, 0, 1));
		transformation = glm::scale(transformation, glm::vec3(opt.size / WINDOW_SIZE_UNITS));
		square.shader.load_mat("transf", transformation);
		glBindTexture(GL_TEXTURE_2D, opt.texture);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}
	glDisableVertexAttribArray(0);
	square.shader.stop();
	layer->Reset();
	options.clear();
};