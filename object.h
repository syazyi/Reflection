#pragma once
#include <string>
#include "classFiled.h"
#include "reflection.h"
namespace kaf {
	class Object {
	public:
		Object() = default;

		void SetClassName(const std::string& className);

		int GetFiledCount();
		ClassFiled* GetFiled(int pos);
		ClassFiled* GetFiled(const std::string& filedName);

		template<typename T>
		void Set(const std::string& filedName,const T& value);

		template<typename T>
		void Get(const std::string& filedName, T& value);

		void call(const std::string& methodName);

		virtual void show() = 0;
	private:
		std::string m_className;
	};
	template<typename T>
	inline void Object::Set(const std::string& filedName, const T& value)
	{
		auto cp = GetFiled(filedName);
		auto offset = cp->GetOffset();
		auto valuePtr = (T*)((size_t)this + offset);
		*valuePtr = value;
	}
	template<typename T>
	inline void Object::Get(const std::string& filedName, T& value)
	{
		auto classfiledPtr = GetFiled(filedName);
		auto offset = classfiledPtr->GetOffset();
		auto valuePtr = (T*)((size_t)this + offset);
		value = *valuePtr;
	}
}