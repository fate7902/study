#include <iostream>
#include <string>
using namespace std;

int main() {
    string str, grade;
    double credit;
    double total_grade = .0f, total_credit = .0f;
    for(int i = 0; i < 20; ++i) {
        cin >> str >> credit >> grade;
        total_credit += credit;
        if (!grade.compare("A+")) total_grade += (4.5f * credit);
        if (!grade.compare("A0")) total_grade += (4.0f * credit);
        if (!grade.compare("B+")) total_grade += (3.5f * credit);
        if (!grade.compare("B0")) total_grade += (3.0f * credit);
        if (!grade.compare("C+")) total_grade += (2.5f * credit);
        if (!grade.compare("C0")) total_grade += (2.0f * credit);
        if (!grade.compare("D+")) total_grade += (1.5f * credit);
        if (!grade.compare("D0")) total_grade += (1.0f * credit);
        if (!grade.compare("P")) total_credit -= credit;
    }
    cout << fixed;
    cout.precision(6);
    cout << total_grade / total_credit;
}