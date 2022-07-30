#include <iostream>
#include <math.h>
using namespace std;
inline int reverse(int num)
{
    int remainder = 0, reversed_number = 0;
    while (num != 0) {
        remainder = num % 10;
        reversed_number = reversed_number * 10 + remainder;
        num /= 10;
    }
    return reversed_number;
}

inline bool isPrime(int num)
{
    if (num == 1 || num == 0)
    {
        return false;
    }
    if (num % 2 == 0) return false;
    for (int i = 3; i <= sqrt(num); i += 2) {
        if (num % i == 0)
        {
            return false;
        }
    }
    return true;
}

int main (int argc, char *argv[])
{
    int N = 0;
    cout << "Enter N: ";
    cin >> N;

    int count = 1;
    int num = 2;
    for (int i = 3; count < N; i += 2) {
        if (isPrime(i) && isPrime(reverse(i)))
        {
            num = i;
            count++;
        }
    }
    cout << "Num is: " << num << endl;

    return 0;
}
