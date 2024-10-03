#ifndef _DES_H
#define _DES_H
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <iomanip> 

using namespace std;

/**
 * @file DES.h
 * @brief • DES (Data Encryption Standard) class.
 * @brief • The DES class supports both encryption and decryption, and it follows the DES specification.
 */
class DES {
private:
	static const vector<int> IP;
	static const vector<int> IPMinusOne;
	static const vector<int> E;
	static const vector<int> P;
	static const vector<int> PCMinusOne;
	static const vector<int> PCMinusTwo;
	static const vector<vector<vector<int>>> SBoxes;

protected:
	static const vector<unsigned char> InitialPermutation(const vector<unsigned char>& text);
	static const vector<unsigned char> FinalPermutation(const vector<unsigned char>& text);
	static const vector<unsigned char> PCMinusOnePermutation(const vector<unsigned char>& text);
	static const vector<unsigned char> PCMinusTwoPermutation(const vector<unsigned char>& text);
	static const vector<unsigned char> ExpansionPermutation(const vector<unsigned char>&text);
	static const vector<unsigned char> pPermutation(const vector<unsigned char>& text);
	static const vector<vector<unsigned char>> KeySchedule(vector<unsigned char> key, const bool isDecrypt = false);
	static const vector<unsigned char> XOR(const vector<unsigned char>& text1, const vector<unsigned char>& text2);
	static const vector<unsigned char> F(const vector<unsigned char>& RightText, const vector<unsigned char>& key);
	static const vector<unsigned char> DESFunction(const vector<unsigned char>& text, const vector<unsigned char>& key, const bool isDecrypt = false);

public:
	/**
	 * @brief • Function that performs DES encryption on given text using specified key.
	 * @brief • This function performs DES encryption with fixed block size of 8 bytes (64-bit).
	 * @param • vector<unsigned char> text
	 * @param • vector<unsigned char> key
	 * @return • vector<unsigned char> cipherText
	 * @throws • invalid_argument thrown if given text is invalid.
	 * @throws • invalid_argument thrown if given key is invalid.
	 */
	static const vector<unsigned char> Encrypt(const vector<unsigned char>& text, const vector<unsigned char>& key);

	/**
	 * @brief • Function that performs DES decryption on given text using specified key.
	 * @brief • This function performs DES decryption with fixed block size of 8 bytes (64-bit).
	 * @param • vector<unsigned char> text
	 * @param • vector<unsigned char> key
	 * @return • vector<unsigned char> decipherText
	 * @throws • invalid_argument thrown if given text is invalid.
	 * @throws • invalid_argument thrown if given key is invalid.
	 */
	static const vector<unsigned char> Decrypt(const vector<unsigned char>& text, const vector<unsigned char>& key);

	/**
	 * @brief • Function for clearing a vector security.
	 * @param • vector<unsigned char> vec
	 */
	static void ClearVector(vector<unsigned char>& vec);

	/**
	 * @brief • Function for clearing a vector of vectors security.
	 * @param • vector<vector<unsigned char>> vec
	 */
	static void ClearVector(vector<vector<unsigned char>>& vec);

	/**
	 * @brief • Function for printing a vector in hexadecimal.
	 * @param • vector<unsigned char> vec
	 */
	static void PrintVector(const vector<unsigned char>& vec);

	/**
	 * @brief • Function for printing a vector of vectors in hexadecimal.
	 * @param • vector<vector<unsigned char>> vec
	 */
	static void PrintVector(const vector<vector<unsigned char>>& vec);
};
#endif
