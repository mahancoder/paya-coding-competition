#include <algorithm>
#include <iostream>
#include <math.h>
#include <string>

using namespace std;

int smallest_larger(int n)
{
    string num = to_string(n);
    int a_index;
    int b_index;
    char largest = 0;
    cout << endl;
    for (int i = num.size() - 1; i >= 0; i--) {
        if (num[i] > largest) {
            largest = num[i];
        } else if (num[i] < largest) {
            a_index = i;
            char smallest_b = 127;
            for (int j = i; j < num.size(); j++) {
                if (num[j] > num[a_index] && num[j] < smallest_b) {
                    smallest_b = num[j];
                    b_index = j;
                }
            }
            char temp = num[a_index];
            num[a_index] = num[b_index];
            num[b_index] = temp;
            sort(num.begin() + a_index + 1, num.end());
            break;
        }
    }
    int result = stoi(num);
    if (result == n) {
        return -1;
    }
    return result;
}

int largest_smaller(int n)
{
    string num = to_string(n);
    int a_index;
    int b_index;
    char smallest = 127;
    cout << endl;
    for (int i = num.size() - 1; i >= 0; i--) {
        if (num[i] < smallest) {
            smallest = num[i];
        } else if (num[i] > smallest) {
            a_index = i;
            char largest_b = 0;
            for (int j = i; j < num.size(); j++) {
                if (num[j] < num[a_index] && num[j] > largest_b) {
                    largest_b = num[j];
                    b_index = j;
                }
            }
            char temp = num[a_index];
            num[a_index] = num[b_index];
            num[b_index] = temp;
            sort(num.begin() + a_index + 1, num.end(), greater<>());
            break;
        }
    }
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
