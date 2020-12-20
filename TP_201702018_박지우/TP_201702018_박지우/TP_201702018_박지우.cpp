#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

class Page {//����� �������� �ܾ��� �ε����� �����ϴ� Ŭ����
private:
	int count;
	Page* prev;
	Page* next;
public:
	Page(int i) {//������
		count = i;
		prev = NULL;
		next = NULL;
	}
	//setter/getter
	int getConut() {
		return count;
	}
	void setCount(int i) {
		count = i;
	}
	Page* getNext() {
		return next;
	}
	void setNext(Page* n) {
		next = n;
	}
	Page* getPrev() {
		return prev;
	}
	void setPrev(Page* p) {
		prev = p;
	}
};

class RunWord {//Page�� �ٷ�� �⺻ �Լ�
public:
	virtual bool solve(Page *page, vector<string> &v, int inputFirstNum, int inputSecondNum, string inputFirstWord, string inputSecondWord) = 0;
};


class InsertWord : public RunWord {//����
public:
	bool solve(Page* page, vector<string>& v, int inputFirstNum, int inputSecondNum, string inputFirstWord, string inputSecondWord) {
		int tempCount;
		int tempSize = 0;
		if (page->getPrev() != NULL) {//���� Page�� ���� �ܾ��� �ε����� ����
			tempCount = page->getConut();
		}
		else {
			tempCount = 0;
		}
        //���� �������� 75����Ʈ ������ �̵�
		for (int i = 0; i < inputFirstNum - 1; i++) {
			while (tempSize + size(v[tempCount]) < 76) {
				if ((tempSize + size(v[tempCount]) + size(v[tempCount + 1])) > 75) {
					tempSize += size(v[tempCount++]);
				}
				else {
					tempSize += (size(v[tempCount++]) + 1);
				}
			}
			tempSize = 0;
		}
		//���� ���� ���� ���� �ִ� �ε������� Ŭ ��� false
		int maxCount = tempCount;
		while (tempSize + size(v[maxCount]) < 76) {
			if ((tempSize + size(v[maxCount]) + size(v[maxCount + 1])) > 75) {
				tempSize += size(v[maxCount++]);
			}
			else {
		  		tempSize += (size(v[maxCount++]) + 1);
			}
		}
		if (maxCount-tempCount < inputSecondNum) {
			return false;
		}
		
		//���� �ε����� �̵��� �ε����� ���Ͽ� ����
		v.insert(v.begin() + tempCount + inputSecondNum, inputFirstWord);
		return true;
	}
};
class DeleteWord : public RunWord {//����
public:
	bool solve(Page* page, vector<string>& v, int inputFirstNum, int inputSecondNum, string inputFirstWord, string inputSecondWord) {
		int tempCount;
		int tempSize = 0;
		if (page->getPrev() != NULL) {
			tempCount = page->getConut();
		}
		else {
			tempCount = 0;
		}
		//���� �������� 75����Ʈ ������ �̵�
		for (int i = 0; i < inputFirstNum - 1; i++) {
			while (tempSize + size(v[tempCount]) < 76) {
				if ((tempSize + size(v[tempCount]) + size(v[tempCount + 1])) > 75) {
					tempSize += size(v[tempCount++]);
				}
				else {
					tempSize += (size(v[tempCount++]) + 1);
				}
			}
			tempSize = 0;
		}
		//���� ���� ���� ���� �ִ� �ε������� Ŭ ��� false
		int maxCount = tempCount;
		while (tempSize + size(v[maxCount]) < 76) {
			if ((tempSize + size(v[maxCount]) + size(v[maxCount + 1])) > 75) {
				tempSize += size(v[maxCount++]);
			}
			else {
				tempSize += (size(v[maxCount++]) + 1);
			}
		}
		if (maxCount - tempCount < inputSecondNum) {
			return false;
		}
		//���� �ε��� + ���� �ε����� �Ͽ� ����
		v.erase(v.begin() + tempCount + inputSecondNum - 1);
		return true;
	}
};

class ChangeWord : public RunWord {//����
	bool solve(Page* page, vector<string>& v, int inputFirstNum, int inputSecondNum, string inputFirstWord, string inputSecondWord) {
		int tempCount = 0;
		bool b = false;
		while (tempCount != v.size()) {//��ü�� Ž���Ͽ� ����� �ܾ ã���� ���Ϳ� ������ �ܾ ����
			if (v[tempCount++] == inputFirstWord) {
				v[tempCount - 1] = inputSecondWord;
				b = true;
			}
		}
		if (b) {
			return true;
		}
		else {
			return false;
		}	
	}
};

class SearchWord : public RunWord {//Ž��
	bool solve(Page* page, vector<string>& v, int inputFirstNum, int inputSecondNum, string inputFirstWord, string inputSecondWord) {
		int tempCount = 0;
		int tempSize = 0;
		int wordCount = 0;
		while (tempCount < v.size()) {//���� ���� �ܾ Ž��
			if (v[tempCount] == inputFirstWord) {//�����ϸ� ����
				break;
			}
			if (tempCount == v.size() - 1) {//������ Ž������ ���ٸ� false
				return false;
			}
			if (tempSize + size(v[tempCount]) < 76) {//���� �������� Ž��, 75����Ʈ ������ ���
				wordCount++;
				if ((tempSize + size(v[tempCount]) + size(v[tempCount + 1])) > 75) {
					tempSize += size(v[tempCount++]);
				}
				else {
					tempSize += (size(v[tempCount++]) + 1);
				}
			}
			else {
				wordCount = 0;
				tempSize = 0;
			}
		}
		//ã�� �ܾ��� ���� �������� �ε��� ����
		page->setCount(tempCount - wordCount);
		tempCount = tempCount - wordCount;

		tempSize = 0;
		while (tempCount != 0) {//ã�� �ܾ��� ���� ã�� ����
			for (int i = 0; i < 20; i++) {//20�� �������� �������� Ž��
				while (!(tempCount == 0) && tempSize + size(v[tempCount]) < 76) {
					if ((tempSize + size(v[tempCount]) + size(v[tempCount - 1])) > 75) {
						tempSize += size(v[tempCount--]);
					}
					else {
						tempSize += (size(v[tempCount--]) + 1);
					}
					if (tempCount == 0) {
						break;
					}
				}
				tempSize = 0;
			}
			//������ ������ Page ��ü�� �����
			if (page->getPrev() != NULL) {//������ �ּҰ� ������ �� ���� ����
				page->getPrev()->setCount(tempCount);
				page = page->getPrev();
			}
			else if (tempCount != 0) {//�ּҰ� ���ٸ� ���� ��ü�� �����Ͽ� �ּҸ� ����
				page->setPrev(new Page(tempCount));
				page = page->getPrev();
			}
			if (tempCount == 0) {//���� Ž���Ͽ� ù��° �ε����� �´ٸ� 0���� ����
				page->setPrev(new Page(0));
				return true;
			}
		}
	}
};

class SaveWord : public RunWord {//����
	bool solve(Page* page, vector<string>& v, int inputFirstNum, int inputSecondNum, string inputFirstWord, string inputSecondWord) {
		remove("test.txt");//�������� ���� �� �ٲ� ���͸� ���Ͽ� ����
		ofstream myFile("test.txt");
		int i = 0;
		while (i < v.size()) {
			myFile << v[i++] + " ";
		}
		return true;
	}
};

//����ó�� �Լ� >> �Լ� �����ε��� ����Ͽ� ���ڿ� ���� �����ϴ� �Լ��� �ٸ��� ȣ��
bool checkInput(string input, vector<string> v, int *fn, int *sn, string *w) {//���� ����
	vector<string> parseV;
	stringstream ss(input);
	string s;
	try {//��� �˻�
		//��ɾ� Ʋ �˻�
		if (input[1] != '(' || input[input.length()-1] != ')' || input.find(",") == string::npos) {
			return false;
		}
		while (getline(ss, s, ',')) {//, �� ������ �� �˻�
			if (s == "") {
				return false;
			}
			parseV.push_back(s);
		}
		if (parseV.size() != 3) {
			return false;
		}
		parseV[0] = parseV[0].erase(0, 2);//�� �ܾ���� �ʿ� �ܾ�� �ٽ� �ڸ�
		
		if (stoi(parseV[0]) > 20) {//20�� �̻� �˻�
			return false;
		}	
		*fn = stoi(parseV[0]);//����ȯ
		*sn = stoi(parseV[1]);	
		parseV[2] = parseV[2].erase(parseV[2].length() - 1, 1);//75����Ʈ �̻� �ܾ� �˻�
		if (size(parseV[2]) > 75) {
			return false;
		}
		else {
			*w = parseV[2];
		}
		return true;
	}
	catch (...) {
		return false;
	}
	
}

bool checkInput(string input, vector<string> v, int* fn, int* sn) {//���� �˻�
	vector<string> parseV;
	stringstream ss(input);
	string s;

	try {//���԰� ����
		if (input[1] != '(' || input[input.length() - 1] != ')' || input.find(",") == string::npos) {
			return false;
		}
		while (getline(ss, s, ',')) {
			parseV.push_back(s);
		}
		if (parseV.size() != 2) {
			return false;
		}
		parseV[0] = parseV[0].erase(0, 2);

		if (stoi(parseV[0]) > 20) {
			return false;
		}
		*fn = stoi(parseV[0]);
		parseV[1] = (parseV[1].erase(parseV[1].length() - 1, 1));

		*sn = stoi(parseV[1]);
		return true;
	}
	catch (...) {
		return false;
	}
}

bool checkInput(string input, vector<string> v, string* fw, string* sw) {//���� �˻�
	vector<string> parseV;
	stringstream ss(input);
	string s;

	try {//�ܼ��� ��ɾ� ��ĸ� �˻�
		if (input[1] != '(' || input[input.length() - 1] != ')' || input.find(",") == string::npos) {
			return false;
		}
		while (getline(ss, s, ',')) {
			parseV.push_back(s);
		}

		if (parseV.size() != 2) {
			return false;
		}

		parseV[0] = parseV[0].erase(0, 2);
		*fw = parseV[0];

		parseV[1] = (parseV[1].erase(parseV[1].length() - 1, 1));
		*sw = parseV[1];

		return true;
	}
	catch (...) {
		return false;
	}
}

bool checkInput(string input, vector<string> v, string* fw) {//Ž�� �˻�
	stringstream ss(input);
	string s;

	try {//��ɾ� ��� �˻�
		if (input[1] != '(' || input[input.length() - 1] != ')') {
			return false;
		}
		input = input.erase(0, 2);
		input = (input.erase(input.length() - 1, 1));
		if (input.size() < 1) {
			return false;
		}
		*fw = input;

		return true;
	}
	catch (...) {
		return false;
	}
}

int main() {

	int byteSize = 0;
	int wordCount = 0;
	string s;
    vector<string> v;
	ifstream myFile("test.txt");
	string input;
	string consoleMessage = "";
	int inputFirstNum = 0;
	int inputSecondNum = 0;
	string inputFirstWord;
	string inputSecondWord;

	//������ ��� ���Ϳ� �ܾ� ������ ����
	while (getline(myFile, s, ' ')) {
		v.push_back(s);
	}
	myFile.close();
	//0��° �ε������� ����
	Page *page = new Page(wordCount);
	int* lineCount = new int[20];
	while (1) {//���
		wordCount = page->getConut();
		
		for (int i = 0; i < 20; i++) {//�ܾ 75����Ʈ ������ ���
			lineCount[i] = wordCount;
			cout << setw(2) << i + 1 << "| ";
			while (!(wordCount == v.size() - 1) && byteSize + size(v[wordCount]) < 76) {
				if ((byteSize + size(v[wordCount]) + size(v[wordCount+1])) > 75) {
					cout << v[wordCount];
					byteSize += size(v[wordCount++]);
				}
				else {
					cout << v[wordCount] << " ";
					byteSize += (size(v[wordCount++]) + 1);
				}
				if (wordCount == v.size()-1) {
					cout << v[wordCount];
					break;
				}
			}
			byteSize = 0;
			cout << endl;
	    }

		int tempCount = wordCount;
		int j;
		for (j = 0; j < 20; j++) {//������ ������ �˻縦 ���� ���� ������ �ݺ�
			while (!(tempCount == v.size() - 1) && byteSize + size(v[tempCount]) < 76) {
				if ((byteSize + size(v[tempCount]) + size(v[tempCount + 1])) > 75) {
					byteSize += size(v[tempCount++]);
				}
				else {
					byteSize += (size(v[tempCount++]) + 1);
				}
				if (tempCount == v.size() - 1) {
					byteSize = 0;
					break;
				}
			}
			if (tempCount == v.size() - 1) {
				break;
			}
			byteSize = 0;
		}

		if (j < 20) {//20���� ��� �� ä�� ��� >> ������ ������
			page->setNext(new Page(lineCount[j+1]));
			page->getNext()->setPrev(page);
		}
		else {//������ �������� �ƴ� ���
			page->setNext(new Page(wordCount));
			page->getNext()->setPrev(page);
		}
		
		for (int i = 0; i < 81; i++) {
			cout << "-";
		}
		cout << "\nn:����������, p:����������, i:����, d:����, c:����, s:ã��, t:����������" << endl;
		for (int i = 0; i < 81; i++) {
			cout << "-";
		}
		cout << "\n(�ָܼ޽���) " << consoleMessage << endl;
		for (int i = 0; i < 81; i++) {
			cout << "-";
		}
		cout << "\n�Է� : ";
		cin >> input;
		RunWord* rw = NULL;
		consoleMessage = "";

		//�� ��ɾ ���� ��ü �� �Լ� ȣ��
		if (input[0] == 'n' && input.length() == 1) {
			if (!(wordCount == v.size() - 1)) {
				page = page->getNext();
			}
			else {
				consoleMessage = "This is the last page!";
			}
		}
		else if (input[0] == 'p' && input.length() == 1) {
			if (!(page->getPrev() == NULL)) {
				page = page->getPrev();
			}
			else {
				consoleMessage = "This is the first page!";
			}
		}
		else if (input[0] == 'i' && checkInput(input, v, &inputFirstNum, &inputSecondNum, &inputFirstWord)) {
			rw = new InsertWord;
			if (rw->solve(page, v, inputFirstNum, inputSecondNum, inputFirstWord, "")) {
				consoleMessage = "Insert Success!";
			}
			else {
				consoleMessage = "Insert Failed...";
			}
		}
		else if (input[0] == 'd' && checkInput(input, v, &inputFirstNum, &inputSecondNum)) {
			rw = new DeleteWord;
			if (rw->solve(page, v, inputFirstNum, inputSecondNum, "", "")) {
				consoleMessage = "Delete Success!";
			}
			else {
				consoleMessage = "Delete Failed...";
			}
		}
		else if (input[0] == 'c' && checkInput(input, v, &inputFirstWord, &inputSecondWord)) {
			rw = new ChangeWord;
			if (rw->solve(NULL, v, 0, 0, inputFirstWord, inputSecondWord)) {
				consoleMessage = "Change Success!";
			}
			else {
				consoleMessage = "Change Failed...";
			}
		}
		else if (input[0] == 's' && checkInput(input, v, &inputFirstWord)) {
			rw = new SearchWord;
			if (rw->solve(page, v, 0, 0, inputFirstWord, "")) {
				consoleMessage = "Search Success!";
			}
			else {
				consoleMessage = "Search Failed...";
			}
		}
		else if (input[0] == 't' && input.length() == 1) {
			rw = new SaveWord;
			if (rw->solve(NULL, v, 0, 0, "", "")) {
				return 0;
			}
		}
		else {
			consoleMessage = "Unvalid input!";
		}
					
	}							
	return 0;
}