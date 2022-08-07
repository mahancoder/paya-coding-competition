#include <iostream>
#include <math.h>
#include <string.h>
#include <bits/stdc++.h>

using namespace std;

string findSmallestPermutation(string s);
 
int main()
{
    // take number input in string
    string num;
	cout << "Addad ra vared konid: ";
	cin >> num;

    cout << "Addade moratab shode: " << findSmallestPermutation(num) << endl;

    return 0;
}

// return the smallest number permutation
string findSmallestPermutation(string s)
{
    int len = s.length();
 
    // sort the string
    sort(s.begin(), s.end());
 
    // check for leading zero in string
    // if there are any leading zeroes,
    // swap the first zero with first non-zero number
    int i = 0;

    while (s[i] == '0')
        i++;
     
    swap(s[0], s[i]);

    return s;
}