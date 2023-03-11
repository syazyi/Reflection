#pragma once
#include <iostream>
#include <string>
#include "reflection.h"
#include "object.h"
namespace kaf {
	class ComponentTestB : public Object{
	public:
		ComponentTestB() = default;
		ComponentTestB(const std::string& name, int age) : m_name(name), m_age(age) {}
		void show() {
			std::cout << "B now is no member" << std::endl;
		}
	public:
		std::string m_name;
		int m_age = 0; 
	};
	REGISTER_CLASS(ComponentTestB)
	REGISTER_CLASSFILED(ComponentTestB, m_name, std::string)
	REGISTER_CLASSFILED(ComponentTestB, m_age, int)
	REGISTER_CLASSMETHOD(ComponentTestB, show)
}