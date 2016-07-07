#include "Dictionary.h"
#include "Board.h"

#include<math.h>
#include<string>
#include<algorithm>
#include<fstream>

using namespace std;

void makeLower(string& s) {
	transform(s.begin(), s.end(), s.begin(), tolower);
}

//int findBoardLength

void initializeBoard(vector<vector<string>>& board) {
	
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
		for (int j = 0; j < brdlenght; j++) {
			column.push_back(letters[itr]);
			itr++;
		}
		board.push_back(column);
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

//-----------------------------------------------------------------------------------------------------------------

int main() {

	string s;
	set<string> dictionary;
	vector<vector<string>> board;

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

//Determine board size
	/*
	string temp;
	int counter = 0;

	in.open("in30b.txt");

	while (in >> temp) {
		counter++;
	}
	int brdlenght = sqrt(counter);
	in.close();
	*/
//Set up board
	initializeBoard(board);

//Print board
	printBoard(board);







	system("pause");
	return 0;
}