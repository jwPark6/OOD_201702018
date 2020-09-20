#include <iostream>
class SetValue {
private:
	int x, y;
public:
	int GetX() {
		return x;
	}
	int GetY() {
		return y;
	}
	void SetX(int x){
		this->x = x;
	}
	void SetY(int y) {
		this->y = y;
	}
};

int main() {
	SetValue obj;
	obj.SetX(33);
	obj.SetY(44);
	std::cout << "X = " << obj.GetX() << " ,Y = " << obj.GetY() << std::endl;
	return 0;
}