#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// needs an input system that reads comma separated numbers

int main(int argc, char* argv[])
{
    int numCount;

    cout << "Tedade adad ha ra vared konid: ";
    cin >> numCount;

    vector<int> numbers(numCount);

    for (int i = 0; i < numCount; i++) {
        cout << "Yek adad vared konid: ";
        cin >> numbers[i];
    }

    sort(numbers.begin(), numbers.end());

    cout << "Adad haye moratab shode: " << endl;

    for (int num : numbers) {
        cout << num << endl;
    }

    return 0;
}
