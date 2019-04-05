#include "Engine.h"
#include "RenderManager.h"
#include "RP_DrawShadows.h"

void RP_DrawShadows::init()
{
	triangle.VAO = engine->mm.getVAO();
	triangle.pos = engine->mm.getVBO();
	triangle.shader = Shader("shaders/triangle");
	glBindVertexArray(triangle.VAO);
	glBindVertexArray(triangle.pos);
	glBindBuffer(GL_ARRAY_BUFFER, triangle.pos);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glDisableVertexAttribArray(0);
	shadow_map_layer.init();
	result_layer.init();
};

void RP_DrawShadows::draw_triangle(glm::vec2* v, float color,GLuint texture,GLuint brightness_map)
{
	triangle.shader.start();
	triangle.shader.load_f("color", color);
	triangle.shader.load_i("scene_pic", 0);
	triangle.shader.load_i("brigh_pic", 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, brightness_map);

	glBindVertexArray(triangle.VAO);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, triangle.pos);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * 3 * 2, v);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	triangle.shader.stop();
}

void RP_DrawShadows::draw_fans(float size, glm::vec2 pos, glm::vec2 center)
{
	center /= WINDOW_SIZE_UNITS / 2.0;
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
		draw_triangle(vertex_triangle, 0);

		vertex_triangle[0] = v_a;
		vertex_triangle[1] = v_b;
		vertex_triangle[2] = v_b + b;
		draw_triangle(vertex_triangle, 0);

	}
}

void RP_DrawShadows::run()
{
	if(positions.size() == 0)
	{

		//эту штуку надо убрать!!!!!!!!!!!!!!!
		for (int i = 0; i < 32; i++)
			for (int j = 0; j < 32; j++)
				if ( options.map->map[i][j]==2 || options.map->map[i][j] == 3)
					positions.push_back(glm::vec2(16 * i - 256 + square_width, 16 * j - 256 + square_width));

					
	}
	//сначала сгенерим карту теней в отдельный слой
	shadow_map_layer.Use();
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (int i = 0; i < positions.size(); i++)
		draw_fans(2*square_width, positions[i], options.light_pos);
	shadow_map_layer.Reset();

	glm::vec2 vertex_triangle[3];
	result_layer.Use();
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	vertex_triangle[0] = glm::vec2(-1, -1);
	vertex_triangle[1] = glm::vec2(1, 1);
	vertex_triangle[2] = glm::vec2(-1, 1);
	draw_triangle(vertex_triangle, -1, options.current_layer->texturebuffer, shadow_map_layer.texturebuffer);
	vertex_triangle[0] = glm::vec2(-1, -1);
	vertex_triangle[1] = glm::vec2(1, -1);
	vertex_triangle[2] = glm::vec2(1, 1);
	draw_triangle(vertex_triangle, -1, options.current_layer->texturebuffer, shadow_map_layer.texturebuffer);


	result_layer.Reset();

	//а теперь сгенерим картинку вместе с картой теней
	options.current_layer->Use();
	engine->rm.draw_square(result_layer.texturebuffer, WINDOW_SIZE_UNITS, glm::vec2(0));
	positions.clear();
};