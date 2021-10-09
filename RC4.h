#pragma once
// July 2021
// RC4 stream cipher implementation in C++ that asks for user keyword and plaintext, and then encrypts it and decrypts it with the user keyword.

#include <vector>

class RC4
{
public:
	std::string encrypt(std::string plaintext, std::string key);
	std::string decrypt(std::string ciphertext, std::string key);
private:
	void initStreamGenerator(std::string key, unsigned char aTemp[256]);
	void getStreamGeneratorPermutations(std::string key);
	std::vector<unsigned char> getKeyGenerator(std::string plaintext, std::string key);
	unsigned char aStreamGenerator[256];
};
