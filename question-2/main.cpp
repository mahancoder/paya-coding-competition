#include <iostream>

using namespace std;

int reverseDigits(int num);

int main()
{
	int num;
	
	cout << "Adad ra vared konid: ";
	cin >> num;

	num = reverseDigits(num);

	cout << num << endl;

	return 0;
}

// function for reversing digits of an int
int reverseDigits(int num)
{
    int rev_num = 0;
    while (num > 0) {
        rev_num = rev_num * 10 + num % 10;
        num = num / 10;
    }
    return rev_num;
}