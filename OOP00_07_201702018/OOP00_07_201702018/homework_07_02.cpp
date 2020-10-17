#include <iostream>

bool funcA() {
    int c;
    std::cin >> c;
    if (c < 10) //Let's assume this is exception
        return false;
    return true;
}
int main() {
    try {
        if (!funcA()) throw std::out_of_range("Invalid Input!!");//해당 문장을 저장하여 catch로 전달
    }
    catch(std::out_of_range& e) {//받은 예외의 문장을 출력
        std::cout << "Exception : " << e.what() << std::endl;
    }
    return 0;
}
