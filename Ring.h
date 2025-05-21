#pragma once
#include <iostream>
#include "BigHex.h"
#include "Hashing.h"
#include "Machine.h"
using namespace std;

class Node 
{
private:
public:
	Machine data;
	Node* next;
	Node()
	{
		this->next = nullptr;
	}
	Node(Machine& data,Node* next = nullptr) 
	{
		this->data = data;
		this->next = next;
	}
};

class Ring 
{
private:
public:
	Node* head;
	Node* tail;
	int identifier_space;
	int b_tree_order;
	Ring() 
	{
		this->head = nullptr;
		this->tail = nullptr;
		this->identifier_space = 4;
		this->b_tree_order = 3;
	}
	void set_identifier_space(int identifier_space)
	{
		this->identifier_space = identifier_space;
		if (this->identifier_space < 4)
		{
			this->identifier_space = 4;
		}
		else if (this->identifier_space > 160)
		{
			this->identifier_space = 160;
		}
		return;
	}
	void set_b_tree_order(int b_tree_order)
	{
		this->b_tree_order = b_tree_order;
		return;
	}
	bool insert() 
	{
		Machine newmachine(true);
		if (newmachine.machine_ID.hex == garbage)
		{
			newmachine.machine_ID.hex = hash_generator(newmachine.name, this->identifier_space);
		}
		Node* temp = new Node(newmachine);
		temp->data.path = machines_folder;
		temp->data.path += "\\";
		temp->data.path += temp->data.name;
		string command = mkdir;
		command += temp->data.path;
		system(command.c_str());
		temp->data.routing_table.make_entries(this->identifier_space);
		temp->data.b_tree.set_order(this->b_tree_order);
		if (this->head == nullptr && this->tail == nullptr) 
		{
			this->head = temp;
			this->tail = temp;
			this->head->next = tail;
			this->tail->next = head;
		}
		else 
		{
			if (temp->data.machine_ID < this->head->data.machine_ID)
			{
				this->tail->next = temp;
				temp->next = this->head;
				File dummy;
				dummy.file_ID.hex = temp->data.machine_ID.hex;
				File tail_dummy;
				tail_dummy.file_ID.hex = this->tail->data.machine_ID.hex;
				transfer_file_to_new_head(temp->data.b_tree, tail_dummy, dummy, this->head->data.b_tree, temp->data.path);
				
				this->head = temp;
			}
			else if(temp->data.machine_ID > this->tail->data.machine_ID)
			{
				this->tail->next = temp;
				temp->next = this->head;
				File tail_dummy;
				tail_dummy.file_ID.hex = this->tail->data.machine_ID.hex;

				this->tail = temp;

				File dummy;
				dummy.file_ID.hex = temp->data.machine_ID.hex;
				transfer_file_to_new_tail_head(temp->data.b_tree, tail_dummy, dummy, this->head->data.b_tree, temp->data.path);
			}
			else
			{
				Node* curr = this->head;
				Node* prev = this->head;
				while (temp->data.machine_ID >= curr->data.machine_ID)
				{
					if (temp->data.machine_ID == curr->data.machine_ID)
					{
						return false;
					}
					prev = curr;
					curr = curr->next;
				}
				

				temp->next = prev->next;
				prev->next = temp;
				File dummy;
				dummy.file_ID.hex = temp->data.machine_ID.hex;
				transfer_b_tree_files(temp->data.b_tree, dummy, temp->next->data.b_tree, temp->data.path);
			}
		}
		return true;
	}
	bool remove(BigHex& ID) 
	{
		if (this->head != nullptr && this->tail != nullptr)
		{
			Node* temp = nullptr;
			if (this->head->data.machine_ID.hex == ID.hex)
			{
				temp = this->head;
				if (this->head != this->tail) {
				transfer_file_tail_head(temp->next->data.b_tree, temp->data.b_tree, temp->next->data.path);
				}
				//possible change
				this->head = this->head->next;
				this->tail->next = this->head;
			}
			else if (this->tail->data.machine_ID.hex == ID.hex)
			{
				Node* curr = this->head;
				Node* prev = this->head;
				while (curr != this->tail)
				{
					prev = curr;
					curr = curr->next;
				}
				temp = curr;
				if (this->head != this->tail) {
					transfer_file_tail_head(temp->next->data.b_tree, temp->data.b_tree, temp->next->data.path);
				}
				this->tail = prev;
				this->tail->next = curr->next;
			}
			else
			{
				Node* curr = this->head;
				Node* prev = this->head;
				do
				{
					prev = curr;
					curr = curr->next;
				} 
				while (curr->data.machine_ID.hex != ID.hex && curr != this->head);
				if (curr == this->head) {
					return false;
				}
				temp = curr;
				File dummy;
				dummy.file_ID.hex = temp->next->data.machine_ID.hex;
				transfer_b_tree_files(temp->next->data.b_tree, dummy, temp->data.b_tree, temp->next->data.path);
				prev->next = curr->next;
			}
			if (temp != nullptr)
			{
				string command = rmdir;
				command = rmdir + temp->data.path;
				system(command.c_str());
				delete temp;
				return true;
			}
		}
		return false;
	}
	Node* get_machine(BigHex& machine_ID)
	{
		Node* ans = nullptr;
		Node* curr = this->head;
		do
		{
			if (curr->data.machine_ID.hex == machine_ID.hex)
			{
				ans = curr;
				break;
			}
			curr = curr->next;
		} 
		while (curr != this->head);
		return ans;
	}
	Node* get_previous_machine(BigHex& machine_ID)
	{
		Node* ans = nullptr;
		Node* curr = this->head;
		do
		{
			if (curr->next->data.machine_ID.hex == machine_ID.hex)
			{
				ans = curr;
				break;
			}
			curr = curr->next;
		} 
		while (curr != this->head);
		return ans;
	}
	void print_ring()
	{
		if (this->head != nullptr) {
			Node* curr = this->head;
			cout << "\nPrinting ring network;\n";
			do
			{
				curr->data.print_machine();
				curr = curr->next;
			} while (curr != this->head);
		}
		else {
			cout << endl << "The ring is empty" << endl;
		}
		
		return;
	}
	void update_tables()
	{
		Node* curr = this->head;
		Node* temp_curr;
		do
		{
			temp_curr = curr;
			this->generate_table(curr);
			curr = temp_curr;
			curr = curr->next;
		} 
		while (curr != this->head);
		return;
	}
	void print_all_tables()
	{
		if (this->head != nullptr) {
			Node* curr = this->head;
			do
			{
				cout << "Printing Routing Table of Machine " << curr->data.machine_ID.hex << ":\n";
				curr->data.routing_table.print_table();
				curr = curr->next;
			} while (curr != this->head);
		}
		else {
			cout << endl << "The ring is empty" << endl;;
		}
		
	}
	void generate_table(Node*& curr)
	{
		BigHex mod_val = pow(2,this->identifier_space,this->identifier_space);
		Route_Entry* ith_entry = curr->data.routing_table.head;
		BigHex finger_formula;
		Node* temp_curr;
		for (int i = 0; i < this->identifier_space && ith_entry != nullptr; ++i)
		{
			BigHex power = pow(2, i, this->identifier_space);
			finger_formula = curr->data.machine_ID + power;
			temp_curr = curr;
			if (finger_formula > this->tail->data.machine_ID && finger_formula < mod_val)
			{
				curr = this->head;
			}
			else
			{
				if (finger_formula > this->tail->data.machine_ID && finger_formula >= mod_val)
				{
					finger_formula = finger_formula % mod_val;
				}
				curr = this->head;
				do
				{
					if (curr->data.machine_ID >= finger_formula)
					{
						break;
					}
					curr = curr->next;
				} 
				while (curr->data.machine_ID < finger_formula && curr != this->head);
			}
			ith_entry->ftp_idx = i + 1;
			ith_entry->machine_id = curr->data.machine_ID;
			ith_entry->machine_address = curr;
			ith_entry = ith_entry->next;
			curr = temp_curr;
		}
		return;
	}
	Node* search_file(BigHex& file_ID, BigHex& starting_machine_ID)
	{
		Node* ans = nullptr;
		bool is_second_cond_true = false;
		if (file_ID > this->tail->data.machine_ID || file_ID < this->head->data.machine_ID)
		{
			ans = this->head;
			cout << "Correct machine Found: " << ans->data.machine_ID.hex << ".\n";
			return ans;
		}
		else
		{
			Node* curr = this->head;
			do
			{
				if (curr->data.machine_ID == starting_machine_ID)
				{
					break;
				}
				curr = curr->next;
			} while (curr != this->head);
			Node* temp_curr = curr;

			while (true) {
				cout << "At machine " << curr->data.machine_ID.hex << " right now.\n";
				Route_Entry* ftpptr = curr->data.routing_table.head;

				if (is_second_cond_true == true) {

					cout << "Correct machine Found: " << curr->data.machine_ID.hex << "\n";
					return curr;

				}
				if (curr->data.machine_ID == file_ID)
				{
					ans = curr;
					cout << "Correct machine Found: " << ans->data.machine_ID.hex << "\n";
					return ans;
				}
				else if (ftpptr->machine_id != curr->data.machine_ID && curr->data.machine_ID < file_ID && file_ID <= ftpptr->machine_id)
				{
					curr = ftpptr->machine_address;
					is_second_cond_true = true;
					continue;
				}
				else
				{
					bool found = false;
					while (ftpptr->next != nullptr)
					{
						if (ftpptr->machine_id != curr->data.machine_ID && file_ID > ftpptr->machine_id && file_ID <= ftpptr->next->machine_id)
						{
							curr = ftpptr->machine_address;
							found = true;
							break;
						}
						ftpptr = ftpptr->next;
					}
					if (found == true) {
						continue;
					}

					if (found == false)
					{
						if (file_ID == ftpptr->machine_id) {
							curr = ftpptr->machine_address;
							is_second_cond_true = true;
							continue;
						}

						if (file_ID > ftpptr->machine_id) {
							curr = ftpptr->machine_address;
							continue;
						}

						else {
							curr = curr->data.routing_table.head->machine_address;
							continue;
						}


					}
				}

			}

		}
		return ans;
	}
};
