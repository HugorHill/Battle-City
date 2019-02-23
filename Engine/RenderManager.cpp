#include "RenderManager.h"
#include "Defines.h"
#include "Engine.h"
#include <stdio.h>
#include <string>
#define _USE_MATH_DEFINES
#include <math.h>


void RenderManager::init(int w, int h)
{
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

	_ptr(engine,Engine)->window = glfwCreateWindow(w, h, title.c_str(), NULL, NULL);
	if (_ptr(engine, Engine)->window == NULL)
	{
		fprintf(stderr, "Невозможно открыть окно GLFW\n");
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(_ptr(engine, Engine)->window);



	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		fprintf(stderr, "Невозможно инициализировать GLEW\n");
		return;
	}

	glfwSetInputMode(_ptr(engine, Engine)->window, GLFW_STICKY_KEYS, GL_TRUE);

	//init structure square
	square.VAO = _ptr(engine, Engine)->mm.getVAO();
	square.pos = _ptr(engine, Engine)->mm.getVBO();
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
	glfwSwapBuffers(_ptr(engine, Engine)->window);
}

//функция рисования квадратика: размеры и позиция указываются в юнитах, а угол в градусах
void RenderManager::drawSquare(GLuint texture, GLuint size, glm::vec2 pos, float angelRotate)
{
	square.shader.start();

	glm::mat4 transformation = glm::mat4(1);
	pos /= WINDOW_SIZE_UNITS/2.0;
	transformation = glm::translate(transformation, glm::vec3(pos, 0));
	transformation = glm::rotate(transformation, (float)(angelRotate*M_PI/180), glm::vec3(0, 0, 1));
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

