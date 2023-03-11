#include <functional>
#include "reflection.h"
#include "componentTestA.h"
#include "componentTestB.h"
//#define TEST
#ifdef TEST
	//#define HKJONE
	#ifdef HKJONE
		#include<cstddef>
	#endif // HKJONE

	//#define HKJTWO
#endif // TEST

//#define FUNCTIONTEST
#ifdef FUNCTIONTEST
class FunctionTestClass {
public:
	FunctionTestClass() = default;

	void TestFunctionA() {
		std::cout << "TestFunctionA\n";
	}

	void call(){
		using funPtrTest = std::function<void(decltype(this))>;
		funPtrTest fpt = &FunctionTestClass::TestFunctionA;
		uintptr_t func = (uintptr_t)&fpt;
		(*(funPtrTest*)func)(this);
	}
};
#endif // FUNCTIONTEST


int main() {
	kaf::Reflection* reflcetionPtr = kaf::Reflection::instance();
	//kaf::ComponentTestA* a = reinterpret_cast<kaf::ComponentTestA*>(reflcetionPtr->CreatClass("ComponentTestA"));
	kaf::Object* a = reinterpret_cast<kaf::Object*>(reflcetionPtr->CreatClass("ComponentTestA"));
	a->show();

	kaf::Object* b = reinterpret_cast<kaf::Object*>(reflcetionPtr->CreatClass("ComponentTestB"));
	std::string fuc = "fuck you!";
	b->Set("m_name", fuc);
	 
	std::string test;
	b->Get("m_name", test);
	std::cout << test << std::endl;

	b->call("show");
	
	b->Call<int, int>("Show", 6, 7);
	int a666 = 666;
	int b666 = 777;
	b->Call("Show", a666, b666);
}
#ifdef FUNCTIONTEST
	FunctionTestClass ftc;
	ftc.call();
#endif // FUNCTIONTEST

	//auto bTest = new kaf::ComponentTestB("sbTest", 100);
#ifdef HKJONE
	//auto b = reinterpret_cast<size_t>(&reinterpret_cast<kaf::ComponentTestB*>(0)->m_age);
	//auto b = OFFSET(kaf::ComponentTestB, m_age);
	auto b = offsetof(kaf::ComponentTestB, m_age);
#endif // HKJONE

#ifdef HKJTWO
	auto b = (size_t)&(bTest->m_age) - (size_t)bTest;
#endif // HKJTWO

#ifdef TEST
	auto c = sizeof(std::string);
	std::cout << c << std::endl;
	std::cout << b << std::endl;
	auto age = *reinterpret_cast<int*>(reinterpret_cast<size_t>(bTest) + b);
	std::cout << age << std::endl;
#endif // TEST