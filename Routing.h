#pragma once
#include<iostream>
#include "BigHex.h"
#include "Ring.h"



class Node;

class Route_Entry
{
private:
public:
	//ith index of finger table.
	int ftp_idx;
	BigHex machine_id;
	Node* machine_address;
	Route_Entry* next;
	Route_Entry* prev;
	Route_Entry()
	{
		this->ftp_idx = -1;
		this->machine_id.hex = garbage;
		this->machine_address = nullptr;
		this->next = nullptr;
		this->prev = nullptr;
	}
	Route_Entry(int ftp_idx)
	{
		this->ftp_idx = ftp_idx;
		this->machine_id.hex = garbage;
		this->machine_address = nullptr;
		this->next = nullptr;
		this->prev = nullptr;
	}
};

class Routing_Table
{
private:
public:
	Route_Entry* head;
	Route_Entry* tail;
	Routing_Table()
	{
		this->head = nullptr;
		this->tail = nullptr;
	}
	void add(int ftp_idx)
	{
		Route_Entry* temp = new Route_Entry(ftp_idx);
		if (this->head == nullptr && this->tail == nullptr)
		{
			this->head = temp;
			this->tail = temp;
		}
		else
		{
			this->tail->next = temp;
			temp->prev = this->tail;
			this->tail = temp;
		}
		return;
	}
	void make_entries(int identifier_space)
	{
		for (int i = 1;i <= identifier_space; ++i)
		{
			this->add(i);
		}
		return;
	}
	void print_table()
	{
		Route_Entry* curr = this->head;
		for (int i = 1; curr != nullptr; ++i)
		{
			cout << "Index: " << curr->ftp_idx << ", Next Machine ID: " << curr->machine_id.hex << ", Machine Address: " << curr->machine_address << '\n';
			curr = curr->next;
		}
		cout << '\n';
		return;
	}
};
