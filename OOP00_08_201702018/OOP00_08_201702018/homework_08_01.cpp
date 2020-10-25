#include <iostream>

class GlobalClass{
private:
	int m_value;
	static GlobalClass* s_instance;

	GlobalClass(int v = 0){
		m_value = v;
	}
public:
	int get_value(){
		return m_value;
	}
	void set_value(int v){
		m_value = v;
	}
	static GlobalClass* instance(){
		if (s_instance == 0) {//기존에 생성된 객체가 존재하는 지 확인
			s_instance = new GlobalClass();//새로운 객체를 할당
		}
		return s_instance;//객체를 반환
	}
};

// Allocating and initializing GlobalClass's
// static data member.  The pointer is being
// allocated - not the object itself.
GlobalClass* GlobalClass::s_instance = 0;

void foo(void){
	GlobalClass::instance()->set_value(1);
	std::cout << "foo: global_ptr is " << GlobalClass::instance()->get_value() << '\n';
}

void bar(void){
	GlobalClass::instance()->set_value(2);
	std::cout << "bar: global_ptr is " << GlobalClass::instance()->get_value() << '\n';
}

int main(){
	std::cout << "main: global_ptr is " << GlobalClass::instance()->get_value() << '\n';
	foo();
	bar();
}