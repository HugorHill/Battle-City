#include "PanzerPlayer.h"

void PanzerPlayer::logic() {
	if (glfwGetKey(window,GLFW_KEY_W) == GLFW_PRESS) {
		direction = 0;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		direction = 1;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		direction = 2;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		direction = 3;
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && cooldown <= 0) {
	Panzer::Shoot();
	}
}