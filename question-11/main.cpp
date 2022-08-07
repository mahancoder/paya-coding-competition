#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

// 2^n digits repeat every 4 times
const int two_cyclic_digits[] = { 2, 4, 8, 6 };
// Get the last digit of 2^n
inline int unit_digit_of_2_expo(int expo)
{
    return two_cyclic_digits[(expo - 1) % 4];
}

// Factorial of 0-4
const int fact_map[] = { 1, 1, 2, 6, 24 };

int unit_digit_fact(int n)
{
    // the floor of 1/5th of n
    int n_5th_floor = floor(n / 5);
    // If n is small...
    if (n_5th_floor < 5) {
        // Run the formula on it directly
        return (fact_map[n_5th_floor] * unit_digit_of_2_expo(n_5th_floor) * fact_map[n % 5]) % 10;
    } else {
        // Otherwise make it small
        // This variable stores the digits in the process of making it small
        int others = 1;
        while (n_5th_floor > 4) {
            others = (unit_digit_of_2_expo(n_5th_floor) * fact_map[n % 5] * others) % 10;
            n = n_5th_floor;
            n_5th_floor = floor(n_5th_floor / 5);
        }
        // Run the formula
        return (fact_map[n_5th_floor] * unit_digit_of_2_expo(n_5th_floor) * fact_map[n % 5] * others) % 10;
    }
}
int main(int argc, char* argv[])
{
    int n = 0;
    cout << "n ra vared konid: ";
    cin >> n;
    cout << endl;
    cout << unit_digit_fact(n) << " avalin ragham na sefr dar " << n << "! mibashad"  << endl;
    return 0;
}
