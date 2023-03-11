#include "reflection.h"

namespace kaf {
	void Reflcetion::Register(const std::string& className, CreatClassFunction method)
	{
		m_classMap[className] = method;
	}

	void* Reflcetion::CreatClass(const std::string& className)
	{
		auto it = m_classMap.find(className);
		if (it == m_classMap.end()) {
			return nullptr;
		}
		return it->second();
	}

	void Reflcetion::RegisterFiled(const std::string& className, const std::string& filedName, const std::string& typeName, size_t offset)
	{
		m_classFiledMap[className].push_back(new ClassFiled(filedName, typeName, offset));
	}

	int Reflcetion::GetFiledCount(const std::string& className)
	{
		return m_classFiledMap.size();
	}

	ClassFiled* Reflcetion::GetFiled(const std::string& className, int pos)
	{
		int size = m_classFiledMap.size();
		if (pos <= 0 || pos > size) {
			return nullptr;
		}
		auto it = m_classFiledMap.find(className);
		if (it == m_classFiledMap.end()) {
			return nullptr;
		}
		return m_classFiledMap[className][pos];
	}

	ClassFiled* Reflcetion::GetFiled(const std::string& className, const std::string& filedName)
	{
		auto it = m_classFiledMap.find(className);
		if (it == m_classFiledMap.end()) {
			return nullptr;
		}
		auto& filed = it->second;
		for (auto& filedIt : filed) {
			if (filedIt->GetName() == filedName) {
				return filedIt;
			}
		}
		return nullptr;
	}

	void Reflcetion::RegisterMethod(const std::string& className, const std::string& methodName, const uintptr_t methodPtr)
	{
		m_classMethodMap[className].push_back(new ClassMethod(methodName, methodPtr));

	}

	int Reflcetion::GetMethodCount(const std::string& className)
	{
		return m_classMethodMap.size();
	}

	ClassMethod* Reflcetion::GetMethod(const std::string& className, int pos)
	{
		int size = m_classMethodMap.size();
		if (pos < 0 || pos >= size) {
			return nullptr;
		}
		auto it = m_classMethodMap.find(className);
		if (it == m_classMethodMap.end()) {
			return nullptr;
		}
		return m_classMethodMap[className][pos];
	}

	ClassMethod* Reflcetion::GetMethod(const std::string& className, const std::string& methodName)
	{
		auto it = m_classMethodMap.find(className);
		if (it == m_classMethodMap.end()) {
			return nullptr;
		}
		auto& vec = it->second;
		for (auto& a : vec) {
			if (methodName == a->GetName()) {
				return a;
			}
		}
		return nullptr;
	}

}