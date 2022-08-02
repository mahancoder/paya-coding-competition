#include <iostream>
#include <math.h>

using namespace std;

// Reverse a number, eg. 657 --> 756
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
    if (num == 1 || num == 0) {
        return false;
    }
    if (num % 2 == 0)
        return false;
    for (int i = 3; i <= sqrt(num); i += 2) {
        if (num % i == 0) {
            return false;
        }
    }
    return true;
}

int main(int argc, char* argv[])
{
    int N = 0;
    cout << "N ra vared konid: ";
    cin >> N;

    // Value gaurds
    if (N < 1) {
        cout << "N na motabar!" << endl;
        return -1;
    }
    if (N == 1 || N == 2 || N == 3) {
        cout << N << "-omin adad double aval " << (N < 3 ? N + 1 : 5) << " mibashad" << endl;
        return 0;
    }

    int count = 1;
    // Latest prime number
    int num = 2;
    // Check every even number to see if both itself and its reverse are prime
    for (int i = 3; count < N; i += 2) {
        if (isPrime(i) && isPrime(reverse(i))) {
            num = i;
            count++;
        }
    }
    cout << N << "-omin adad double aval " << num << " mibashad" << endl;

    return 0;
}
