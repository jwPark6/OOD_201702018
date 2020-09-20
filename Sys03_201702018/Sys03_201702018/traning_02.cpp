#include <iostream>
#define MAXSTACKSIZE 1000//스택의 최대 크기

class Stack{
	int top;
public :
	int a[MAXSTACKSIZE];//스택

	Stack() { top = -1; } //스택의 꼭대기 값 초기화
	bool push(int x);
	int pop();
};

bool Stack::push(int x) {
	if (top >= MAXSTACKSIZE - 1) {
		std::cout << "오류 : 스택이 넘쳤습니다" << std::endl;
		return false;
	}
	else {
		a[++top] = x; // 추가한 코드 : ++top을 이용하여 해당 인덱스 위치에 추가한 값을 대입, top의 값을 증가후 사용하는 것이 중요
		std::cout << x << " 이 스택에 들어갔습니다." << std::endl;
		return true;
	}
}

int Stack::pop() {
	if (top < 0) {
		std::cout<<"오류 : 스택이 비었습니다." << std::endl;
		return 0;
	}
	else {
		int x = a[top];// top 이 값이 저장된 최대 인덱스이므로 이를 사용하여 x 에 대입
		a[top--] = NULL;// 이후 기존값 제거후 top--을 통해 1감소
		return x;
	}
}

int main() {
	class Stack s;
	s.push(7);
	s.push(88);
	s.push(999);
	std::cout << s.pop() << "을 스택에서 꺼냈습니다." << std::endl;
	std::cout << s.pop() << "을 스택에서 꺼냈습니다." << std::endl;
	std::cout << s.pop() << "을 스택에서 꺼냈습니다." << std::endl;

	system("pause");
	return 0;
}