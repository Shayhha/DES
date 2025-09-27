#ifndef _DES_H
#define _DES_H
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/**
 * @file DES.h
 * @brief • DES (Data Encryption Standard) class.
 * @brief • The DES class supports both encryption and decryption, and it follows the DES specification.
 */
class DES {
private:
	static const int IP[64];
	static const int IPMinusOne[64];
	static const int PCMinusOne[56];
	static const int PCMinusTwo[48];
	static const int E[48];
	static const int P[32];
	static const int SBoxes[8][4][16];

protected:
	static vector<unsigned char> InitialPermutation(const vector<unsigned char>& text);
	static vector<unsigned char> FinalPermutation(const vector<unsigned char>& text);
	static vector<unsigned char> PCMinusOnePermutation(const vector<unsigned char>& text);
	static vector<unsigned char> PCMinusTwoPermutation(const vector<unsigned char>& text);
	static vector<unsigned char> ExpansionPermutation(const vector<unsigned char>&text);
	static vector<unsigned char> pPermutation(const vector<unsigned char>& text);
	static vector<vector<unsigned char>> KeySchedule(const vector<unsigned char>& key, const bool isDecrypt = false);
	static vector<unsigned char> XOR(const vector<unsigned char>& text1, const vector<unsigned char>& text2);
	static vector<unsigned char> F(const vector<unsigned char>& RightText, const vector<unsigned char>& key);
	static vector<unsigned char> DESFunction(const vector<unsigned char>& text, const vector<unsigned char>& key, const bool isDecrypt = false);

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
	static vector<unsigned char> Encrypt(const vector<unsigned char>& text, const vector<unsigned char>& key);

	/**
	 * @brief • Function that performs DES decryption on given text using specified key.
	 * @brief • This function performs DES decryption with fixed block size of 8 bytes (64-bit).
	 * @param • vector<unsigned char> text
	 * @param • vector<unsigned char> key
	 * @return • vector<unsigned char> decipherText
	 * @throws • invalid_argument thrown if given text is invalid.
	 * @throws • invalid_argument thrown if given key is invalid.
	 */
	static vector<unsigned char> Decrypt(const vector<unsigned char>& text, const vector<unsigned char>& key);

	/**
	 * @brief • Function for converting vector of bytes to hexadecimal string representation.
	 * @param • vector<unsigned char> vec
	 * @return • string hex
	 */
	static string VectorToHex(const vector<unsigned char>& vec);

	/**
	 * @brief • Function for converting hexadecimal string to vector of bytes representation.
	 * @param • string hex
	 * @return • vector<unsigned char> vec
	 * @throws • invalid_argument thrown if given hex is invalid.
	 */
	static vector<unsigned char> HexToVector(const string& hex);

	/**
	 * @brief • Function for clearing a vector securly.
	 * @param • vector<unsigned char> vec
	 */
	static void ClearVector(vector<unsigned char>& vec);

	/**
	 * @brief • Function for clearing a vector of vectors securly.
	 * @param • vector<vector<unsigned char>> vec
	 */
	static void ClearVector(vector<vector<unsigned char>>& vec);

	/**
	 * @brief • Function for printing a vector of bytes as characters.
	 * @param • vector<unsigned char> vec
	 */
	static void PrintVector(const vector<unsigned char>& vec);

	/**
	 * @brief • Function for printing a vector of vectors of bytes as characters.
	 * @param • vector<vector<unsigned char>> vec
	 */
	static void PrintVector(const vector<vector<unsigned char>>& vec);
};
#endif
