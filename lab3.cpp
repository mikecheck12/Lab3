#include<iostream>
#include<math.h>
#include<string>
#include<algorithm>
#include<fstream>
#include<vector>
#include<set>

using namespace std;

void makeLower(string& s) {
        transform(s.begin(), s.end(), s.begin(), ::tolower);
}

void initializeBoard(vector<vector<string>>& board, vector<vector<bool>>& boolBoard, char* argv[]) {
	
	string temp;
	vector<string> letters;
	int counter = 0;
	int brdlenght;

	ifstream in;
        in.open(argv[2]);

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

//Output function
void printBoardandAnswers(vector<vector<string>> board, vector<string>& answerList, char* argv[]) {

    ofstream out;
    out.open(argv[3]);
	
	for (int i = 0; i < board.size(); i++) {
		for (int j = 0; j < board.size(); j++) {
                        out << board[i][j];
			if (j != board.size() - 1) {
                                out << " ";
			}
		}
                out << endl;
	}
//Print Answers
        sort(answerList.begin(), answerList.end());
        out << endl;

        for (int i = 0; i < answerList.size(); i++) {
                out << answerList[i] << endl;
        }
        out.close();
}
//Dictionary Search
void searchDictionary(set<string> dictionary, vector<string>& answerList, string pre){
    if (dictionary.find(pre) != dictionary.end()) {
            if(find(answerList.begin(), answerList.end(), pre) == answerList.end())
            answerList.push_back(pre);
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
                                        if (pre.length() > 3) {		// find in dictionary and add to vector
                                                searchDictionary(dictionary, answerList, pre);
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

//Wrapper - iterates through each position
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

int main(int argc, char* argv[]) {

	string s;
	set<string> dictionary;
	vector<vector<string>> board;
	vector <vector<bool>> boolBoard;
	string pre;
	vector<string> answerList;

//Open and get dictionary data

	ifstream in;
        in.open(argv[1]);

	while (in >> s) {
		makeLower(s);
		dictionary.insert(s);
	}
	in.close();

//Set up board
        initializeBoard(board, boolBoard, argv);


//Run
	recStart(pre, board, boolBoard, dictionary, answerList);
	
//Print board
        printBoardandAnswers(board, answerList, argv);

	return 0;
}
