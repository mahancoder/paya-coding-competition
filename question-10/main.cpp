#include <iostream>
#include <math.h>

using namespace std;

long double factorial(int start, int end)
{
    long double result = max(start, 1);
    for (int i = result + 1; i <= end; i++) {
        result *= i;
    }
    return result;
}

int main(int argc, char* argv[])
{
    int n, k;
    cout << "n va k ra vared konid: ";
    cin >> n >> k;

    // Formula: (k + n)! / (k! * n!)
    long double top_part = k + n;
    // Simplify the division
    int bigger_one = max(k, n);
    top_part = factorial(bigger_one + 1, top_part);
    cout << endl;
    long double result = top_part / factorial(1, min(n, k));
    cout << result << endl;
    return 0;
}
