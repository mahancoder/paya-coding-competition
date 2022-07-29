#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/* needs an input system that reads comma separated numbers */

int main(){
    int vectorLength;

    cout << "Tedade adad ha ra vared konid: ";
    cin >> vectorLength;

    vector<int> numbers(vectorLength);

    for (int i = 0; i <= vectorLength - 1; i++){
        int newNum;

        cout << "Yek adad vared konid: ";
        cin >> newNum;

        numbers.at(i) = newNum;
    }

    std::sort(numbers.begin(), numbers.end());

    cout << "Adad haye moratab shode: " << endl;
    
    for(int i = 0; i <= vectorLength - 1; i++){
        cout << numbers.at(i) << endl;
    }

    return 0;
}