#include <algorithm>
#include <iostream>
#include <math.h>
#include <string>

using namespace std;

// Part A
int smallest_larger(int n)
{
    string num = to_string(n);
    int a_index;
    int b_index;
    char largest = 0;
    cout << endl;
    // Start reading the num from right to left
    for (int i = num.size() - 1; i >= 0; i--) {
        // Find the largest digit
        if (num[i] > largest) {
            largest = num[i];
            // The first smaller digit than our largest
        } else if (num[i] < largest) {
            a_index = i;
            char smallest_b = 127;
            // Find the smallest digit to the right of a, that is larger than a (mark it as b)
            for (int j = i; j < num.size(); j++) {
                if (num[j] > num[a_index] && num[j] < smallest_b) {
                    smallest_b = num[j];
                    b_index = j;
                }
            }
            // Swap a and b values
            char temp = num[a_index];
            num[a_index] = num[b_index];
            num[b_index] = temp;
            // Sort digits to the right of b (but not b itself) (since we have swapped, b is now in the position of a)
            sort(num.begin() + a_index + 1, num.end());
            break;
        }
    }
    // If the result is the same, it means it's impossible to do
    int result = stoi(num);
    if (result == n) {
        return -1;
    }
    return result;
}

// Part B
int largest_smaller(int n)
{
    string num = to_string(n);
    int a_index;
    int b_index;
    char smallest = 127;
    cout << endl;
    // Start reading the num from right to left
    for (int i = num.size() - 1; i >= 0; i--) {
        // Find the smallest digit
        if (num[i] < smallest) {
            smallest = num[i];
            // the first larger digit than the our smallest
        } else if (num[i] > smallest) {
            a_index = i;
            char largest_b = 0;
            // Find the largest digit to the right of a that is smaller than a (mark it as b)
            for (int j = i; j < num.size(); j++) {
                if (num[j] < num[a_index] && num[j] > largest_b) {
                    largest_b = num[j];
                    b_index = j;
                }
            }
            // Swap the values of a and b
            char temp = num[a_index];
            num[a_index] = num[b_index];
            num[b_index] = temp;
            // Sort digits to the right of b in descending order (but not b iself) (since we have swapped, b is now in the position of a)
            sort(num.begin() + a_index + 1, num.end(), greater<>());
            break;
        }
    }
    // If the result is the same, it means it's impossible
    int result = stoi(num);
    if (result == n) {
        return -1;
    }
    return result;
}

int main(int argc, char* argv[])
{
    int input;
    cout << "Adad ra vared konid: ";
    cin >> input;
    int smallest = smallest_larger(input);
    int largest = largest_smaller(input);
    cout << "A: " << (smallest == -1 ? "impossible" : to_string(smallest)) << endl;
    cout << "B: " << (largest == -1 ? "impossible" : to_string(largest)) << endl;
    return 0;
}
