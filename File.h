#pragma once
#include<iostream>
#include "BigHex.h"

string extract_name(string old_path)
{
	string name = "";
	int n = old_path.length() - 1;
	int i = n;
	for (; old_path[i] != '\\'; i--) {}
	i++;
	for (; i <= n; i++)
	{
		name = name + old_path[i];
	}
	return name;
}

class File
{
private:
public:
	BigHex file_ID;
	string path;
	File* next;
	File(string hash = garbage, string path = "N/A", File* pointer = nullptr)
	{
		this->file_ID.hex = hash;
		this->path = path;
		this->next = pointer;
	}
	File(File& file)
	{
		this->file_ID.hex = file.file_ID.hex;
		this->path = file.path;
		this->next = file.next;
	}
	File& operator = (File& file)
	{
		this->file_ID.hex = file.file_ID.hex;
		this->path = file.path;
		if (file.next) {

			File* tmp_1 = file.next;
			File* tmp = new File;
			tmp->file_ID = tmp_1->file_ID;
			tmp->path = tmp_1->path;
			this->next = tmp;
			while (tmp_1->next) {
				tmp->next = new File;
				tmp = tmp->next;
				tmp_1 = tmp_1->next;
				tmp->file_ID = tmp_1->file_ID;
				tmp->path = tmp_1->path;
			}
		}
		else {
			this->next = file.next;
		}
		return *this;
	}
	File& operator = (string garbage)
	{
		this->file_ID = garbage;
		this->path = "N/A";
		this->next = nullptr;
		return *this;
	}
	bool operator == (File& file)
	{
		if (this->file_ID == file.file_ID)
		{
			return true;
		}
		return false;
	}
	bool operator != (File& file)
	{
		if (this->file_ID != file.file_ID)
		{
			return true;
		}
		return false;
	}
	bool operator > (File& file)
	{
		if (this->file_ID > file.file_ID)
		{
			return true;
		}
		return false;
	}
	bool operator < (File& file)
	{
		if (this->file_ID < file.file_ID)
		{

			return true;
		}
		return false;
	}
	bool operator >= (File& file)
	{
		if (this->file_ID >= file.file_ID)
		{
			return true;
		}
		return false;
	}
	bool operator <= (File& file)
	{
		if (this->file_ID <= file.file_ID)
		{
			return true;
		}
		return false;
	}
	void insert_next(File& file)
	{
		File* temp = new File(file);
		File* t = this->next;
		if (t == nullptr)
		{
			this->next = temp;
		}
		else
		{
			while (t->next != nullptr)
			{
				t = t->next;
			}
			t->next = temp;
		}
	}
	void del()
	{
		File* temp = this->next;
		while (temp->next != nullptr)
		{
			temp = temp->next;
		}
		delete temp;
		if (temp == this->next) {
			this->next = nullptr;
		}
	}
	void del_nxt()
	{
		while (this->next)
		{
			this->del();
		}
	}
	void print_file()
	{
		cout << "Hash: " << this->file_ID.hex << ", Path: " << this->path ;
		File* tmp = this->next;
		while (tmp) {
			cout << " -> ";
			cout << "Hash: " << tmp->file_ID.hex << ", Path: " << tmp->path ;
			tmp = tmp->next;
		}
		cout << '\n';
		return;
	}
	void transfer(string const_new_path) {
		string tmp = const_new_path;
		tmp = tmp + "\\";
		tmp = tmp + extract_name(this->path);
		move_file(this->path, tmp);
		this->path = tmp;
		File* tmp1 = this->next;
		while (tmp1 != nullptr) {
			string tmp_2 = const_new_path;
			tmp_2 = tmp_2 + "\\";
			tmp_2 = tmp_2 + extract_name(tmp1->path);
			move_file(tmp1->path, tmp_2);
			tmp1->path = tmp_2;
			tmp1 = tmp1->next;
		}
	}
};
