#include <iostream>
#include <math.h>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[])
{
    int degree;
    vector<int> coefficients;
    cout << "Daraje ra vared konid: ";
    cin >> degree;
    cout << endl << "Zarib ha ra vared konid: ";
    for (int i = 0; i <= degree ; i++) {
        int c = 0;
        cin >> c;
        coefficients.push_back(c);
    }
    cout << endl;
    // Find all the roots (non-negative integers less than 11)
    vector<int> roots;
    for (int i = 0; i < 11; i++) {
        int result = 0;
        for (int j = degree; j >= 0 ; j--) {
            result += coefficients[degree - j] * pow(i, j);
        }
        if (result == 0)
        {
            roots.push_back(i);
        }
    }
    // Build the polynomial
    string poly("");
    if (coefficients[0] > 1)
    {
        poly += to_string(coefficients[0]) + " * "; 
    }
    for(int root : roots)
    {
        poly += ("(x - " + to_string(root) + ") * ");
    }
    // Replace (x - 0) withjust x
    if (poly.find("(x - 0)") != string::npos)
    {
        poly.replace(poly.find("(x - 0)"), 7, "x");
    }
    // Remove the last " * "
    poly = poly.substr(0, poly.size() - 3);
    cout << "Tajzie: " << poly << endl;
    return 0;
}
