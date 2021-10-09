#include "RC4.h"
#include <iostream>
#include <string>
#include <array>
#include <vector>

using namespace std;

std::string RC4::encrypt(string plaintext, string key)
{
	string ciphertext;
	vector<unsigned char> allCharKeys = getKeyGenerator(plaintext, key);

	for (int i = 0; i < plaintext.length(); i++)
	{
		ciphertext.push_back(allCharKeys.at(i) ^ plaintext.at(i));
	}

	return ciphertext;
}
std::string RC4::decrypt(string ciphertext, string key)
{
	string plaintext;
	vector<unsigned char> allCharKeys = getKeyGenerator(ciphertext, key);

	for (int i = 0; i < ciphertext.length(); i++)
	{
		plaintext.push_back(allCharKeys.at(i) ^ ciphertext.at(i));
	}

	return plaintext;
}
void RC4::initStreamGenerator(string key, unsigned char aTemp[256])
{
	for (int i = 0; i < 256; i++)
	{
		aStreamGenerator[i] = i;
		aTemp[i] = key.at(i % key.size()); // Temporary array to generate permutations of S
	}
}
void RC4::getStreamGeneratorPermutations(string key)
{
	unsigned char aTemp[256];
	initStreamGenerator(key, aTemp);
	int j = 0;

	for (int i = 0; i < 256; i++)
	{
		j = (j + aStreamGenerator[i] + aTemp[i]) % 256;
		swap(aStreamGenerator[i], aStreamGenerator[j]); // Generate all permutations of S
	}
}
vector<unsigned char> RC4::getKeyGenerator(string plaintext, string key)
{
	unsigned char i = 0, j = 0, t = 0, k = 0;
	int index = 0; // Index of character in plaintext
	vector<unsigned char> allCharKeys;
	getStreamGeneratorPermutations(key);

	while (index < plaintext.length())
	{
		i = (i + 1) % 256;
		j = (j + aStreamGenerator[i]) % 256;
		swap(aStreamGenerator[i], aStreamGenerator[j]);
		t = (aStreamGenerator[i] + aStreamGenerator[j]) % 256;
		k = aStreamGenerator[t]; // Byte key used to encrypt char in plaintext
		allCharKeys.push_back(k);
		index++;
	}
	
	return allCharKeys;
}

int main()
{
	RC4 rc4;
	string key;
	string plaintext;
	string ciphertext;

	cout << "Enter keyword: ";
	getline(cin, key);

	cout << "Enter plaintext: ";
	getline(cin, plaintext);

	cout << "\nPlaintext (Before Encryption): " << plaintext << endl;

	ciphertext = rc4.encrypt(plaintext, key);
	cout << "\nCiphertext: " << ciphertext << endl;

	plaintext = rc4.decrypt(ciphertext, key);
	cout << "\nPlaintext (After Decryption): " << plaintext << endl;
}