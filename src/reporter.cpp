#include <iostream>
#include <fstream>
#include <string>
#include <vector>     
#include <algorithm>  
#include <iomanip>   
#include "employee.h" 
using namespace std;

int main(int argc, char* argv[]) {
   if (argc != 4) {
        cout << "Invalid arguments.\n";
        cout << "Usage: Reporter.exe <binary_file> <report_file> <hourly_rate>\n";
        return 1;
    }

    string binFileName = argv[1];
    string reportFileName = argv[2];
    double hourlyRate = stod(argv[3]); 
    ifstream inFile(binFileName, ios::binary);
    if (!inFile) {
        cout << "Error opening binary file: " << binFileName << endl;
        return 1;
    }

    vector<employee> employees;
    employee temp;
    while (temp.read(inFile))
    {
        employees.push_back(temp);
    }
    inFile.close();
    sort(employees.begin(), employees.end());

    ofstream outFile(reportFileName);
    if (!outFile) {
        cout << "Error creating report file: " << reportFileName << endl;
        return 1;
    }

    outFile << "Report for file \"" << binFileName << "\"\n";
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
    return 0;
}