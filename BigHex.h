#pragma once
#include<iostream>
using namespace std;
string garbage = "-1";
string mkdir = "mkdir ";
string rmdir = "rmdir /s ";
string machines_folder = "IPFS_Machines";
int identifier_size_bighex = 4;



class BigHex {
public:
	string hex;

	BigHex(string str) {
		hex = str;
		//str_binary = "";
	}

	BigHex() {
		hex = "";
	}

	string convert_to_binary() {
		//A4B4016089A8C6B22E76C40EC40F9702E67B3B00
		string str_binary = "";
		int size = hex.length();
		for (int i = 0; i < size; i++) {
			if (hex[i] == '0') {
				str_binary += "0000";
			}
			else if (hex[i] = '1') {
				str_binary += "0001";
			}
			else if (hex[i] = '2') {
				str_binary += "0010";
			}
			else if (hex[i] = '3') {
				str_binary += "0011";
			}
			else if (hex[i] = '4') {
				str_binary += "0100";
			}
			else if (hex[i] = '5') {
				str_binary += "0101";
			}
			else if (hex[i] = '6') {
				str_binary += "0110";
			}
			else if (hex[i] = '7') {
				str_binary += "0111";
			}
			else if (hex[i] = '8') {
				str_binary += "1000";
			}
			else if (hex[i] = '9') {
				str_binary += "1001";
			}
			else if (hex[i] = 'A') {
				str_binary += "1010";
			}
			else if (hex[i] = 'B') {
				str_binary += "1011";
			}
			else if (hex[i] = 'C') {
				str_binary += "1100";
			}
			else if (hex[i] = 'D') {
				str_binary += "1101";
			}
			else if (hex[i] = 'E') {
				str_binary += "1110";
			}
			else if (hex[i] = 'F') {
				str_binary += "1111";
			}
		}
		return str_binary;
	}

	string convert_to_binary(string hex) { //overloaded function
		//A4B4016089A8C6B22E76C40EC40F9702E67B3B00
		string str_binary = "";
		int size = hex.length();
		for (int i = 0; i < size; i++) {
			if (hex[i] == '0') {
				str_binary += "0000";
			}
			else if (hex[i] == '1') {
				str_binary += "0001";
			}
			else if (hex[i] == '2') {
				str_binary += "0010";
			}
			else if (hex[i] == '3') {
				str_binary += "0011";
			}
			else if (hex[i] == '4') {
				str_binary += "0100";
			}
			else if (hex[i] == '5') {
				str_binary += "0101";
			}
			else if (hex[i] == '6') {
				str_binary += "0110";
			}
			else if (hex[i] == '7') {
				str_binary += "0111";
			}
			else if (hex[i] == '8') {
				str_binary += "1000";
			}
			else if (hex[i] == '9') {
				str_binary += "1001";
			}
			else if (hex[i] == 'A') {
				str_binary += "1010";
			}
			else if (hex[i] == 'B') {
				str_binary += "1011";
			}
			else if (hex[i] == 'C') {
				str_binary += "1100";
			}
			else if (hex[i] == 'D') {
				str_binary += "1101";
			}
			else if (hex[i] == 'E') {
				str_binary += "1110";
			}
			else if (hex[i] == 'F') {
				str_binary += "1111";
			}
		}
		return str_binary;
	}

	string convert_to_hex(string bin) {
		string binary = "";

		int add = bin.length() % 4;

		while (add > 0 && add < 4) {
			binary += "0";
			add++;
		}
		int i = 0;
		while (bin[i] != '\0') {
			binary += bin[i];
			i++;
		}
		//cout << "ch: " << binary << endl;
		int index = 0;
		i = 0;
		string hex2 = "";
		//cout << "bin length: " << binary.length();
		while (i != binary.length()) {
			//cout << "h\n";
			if (binary[i] == '0' && binary[i + 1] == '0' && binary[i + 2] == '0' && binary[i + 3] == '0') {
				hex2 += '0';
			}
			else if (binary[i] == '0' && binary[i + 1] == '0' && binary[i + 2] == '0' && binary[i + 3] == '1') {
				hex2 += '1';
			}
			else if (binary[i] == '0' && binary[i + 1] == '0' && binary[i + 2] == '1' && binary[i + 3] == '0') {
				hex2 += '2';
			}
			else if (binary[i] == '0' && binary[i + 1] == '0' && binary[i + 2] == '1' && binary[i + 3] == '1') {
				hex2 += '3';
			}
			else if (binary[i] == '0' && binary[i + 1] == '1' && binary[i + 2] == '0' && binary[i + 3] == '0') {
				hex2 += '4';
			}
			else if (binary[i] == '0' && binary[i + 1] == '1' && binary[i + 2] == '0' && binary[i + 3] == '1') {
				hex2 += '5';
			}
			else if (binary[i] == '0' && binary[i + 1] == '1' && binary[i + 2] == '1' && binary[i + 3] == '0') {
				hex2 += '6';
			}
			else if (binary[i] == '0' && binary[i + 1] == '1' && binary[i + 2] == '1' && binary[i + 3] == '1') {
				hex2 += '7';
			}
			else if (binary[i] == '1' && binary[i + 1] == '0' && binary[i + 2] == '0' && binary[i + 3] == '0') {
				hex2 += '8';
			}
			else if (binary[i] == '1' && binary[i + 1] == '0' && binary[i + 2] == '0' && binary[i + 3] == '1') {
				hex2 += '9';
			}
			else if (binary[i] == '1' && binary[i + 1] == '0' && binary[i + 2] == '1' && binary[i + 3] == '0') {
				hex2 += 'A';
			}
			else if (binary[i] == '1' && binary[i + 1] == '0' && binary[i + 2] == '1' && binary[i + 3] == '1') {
				hex2 += 'B';
			}
			else if (binary[i] == '1' && binary[i + 1] == '1' && binary[i + 2] == '0' && binary[i + 3] == '0') {
				hex2 += 'C';
			}
			else if (binary[i] == '1' && binary[i + 1] == '1' && binary[i + 2] == '0' && binary[i + 3] == '1') {
				hex2 += 'D';
			}
			else if (binary[i] == '1' && binary[i + 1] == '1' && binary[i + 2] == '1' && binary[i + 3] == '0') {
				hex2 += 'E';
			}
			else if (binary[i] == '1' && binary[i + 1] == '1' && binary[i + 2] == '1' && binary[i + 3] == '1') {
				hex2 += 'F';
			}

			i += 4;
		}
		//cout << hex2 << endl;
		return hex2;
	}

	BigHex subtract_one(int ids = 8) {
		int s1 = this->hex.size();
		//s1 = s1 * 4;
		string twos_comp;
		for (int i = 0; i < ids; i++) {
			twos_comp += "1";
		}

		BigHex subber;
		subber.hex = convert_to_hex(twos_comp);
		BigHex result = ((*this) + subber);
		//cout << result.hex[0] << " " << result.hex[1] << " " << result.hex[2] << endl;
		return ((*(this)) + subber);
	}

	//BigHex pow(int base, int power, int m) { //m is no of bits in identifier space
	//	//we have to apply left shift power no of times
	//	//copy binary string to another string but from 
	//	string binary = "";

	//	for (int i = 0; i < m - 1; i++) {
	//		binary += "0";
	//	}

	//	binary += "1";
	//	/*cout << binary << endl;*/

	//	string temp_binary = "";
	//	for (int i = 0; i < power; i++) {
	//		for (int j = 1; j < m; j++) {
	//			temp_binary += binary[j];
	//		}
	//		temp_binary += "0";
	//		binary = temp_binary;
	//		/*cout << binary << endl;*/
	//		temp_binary = "";
	//	}
	//	//cout << "binary: " << binary << endl;
	//	string hex_ret = "";
	//	hex_ret = convert_to_hex(binary);
	//	//cout << "hex: "<<hex_ret<<endl;

	//	BigHex temp(hex_ret);

	//	return temp;
	//}


	BigHex operator+(BigHex& b) {
		string string_1 = convert_to_binary(b.hex);
		string string_2 = convert_to_binary(this->hex);

		/*cout << "binary _ checking: " << string_1 << endl;
		cout << "binary _ testing: " << string_2 << endl;*/

		int size = string_1.size();

		int last_index = size - 1;
		string* result = new string[size];
		char c = '0';
		while (last_index >= 0) {
			if (string_1[last_index] == '0' && string_2[last_index] == '0' && c == '0') {
				result[last_index] = '0';
				c = '0';
			}
			else if (string_1[last_index] == '0' && string_2[last_index] == '0' && c == '1') {
				result[last_index] = '1';
				c = '0';
			}
			else if (string_1[last_index] == '0' && string_2[last_index] == '1' && c == '0') {
				result[last_index] = '1';
				c = '0';
			}
			else if (string_1[last_index] == '0' && string_2[last_index] == '1' && c == '1') {
				result[last_index] = '0';
				c = '1';
			}
			else if (string_1[last_index] == '1' && string_2[last_index] == '0' && c == '0') {
				result[last_index] = '1';
				c = '0';
			}
			else if (string_1[last_index] == '1' && string_2[last_index] == '0' && c == '1') {
				result[last_index] = '0';
				c = '1';
			}
			else if (string_1[last_index] == '1' && string_2[last_index] == '1' && c == '0') {
				result[last_index] = '0';
				c = '1';
			}
			else if (string_1[last_index] == '1' && string_2[last_index] == '1' && c == '1') {
				result[last_index] = '1';
				c = '1';
			}

			last_index--;
		}

		/*for (int i = 0; i < size; i++) {
			cout << result[i] << " ";
		}


		cout << endl;*/
		string result_2 = "";
		if (c == '1') {//it means the last carry is one so
			result_2 = "1";
			for (int i = 0; i < size; i++) {
				result_2 += result[i];
			}

		}
		else {
			for (int i = 0; i < size; i++) {
				result_2 += result[i];
			}
		}

		string hex_result = convert_to_hex(result_2);

		BigHex temp(hex_result);
		return temp;

	}

	BigHex& operator++ () {
		int size = this->hex.length();
		string str = "";

		for (int i = 0; i < size - 1; i++) {
			str += "0";
		}
		str += "1";

		BigHex temp(str);
		(*this) = (*this) + temp;
		return *this;
	}

	bool operator == (BigHex& a) {
		if (this->hex == a.hex) {
			return true;
		}
		else
			return false;
	}

	bool operator < (BigHex& a) {
		string s1 = remove_leading_zeroes(this->hex);
		string s2 = remove_leading_zeroes(a.hex);
		if (s1.length() > s2.length()) {
			return false;
		}

		else if (s1.length() < s2.length()) {
			return true;
		}
		else {
			int size = s1.length();
			int last_index = 0;

			while (last_index < size) {
				if (s1[last_index] != s2[last_index]) {
					if (s1[last_index] < s2[last_index]) {

						return true;
					}
					else if (s1[last_index] > s2[last_index]) {
						return false;
					}
				}
				last_index++;
			}

			return false;
		}

	}

	string remove_leading_zeroes(string str) {
		string result = "";
		int i = 0;
		while (str[i] != '\0' && str[i] == '0') {
			i++;
		}

		while (str[i] != '\0') {
			result += str[i];
			i++;
		}
		return result;
	}

	bool operator > (BigHex& a) {
		//remove leading zeroes if any
		string s1 = remove_leading_zeroes(this->hex);
		string s2 = remove_leading_zeroes(a.hex);
		if (s1.length() > s2.length()) {
			return true;
		}

		else if (s1.length() < s2.length()) {
			return false;
		}
		else {
			int size = s1.length();
			int last_index = 0;

			while (last_index < size) {
				if (s1[last_index] != s2[last_index]) {
					if (s1[last_index] > s2[last_index]) {

						return true;
					}
					else if (s1[last_index] < s2[last_index]) {
						return false;
					}
				}
				last_index++;
			}

			return false;
		}

	}

	bool operator <= (BigHex& a) {
		if (((*this) < a) || ((*this) == a)) {
			return true;
		}
		else
			return false;
	}

	bool operator >= (BigHex& a) {
		if (((*this) > a) || ((*this) == a)) {
			return true;
		}
		else
			return false;
	}

	bool operator != (BigHex& a) {
		if (!((*this) == a)) {
			return true;
		}
		else
			return false;
	}

	BigHex operator % (BigHex a) {

		string a_binary_1 = convert_to_binary(a.hex);
		string l = convert_to_binary(this->hex);
		int io = 0;

		while (io < l.size() && l[io] != '1') {
			io++;
		}

		int io2 = 0;
		while (io2 < a_binary_1.size() && a_binary_1[io2] != '1') {
			io2++;
		}

		int count1 = l.length() - io; //count 1 is the length of the dividend
		int count2 = a_binary_1.length() - io2;  //count 2 is the length of divisor

		int count = 0;
		bool is_divisor_bigger = false;

		if (count1 > count2)
			count = count1;
		else if (count2 > count1) {
			count = count2;

			//if divisor is greater than dividend then remainder will always be the dividend itself
			return (*this);
		}
		else if (count1 == count2) {
			if (a_binary_1 > l) {
				return (*this);
			}
			else
				count = count1;
		}



		string* a_binary = new string[count + 1];
		int rec = 0;
		for (int i = a_binary_1.size() - 1, j = count; (i >= 0 && j >= 0); i--, j--) {
			a_binary[j] = a_binary_1[i];
			rec = j;
		}

		for (int i = 0; i < rec; i++) {
			a_binary[i] = "0";
		}
		//cout << "count: " << count << endl;
		//this is dividend --> Q
		//a is divisor --> M
		//cout << "count: " << count << endl;
		string A = "";
		char Qo;
		for (int i = 0; i < count + 1; i++) {
			A += "0";
		}


		string* M_comp = new string[count + 1];

		/*for (int i = 0; i < count + 1; i++) {
			cout << a_binary[i];
		}*/
		//cout << endl;
		bool first_one = false;
		for (int i = count; i >= 0; i--) {
			if (first_one == false && a_binary[i] == "0") {

				M_comp[i] = '0';
			}
			else if (first_one == false && a_binary[i] == "1") {
				first_one = true;
				M_comp[i] = '1';
			}
			else if (first_one == true && a_binary[i] == "0") {
				M_comp[i] = '1';
			}
			else if (first_one == true && a_binary[i] == "1") {
				M_comp[i] = '0';
			}
		}

		string m_comp = "";
		for (int i = 0; i < count + 1; i++) {
			m_comp += M_comp[i];
		}
		//cout << "M complement is: " << m_comp << endl;

		string this_binary = convert_to_binary(hex);
		string Q = "";
		//int rec_2 = 0;
		for (int i = this_binary.size() - count; i < this_binary.size(); i++) {
			Q += this_binary[i];
			//rec_2 = j;
		}


		int ind = count - 1;
		while (ind >= 0) {
			char temp_char;


			//shifting Q left
			string temp_binary = "";
			temp_char = Q[0];
			for (int j = 1; j < count; j++) {
				temp_binary += Q[j];
			}
			temp_binary += "0";
			Q = temp_binary;

			//Shifting A left
			temp_binary = "";

			for (int j = 1; j < count + 1; j++) {
				temp_binary += A[j];
			}
			temp_binary += temp_char;

			A = temp_binary;
			temp_binary = "";


			//A-M
			string restore = A;
			A = helper_add(A, m_comp);

			if (A[0] == '1') {
				Qo = '0';
				A = restore;
				Q[count - 1] = Qo;
			}

			else if (A[0] == '0') {
				Qo = '1';
				Q[count - 1] = Qo;
			}


			//cout << "A: " << A << "        "<<"Q: "<<Q <<endl;

			ind--;
		}
		//cout << "A LENGTH: "<<A.length() << endl;
		A = convert_to_hex(A);
		string B;
		//check if size of A is bigger than this->hex
		/*if (A.size() > this->hex.size()) {
			for (int i = 1; i < A.size(); i++) {
				B += A[i];
			}
			BigHex res2(B);
			return res2;
		}*/
		//cout << A << endl;
		string temp = "";
		if (identifier_size_bighex % 4 == 0) {
			while ((A.size() * 4) > identifier_size_bighex) {
				if (A[0] == '0') {
					for (int i = 1; i < A.size(); i++) {
						temp += A[i];
					}
					A = temp;
				}
			}
		}
		else {
			int rem = identifier_size_bighex % 4;
			int val = identifier_size_bighex + (4 - rem);
			if (A.size() * 4 > val) {
				while ((A.size() * 4) > val) {
					if (A[0] == '0') {
						for (int i = 1; i < A.size(); i++) {
							temp += A[i];
						}
						A = temp;
					}
				}
			}
		}
		BigHex res(A);
		return res;
	}

	string helper_add(string string_1, string string_2) {

		char c = '0';
		int last_index = string_1.length() - 1;
		string* result = new string[string_1.length()];

		while (last_index >= 0) {
			if (string_1[last_index] == '0' && string_2[last_index] == '0' && c == '0') {
				result[last_index] = '0';
				c = '0';
			}
			else if (string_1[last_index] == '0' && string_2[last_index] == '0' && c == '1') {
				result[last_index] = '1';
				c = '0';
			}
			else if (string_1[last_index] == '0' && string_2[last_index] == '1' && c == '0') {
				result[last_index] = '1';
				c = '0';
			}
			else if (string_1[last_index] == '0' && string_2[last_index] == '1' && c == '1') {
				result[last_index] = '0';
				c = '1';
			}
			else if (string_1[last_index] == '1' && string_2[last_index] == '0' && c == '0') {
				result[last_index] = '1';
				c = '0';
			}
			else if (string_1[last_index] == '1' && string_2[last_index] == '0' && c == '1') {
				result[last_index] = '0';
				c = '1';
			}
			else if (string_1[last_index] == '1' && string_2[last_index] == '1' && c == '0') {
				result[last_index] = '0';
				c = '1';
			}
			else if (string_1[last_index] == '1' && string_2[last_index] == '1' && c == '1') {
				result[last_index] = '1';
				c = '1';
			}

			last_index--;
		}

		string result_final = "";

		for (int i = 0; i < string_1.length(); i++) {
			result_final += result[i];
		}
		return result_final;
	}
};

BigHex pow(int base, int power, int m) { //m is no of bits in identifier space
	//we have to apply left shift power no of times
	//copy binary string to another string but from
	string result_special = "";
	BigHex result_special_big;
	if (power == m) {
		result_special += "1";
		for (int i = 0; i < m; i++) {
			result_special += "0";
		}
		result_special = result_special_big.convert_to_hex(result_special);
		result_special_big.hex = result_special;
		return result_special_big;
	}
	string binary = "";

	for (int i = 0; i < m - 1; i++) {
		binary += "0";
	}

	binary += "1";
	//cout << binary << endl;

	string temp_binary = "";
	for (int i = 0; i < power; i++) {
		for (int j = 1; j < m; j++) {
			temp_binary += binary[j];
		}
		temp_binary += "0";
		binary = temp_binary;
		//cout << binary << endl;
		temp_binary = "";
	}
	//cout << "binary: " << binary << endl;
	string hex_ret = "";
	BigHex temp;
	hex_ret = temp.convert_to_hex(binary);
	//cout << "hex: "<<hex_ret<<endl;
	temp.hex = hex_ret;
	return temp;
}
