#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct employee
 {
    int num;
    char name[10]; 
    double hours; 
 };

 int main(int argc, char *argv[])
 {
    string fileName = argv[1];
    int countEntries = stoi(argv[2]);
    ofstream file(fileName, ios::binary);
    for (int i = 0; i < countEntries; ++i)
    {
        employee emp;
        cout << "Enter data for employee " << i + 1 <<" ..." << endl;
        cout << "Enter indentical number: ";
        cin >> emp.num;
        cout << "Enter name of employee (max 10 characters): ";
        cin >> emp.name;
        cout << "Enter hours worked: ";
        cin >> emp.hours;
        file.write((char*)&emp, sizeof(employee));
        cout << "-----------------------------------------" << endl;
    }
    file.close();
    return 0;
 }