#include<iostream>
#include<math.h>
#include<string>
#include<algorithm>
#include<fstream>
#include<vector>
#include<set>

using namespace std;

void makeLower(string& s) {
	transform(s.begin(), s.end(), s.begin(), tolower);
}

void initializeBoard(vector<vector<string>>& board, vector<vector<bool>>& boolBoard) {
	
	string temp;
	vector<string> letters;
	int counter = 0;
	int brdlenght;

	ifstream in;
	in.open("in30b.txt");

	while (in >> temp) {
		makeLower(temp);
		letters.push_back(temp);
		counter++;
	}

	brdlenght = sqrt(counter);

	in.close();

	int itr = 0;

	for (int i = 0; i < brdlenght; i++) {
		vector<string> column;
		vector<bool> boolColumn;
		for (int j = 0; j < brdlenght; j++) {
			column.push_back(letters[itr]);
			boolColumn.push_back(0);
			itr++;
		}
		board.push_back(column);
		boolBoard.push_back(boolColumn);
	}
}

void printBoard(vector<vector<string>> board) {
	
	for (int i = 0; i < board.size(); i++) {
		for (int j = 0; j < board.size(); j++) {
			cout << board[i][j];
			if (j != board.size() - 1) {
				cout << " ";
			}
		}
		cout << endl;
	}
}

void printBoolBoard(vector<vector<bool>> boolBoard) {

	for (int i = 0; i < boolBoard.size(); i++) {
		for (int j = 0; j < boolBoard.size(); j++) {
			cout << boolBoard[i][j];
			if (j != boolBoard.size() - 1) {
				cout << " ";
			}
		}
		cout << endl;
	}
}


//Recursive check function
void rec(int row, int col, string pre, vector<vector<string>> board, vector<vector<bool>> boolBoard, set<string>& dictionary, vector<string>& answerList) {
	

	if (row < 0 || row >= boolBoard.size() || col < 0 || col >= boolBoard.size() || boolBoard[row][col] == 1) {
		return;
	}
	else {
		boolBoard[row][col] = 1;
		pre = pre + board[row][col];
		auto itr = dictionary.lower_bound(pre);
		
		if (itr != dictionary.end() && pre == (*itr).substr(0, pre.length())) {
					if (pre.length() > 3) {							// find in dictionary and add to vector
						if (dictionary.find(pre) != dictionary.end()) {
							if(find(answerList.begin(), answerList.end(), pre) == answerList.end())
							answerList.push_back(pre);
						}
					}
			rec(row - 1, col, pre, board, boolBoard, dictionary, answerList);
			rec(row - 1, col + 1, pre, board, boolBoard, dictionary, answerList);
			rec(row, col + 1, pre, board, boolBoard, dictionary, answerList);
			rec(row + 1, col + 1, pre, board, boolBoard, dictionary, answerList);
			rec(row + 1, col, pre, board, boolBoard, dictionary, answerList);
			rec(row + 1, col - 1, pre, board, boolBoard, dictionary, answerList);
			rec(row, col - 1, pre, board, boolBoard, dictionary, answerList);
			rec(row - 1, col - 1, pre, board, boolBoard, dictionary, answerList);
		}
		else {

			return;
			}
	  }
}

//Print Answers
void printAnswers(vector<string>& answerList) {
	sort(answerList.begin(), answerList.end());
	cout << endl;
	for (int i = 0; i < answerList.size(); i++) {
		cout << answerList[i] << endl;
	}
}

//wrapper function goes through each position
void recStart(string pre, vector<vector<string>> board, vector<vector<bool>> boolBoard, set<string>& dictionary, vector<string>& answerList){
	
	int row;
	int col;

	for(row = 0; row < board.size(); row++){
		for (col = 0; col < board.size(); col++) {
			rec(row, col, pre, board, boolBoard, dictionary, answerList);
		}
	}
}


//--------------------------------------------------------------------------------------------------------------------

int main() {

	string s;
	set<string> dictionary;
	vector<vector<string>> board;
	vector <vector<bool>> boolBoard;
	string pre;
	vector<string> answerList;

//Open and get dictionary data

	ifstream in;
	in.open("in30a.txt");

	while (in >> s) {
		makeLower(s);
		dictionary.insert(s);
	}
	in.close();

	//cerr << dictionary.size() << endl;
	//cerr << dictionary.count("blue") << endl;

//Set up board
	initializeBoard(board, boolBoard);

//Print board
	printBoard(board);

//Print boolBoard
	//printBoolBoard(boolBoard);

//Run
	//rec(0, 0, pre, board, boolBoard, dictionary, answerList);

	/*
	int row;
	int col;

	for (row = 0; row < board.size(); row++) {
		for (col = 0; col < board.size(); col++) {
			cout << row << " " << col << endl;
			//rec(row, col, pre, board, boolBoard, dictionary, answerList);
		}
	}
	*/
	//cout << row << " " << col << endl;
	//rec(row, col, pre, board, boolBoard, dictionary, answerList);

	recStart(pre, board, boolBoard, dictionary, answerList);
	
//Print Answers
	printAnswers(answerList);



	system("pause");
	return 0;
}