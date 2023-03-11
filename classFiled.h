#pragma once
#include <string>
namespace kaf {
	class ClassFiled {
	public:
		ClassFiled() = default;
		ClassFiled(const std::string& name, const std::string& type, size_t offset) : m_name(name), m_type(type), m_offset(offset) {}

		std::string& GetName() {
			return m_name;
		}
		std::string& GetType() {
			return m_type;
		}
		size_t GetOffset() {
			return m_offset;
		}
	private:
		std::string m_name;
		std::string m_type;
		size_t m_offset;
	};

}