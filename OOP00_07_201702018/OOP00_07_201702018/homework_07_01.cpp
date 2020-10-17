#include <fstream>
#include <iostream>
#include <string>

class AnyString {
	std::string anyString;

public:
	AnyString(const std::string& anyString) : anyString(anyString) {}
	std::string getAnyString() {
		return "Stored String :: " + anyString;
	}
	friend std::ofstream& operator<<(std::ofstream& out, AnyString& a);//내부 데이터 사용을 위해 friend로 정의	
};

std::ofstream& operator<<(std::ofstream& out, AnyString &a) {//연산자 오버로딩 정의
	out << a.getAnyString();//매개변수로 받은 객체에 저장
	return out;
}

int main() {
	std::ofstream out("testOveroding.txt");
	AnyString a("Hello, this is operator overloading test!!!");
	
	out << a << std::endl;

	return 0;
}