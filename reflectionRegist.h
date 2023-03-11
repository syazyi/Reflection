#pragma once
#include <iostream>
#include <string>
#include "reflection.h"
#include "object.h"
namespace kaf {
	class ReflectionRegist {
	public:
		ReflectionRegist(const std::string& className, CreatClassFunction method) {
			Reflection* reflection = Reflection::instance();
			reflection->Register(className, method);
			std::cout << "Has been Regist class\n";
		}

		ReflectionRegist(const std::string& className, const std::string& filedName, const std::string& typeName, size_t offset) {
			Reflection* reflection = Reflection::instance();
			reflection->RegisterFiled(className, filedName, typeName, offset);
			std::cout << "Has been Regist Filed , " << filedName << std::endl;
		}

		ReflectionRegist(const std::string& className, const std::string& methodName, uintptr_t methodPtr) {
			auto r = Reflection::instance();
			r->RegisterMethod(className, methodName, methodPtr);
			std::cout << "Has been Regist Method , " << methodName << "\n";
		}
	};
#define REGISTER_CLASS(className)									\
		ReflectionRegist ReflectionRegist##className(#className,	\
			[]()->auto{												\
			Object* obj = new className();							\
			obj->SetClassName(#className);							\
			return obj;												\
		});

#define REGISTER_CLASSFILED(className, filedName, filedType)  \
		className className##filedName;						\
		ReflectionRegist ReflectionRegist##className##filedName(#className, #filedName, #filedType,				\
										(size_t)&className##filedName.filedName - (size_t)&className##filedName);
		

#define REGISTER_CLASSMETHOD(className, methodName)				\
		std::function<void(className*)> className##methodName##method = &className::methodName; \
		ReflectionRegist ReflectionRegist##className##methodName(#className, #methodName, (uintptr_t)&className##methodName##method);
}

//C++17
//#define REGISTER_CLASSMETHODFLAG(className, methodName, size)\
//bool className_Wrapper(std::vector<void*> args) {\
//		if constexpr(size == 0){\
//			if (args.size() != 0) {\
//				return false;\
//			}\
//			else{\
//				methodName();\
//			}\
//		}\
//}\

//C++11
#define REGISTER_CLASSMETHOD_ZEROPARAMETER(className, methodName)\
bool className##methodName##_Wrapper(std::vector<void*> args) {\
		if (args.size() != 0) {\
			return false;\
		}\
		else{\
			methodName();\
			return true;\
		}\
}\

#define REGISTER_CLASSMETHOD_ONEPARAMETER(className, methodName, parameter1)\
bool className##methodName##_Wrapper(std::vector<void*> args) {\
		if (args.size() != 1) {\
			return false;\
		}\
		else{\
			methodName(reinterpret_cast<parameter1*>(args[0]));\
			return true;\
		}\
}\

#define REGISTER_CLASSMETHOD_TWOPARAMETER(className, methodName, parameter1, parameter2)\
bool className##methodName##_Wrapper(std::vector<void*> args) {\
		if (args.size() != 2) {\
			return false;\
		}\
		else{\
			methodName(reinterpret_cast<parameter1>(args[0]), reinterpret_cast<parameter2>(args[1]));\
			return true;\
		}\
}\

#define REGISTER_CLASSMETHOD_THREEPARAMETER(className, methodName, parameter1, parameter2, parameter3)\
bool className##methodName##_Wrapper(std::vector<void*> args) {\
		if (args.size() != 3) {\
			return false;\
		}\
		else{\
			methodName(reinterpret_cast<parameter1*>(args[0]), reinterpret_cast<parameter2*>(args[1]), reinterpret_cast<parameter3*>(args[2]));\
			return true;\
		}\
}\

#define REGISTER_CLASSMETHODWRAPPER(className, methodName)\
		std::function<bool(className*, std::vector<void*>)> className##methodName##method = &className::className##methodName##_Wrapper; \
		ReflectionRegist ReflectionRegist##className##methodName(#className, #methodName, (uintptr_t)&className##methodName##method);
