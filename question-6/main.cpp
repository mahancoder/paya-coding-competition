#include <algorithm>
#include <cctype>
#include <iostream>
#include <math.h>
#include <string>
#include <unordered_map>

using namespace std;

const unordered_map<string, int> days = {
    { "saturday", 0 },
    { "sunday", 1 },
    { "monday", 2 },
    { "tuesday", 3 },
    { "wednesday", 4 },
    { "thursday", 5 },
    { "friday", 6 }
};
const unordered_map<int, int> month_length = {
    { 1, 31 },
    { 2, 31 },
    { 3, 31 },
    { 4, 31 },
    { 5, 31 },
    { 6, 31 },
    { 7, 30 },
    { 8, 30 },
    { 9, 30 },
    { 10, 30 },
    { 11, 30 },
    { 12, 30 }
};

int main(int argc, char* argv[])
{
    string day;
    int day_in_week;
    int first_month;
    int first_date;
    int second_date;
    int second_month;
    cout << "Rooz va tarikh ra vared konid: ";
    cin >> first_date >> first_month >> day;
    cout << "Tarikh na maloom ra vared konid: ";
    cin >> second_date >> second_month;
    cout << endl;
    // Lowercase the day
    transform(day.begin(), day.end(), day.begin(),
        [](unsigned char c) { return tolower(c); });
    try {
        day_in_week = days.at(day);
    } catch (const out_of_range&) {
        cout << "Rooz na motabar!" << endl;
        return -1;
    }
    int days_past;

    if (first_month == second_month) {
        // If they are both in the same month
        days_past = second_date - first_date;
    } else if (second_month > first_month) {
        // If we are going forwards
        days_past = (month_length.at(first_month) - first_date) + second_date;
        for (int i = first_month + 1; i < second_month; i++) {
            days_past += month_length.at(i);
        }
    } else {
        // If we are going backwards
        days_past = -(month_length.at(second_month) - second_date + first_date);
        for (int i = first_month - 1; i > second_month; i--) {
            days_past -= month_length.at(i);
        }
    }
    // Calculate the new day in the week
    int new_day_in_week = (7 + (day_in_week + (days_past % 7))) % 7;
    string new_day;
    // Find the new day's name
    for (auto& day : days) {
        if (day.second == new_day_in_week) {
            new_day = day.first;
            break;
        }
    }
    // Upper case first letter
    new_day[0] = toupper(new_day[0]);
    cout << new_day << endl;
    return 0;
}
