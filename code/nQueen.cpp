#pragma once
#include <set>
#include <vector>
#include <list>
#include <iostream>

using namespace std;
/*
8.	N-Queens
The n-queens puzzle is the problem of placing n queens on an n×n chessboard such that no two queens attack each other.
Given an integer n, return all distinct solutions to the n-queens puzzle.
Each solution contains a distinct board configuration of the n-queens' placement, where 'Q' and '.' both indicate a queen and an empty space respectively.
For example,
There exist two distinct solutions to the 4-queens puzzle:
[
 [".Q..",  // Solution 1
  "...Q",
  "Q...",
  "..Q."],

 ["..Q.",  // Solution 2
  "Q...",
  "...Q",
  ".Q.."]
]
*/
struct Dominated {
	set<int> col;
	set<int> dig_TL_BR;
	set<int> dig_TR_BL;
};


void NQueen(const int N, 
			int curRow, 
			Dominated domPos,
			vector<int> &placement, 
			list<vector<int>> &result) {

	if (curRow == N) {
		result.push_back(placement);
		return;
	}

	for (int j = 0; j < N; j++) {
		if (domPos.col.find(j) == domPos.col.end() && 
			domPos.dig_TL_BR.find(j + curRow)  == domPos.dig_TL_BR.end() && 
			domPos.dig_TR_BL.find(N-1-j + curRow) == domPos.dig_TR_BL.end()) {

			// place the queen and update the dominated positions.
			placement.push_back(j);
			domPos.col.insert(j);
			domPos.dig_TL_BR.insert(j + curRow);
			domPos.dig_TR_BL.insert(N - 1 - j + curRow);

			// make the next move in the next row
			NQueen(N, curRow + 1, domPos, placement, result);

			// undo placement of the queen and update the dominated positions. 
			placement.pop_back();
			domPos.col.erase(j);
			domPos.dig_TL_BR.erase(j + curRow);
			domPos.dig_TR_BL.erase(N - 1 - j +curRow);
		}
	}
}


void printResult(const list<vector<int>> &result) {
	for (list<vector<int>>::const_iterator p = result.begin(); p != result.end(); p++) {
		vector<int> soln = *p;
		for (size_t i = 0; i < soln.size(); i++) {
			cout << "\t";
			for (size_t j = 0; j < soln.size(); j++) {
				cout << ((soln[i] == j) ? "Q" : ".");
			}
			cout << endl;
		}
		cout << endl;
	}
}


void main() {
	Dominated domPos;
	vector<int> placement;
	list<vector<int>> result;

	NQueen(4, 0, domPos, placement, result);
	printResult(result);

	NQueen(5, 0, domPos, placement, result);
	printResult(result);
}
