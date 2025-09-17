#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include <iostream>
#include <fstream>
#pragma pack(push, 1)

using namespace std;
struct employee
{
    int num;
    char name[10];
    double hours;

    void write(ostream& os)
    {
        os.write((char*)this, sizeof(employee));
    }

    istream& read(istream& is)
    {
        is.read((char*)this, sizeof(employee));
        return is;
    }

    bool operator<(const employee& other) const
    {
        return this->num < other.num;
    }
};
#pragma pack(pop)

#endif // EMPLOYEE_H