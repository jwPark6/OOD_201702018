#define _CRT_SECURE_NO_WARNINGS// 보안경고로 인한 컴파일 에러 방지
#include <stdio.h>

int main() {
	char s[100];//입력받을 문자를 100의 크기의 char 배열에 저장
	printf("문자를 입력하세요(100자 이내).\n");//해당문장 출력
	scanf("%s", s);//scanf 로 입력, 배열은 주소이므로 & 를 붙이지 않음
	printf("입력된 문자는 %s 입니다.", s);//s 출력

	return 0;
}