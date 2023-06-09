#include "object.h"
#include <functional>

namespace kaf {
	void Object::SetClassName(const std::string& className)
	{
		m_className = className;
	}
	int Object::GetFiledCount()
	{
		auto r = Reflection::instance();
		return r->GetFiledCount(m_className);
	}
	ClassFiled* Object::GetFiled(int pos)
	{
		auto r = Reflection::instance();
		return r->GetFiled(m_className, pos);
	}
	ClassFiled* Object::GetFiled(const std::string& filedName)
	{
		auto r = Reflection::instance();
		return r->GetFiled(m_className, filedName);
	}
	void Object::call(const std::string& methodName)
	{
		auto r = Reflection::instance();
		auto method = r->GetMethod(m_className, methodName)->GetMethod();
		using methodType = std::function<void(decltype(this))>;
		(*(methodType*)method)(this);
	}
}