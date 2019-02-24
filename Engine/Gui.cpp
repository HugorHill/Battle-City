#include "Gui.h"
#include "Shader.h"
#include "RenderManager.h"
#include <map>


void gui::Label::init(void * p)
{
	engine = p;
	caption = "Label";
}
