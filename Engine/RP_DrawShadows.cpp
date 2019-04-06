#include "Engine.h"
#include "RenderManager.h"
#include "RP_DrawShadows.h"

void RP_DrawShadows::init()
{
	square.VAO = engine->mm.getVAO();
	square.pos = engine->mm.getVBO();
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

	multiply_shader = Shader("shaders/multiply_shader");
	blur_shader = Shader("shaders/gauss");
	light_shader = Shader("shaders/light");
	lightmap_texture = engine->mm.loadTexture("shaders/lightmap.png");



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

void RP_DrawShadows::draw_raw_square()
{
	glBindVertexArray(square.VAO);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, square.pos);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void RP_DrawShadows::draw_triangle(glm::vec2* v, float color, GLuint texture, GLuint brightness_map)
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

	triangle.shader.start();
	triangle.shader.load_f("color", 0);
	glBindVertexArray(triangle.VAO);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, triangle.pos);

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
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * 3 * 2, vertex_triangle);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		vertex_triangle[0] = v_a;
		vertex_triangle[1] = v_b;
		vertex_triangle[2] = v_b + b;
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * 3 * 2, vertex_triangle);
		glDrawArrays(GL_TRIANGLES, 0, 3);

	}

	triangle.shader.stop();
}

static float time = 0;
void RP_DrawShadows::render(Layer* layer)
{
	//сначала сгенерим карту теней в отдельный слой
	shadow_map_layer.Use();
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//эффект иточника света
	light_shader.start();
		light_shader.load_i("pic", 0);
		light_shader.load_i("light_map", 1);
		glm::vec2 light_pos = options[0].light_pos;
		light_pos /= (WINDOW_SIZE_UNITS / 2.0);//пересчет в координаты [-1;1]
		light_shader.load_vec("light_pos", light_pos);
		glActiveTexture(GL_TEXTURE0); glBindTexture(GL_TEXTURE_2D, shadow_map_layer.texturebuffer);
		glActiveTexture(GL_TEXTURE1); glBindTexture(GL_TEXTURE_2D, lightmap_texture);
		draw_raw_square();
	light_shader.stop();
	//рисование теней
	for (auto &opt:options)
		draw_fans(2*square_width, opt.wall, opt.light_pos);
	//размытие
	blur_shader.start();
		blur_shader.load_i("picture", 0);
		glActiveTexture(GL_TEXTURE0); glBindTexture(GL_TEXTURE_2D, shadow_map_layer.texturebuffer);
		for (int i = 0; i<10; i++)
		draw_raw_square();
	blur_shader.stop();
	
	shadow_map_layer.Reset();

	//производим перемножение карты теней(€ркости) и исходного изображени€
	result_layer.Use();
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		multiply_shader.start();
		multiply_shader.load_i("a_pic", 0);
		multiply_shader.load_i("b_pic", 1);
		glActiveTexture(GL_TEXTURE0); glBindTexture(GL_TEXTURE_2D, layer->texturebuffer);
		glActiveTexture(GL_TEXTURE1); glBindTexture(GL_TEXTURE_2D, shadow_map_layer.texturebuffer);
		draw_raw_square();
		multiply_shader.stop();
	result_layer.Reset();

	//а теперь герерим полноценную картинку в буффер откуда мы еЄ вз€ли
	layer->Use();
	engine->rm.draw_square(result_layer.texturebuffer, WINDOW_SIZE_UNITS, glm::vec2(0));
	engine->rm.render_squares();
	layer->Reset();
	options.clear();
};