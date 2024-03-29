#include <iostream>
#include <assert.h>
#include <stack>
#include <math.h>

using namespace std;
/*
Divide Two Positive Integers

Divide two integers without using multiplication, division and mod operator.
*/

int divide(const unsigned int x, const unsigned int y)
{
    if (y == 0) {
        throw "divide by zero error";
    }

    unsigned int a = y;
    unsigned int b = x;

    while (b >= a)
    {
        unsigned int tmp = a << 1;
        if (tmp < a) { // integer overflow
            throw "integer overflow";
        a = tmp;
    }
   
    unsigned int result = 0;
    while (a >= y)
    {
        result = result << 1;
        if (b >= a)
        {
            b -= a;
            result++;
        }

        a = a >> 1; // divide a by 2
    }
    return result;
}


void main() {
    assert(divide(0, 2) == 0/2);
    assert(divide(1, 3) == 1/3);

    assert(divide(4, 2) == 4/2);
    assert(divide(5, 2) == 5/2);
    assert(divide(4, 3) == 4/3);
    assert(divide(14, 5) == 14/5);
    assert(divide(2031, 31) == 2031/31);

    bool exceptionThrown = false;
    try {
        divide(123, 0);
    }
    catch (const char *e)
    {
        printf("Exception %s\n", e);
        exceptionThrown = true;
    }
    assert(exceptionThrown);

    try {
        divide(MAX_INT - 10, 10);
    }
    catch (const char *e)
    {
        printf("Exception %s\n", e);
        exceptionThrown = true;
    }
    assert(exceptionThrown);

    cout << "All tests passed!" << endl;

}
