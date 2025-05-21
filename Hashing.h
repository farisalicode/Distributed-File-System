#pragma once
#include<sha.h>
#include<filters.h>
#include<hex.h>
#include<iostream>
#include<string>
#include<fstream>
#include<cstdio>
using namespace std;



string hex_to_bin(string hexadecimal)
{
	string binary;
	for (int i = 0; i < hexadecimal.length(); ++i)
	{
		if (hexadecimal[i] == '0')
		{
			binary = binary + "0000";
		}
		else if (hexadecimal[i] == '1')
		{
			binary = binary + "0001";
		}
		else if (hexadecimal[i] == '2')
		{
			binary = binary + "0010";
		}
		else if (hexadecimal[i] == '3')
		{
			binary = binary + "0011";
		}
		else if (hexadecimal[i] == '4')
		{
			binary = binary + "0100";
		}
		else if (hexadecimal[i] == '5')
		{
			binary = binary + "0101";
		}
		else if (hexadecimal[i] == '6')
		{
			binary = binary + "0110";
		}
		else if (hexadecimal[i] == '7')
		{
			binary = binary + "0111";
		}
		else if (hexadecimal[i] == '8')
		{
			binary = binary + "1000";
		}
		else if (hexadecimal[i] == '9')
		{
			binary = binary + "1001";
		}
		else if (hexadecimal[i] == 'A')
		{
			binary = binary + "1010";
		}
		else if (hexadecimal[i] == 'B')
		{
			binary = binary + "1011";
		}
		else if (hexadecimal[i] == 'C')
		{
			binary = binary + "1100";
		}
		else if (hexadecimal[i] == 'D')
		{
			binary = binary + "1101";
		}
		else if (hexadecimal[i] == 'E')
		{
			binary = binary + "1110";
		}
		else if (hexadecimal[i] == 'F')
		{
			binary = binary + "1111";
		}
	}
	return binary;
}

string bin_to_hex(string binary)
{
	string hexadecimal;
	if ((binary.length() % 4) == 0)
	{
		for (int i = 0; i < binary.length(); i += 4)
		{
			string sub;
			sub = sub + binary[i + 0];
			sub = sub + binary[i + 1];
			sub = sub + binary[i + 2];
			sub = sub + binary[i + 3];
			if (sub == "0000")
			{
				hexadecimal = hexadecimal + '0';
			}
			else if (sub == "0001")
			{
				hexadecimal = hexadecimal + '1';
			}
			else if (sub == "0010")
			{
				hexadecimal = hexadecimal + '2';
			}
			else if (sub == "0011")
			{
				hexadecimal = hexadecimal + '3';
			}
			else if (sub == "0100")
			{
				hexadecimal = hexadecimal + '4';
			}
			else if (sub == "0101")
			{
				hexadecimal = hexadecimal + '5';
			}
			else if (sub == "0110")
			{
				hexadecimal = hexadecimal + '6';
			}
			else if (sub == "0111")
			{
				hexadecimal = hexadecimal + '7';
			}
			else if (sub == "1000")
			{
				hexadecimal = hexadecimal + '8';
			}
			else if (sub == "1001")
			{
				hexadecimal = hexadecimal + '9';
			}
			else if (sub == "1010")
			{
				hexadecimal = hexadecimal + 'A';
			}
			else if (sub == "1011")
			{
				hexadecimal = hexadecimal + 'B';
			}
			else if (sub == "1100")
			{
				hexadecimal = hexadecimal + 'C';
			}
			else if (sub == "1101")
			{
				hexadecimal = hexadecimal + 'D';
			}
			else if (sub == "1110")
			{
				hexadecimal = hexadecimal + 'E';
			}
			else if (sub == "1111")
			{
				hexadecimal = hexadecimal + 'F';
			}
		}
	}
	else
	{
		int gap = ((binary.length() / 4) * 4);
		gap = (binary.length() - gap);
		for (int i = gap; i < binary.length(); i += 4)
		{
			string sub;
			sub = sub + binary[i + 0];
			sub = sub + binary[i + 1];
			sub = sub + binary[i + 2];
			sub = sub + binary[i + 3];
			if (sub == "0000")
			{
				hexadecimal = hexadecimal + '0';
			}
			else if (sub == "0001")
			{
				hexadecimal = hexadecimal + '1';
			}
			else if (sub == "0010")
			{
				hexadecimal = hexadecimal + '2';
			}
			else if (sub == "0011")
			{
				hexadecimal = hexadecimal + '3';
			}
			else if (sub == "0100")
			{
				hexadecimal = hexadecimal + '4';
			}
			else if (sub == "0101")
			{
				hexadecimal = hexadecimal + '5';
			}
			else if (sub == "0110")
			{
				hexadecimal = hexadecimal + '6';
			}
			else if (sub == "0111")
			{
				hexadecimal = hexadecimal + '7';
			}
			else if (sub == "1000")
			{
				hexadecimal = hexadecimal + '8';
			}
			else if (sub == "1001")
			{
				hexadecimal = hexadecimal + '9';
			}
			else if (sub == "1010")
			{
				hexadecimal = hexadecimal + 'A';
			}
			else if (sub == "1011")
			{
				hexadecimal = hexadecimal + 'B';
			}
			else if (sub == "1100")
			{
				hexadecimal = hexadecimal + 'C';
			}
			else if (sub == "1101")
			{
				hexadecimal = hexadecimal + 'D';
			}
			else if (sub == "1110")
			{
				hexadecimal = hexadecimal + 'E';
			}
			else if (sub == "1111")
			{
				hexadecimal = hexadecimal + 'F';
			}
		}
		string temporary = hexadecimal;
		string padding;
		if (gap == 1)
		{
			padding = "00";

		}
		else if (gap == 2)
		{
			padding = "0";

		}
		for (int i = 0; i < gap; ++i)
		{
			padding = padding + binary[i];
		}
		if (padding == "000")
		{
			hexadecimal = '0';
		}
		else if (padding == "001")
		{
			hexadecimal = '1';
		}
		else if (padding == "010")
		{
			hexadecimal = '2';
		}
		else if (padding == "011")
		{
			hexadecimal = '3';
		}
		else if (padding == "100")
		{
			hexadecimal = '4';
		}
		else if (padding == "101")
		{
			hexadecimal = '5';
		}
		else if (padding == "110")
		{
			hexadecimal = '6';
		}
		else if (padding == "111")
		{
			hexadecimal = '7';
		}
		hexadecimal = hexadecimal + temporary;
	}
	return hexadecimal;
}

string Secure_Hashing_Algorithm_1(string text)
{
	CryptoPP::SHA1 sha1;
	string sha_1_hash;
	CryptoPP::StringSource(text, true, new CryptoPP::HashFilter(sha1, new CryptoPP::HexEncoder(new CryptoPP::StringSink(sha_1_hash))));
	return sha_1_hash;
}

string hash_generator(string text, int identifer_space_size)
{
	if (identifer_space_size < 4)
	{
		identifer_space_size = 4;
	}
	if (identifer_space_size > 160)
	{
		identifer_space_size = 160;
	}
	string hash;
	string digest;
	digest = Secure_Hashing_Algorithm_1(text);
	string bin_dig = hex_to_bin(digest);
	for (int i = 0; i < identifer_space_size; ++i)
	{
		hash = hash + bin_dig[i];
	}
	hash = bin_to_hex(hash);
	return hash;
}
