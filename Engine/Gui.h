#pragma once
#include "Engine.h"
#include "Defines.h"
#include "MemoryManager.h"
#include <iostream>
#include <string>

namespace gui
{

	class Label: public GameObject
	{
		public:
			Label() {};
			~Label() {};
			void init(void* p);
			void draw() {};
			void update() {};
			void logic() {};
		private:
			std::string caption;
	};
}
