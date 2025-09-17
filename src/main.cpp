#define _CONSOLE

#include <iostream>
#include <string>
#include <windows.h>
#include <fstream>
#include <cstring>
#include "employee.h"

using namespace std;

void PrintFile(const string& fileName)
{
    ifstream file(fileName, ios::binary);
    if(!file.is_open())
    {
        cout<< "Error: Could not open file" << fileName << endl;
        return;
    }
    cout << file.rdbuf();
    file.close();
}

bool createProcessAndWait(const string& command)
{
    char cmd[200];
    strcpy(cmd, command.c_str());
    STARTUPINFOA si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(STARTUPINFOA));
    si.cb = sizeof(STARTUPINFOA);
    ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));
    bool isProcessCreated = CreateProcessA(
        NULL,
        cmd,
        NULL,
        NULL,
        FALSE,
        CREATE_NEW_CONSOLE,
        NULL,
        NULL,
        &si,
        &pi
    );
    if (!isProcessCreated) {
        cout << "Failed to create process for command: " << command << ". Error code: " << GetLastError() << endl;
        return false; 
    }

    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    return true;

}

int main() {
    string binFileCreatorCmdStr;
    int recordsCount;

    cout << "Enter binary file name: ";
    cin >> binFileCreatorCmdStr;

    cout << "Enter records count: ";
    cin >> recordsCount;

    string commandLineStr = "Creator.exe " + binFileCreatorCmdStr + " " + to_string(recordsCount);
    bool creatorSuccess = createProcessAndWait(commandLineStr);
    if (!creatorSuccess) 
    {
        cout << "Failed to create Creator process." << endl;
        return 1;
    }

    ifstream inFile(binFileCreatorCmdStr, ios::binary);
    PrintFile(binFileCreatorCmdStr);

    string reportFileName;
    double hourlyRate;

    cout << "Enter the name of the report file: ";
    cin>> reportFileName;

    cout << "Enter the hourly rate: ";
    cin >> hourlyRate;
    string reporterCmdStr = "Reporter.exe " + binFileCreatorCmdStr + " " + reportFileName + " " + to_string(hourlyRate);

    bool reporterSuccess = createProcessAndWait(reporterCmdStr);
    if (!reporterSuccess) 
    {
        cout << "Failed to create Reporter process." << endl;
        return 1;
    }
    PrintFile(reportFileName);
    return 0;
}