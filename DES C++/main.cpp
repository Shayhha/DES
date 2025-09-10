#include "DES.h"


int main() {
    string plainText = "thoughts";
    string key = "nonsense";

    //convert the text and key to vectors of unsigned chars 
    vector<unsigned char> plainTextVec(plainText.begin(), plainText.end());
    vector<unsigned char> keyVec(key.begin(), key.end());

    try {
        //print the encrypted text 
        cout << "Cipher Text:" << endl;
        vector<unsigned char> cipherText = DES::Encrypt(plainTextVec, keyVec);
        cout << DES::VectorToHex(cipherText) << endl;
        DES::PrintVector(cipherText);
		cout << endl;

        //print the decrypted text 
        cout << "Original Text:" << endl;
        vector<unsigned char> decryptedText = DES::Decrypt(cipherText, keyVec);
        cout << DES::VectorToHex(decryptedText) << endl;
		DES::PrintVector(decryptedText);
    }
    catch (const invalid_argument& e) {
        cerr << e.what() << endl;
        return 1;
    }

    return 0;
}