#define _CONSOLE

#include <iostream>
#include <string>
#include <windows.h>
#include <cstring>

using namespace std;

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

    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(STARTUPINFO));
    si.cb = sizeof(STARTUPINFO);
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

    cout << "Main process continues..." << endl;

    return 0;
}