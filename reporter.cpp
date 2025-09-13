#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include "employee.h"

using namespace std;

bool compareEmployees(const employee& emp1, const employee& emp2)
{
    return emp1.num < emp2.num;
}

int main(int argc, char *argv[])
{
    string fileName = argv[1];
    string reporterName = argv[2];
    double hourlyRate = stod(argv[3]);
    ifstream inFile(fileName, ios::binary);

    vector<employee> employees;
    employee temp;
    while(inFile.read((char*)&temp, sizeof(employee)))
    {
        employees.push_back(temp);
    }
    inFile.close();
    sort(employees.begin(), employees.end(), compareEmployees);
    ofstream outFile(reporterName);
    if (!outFile) {
        cout << "Error creating report file: " << reporterName << endl;
        return 1;
    }
    outFile << "Report for file \"" << fileName << "\"\n";
    outFile << left;
    outFile << setw(10) << "ID"
            << setw(15) << "Name"
            << setw(10) << "Hours"
            << setw(15) << "Salary" << endl;
    outFile << "-----------------------------------------------------\n";
    outFile << fixed << setprecision(2); 
    for (const auto& emp : employees) {
        double salary = emp.hours * hourlyRate;
        outFile << setw(10) << emp.num
                << setw(15) << emp.name
                << setw(10) << emp.hours
                << setw(15) << salary << endl;
    }
    
    outFile.close();
    cout << "Report file '" << reporterName << "' created successfully.\n";
    return 0;
}



