#pragma once
#include<iostream>
#include<string>
#include "BigHex.h"
#include "Routing.h"
#include "B_tree.h"
using namespace std;



class Machine
{
private:
public:
    BigHex machine_ID;
    string name;
    string path;
    Routing_Table routing_table;
    B_tree b_tree;
    Machine()
    {
        this->machine_ID = garbage;
        this->name = "N/A";
        this->path = "N/A";
    }
    Machine(bool inputs_constructor)
    {
        cout << '\n';
        short int option = 1;
        cout << "\nPlease enter the name of the new machine to be inserted.\nMachine's name: ";
        getline(cin, this->name);
        cout << "Would like to enter the machine's ID manually or have it automatically assigned by the hashing algorithm.\n";
        cout << "Enter 1 for manual assignment, or 0 for automatic assignment.\nOption: ";
        cin >> option;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (option == 0)
        {
            this->machine_ID.hex = garbage;
        }
        else
        {
            cout << "Please enter the ID of the new machine to be inserted.\nMachine's ID: ";
            getline(cin,machine_ID.hex);
        }
        cout << '\n';
    }
    Machine(BigHex machine_ID, string name,string path)
    {
        this->machine_ID = machine_ID;
        this->name = name;
        this->path = path;
    }
    Machine(const Machine& machine)
    {
        this->machine_ID = machine.machine_ID;
        this->name = machine.name;
        this->path = machine.path;
    }
    Machine& operator= (const Machine& machine)
    {
        this->machine_ID = machine.machine_ID;
        this->name = machine.name;
        this->path = machine.path;
        return *this;
    }
    void print_machine()
    {
        cout << "ID: " << this->machine_ID.hex << '\n';
        cout << "Name: " << this->name << '\n';
        cout << "Path: " << this->path << '\n';
        return;
    }
};
