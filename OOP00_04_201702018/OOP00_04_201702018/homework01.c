#define _CRT_SECURE_NO_WARNINGS// ���Ȱ��� ���� ������ ���� ����
#include <stdio.h>

int main() {
	char s[100];//�Է¹��� ���ڸ� 100�� ũ���� char �迭�� ����
	printf("���ڸ� �Է��ϼ���(100�� �̳�).\n");//�ش繮�� ���
	scanf("%s", s);//scanf �� �Է�, �迭�� �ּ��̹Ƿ� & �� ������ ����
	printf("�Էµ� ���ڴ� %s �Դϴ�.", s);//s ���

	return 0;
}