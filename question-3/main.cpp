#include <iostream>
#include <math.h>

using namespace std;

int main(int argc, char* argv[])
{
    int years, increase_percentage;
    cout << "Tedad sal va darsad afzayesh hoghoogh ra vared konid: ";
    cin >> years >> increase_percentage;
    // Formula: (((present / past) ^ 1 / years) - 1) * 100
    cout << "Miangin darsad afzayesh saliane: " << ceil((pow((100 + increase_percentage) / 100.0, 1.0 / years) - 1.0) * 100) << endl;
    return 0;
}
