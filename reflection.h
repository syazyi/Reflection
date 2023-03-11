#pragma once
#include <map>
#include <vector>
#include <string>
#include <functional>
#include "classFiled.h"
#include "classMethod.h"
#include "object.h"
namespace kaf {
	class Object;
	//typedef Object* (*CreatClassFunction)(void);
	using CreatClassFunction = std::function<Object* (void)>;

	class Reflection {
	public:
		Reflection(const Reflection&) = delete;
		Reflection& operator=(const Reflection&) = delete;

		static Reflection* instance() {
			static Reflection instance;
			return &instance;
		}
		void Register(const std::string& className, CreatClassFunction method);
		void* CreatClass(const std::string& className);

		void RegisterFiled(const std::string& className, const std::string& filedName, const std::string& typeName, size_t offset);
		int GetFiledCount(const std::string& className);
		ClassFiled* GetFiled(const std::string& className, int pos);
		ClassFiled* GetFiled(const std::string& className, const std::string& filedName);

		void RegisterMethod(const std::string& className, const std::string& methodName, const uintptr_t methodPtr);
		int GetMethodCount(const std::string& className);
		ClassMethod* GetMethod(const std::string& className, int pos);
		ClassMethod* GetMethod(const std::string& className, const std::string& methodName);

	private:
		Reflection() = default;
		std::map<std::string, CreatClassFunction> m_classMap;
		std::map<std::string, std::vector<ClassFiled*>> m_classFiledMap;
		std::map<std::string, std::vector<ClassMethod*>> m_classMethodMap;
		
		//std::map<std::string, >
	};


#define OFFSET(className, filedName)			\
		reinterpret_cast<size_t>(&reinterpret_cast<className*>(0)->filedName)
}