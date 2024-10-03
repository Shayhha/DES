#include "DES.h"


int main() {
    string plainText = "thoughts";
    string key = "nonsense";

    //convert the text and key to vectors of unsigned chars 
    vector<unsigned char> plainTextVec(plainText.begin(), plainText.end());
    vector<unsigned char> keyVec(key.begin(), key.end());

    try {
        //encrypt the plain text
        vector<unsigned char> cipherText = DES::Encrypt(plainTextVec, keyVec);

        //print the encrypted text 
        cout << "Cipher Text: " << string(cipherText.begin(), cipherText.end()) << endl;
        DES::PrintVector(cipherText);

        //decrypt the cipher text
        vector<unsigned char> decryptedText = DES::Decrypt(cipherText, keyVec);

        //print the decrypted text 
        cout << "Decrypted Text: " << string(decryptedText.begin(), decryptedText.end()) << endl;
    }
    catch (const invalid_argument& e) {
        cerr << e.what() << endl;
        return 1;
    }

    return 0;
}