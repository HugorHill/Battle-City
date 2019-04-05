#include "Engine.h"
#include "RP_DrawSquare.h"
#include <glm\glm.hpp>

void RP_DrawSquare::init()
{
	//init square
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
};

void RP_DrawSquare::run()
{
	square.shader.start();

	glm::mat4 transformation = glm::mat4(1);
	options.pos /= WINDOW_SIZE_UNITS / 2.0;
	transformation = glm::translate(transformation, glm::vec3(options.pos, 0));
	transformation = glm::rotate(transformation, glm::radians(options.angelRotate), glm::vec3(0, 0, 1));
	transformation = glm::scale(transformation, glm::vec3(options.size / WINDOW_SIZE_UNITS));

	square.shader.load_mat("transf", transformation);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, options.texture);
	glBindVertexArray(square.VAO);
	glEnableVertexAttribArray(0);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisableVertexAttribArray(0);
	square.shader.stop();
};