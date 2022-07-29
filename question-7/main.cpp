#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char* argv[])
{
    int numCount;

    cout << "Tedade adad ha ra vared konid: ";
    cin >> numCount;

    vector<int> numbers(numCount);

    cout << "Adad ha ra vared konid: ";

    for (int i = 0; i < numCount; i++) {
        cin >> numbers[i];
    }

    sort(numbers.begin(), numbers.end());

    cout << "Adad haye moratab shode: " << endl;

    for (int num : numbers) {
        cout << num << ' ';
    }
    cout << endl;

    return 0;
}
