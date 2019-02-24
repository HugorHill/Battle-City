#include "Gui.h"
#include "Shader.h"
#include "RenderManager.h"
#include <map>
#include <Windows.h>

void gui::Menu::init(void* p)
{
	engine = p;
	current_button = 0;
	window = _ptr(engine, Engine)->getWindow();
	rm = &_ptr(engine, Engine)->rm;
	bgTextTexture = _ptr(engine, Engine)->mm.loadTexture("menu/bgTextTexture.jpg",true);
	pointerTexture = _ptr(engine, Engine)->mm.loadTexture("menu/tank.jpg");
}

void gui::Menu::draw()
{
	rm->drawText("BATTLE", glm::vec2(0, WINDOW_SIZE_UNITS / 4), true, glm::vec3(0), 1.5, bgTextTexture);
	rm->drawText("CITY", glm::vec2(0, WINDOW_SIZE_UNITS / 8), true, glm::vec3(0), 1.5, bgTextTexture);
	rm->drawText("1 PLAYER", glm::vec2(0), true, glm::vec3(1), 0.5);
	rm->drawText("2 PLAYERS", glm::vec2(0,-WINDOW_SIZE_UNITS / 16), true,glm::vec3(1),0.5);
	const float size_square_pointer = WINDOW_SIZE_UNITS / 28;
	rm->drawSquare(pointerTexture, size_square_pointer, glm::vec2(-WINDOW_SIZE_UNITS / 4, size_square_pointer/2 - current_button*WINDOW_SIZE_UNITS/16));
}

static GLuint key_down_status = 0;
static GLuint key_up_status = 0;

void gui::Menu::logic()
{
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS && key_down_status == GLFW_RELEASE)
		current_button^=1;
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS && key_up_status == GLFW_RELEASE)
		current_button^=1;

	if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
		_ptr(engine, Engine)->set_current_scene(1 + current_button);

	key_down_status = glfwGetKey(window, GLFW_KEY_DOWN);
	key_up_status = glfwGetKey(window, GLFW_KEY_UP);

}

void gui::PassWindow::init(void* p)
{
	engine = p;
	rm = &_ptr(engine, Engine)->rm;
	window = _ptr(engine, Engine)->getWindow();
	timer = glfwGetTime();
}

void gui::PassWindow::draw()
{
	rm->drawText("It has not realized yet!", glm::vec2(0), true, glm::vec3(1), 0.25);
	rm->drawText("This window will close after " + std::to_string((int)(5-timer)) + " sec.", glm::vec2(0,-WINDOW_SIZE_UNITS / 16), true, glm::vec3(1),0.25);
}

static float time = 0;
void gui::PassWindow::logic()
{
	if(time == 0) time = glfwGetTime();

	timer += glfwGetTime() - time;
	time = glfwGetTime();
	if (timer > 4)
	{
		_ptr(engine, Engine)->set_current_scene(0);
		timer = 0;
		time = 0;
	}
}
