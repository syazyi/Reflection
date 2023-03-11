#pragma once
#include <iostream>
#include <string>
#include "reflection.h"
#include "object.h"
namespace kaf {
	class ReflectionRegist {
	public:
		ReflectionRegist(const std::string& className, CreatClassFunction method) {
			Reflcetion* reflection = Reflcetion::instance();
			reflection->Register(className, method);
			std::cout << "Has been Regist class\n";
		}

		ReflectionRegist(const std::string& className, const std::string& filedName, const std::string& typeName, size_t offset) {
			Reflcetion* reflection = Reflcetion::instance();
			reflection->RegisterFiled(className, filedName, typeName, offset);
			std::cout << "Has been Regist Filed , " << filedName << std::endl;
		}

		ReflectionRegist(const std::string& className, const std::string& methodName, uintptr_t methodPtr) {
			auto r = Reflcetion::instance();
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


#define REGISTER_CLASSMETHOD_TEST(className, methodName, returnType, ...)\
		struct className##methodName##returnType##FunctionType_Used : public ClassMethod{ \
			using FunctionType = std::function<returnType(className*, __VA_ARGS__ )>\
		};\
		className##methodName##returnType##FunctionType_Used::FunctionType className##methodName##method = &className::methodName;\
		ReflectionRegist ReflectionRegist##className##methodName(#className, #methodName, (uintptr_t)&className##methodName##method);\