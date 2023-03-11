#pragma once
#include <string>
#include "classFiled.h"
#include "reflection.h"
namespace kaf {
	class Reflection;	
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

		template<typename... Args>
		void Call(const std::string& methodWrapperName, Args&&... args);

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
	
	template<typename ...Args>
	inline void Object::Call(const std::string& methodWrapperName, Args&&... args)
	{
		auto r = Reflection::instance();
		auto method = r->GetMethod(m_className, methodWrapperName)->GetMethod();
		using methodType = std::function<bool(decltype(this), std::vector<void*>)>;
		std::vector<void*> tempArr{reinterpret_cast<void*>(std::forward<Args>(args))...};
		(*(methodType*)method)(this, tempArr);
	}
}