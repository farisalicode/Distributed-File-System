#pragma once
#include<iostream>
#include "DHT.h"
using namespace std;



void IPFS()
{
    cout << "\"Bad programmers worry about the code. Good programmers\nworry about data structures and their relationships.\"\n\nLinus Torvalds\n\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    system("cls");
    DHT dht;
    char choice = ' ';
    while (choice != 'x')
    {
        cout << "\nPlease select an operation from the below given ones.\n\n";
        cout << "A: Add a machine.\n";
        cout << "B: Remove a machine.\n";
        cout << "C: Add a file.\n";
        cout << "D: Remove a file.\n";
        cout << "E: Print all the machines.\n";
        cout << "F: Print a specific file.\n";
        cout << "G: Print the routing table of a specific machine.\n";
        cout << "H: Print the B-Tree of a specific machine.\n";
        cout << "I: Print the DHT details.\n";
        cout << "X: To exit.\n";
        cout << "Z: Clear the console.\n";
        cout << "Choice: ";
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (choice == 'a'|| choice =='A')
        {
            dht.add_machine();
        }
        else if (choice == 'b' || choice == 'B')
        {
            dht.remove_machine();
        }
        else if (choice == 'c' || choice == 'C')
        {
            dht.add_file();
        }
        else if (choice == 'd' || choice == 'D')
        {
            dht.remove_file();
        }
        else if (choice == 'e' || choice == 'E')
        {
            dht.ring.print_ring();
        }
        else if (choice == 'f' || choice == 'F')
        {
            dht.print_file();
        }
        else if (choice == 'g' || choice == 'G')
        {
            dht.print_machine_routing_table();
        }
        else if (choice == 'h' || choice == 'H')
        {
            dht.print_machine_b_Tree();
        }
        else if (choice == 'i' || choice == 'I')
        {
            dht.print_details();
        }
        else if (choice == 'z' || choice == 'Z')
        {
            system("cls");
        }
    }
    return;
}
