
#pragma once

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <map>
#include <string>
#include <glm\glm.hpp>
#include "Shader.h"
#include "Defines.h"

class Engine;

class RenderProcessObject
{
	friend class Engine;
public:
	RenderProcessObject() {};
	~RenderProcessObject() {};
	virtual void init() = 0;
	virtual void run() = 0;
protected:
	static Engine* engine;
};

struct Layer
{
	GLuint framebuffer;
	GLuint texturebuffer;
	GLuint renderbuffer;
	void init();
	inline void Use();
	inline void Reset();
};

class Map;
class RenderManager
{
	friend class Engine;
	public:
		RenderManager() : engine(NULL) {};
		~RenderManager() {};
		void draw_square(GLuint texture,GLuint size,glm::vec2 pos,float angelRotate = 0);
		void draw_text(std::string text, glm::vec2 pos, bool atCenter = false, glm::vec3 color = glm::vec3(0), float scale = 1,GLuint bgTexture = 0);
		void draw_shadows(glm::vec2 light_position, Map* map);
	private:
		void init(int w, int h, Engine* ptr);
		void updateScreen();
		Engine* engine; // указатель на движок
		std::map<std::string, RenderProcessObject*> renderProcess;
		std::map<std::string, Layer*> layers;
};
