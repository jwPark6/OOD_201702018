#include <iostream>
class Strategy{//�⺻ Ŭ����
public :
	virtual int doOperation(int num1, int num2)=0;
};

class OperationAdd : public Strategy {//�� ������ �ٽ� �����ϱ� ���� Ŭ����
public :
	int doOperation(int num1, int num2) override { return num1 + num2; };
};

class OperationSubstract : public Strategy {
	int doOperation(int num1, int num2) override { return num1 - num2; };
};

class OperationMultiply : public Strategy {
	int doOperation(int num1, int num2) override { return num1 * num2; };
};

class Context {//��� ���� Ŭ����
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

int main() {//�� ������ ����Ͽ� Ȯ��
	Context *context = new Context(new OperationAdd);
	std::cout << "10 + 5 = " << context -> executeStrategy(10, 5) << '\n';
	context = new Context(new OperationSubstract);
	std::cout << "10 - 5 = " << context->executeStrategy(10, 5) << '\n';
	context = new Context(new OperationMultiply);
	std::cout << "10 * 5 = " << context->executeStrategy(10, 5) << '\n';
	return 0;
}