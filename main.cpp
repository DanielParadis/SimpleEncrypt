#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "simple_encrypt.hpp"

std::vector<char> loadFile(std::string filename)
{
	std::vector<char> buf;
	// Next we are going to open the file
	std::ifstream fileStream(filename.c_str(), std::ios::in | std::ios::binary | std::ios::ate);
	// Next we are going to load the file or throw an error if someone is an idiot
	if (fileStream.is_open())
	{
		std::streampos size = fileStream.tellg();
		buf.resize(size);
		fileStream.seekg(0, std::ios::beg);
		fileStream.read(&buf[0], size);
		fileStream.close();
	}
	else
	{
		std::cout << filename << " failed to load!" << std::endl;
	}
	return buf;
}

void saveFile(std::string filename, std::vector<char> buffer)
{
	if (buffer.size() > 0)
	{
		std::ofstream fileStream(filename.c_str(), std::ios::out | std::ios::binary);
		fileStream.write(buffer.data(), buffer.size());
		fileStream.close();
	}
	else
	{
		std::cout << "No data to write!" << std::endl;
	}
}

std::string getString()
{
	std::string buf;
	std::cin >> buf;
	return buf;
}

int mainMenu()
{
	// List the options, get the input
	std::cout << "Options: " << std::endl;
	std::cout << "1. Encrypt file" << std::endl;
	std::cout << "2. Decrypt file" << std::endl;
	std::cout << "3. Quit" << std::endl;
	std::cout << "Enter your selection: ";
	int buf = 0;
	while (buf < 1 || buf > 3)
		std::cin >> buf;
	std::cin.get();
	return buf;
}

bool getYesNo()
{
	// Simple function returns a bool depending on user input
	std::string YN;
	while (YN != "Y" && YN != "N" && YN != "y" && YN != "n")
	{
		std::cin >> YN;
	}
	if (YN == "Y" || YN == "y")
		return true;
	else
		return false;
	return false;
}

void saveKeyMenu(std::string key)
{
	// Ask user if they want to save the key
	std::cout << "Do you want to save your key?(Y/N): ";
	if (getYesNo())
	{
		// Save the key to a file
		std::cout << "Enter in key filename: ";
		std::string filename = getString();
		std::vector<char> buf(key.begin(), key.end());
		saveFile(filename, buf);
	}
}

void encryptMenu()
{
	// Get a filename
	// Create a key
	// Get a new filename in case you don't want to overwrite the old one
	std::cout << "Enter a file name: ";
	std::string filename = getString();
	std::cout << "Enter a key: ";
	std::string key = getString();
	std::cout << "Enter a new file name: ";
	std::string newfilename = getString();
	std::cout << "Files with the new file name may be overwritten." << std::endl;
	std::cout << "If you lose the key you will not be able to decrypt the new file." << std::endl;
	std::cout << "Are you sure you want to continue? (Y/N): ";
	// Check to see if user wants to continue
	if (getYesNo())
	{
		std::vector<char> data = loadFile(filename);
		data = encrypt(data, key);
		saveFile(newfilename, data);
		// Check to see if user wants to save the key to a separate file
		saveKeyMenu(key);
	}
}

std::string loadKeyMenu()
{
	// Load the key into a buffer
	// Convert to string
	// Return the string
	std::cout << "Enter file name: ";
	std::string filename = getString();
	std::vector<char> buf = loadFile(filename);
	std::string key(buf.begin(), buf.end());
	return key;
}

void decryptMenu()
{
	// Get a file name
	std::cout << "Enter a file name: ";
	std::string filename = getString();
	std::cout << "Do you have a key file?(Y/N): ";
	std::string key;
	// Check to see if someone wants to use a key file
	if (getYesNo())
	{
		key = loadKeyMenu();
	}
	else
	{
		// Otherwise write your own key
		std::cout << "Enter a key: ";
		key = getString();
	}
	// Get a new filename for the finished result
	std::cout << "Enter a new file name: ";
	std::string newfilename = getString();
	std::cout << "Files with the new file name may be overwritten." << std::endl;
	std::cout << "Are you sure you want to continue? (Y/N): ";
	// Ask for consent
	if (getYesNo())
	{
		saveFile(newfilename, encrypt(loadFile(filename), key));
	}
}

// Simple loop that grabs the result of main menu and calls proper functions

void menuLoop()
{
	bool close = false;
	while (!close)
	{
		switch (mainMenu())
		{
		case 1:
			encryptMenu();
			break;
		case 2:
			decryptMenu();
			break;
		case 3:
			close = true;
			break;
		}
	}
}

int main()
{
	menuLoop();
	return 0;
}