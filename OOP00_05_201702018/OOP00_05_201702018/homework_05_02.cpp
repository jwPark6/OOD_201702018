#include <iostream>
using namespace std;

int i;

class A {
public:
	~A() {
		i = 10;
	}
};
int foo(){
	{//다음과 같이 블록을 지정하면 블록이 끝날 때 객체가 소멸되어 i에 10이 대입된다.
		i = 3;
		A ob; 
	}
	return i;
}
int main() {
	cout << foo() << endl;
	return 0;
}