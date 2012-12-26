#include <math.h>
#include <iostream>
#include <assert.h>

using namespace std;
// implement log_2 using sqrt only, assuming the input is at least 1.  
// Idea: 'index' binary search. For example, log_2(27). We know it is 
// between 4 and 5. 
//
float log_2(const float x, const float precision = 1.0e-006 )
{
	// the left and right boundary of the normal-space
	float leftVal = 1.0f, midVal, rightVal=2.0f;

	// the left and right boundary of the log-space
	float left = 0.0f, mid, right=1.0f; 

	// determine the left and right boundary that contains log_2(x) s.t
	// right - left = 1
	while (x > rightVal) 
	{
		right += 1;
		rightVal *= 2;
	}
	left = right - 1;
	leftVal = rightVal / 2;

	// perform the binary search in log-space while updating the 
	// corresponding mid point in normal space.
	while (rightVal - leftVal > precision)
	{
		midVal = sqrt(leftVal * rightVal);
		mid = (left + right)/2;

		if (midVal < x)
		{
			left = mid; 
			leftVal = midVal;
		}
		else
		{
			right = mid; 
			rightVal = midVal;
		}	
	}

	return mid;
}

void main() {
	const float log_e_2 = log(2.0f);
	float test[] = {1.0f, 1.4f, 2.0f, 3.0f, 4.0f, 6.5f, 32.33f};

	for (size_t i = 0; i < 6 ; i++) {
		assert(abs(log_2(test[i]) - log(test[i])/log_e_2) < 1.0e-006);
	}
}

