#include "Terrain.h"
#include "Defines.h"
#include "Engine.h"
//#define GLM_ENABLE_EXPERIMENTAL 1
//#include <glm\gtx\transform.hpp>

Square::Square(float unit_size, void * engine)
{
	square_size = unit_size;
	Shader_prog = Shader("static",engine);
	VAO = _ptr(engine, Engine)->mm.getVAO();
	Positions = _ptr(engine, Engine)->mm.getVBO();
	Texture_coords = _ptr(engine, Engine)->mm.getVBO();


	glBindVertexArray(VAO);

	unit_size /= WINDOW_SIZE_UNITS;

	static const GLfloat pos[] =
	{
		-1,-1,0,
		1,-1,0,
		-1,1,0,
		-1,1,0,
		1,-1,0,
		1,1,0
	};

	glBindBuffer(GL_ARRAY_BUFFER, Positions);
	glBufferData(GL_ARRAY_BUFFER, sizeof(pos), pos, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(void*)0);
	glDisableVertexAttribArray(0);

}

void Square::draw(GLuint texture)
{
	Shader_prog.start();
	Shader_prog.load_mat("transf", glm::scale(glm::mat4(1),glm::vec3(square_size/WINDOW_SIZE_UNITS)));
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glBindVertexArray(VAO);
	glEnableVertexAttribArray(0);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisableVertexAttribArray(0);
	Shader_prog.stop();
}



void Terrain::init(void* p)
{
	engine = p;
	sqr = Square(512, engine);
	texture = _ptr(engine, Engine)->mm.loadTexture("sample.jpg");
}

void Terrain::draw()
{
	sqr.draw(texture);
	
}

