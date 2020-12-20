#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

class Page {//출력할 페이지의 단어의 인덱스를 저장하는 클래스
private:
	int count;
	Page* prev;
	Page* next;
public:
	Page(int i) {//생성자
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

class RunWord {//Page를 다루는 기본 함수
public:
	virtual bool solve(Page *page, vector<string> &v, int inputFirstNum, int inputSecondNum, string inputFirstWord, string inputSecondWord) = 0;
};


class InsertWord : public RunWord {//삽입
public:
	bool solve(Page* page, vector<string>& v, int inputFirstNum, int inputSecondNum, string inputFirstWord, string inputSecondWord) {
		int tempCount;
		int tempSize = 0;
		if (page->getPrev() != NULL) {//현재 Page의 시작 단어의 인덱스를 저장
			tempCount = page->getConut();
		}
		else {
			tempCount = 0;
		}
        //행을 기준으로 75바이트 단위로 이동
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
		//열의 값이 현재 행의 최대 인덱스보다 클 경우 false
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
		
		//열의 인덱스를 이동한 인덱스에 더하여 삽입
		v.insert(v.begin() + tempCount + inputSecondNum, inputFirstWord);
		return true;
	}
};
class DeleteWord : public RunWord {//삭제
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
		//행을 기준으로 75바이트 단위로 이동
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
		//열의 값이 현재 행의 최대 인덱스보다 클 경우 false
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
		//열의 인덱스 + 현재 인덱스를 하여 삭제
		v.erase(v.begin() + tempCount + inputSecondNum - 1);
		return true;
	}
};

class ChangeWord : public RunWord {//변경
	bool solve(Page* page, vector<string>& v, int inputFirstNum, int inputSecondNum, string inputFirstWord, string inputSecondWord) {
		int tempCount = 0;
		bool b = false;
		while (tempCount != v.size()) {//전체를 탐색하여 변경될 단어를 찾으면 벡터에 변경할 단어를 대입
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

class SearchWord : public RunWord {//탐색
	bool solve(Page* page, vector<string>& v, int inputFirstNum, int inputSecondNum, string inputFirstWord, string inputSecondWord) {
		int tempCount = 0;
		int tempSize = 0;
		int wordCount = 0;
		while (tempCount < v.size()) {//제일 먼저 단어를 탐색
			if (v[tempCount] == inputFirstWord) {//동일하면 정지
				break;
			}
			if (tempCount == v.size() - 1) {//마지막 탐색까지 없다면 false
				return false;
			}
			if (tempSize + size(v[tempCount]) < 76) {//행을 기준으로 탐색, 75바이트 단위를 사용
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
		//찾은 단어의 행을 기준으로 인덱스 저장
		page->setCount(tempCount - wordCount);
		tempCount = tempCount - wordCount;

		tempSize = 0;
		while (tempCount != 0) {//찾은 단어의 행을 찾는 과정
			for (int i = 0; i < 20; i++) {//20행 기준으로 역순으로 탐색
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
			//기존의 생성된 Page 객체를 사용함
			if (page->getPrev() != NULL) {//이전의 주소가 존재할 때 새로 설정
				page->getPrev()->setCount(tempCount);
				page = page->getPrev();
			}
			else if (tempCount != 0) {//주소가 없다면 새로 객체를 생성하여 주소를 설정
				page->setPrev(new Page(tempCount));
				page = page->getPrev();
			}
			if (tempCount == 0) {//역순 탐색하여 첫번째 인덱스로 온다면 0으로 설정
				page->setPrev(new Page(0));
				return true;
			}
		}
	}
};

class SaveWord : public RunWord {//저장
	bool solve(Page* page, vector<string>& v, int inputFirstNum, int inputSecondNum, string inputFirstWord, string inputSecondWord) {
		remove("test.txt");//기존파일 삭제 후 바뀐 벡터를 파일에 저장
		ofstream myFile("test.txt");
		int i = 0;
		while (i < v.size()) {
			myFile << v[i++] + " ";
		}
		return true;
	}
};

//예외처리 함수 >> 함수 오버로딩을 사용하여 인자에 따라서 검증하는 함수가 다르게 호출
bool checkInput(string input, vector<string> v, int *fn, int *sn, string *w) {//삽입 검증
	vector<string> parseV;
	stringstream ss(input);
	string s;
	try {//양식 검사
		//명령어 틀 검사
		if (input[1] != '(' || input[input.length()-1] != ')' || input.find(",") == string::npos) {
			return false;
		}
		while (getline(ss, s, ',')) {//, 로 분할할 때 검사
			if (s == "") {
				return false;
			}
			parseV.push_back(s);
		}
		if (parseV.size() != 3) {
			return false;
		}
		parseV[0] = parseV[0].erase(0, 2);//각 단어들을 필요 단어로 다시 자름
		
		if (stoi(parseV[0]) > 20) {//20행 이상 검사
			return false;
		}	
		*fn = stoi(parseV[0]);//형변환
		*sn = stoi(parseV[1]);	
		parseV[2] = parseV[2].erase(parseV[2].length() - 1, 1);//75바이트 이상 단어 검사
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

bool checkInput(string input, vector<string> v, int* fn, int* sn) {//삭제 검사
	vector<string> parseV;
	stringstream ss(input);
	string s;

	try {//삽입과 동일
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

bool checkInput(string input, vector<string> v, string* fw, string* sw) {//변경 검사
	vector<string> parseV;
	stringstream ss(input);
	string s;

	try {//단순히 명령어 양식만 검사
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

bool checkInput(string input, vector<string> v, string* fw) {//탐색 검사
	stringstream ss(input);
	string s;

	try {//명령어 양식 검사
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

	//파일을 열어서 벡터에 단어 단위로 삽입
	while (getline(myFile, s, ' ')) {
		v.push_back(s);
	}
	myFile.close();
	//0번째 인덱스부터 시작
	Page *page = new Page(wordCount);
	int* lineCount = new int[20];
	while (1) {//출력
		wordCount = page->getConut();
		
		for (int i = 0; i < 20; i++) {//단어를 75바이트 단위로 출력
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
		for (j = 0; j < 20; j++) {//마지막 페이지 검사를 위한 다음 페이지 반복
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

		if (j < 20) {//20행을 모두 못 채운 경우 >> 마지막 페이지
			page->setNext(new Page(lineCount[j+1]));
			page->getNext()->setPrev(page);
		}
		else {//마지막 페이지가 아닐 경우
			page->setNext(new Page(wordCount));
			page->getNext()->setPrev(page);
		}
		
		for (int i = 0; i < 81; i++) {
			cout << "-";
		}
		cout << "\nn:다음페이지, p:이전페이지, i:삽입, d:삭제, c:변경, s:찾기, t:저장후종료" << endl;
		for (int i = 0; i < 81; i++) {
			cout << "-";
		}
		cout << "\n(콘솔메시지) " << consoleMessage << endl;
		for (int i = 0; i < 81; i++) {
			cout << "-";
		}
		cout << "\n입력 : ";
		cin >> input;
		RunWord* rw = NULL;
		consoleMessage = "";

		//각 명령어에 따른 객체 및 함수 호출
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