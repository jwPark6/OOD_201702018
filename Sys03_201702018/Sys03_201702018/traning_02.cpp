#include <iostream>
#define MAXSTACKSIZE 1000//������ �ִ� ũ��

class Stack{
	int top;
public :
	int a[MAXSTACKSIZE];//����

	Stack() { top = -1; } //������ ����� �� �ʱ�ȭ
	bool push(int x);
	int pop();
};

bool Stack::push(int x) {
	if (top >= MAXSTACKSIZE - 1) {
		std::cout << "���� : ������ ���ƽ��ϴ�" << std::endl;
		return false;
	}
	else {
		a[++top] = x; // �߰��� �ڵ� : ++top�� �̿��Ͽ� �ش� �ε��� ��ġ�� �߰��� ���� ����, top�� ���� ������ ����ϴ� ���� �߿�
		std::cout << x << " �� ���ÿ� �����ϴ�." << std::endl;
		return true;
	}
}

int Stack::pop() {
	if (top < 0) {
		std::cout<<"���� : ������ ������ϴ�." << std::endl;
		return 0;
	}
	else {
		int x = a[top];// top �� ���� ����� �ִ� �ε����̹Ƿ� �̸� ����Ͽ� x �� ����
		a[top--] = NULL;// ���� ������ ������ top--�� ���� 1����
		return x;
	}
}

int main() {
	class Stack s;
	s.push(7);
	s.push(88);
	s.push(999);
	std::cout << s.pop() << "�� ���ÿ��� ���½��ϴ�." << std::endl;
	std::cout << s.pop() << "�� ���ÿ��� ���½��ϴ�." << std::endl;
	std::cout << s.pop() << "�� ���ÿ��� ���½��ϴ�." << std::endl;

	system("pause");
	return 0;
}