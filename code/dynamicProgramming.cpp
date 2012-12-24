#include <set>
#include <vector>
#include <iostream>

using namespace std;

/**
	Given a M x N rectangular with some obstacle in some nodes. How many unique
	paths are there from the top left to bottom right corner? Some of the cells have 
	obstacle which prevent one from passing through it. 

	Three dynamic programming solutions of increasing efficiency is precented here. 
	Here, A[i][j] is the number of unique paths from cell(0,0) to cell(i,j). 

	The solution is to compute the easy partial solution along the first row and then extend
	the solution to the next row until we completely filled up the matrix A. Once it is 
	filled, the solution is just at the right-bottom cell of A. 
**/
// O(M*N) Space version
int numUniquePaths_2D(const set<pair<int, int>> obstacles, const int N, const int M)
{
    vector<vector<int>> A (N, vector<int> (M, 0));
    
	// fill in the boundary condition along the first row
    A[0][0] = 1;
	pair<int, int> cell = make_pair(0,0);
    for (int i = 1; i < M; i++) {
		cell.first = 0;
		cell.second = i;
        if (obstacles.find(cell) == obstacles.end())
            A[0][i] = 1;
        else
            break;
	}
    
    for (int i = 1; i < N; i++) {
		cell.first = i;
		cell.second = 0;
        if (obstacles.find(cell) == obstacles.end())
            A[i][0] = 1;
        else
            break; 
	}
                 
	/**
	 fill up the table
	 **/
    for (int i = 1; i < N; i++)
        for (int j = 1; j < M; j++) {
            pair<int, int> cell = make_pair(i,j);
            if (obstacles.find(cell) == obstacles.end())
                A[i][j] += A[i-1][j] + A[i][j-1];
        }
        
    return A[N-1][M-1];
        
}


/** 
	space optimized version: Here we only need to keep track of previous and currow 
	rows that we need in the current iterations. 
**/
int numUniquePaths_2Rows(set<pair<int, int>> obstacles, const int N, const int M)
{
    vector<int> pre (M, 0);
    
	// fill in the boundary condition along the first row
    int curRowNumber = 0;
	pair<int, int> cell = make_pair(0,0); 
    pre[0] = 1;
    for (int i = 1; i < M; i++) {
        cell.first = 0;
		cell.second = i;
        if (obstacles.find(cell) == obstacles.end())
            pre[i] = 1;
        else
            break;
	}

	/**
	 maintain the solution in the previous and current rows.
	 **/
    vector<int> cur (M,0);    
    while (curRowNumber < N-1) {
        curRowNumber++;
        for (int j = 0; j < M; j++) {
             cell.first = curRowNumber;
             cell.second = j;
             cur[j] = 0;
             if (obstacles.find(cell) == obstacles.end())
                cur[j] += pre[j];
             if (j != 0 && (obstacles.find(cell) == obstacles.end()))
                cur[j] +=cur[j-1]; 
        }
        swap(pre, cur);
    }  
                         
    return pre[M-1];   
}


/* the previous solution keep tracks of two rows of information. However, at any point
   in time, we only need to keep track of the "right-portion" of the previous row and the
   "left-portion" of the current row. */
int numUniquePaths_1Row(set<pair<int, int>> obstacles, const int N, const int M)
{
    vector<int> V (M, 0);
	V[0] = 1; 
    int row = 0;

	// process the first row
	pair<int, int> cell = make_pair(0,0);
    for (int i = 1; i < M; i++) {
		cell.first = 0;
		cell.second = i;
        if (obstacles.find(cell) == obstacles.end())
            V[i] = 1;
        else
            break;
	}

	/* keep track and maintain the "right-portion" of the previous row and the
       "left-portion" of the current row. 
	*/
	row = 1;
	for (; row < N; row++) {
		for (int col = 0; col < M; col++) {
             cell.first = row;
             cell.second = col;

			 int cur = 0;
             if (obstacles.find(cell) == obstacles.end())
                cur += V[col];
             if (col != 0 && (obstacles.find(cell) == obstacles.end()))
                cur +=V[col-1]; 
			 V[col] = cur;
        }
	}
                         
    return V[M-1];     
}

void main() {
	set<pair<int, int>> obstacles;
	cout << numUniquePaths_2D(obstacles, 3, 3) << endl;
	cout << numUniquePaths_2Rows(obstacles, 3, 3) << endl;
	cout << numUniquePaths_1Row(obstacles, 3, 3) << endl;

	obstacles.insert(make_pair(1, 1));
	cout << numUniquePaths_2D(obstacles, 4, 4) << endl;
	cout << numUniquePaths_2Rows(obstacles, 4, 4) << endl;
	cout << numUniquePaths_1Row(obstacles, 4, 4) << endl;

	obstacles.insert(make_pair(2, 3));
	cout << numUniquePaths_2D(obstacles, 5, 5) << endl;
	cout << numUniquePaths_2Rows(obstacles, 5, 5) << endl;
	cout << numUniquePaths_1Row(obstacles, 5, 5) << endl;
}
