#pragma once
#include<iostream>
#include<fstream>
#include<string>
using namespace std;



bool open_file(string& path, string& contents)
{
	cout << "\nPlease enter the path of your file.\nPath: ";
	getline(cin, path);
	ifstream file;
	file.open(path, ios::in);
	if (file)
	{
		getline(std::ifstream(path), contents, '\0');
	}
	else
	{
		return false;
	}
	file.close();
	return true;
}

void write_file(ofstream& file, string& contents)
{
	cout << "Please enter the contents of your file.\nContents: ";
	getline(cin, contents);
	cout << '\n';
	file << contents;
	return;
}

bool create_file(string& path, string& contents)
{
	string filename;
	cout << "Please enter the path of your new file.\nPath: ";
	getline(cin, path);
	cout << "Please enter the name of your new file, including its type.\nFilename: ";
	getline(cin, filename);
	path = path + "\\";
	path = path + filename;
	ofstream file;
	file.open(path, ios::out);
	if (file)
	{
		cout << "File " << filename << " created successfully.\n";
		write_file(file, contents);
	}
	else
	{
		cout << "Error: File " << filename << " could not be created.\n";
		return false;
	}
	file.close();
	return true;
}

bool edit_file(string& contents)
{
	string path;
	string filename;
	cout << "Please enter the path of your file.\nPath: ";
	getline(cin, path);
	cout << "Please enter the name of your file, including its type.\nFilename: ";
	getline(cin, filename);
	path = path + "\\";
	path = path + filename;
	short int choice;
	ofstream file;
	cout << "Do you want to add the new contents to the end or overwrite the existing contents?\n";
	cout << "Enter 1 for first choice, or 0 for second choice.\nChoice: ";
	cin >> choice;
	//Clear input buffer;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	if (choice == 0)
	{
		file.open(path, ios::out);
	}
	else
	{
		file.open(path, ios::app);
	}
	if (file)
	{
		cout << "File " << filename << " opened successfully.\n";
		write_file(file, contents);
	}
	else
	{
		cout << "Error: File " << filename << " could not be opened.\n";
		return false;
	}
	file.close();
	return true;
}

bool transfer(string new_path, string contents)
{
	ofstream new_file;
	new_file.open(new_path, ios::out);
	if (new_file)
	{
		new_file << contents;
	}
	else
	{
		return false;
	}
	new_file.close();
	return true;
}

bool move_file(string old_path, string new_path)
{
	ifstream old_file;
	old_file.open(old_path, ios::in);
	if (old_file)
	{
		ofstream new_file;
		new_file.open(new_path, ios::out);
		if (new_file)
		{
			string contents;
			getline(std::ifstream(old_path), contents, '\0');
			old_file.close();
			remove(old_path.c_str());
			transfer(new_path, contents);
			new_file.close();
			return true;
		}
		new_file.close();
		old_file.close();
		return false;
	}
	old_file.close();
	return false;
}

bool copy_file(string old_path, string new_path)
{
	ifstream old_file;
	old_file.open(old_path, ios::in);
	if (old_file)
	{
		ofstream new_file;
		new_file.open(new_path, ios::out);
		if (new_file)
		{
			string contents;
			getline(std::ifstream(old_path), contents, '\0');
			old_file.close();
			transfer(new_path, contents);
			new_file.close();
			return true;
		}
		new_file.close();
		old_file.close();
		return false;
	}
	old_file.close();
	return false;
}

void destroy_file(string path)
{
	if (remove(path.c_str()) == 0)
	{
		cout << "Deleted successfully.\n";
	}
	else
	{
		cout << "Error: Unable to delete the file.\n";
	}
	return;
}
