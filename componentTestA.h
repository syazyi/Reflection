#pragma once
#include <iostream>
#include <string>
#include "reflectionRegist.h"
#include "object.h"
namespace kaf {
	class ComponentTestA : public Object {
	public:
		ComponentTestA() = default;
		void show() {
			std::cout << "A now is no member" << std::endl;
		}
	private:
		std::string m_name;
	};

	REGISTER_CLASS(ComponentTestA)
	//REGISTER_CLASSFILED(ComponentTestA, m_name, std::string)
}