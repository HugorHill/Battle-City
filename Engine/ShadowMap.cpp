#include "ShadowMap.h"
#include <iostream>

#define WIN_SIZE 700
static std::vector<glm::vec2> positions;


void ShadowMap::init()
{
	for (int i = 0; i < 15; i++)
	{
		const float C = WINDOW_SIZE_UNITS;
		positions.push_back(glm::vec2(rand() % (int)C - C / 2, rand() % (int)C - C / 2));
	}

	glGenFramebuffers(1, &framebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	glGenTextures(1, &textureColorbuffer);
	glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, WIN_SIZE, WIN_SIZE, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, WIN_SIZE, WIN_SIZE); 
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo); 
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	quad_texture = engine->mm.loadTexture("map/water.jpg");
	//gauss_shader = Shader("shaders/gauss", engine);

	square.VAO = engine->mm.getVAO();
	square.pos = engine->mm.getVBO();
	square.shader =  Shader("shaders/scene");
	glBindVertexArray(square.VAO);
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


	triangle.VAO = engine->mm.getVAO();
	triangle.pos = engine->mm.getVBO();
	triangle.shader = Shader("shaders/triangle");
	glBindVertexArray(triangle.VAO);
	glBindVertexArray(triangle.pos);
	glBindBuffer(GL_ARRAY_BUFFER, triangle.pos);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*6, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glDisableVertexAttribArray(0);

}


bool use_frame = true;

void ShadowMap::draw_quad()
{
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
	glBindVertexArray(square.VAO);
	glEnableVertexAttribArray(0);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisableVertexAttribArray(0);
}

void ShadowMap::draw_triangle(glm::vec2* v, float color)
{
	triangle.shader.start();
	triangle.shader.load_f("color", color);
	glBindVertexArray(triangle.VAO);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, triangle.pos);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * 3 * 2, v);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	triangle.shader.stop();
}

void ShadowMap::draw_fans(float size, glm::vec2 pos,glm::vec2 center)
{
	glm::vec2 vertex_triangle[3] = { center };
	size /= WINDOW_SIZE_UNITS;
	pos /= WINDOW_SIZE_UNITS / 2.0;
	const glm::vec2 d_vertex[] = { glm::vec2(1,1),glm::vec2(1,-1),glm::vec2(-1,-1),glm::vec2(-1,1),glm::vec2(1,1) };
	for (int i = 0; i < 4; i++)
	{
		glm::vec2 a = glm::normalize(pos + size*d_vertex[i] - center);
		glm::vec2 v_a = pos + size*d_vertex[i];
		glm::vec2 b = glm::normalize(pos + size*d_vertex[i + 1] - center);
		glm::vec2 v_b = pos + size*d_vertex[i + 1];
		a *= 2;
		b *= 2;

		vertex_triangle[0] = v_a;
		vertex_triangle[1] = v_a + a;
		vertex_triangle[2] = v_b + b;
		draw_triangle(vertex_triangle,0);

		vertex_triangle[0] = v_a;
		vertex_triangle[1] = v_b;
		vertex_triangle[2] = v_b + b;
		draw_triangle(vertex_triangle, 0);

	}
}

static bool debug = true;

void ShadowMap::draw()
{

	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (int i = 0; i < positions.size(); i++)
	{
		draw_fans(25, positions[i],glm::vec2(sinf(0),cosf(0)));
		//engine->rm.drawSquare(quad_texture, 25, positions[i]);
	}


	/*gauss_shader.start();
	gauss_shader.load_vec("win_size", glm::vec2(700, 700));
	gauss_shader.load_vec("dir", glm::vec2(1, 0));
	gauss_shader.load_f("radius", 1.5);
	gauss_shader.load_i("screenTexture", 0);
	draw_quad();
	gauss_shader.load_vec("dir", glm::vec2(0, 1));
	draw_quad();
	gauss_shader.stop();*/
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	if (debug)
	{
		glClearColor(0, 0, 0, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		square.shader.start();
		square.shader.load_i("screenTexture", 0);
		draw_quad();
		square.shader.stop();
	}

}