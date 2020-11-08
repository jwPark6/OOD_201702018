#include <iostream>
class Strategy{//기본 클래스
public :
	virtual int doOperation(int num1, int num2)=0;
};

class OperationAdd : public Strategy {//각 연산을 다시 지정하기 위한 클래스
public :
	int doOperation(int num1, int num2) override { return num1 + num2; };
};

class OperationSubstract : public Strategy {
	int doOperation(int num1, int num2) override { return num1 - num2; };
};

class OperationMultiply : public Strategy {
	int doOperation(int num1, int num2) override { return num1 * num2; };
};

class Context {//제어를 위한 클래스
public :
	Context(Strategy *strategy) {
		this->strategy = strategy;
	}
	int executeStrategy(int num1, int num2) {
		return strategy->doOperation(num1, num2);
	}
private :
	Strategy *strategy;
};

int main() {//각 연산을 출력하여 확인
	Context *context = new Context(new OperationAdd);
	std::cout << "10 + 5 = " << context -> executeStrategy(10, 5) << '\n';
	context = new Context(new OperationSubstract);
	std::cout << "10 - 5 = " << context->executeStrategy(10, 5) << '\n';
	context = new Context(new OperationMultiply);
	std::cout << "10 * 5 = " << context->executeStrategy(10, 5) << '\n';
	return 0;
}