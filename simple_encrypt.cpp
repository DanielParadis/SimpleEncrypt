#include <iostream>
#include <string>
#include <vector>
#include "custom_random.hpp"
#include "simple_encrypt.hpp"

// Literally just xors a char against another char.
// We use our custom rand function to get a random char to xor against
// That way we can use a seed as a key to decrypt
// The decrypt function is the same function
// This is known as a stream cipher. It's a very weak one
// It should get the job done for preventing players in a game from messing with files
// For example, the save file could contain the key in the beginning of the file to
// decrypt its contents, where assets could have the seed hardcoded into code.

std::vector<char> encrypt(std::vector<char> data, unsigned int seed)
{
	if (data.size() > 0)
	{
		int length = data.size();
		crand::srand(seed);
		for (int i = 0; i < length; ++i)
		{
			data[i] = data[i] ^ (crand::rand() % 256);
		}
	}
	else
	{
		std::cout << "No data to encrypt/decrypt!" << std::endl;
	}
	return data;
}
std::vector<char> decrypt(std::vector<char> data, unsigned int seed)
{
	return(encrypt(data, seed));
}

// This next implementation simply xors over a key repeatedly. This can be broken easily

/*
std::string encrypt(std::string data, std::string key)
{
	int dataLength = data.length();
	int keyLength = key.length();
	int keyCounter = 0;
	for (int i = 0; i < dataLength; ++i)
	{
		data[i] = data[i] ^ key[keyCounter];
		++keyCounter;
		if (keyCounter >= keyLength)
			keyCounter = 0;
	}
	return data;
}
*/

// Let's make it a little more complicated

std::vector<char> encrypt(std::vector<char> data, std::string key)
{
	if (data.size() > 0)
	{
		// We will store our current seed
		unsigned int currentSeed = crand::getSeed();
		int dataLength = data.size();
		int keyLength = key.length();
		// We will generate a new seed using our key
		unsigned int newSeed = keyLength;
		for (int i = 0; i < keyLength; ++i)
		{
			// These are all just a bunch of random rules I came up with
			// I tried to use several operations using both the position in 
			// the key as well as the value of the key
			if (i % 2 == 0 && key[i] % 2 == 0)
			{
				newSeed *= key[i];
			}
			else if (key[i] % 2 == 0)
			{
				newSeed += key[i];
			}
			else if (i % 2 == 0)
			{
				++newSeed;
			}
			else
			{
				--newSeed;
			}
		}
		crand::srand(newSeed);
		int keyCounter = 0;
		for (int i = 0; i < dataLength; ++i)
		{
			// Now we are adding a random number to our key and modulos by 256
			data[i] = data[i] ^ ((key[keyCounter] + crand::rand()) % 256);
			++keyCounter;
			if (keyCounter >= keyLength)
				keyCounter = 0;
		}
		crand::srand(currentSeed);
	}
	else
	{
		std::cout << "No data to encrypt/decrypt!" << std::endl;
	}
	return data;
}

std::vector<char> decrypt(std::vector<char> data, std::string key)
{
	return(encrypt(data, key));
}