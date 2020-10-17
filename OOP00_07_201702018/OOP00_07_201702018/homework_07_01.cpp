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
	friend std::ofstream& operator<<(std::ofstream& out, AnyString& a);//���� ������ ����� ���� friend�� ����	
};

std::ofstream& operator<<(std::ofstream& out, AnyString &a) {//������ �����ε� ����
	out << a.getAnyString();//�Ű������� ���� ��ü�� ����
	return out;
}

int main() {
	std::ofstream out("testOveroding.txt");
	AnyString a("Hello, this is operator overloading test!!!");
	
	out << a << std::endl;

	return 0;
}