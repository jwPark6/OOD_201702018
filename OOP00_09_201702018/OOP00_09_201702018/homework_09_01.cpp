#include <iostream>

class MyData{
 int number;
 std::string strNumber;
public:
 MyData(int data, std::string str): number(data), strNumber(str){}
//Operator conversion
 operator int(){return number;}
 operator std::string(){return strNumber;}

//Unary operator
 int operator++(int){ //postfix operation (indicated by dummy 'int')
	 int temp = number;//증가되기 이전의 값을 저장
	 number = number + 1;//number를 증가
	 return temp;//증가전의 값을 반환
 }
 int operator++(){ //prefix operation
	 number = number + 1;//number 를 증가
	 return number;//증가된 number를 반환
 }

 friend std::ostream& operator<<(std::ostream&, MyData &);
};

// non-member operator<< function
std::ostream& operator<<(std::ostream& os, MyData & md){
	return os << "This number is: " << md.strNumber << "\n";
}

int main(){
 MyData mydata(1, "one");

 std::string strNum = mydata;
 int intNum = mydata;

 std::cout << strNum << std::endl; // one
 std::cout << intNum << std::endl; // 1
 std::cout << mydata++ << std::endl; // 1
 std::cout << ++mydata << std::endl; // 3
 std::cout << mydata;

}