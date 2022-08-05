#include <iostream>
#include <math.h>

using namespace std;

// Find the decade the number is in (the 10 base power + 1)
inline int find_decade(int n, int& sum_before)
{
    int digits = 0;
    int sum = 0;
    int result = 1;
    while (digits < n) {
        digits = result * 9 * pow(10, result - 1);
        sum += digits;
        result++;
    }
    // Result is off by one
    result--;
    // Make sum have the sum of all decades before our decade
    sum -= digits;
    sum_before = sum;
    return result;
}

int main(int argc, char* argv[])
{
    int n;
    cout << "n ra vared konid: ";
    cin >> n;
    cout << endl;
    int sum_bfore = 0;
    int decade = find_decade(n, sum_bfore);
    // Eg. If you want the 11th digit, it means the 2nd digit in the 2 decade, and 2nd is the value stored here
    int n_digit_in_decade = n - sum_bfore;
    // Eg. If you want the 11th digit, It will be part of the 1st number of the 2 decade, and 1st is stored here
    int n_number_in_decade = ceil(static_cast<double>(n_digit_in_decade) / decade);
    // Eg. If you want the 11th digit, It will be part of 10, and 10 is stored in here
    int num = (n_number_in_decade - 1) + pow(10, decade - 1);
    int digit = static_cast<int>(num / pow(10, decade - ((n_digit_in_decade - 1) % decade) - 1)) % 10; // Calculate the digit
    cout << n << "-omin adad donbale: " << digit << endl;
    return 0;
}
