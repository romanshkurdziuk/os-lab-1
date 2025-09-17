#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include <fstream>
#pragma pack(push, 1)

using namespace std;
struct employee
{
    int num;
    char name[10];
    double hours;

    void write(ofstream& outFile)
    {
        outFile.write((char*)this, sizeof(employee));
    }

    ifstream& read(ifstream& inFile)
    {
        inFile.read((char*)this, sizeof(employee));
        return inFile;
    }

    bool operator<(const employee& other) const
    {
        return this->num < other.num;
    }
};
#pragma pack(pop)

#endif // EMPLOYEE_H