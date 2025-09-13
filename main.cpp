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

int main() {
    string binFileName;
    int recordsCount;

    cout << "Enter binary file name: ";
    cin >> binFileName;

    cout << "Enter records count: ";
    cin >> recordsCount;

    string commandLineStr = "Creator.exe " + binFileName + " " + to_string(recordsCount);
    cout << "\nCommand to execute: " << commandLineStr << endl;
    
    char commandLine[200];
    strcpy(commandLine, commandLineStr.c_str());

    STARTUPINFOA si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(STARTUPINFOA));
    si.cb = sizeof(STARTUPINFOA);
    ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));

    cout << "Starting Creator process..." << endl;
    bool isProcessCreated = CreateProcessA(
        NULL,
        commandLine,
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
        cout << "Failed to create Creator process. Error code: " << GetLastError() << endl;
        return 1;
    }

    cout << "Creator process started successfully." << endl;
    WaitForSingleObject(pi.hProcess, INFINITE);
    cout << "\nCreator process finished." << endl;
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    ifstream inFile(binFileName, ios::binary);
    PrintFile(binFileName);

    string reportFileName;
    double hourlyRate;

    cout << "Enter the name of the report file: ";
    cin>> reportFileName;

    cout << "Enter the hourly rate: ";
    cin >> hourlyRate;
    string reporterCmdStr = "Reporter.exe " + binFileName + " " + reportFileName + " " + to_string(hourlyRate);
    char reporterCmd[200];
    strcpy(reporterCmd, reporterCmdStr.c_str());

    STARTUPINFOA siReporter;
    PROCESS_INFORMATION piReporter;

    ZeroMemory(&siReporter, sizeof(STARTUPINFOA));
    siReporter.cb = sizeof(STARTUPINFOA);
    ZeroMemory(&piReporter, sizeof(PROCESS_INFORMATION));

    CreateProcessA(
        NULL,
        reporterCmd,
        NULL,
        NULL,
        FALSE,
        CREATE_NEW_CONSOLE,
        NULL,
        NULL,
        &siReporter,
        &piReporter
    );
    cout << "Waiting for Reporter process to finish..." << endl;
    WaitForSingleObject(piReporter.hProcess, INFINITE);
    CloseHandle(piReporter.hProcess);
    CloseHandle(piReporter.hThread);
    cout << "Reporter process finished." << endl;

    PrintFile(reportFileName);

    cout << "Main process continues..." << endl;

    return 0;
}