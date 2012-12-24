#include <vector>
#include <iostream>
#include <assert.h>

using namespace std;
/*
Best Time to Buy and Sell Stock

Say you have an array for which the ith element is the price of a given stock on day i.

If you were only permitted to complete at most one transaction (ie, buy one and sell one share of the stock), 
design an algorithm to find the maximum profit.

The idea here is to 
1. maintain a current min and current max. Initially both have A[0] as their values. They are 
updated as we scan the next element. 
2. When we have a new max value, we check if current max - current min is greater than the 'bestSoFar'. 
3. When we have a new min value, we start all over by also setting max to the new min. 
*/
pair<int, int> bestTimeToBuyAndSell(const vector<int> &A)
{
	if (A.empty()) {
		return make_pair(-1,-1);
	}

	int curMin = 0;
	int curMax = 0;
	int start = 0;
	int end = 0;

	for (size_t i = 0; i < A.size(); i++)
	{
		if (A[i] > A[curMax]) {
			curMax = i;	
			if (A[curMax] - A[curMin] >= A[end] - A[start])           
			{
				end=curMax;
				start=curMin;
			}
		}
		else if (A[i] <= A[curMin])
		{
			curMin = i;
			curMax = i;
		}
	}
	return make_pair(start, end);

}


void main() {
		
	// Case 1: test when the vector is empty
	vector<int> V0;
	pair<int, int> timing =  bestTimeToBuyAndSell(V0);
	cout << "Case 0: Buy at " << timing.first << " sell at " << timing.second << endl;
	assert(timing.first == -1);
	assert(timing.second == -1);
		
	// Case 2: test when the vector only has 1 entry
	vector<int> V1
	V1.push_back(1);
	timing =  bestTimeToBuyAndSell(V1);
	cout << "Case 1: Buy at " << timing.first << " sell at " << timing.second << endl;
	assert(timing.first == 0);
	assert(timing.second == 0);

	// Case 3: test when all entries have the same values
	int tmp2[] = {1,1,1,1,1,1,1};	
	vector<int> V2 (tmp2, tmp2+7);
	timing =  bestTimeToBuyAndSell(V2);
	cout << "Case 2: Buy at " << timing.first << " sell at " << timing.second << endl;
	assert(timing.first == 0);
	assert(timing.second == 0);

	// Case 4: test when the chart looks like a 'slanted N'
	int tmp3[] = {101,103,105,101,102,102,110,100};
	vector<int> V3 (tmp3, tmp3+8);
	timing =  bestTimeToBuyAndSell(V3);
	cout << "Case 3: Buy at " << timing.first << " sell at " << timing.second << endl;
	assert(timing.first == 3);
	assert(timing.second == 6);

	// Case 5: test when the best solution occurs after Case 4.
	int tmp4[] = {101,103,105,101,102,102,100,52,59,86};	
	vector<int> V4 (tmp4, tmp4+10);
	timing =  bestTimeToBuyAndSell(V4);
	cout << "Case 4: Buy at " << timing.first << " sell at " << timing.second << endl;
	assert(timing.first == 7);
	assert(timing.second == 9);
}
