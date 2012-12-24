#include <iostream>
#include <assert.h>
using namespace std;

/*
'.' Matches any single character.
'*' Matches zero or more of the preceding element.

The matching should cover the entire input string (not partial).
*/
bool isMatch(const char *s, const char *p) {
	if (*p == '\0')
		return *s == '\0';

	if (*(p+1) == '*')
	{
		// map * is match to empty string 
		if (isMatch(s,p+2))
			return true;

		// match * with increasing length of valid substrings
		while ((*p == '.' || *p == *s) && s!='\0')
		{
			s++;
			if (isMatch(s, p+2))
				return true;
		}
	}
	// match single character
	else if (*p == '.' || *p == *s)
		return isMatch(s+1,p+1);
	return false;
}


void main() {
	// test basic matching without operator
	assert(isMatch("", "") == true);
	assert(isMatch("a", "a") == true);

	assert(isMatch("a", "") == false);
	assert(isMatch("a", "b") == false);
	assert(isMatch("", "b") == false);

	// test basic operator
	assert(isMatch("b", ".") == true);
	assert(isMatch("aaa", "a*") == true);
	assert(isMatch("abcd", ".*") == true);

	// test more complex matching
	assert(isMatch("abcde","ab*cde") == true);
	assert(isMatch("abcde","ab*cde") == true);
	assert(isMatch("abcde","ab*cddde") == false);
	assert(isMatch("abcde","a.*") == true);
	assert(isMatch("aa","a") == false);
	assert(isMatch("aa","aa") == true);
	assert(isMatch("aaa","aa") == false);
	assert(isMatch("aa", "a*") == true);
	assert(isMatch("abcde", ".*") == true);
	assert(isMatch("aab", "c*a*b") == true);
}
