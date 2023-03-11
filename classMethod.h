#pragma once
#include <string>
namespace kaf {
	class ClassMethod {
	public:
		ClassMethod() = default;
		ClassMethod(const std::string& name, uintptr_t method) : m_name(name), m_method(method) {}

		std::string& GetName() {
			return m_name;
		}
		uintptr_t GetMethod() {
			return m_method;
		}
	private:
		std::string m_name;
		uintptr_t m_method;
	};
}