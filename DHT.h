#pragma once
#include<iostream>
#include<cstdlib>
#include<cmath>
#include<string>
#include "Hashing.h"
#include "File_Handling.h"
#include "File.h"
#include"Ring.h"
using namespace std;

class DHT
{
private:
public:
    long long int max_num_machines;
    long long int curr_num_machines;
    int identifier_space;
    int b_tree_order;
    Ring ring;
    DHT()
    {
        short int option = 1;
        cout << "\nWelcome to our Distributed Hash Table (DHT) system!\n\n";
        cout << "Press Enter to continue.\n\n";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Please enter the maximum number of machines in the DHT.\nMaximum number of machines: ";
        cin >> this->max_num_machines;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        this->curr_num_machines = 0;
        cout << "Please enter the size of the identifier space.\nSize of identifier space: ";
        cin >> this->identifier_space;
        this->ring.set_identifier_space(this->identifier_space);
        identifier_size_bighex = this->identifier_space;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Please enter the order (greater than 2) of you B-trees.\nOrder of B-trees: ";
        cin >> this->b_tree_order;
        while (this->b_tree_order < 3) {
            cout << "Please enter the order (greater than 2) of you B-trees.\nOrder of B-trees: ";
            cin >> this->b_tree_order;
        }
        this->ring.set_b_tree_order(this->b_tree_order);
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        string command = mkdir;
        command += machines_folder;
        system(command.c_str());
        system("cls");
    }
    void add_machine()
    {
        if (this->curr_num_machines < this->max_num_machines)
        {
            if (this->ring.insert() == true)
            {
                cout << "New machine added to the system successfully.\n";
                ++this->curr_num_machines;
                this->ring.update_tables();
            }
            else
            {
                cout << "Error: Duplicate ID machines are not allowed.\n";
            }
        }
        else
        {
            cout << "Error: Number of maximum possible machines has been reached, remove a machine to add a new one.\n";
        }
        return;
    }
    void remove_machine()
    {
        BigHex machine_ID;
        cout << "\nPlease enter the ID of the machine you want to delete from the ring.\nMachine's ID: ";
        getline(cin, machine_ID.hex);
        if (this->curr_num_machines > 0)
        {
            if(this->ring.remove(machine_ID) == true)
            {
                cout << "Machine removed from the system successfully.\n";
                --this->curr_num_machines;
                if (this->curr_num_machines > 0)
                {
                    this->ring.update_tables();
                }
                else {
                    this->ring.head = nullptr;
                    this->ring.tail = nullptr;
                }

            }
        }
        else
        {
            cout << "Error: No machines in the system right now, add a new machine to remove one.\n";
        }
        return;
    }
    void add_file()
    {
        if (this->ring.head != nullptr) {
            string old_path;
            string new_path;
            string file_name;
            string contents;
            bool invalid_file_path_chk = true;
            while (invalid_file_path_chk == true)
            {
                if (open_file(old_path, contents))
                {
                    invalid_file_path_chk = false;
                    BigHex hash;
                    BigHex machine_ID;
                    hash.hex = hash_generator(contents, this->identifier_space);
                    cout << "Please enter the ID of the starting machine.\nMachine ID: ";
                    getline(cin, machine_ID.hex);
                    file_name = extract_name(old_path);
                    Node* curr_machine = this->ring.search_file(hash, machine_ID);
                    if (curr_machine != nullptr)
                    {
                        new_path = curr_machine->data.path;
                        new_path += '\\';
                        new_path += file_name;
                        File newfile(hash.hex, new_path);
                        newfile.print_file();
                        if (copy_file(old_path, new_path) == true)
                        {
                            curr_machine->data.b_tree.insert(newfile);
                        }
                    }
                }
                else
                {
                    cout << "Error: An invalid file path was entered.\n";
                }
            }
        }

        else {
            cout << "\n";
            cout << "No machine in the system, please add a machine.\n";
            
        }

        return;
    }
    void remove_file()
    {
        if (this->ring.head != nullptr) {
            BigHex hash;
            BigHex machine_ID;
            string path;
            cout << "\nPlease enter the ID of the file you want to delete.\nFile ID: ";
            getline(cin, hash.hex);
            cout << "Please enter the ID of the starting machine.\nMachine ID: ";
            getline(cin, machine_ID.hex);
            Node* curr_machine = this->ring.search_file(hash, machine_ID);
            if (curr_machine != nullptr)
            {
                File dummy;
                File* file;
                dummy.file_ID = hash.hex;
                file = curr_machine->data.b_tree.search_b_tree_ret_file(dummy);
                if (file != nullptr)
                {
                    while (file != nullptr) {
                        remove(file->path.c_str());
                        file = file->next;
                    }

                    curr_machine->data.b_tree.del(dummy);
                }
            }
            else {
                cout << "File not found" << endl;
            }
        }
        else {
            cout << endl << "The ring is empty" << endl;
        }
       
        return;
    }
    void print_machine_b_Tree()
    {
        if (this->ring.head != nullptr) {
            BigHex ID;
            cout << "\nPlease enter the ID of the machine whose B-Tree you want to print.\nMachine ID: ";
            getline(cin, ID.hex);
            Node* ans = this->ring.get_machine(ID);
            if (ans != nullptr)
            {
                ans->data.b_tree.print_b_tree();
            }
            else
            {
                cout << "Error: The machine given could not be found.\n";
            }
        }
        else {
            cout << endl << "The ring is empty" << endl;
        }
        
        return;
    }
    void print_machine_routing_table()
    {
        if (this->ring.head != nullptr) {
            BigHex ID;
            cout << "\nPlease enter the ID of the machine whose routing table you want to print.\nMachine ID: ";
            getline(cin, ID.hex);
            Node* ans = this->ring.get_machine(ID);
            if (ans != nullptr)
            {
                ans->data.routing_table.print_table();
            }
            else
            {
                cout << "Error: The machine given could not be found.\n";
            }
        }
        else {
            cout << endl << "The ring is empty" << endl;
        }
       
        return;
    }
    void print_details()
    {
        cout << "\n\n";
        cout << "Printing DHT details;\n";
        cout << "Identifier space size: " << this->identifier_space << '\n';
        cout << "Maximum number of machines allowed: " << this->max_num_machines << '\n';
        cout << "Current number of machines in the system: " << this->curr_num_machines << '\n';
        cout << "Order of B-trees in the system: " << this->b_tree_order;
        cout << "\n\n";
        return;
    }
    void print_file()
    {
        if (this->ring.head != nullptr) {
            BigHex file_id;
            cout << "\nPlease enter the ID of the file you want to print.\File ID: ";
            getline(cin, file_id.hex);
            BigHex machine_id;
            cout << "Please enter the ID of the starting machine.\nMachine ID: ";
            getline(cin, machine_id.hex);
            Node* ans = this->ring.search_file(file_id, machine_id);
            if (ans != nullptr)
            {
                File dummy;
                File* fptr = nullptr;
                dummy.file_ID.hex = file_id.hex;
                fptr = ans->data.b_tree.search_b_tree_ret_file(dummy);
                if (fptr != nullptr)
                {
                    cout << "Printing file;\n";
                    fptr->print_file();
                }
                else
                {
                    cout << "Error: The specified file could not be found.\n";
                }
            }
            else
            {
                cout << "Error: The machine given could not be found.\n";
            }
        }
        else {
            cout <<endl<< "The ring is empty" << endl;
        }
        
        return;
    }
    ~DHT()
    {
        cout << "\nThank you for using our Distributed Hash Table (DHT) system!\n\n";
        cout << "Press Enter to continue.\n\n";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        string command = rmdir;
        command += machines_folder;
        system(command.c_str());
        system("cls");
        system("cls");
    }
};
