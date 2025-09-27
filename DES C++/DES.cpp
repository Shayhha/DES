#include "DES.h"


//default tables for DES
const int DES::IP[64] = {
    58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17,  9, 1,
    59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7
};


const int DES::IPMinusOne[64] = {
    40, 8, 48, 16, 56, 24, 64, 32,
    39, 7, 47, 15, 55, 23, 63, 31,
    38, 6, 46, 14, 54, 22, 62, 30,
    37, 5, 45, 13, 53, 21, 61, 29,
    36, 4, 44, 12, 52, 20, 60, 28,
    35, 3, 43, 11, 51, 19, 59, 27,
    34, 2, 42, 10, 50, 18, 58, 26,
    33, 1, 41,  9, 49, 17, 57, 25
};


const int DES::E[48] = {
    32,  1,  2,  3,  4,  5,
     4,  5,  6,  7,  8,  9,
     8,  9, 10, 11, 12, 13,
    12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21,
    20, 21, 22, 23, 24, 25,
    24, 25, 26, 27, 28, 29,
    28, 29, 30, 31, 32,  1
};


const int DES::P[32] = {
    16,  7, 20, 21,
    29, 12, 28, 17,
     1, 15, 23, 26,
     5, 18, 31, 10,
     2,  8, 24, 14,
    32, 27,  3,  9,
    19, 13, 30,  6,
    22, 11,  4, 25
};


const int DES::PCMinusOne[56] = {
    57, 49, 41, 33, 25, 17,  9,
     1, 58, 50, 42, 34, 26, 18,
    10,  2, 59, 51, 43, 35, 27,
    19, 11,  3, 60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15,
     7, 62, 54, 46, 38, 30, 22,
    14,  6, 61, 53, 45, 37, 29,
    21, 13,  5, 28, 20, 12,  4
};


const int DES::PCMinusTwo[48] = {
    14, 17, 11, 24,  1,  5,
     3, 28, 15,  6, 21, 10,
    23, 19, 12,  4, 26,  8,
    16,  7, 27, 20, 13,  2,
    41, 52, 31, 37, 47, 55,
    30, 40, 51, 45, 33, 48,
    44, 49, 39, 56, 34, 53,
    46, 42, 50, 36, 29, 32
};


//SBox tables
const int DES::SBoxes[8][4][16] = {
    {
        {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
        {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
        {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
        {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}
    },
    {
        {15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
        {3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
        {0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
        {13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9}
    },
    {
        {10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
        {13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
        {13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
        {1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12}
    },
    {
        {7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15},
        {13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},
        {10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},
        {3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14}
    },
    {
        {2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
        {14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6},
        {4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14},
        {11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3}
    },
    {
        {12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},
        {10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
        {9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
        {4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13}
    },
    {
        {4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},
        {13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6},
        {1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2},
        {6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12}
    },
    {
        {13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
        {1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
        {7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8},
        {2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}
    }
};


string DES::VectorToHex(const vector<unsigned char>& vec) {
    const string hexChars = "0123456789abcdef"; //hex characters for conversion
    string result; //create result string
    result.reserve(vec.size() * 2); //reserve memory for result string
    for (const unsigned char& byte : vec) { //iterate through each byte in the vector
        result.push_back(hexChars[byte >> 4]); //append the left 4 bits as a hex character
        result.push_back(hexChars[byte & 0x0F]); //append the right 4 bits as a hex character
    }
    return result; //return the result string
}


vector<unsigned char> DES::HexToVector(const string& hex) {
    if (hex.size() % 2 != 0) //if hex string has odd length
        throw invalid_argument("Hex string must have even length."); //throw invalid argument
    vector<unsigned char> result; //create result vector
    result.reserve(hex.size() / 2); //reserve memory for result vector
    for (size_t i = 0; i < hex.size(); i += 2) { //iterate through each hex string two characters at a time
        unsigned char byte = (unsigned char)stoi(hex.substr(i, 2), NULL, 16); //convert substring of two chars to a byte
        result.push_back(byte); //append the byte to result vector
    }
    return result; //return the result vector
}


void DES::ClearVector(vector<unsigned char>& vec) {
    fill(vec.begin(), vec.end(), 0x00); //fill vector with zeros 
    vec.clear(); //clear vector for added security after finishing operations
}


void DES::ClearVector(vector<vector<unsigned char>>& vec) {
    for (vector<unsigned char>& innerVec : vec) //iterate through each innerVec in vector
        ClearVector(innerVec); //clear each innerVec 
    vec.clear(); //clear vector for added security after finishing operations
}


void DES::PrintVector(const vector<unsigned char>& vec) {
    for (const unsigned char& byte : vec) //iterate through each byte in vector
        cout << byte; //print byte as character
    cout << endl; //new line
}


void DES::PrintVector(const vector<vector<unsigned char>>& vec) {
    for (const vector<unsigned char>& innerVec : vec) //iterate through each innerVec in vector
        PrintVector(innerVec); //print innerVec as characters
    cout << endl; //new line
}


vector<unsigned char> DES::InitialPermutation(const vector<unsigned char>& text) {
    vector<unsigned char> output(8, 0); //create a new byte array of size 64 bits (8 bytes)

    //goes through IP table and initializing the new output array with correct index
    for (size_t i = 0; i < 64; i++) {
        int bitInx = IP[i] - 1;  //represents the bit index of IP table
        int byteInx = bitInx / 8; //calculates the byte index in array by simply dividing by 8 because all bytes are size of 8

        int bitOffset = 7 - (bitInx % 8); //bitOffset is the bit position inside the byte, we know that it starts from LSB 0 to 7 MSB, we subtract from it the bitInx % 8 for the reminder
        //we know that bitInx represents the index in text array that the desired bit is located at, 
        //so we can calculate the position with the remainder of its position when divided by 8

        int bitValue = (text[byteInx] >> bitOffset) & 0x1; //gets the desired bit from text array, 
        //and shifting the bit with offset to right to get it in the LSB index and then we & with 00000001 = 0x1 so we get only our desired bit
        output[i / 8] |= (unsigned char)(bitValue << (7 - (i % 8))); //sets current bit val in the output vector by doing OR between the current value of the byte and the shifted bitValue
    }
    return output; //return the permuted array
}


vector<unsigned char> DES::FinalPermutation(const vector<unsigned char>& text) {
    vector<unsigned char> output(8, 0); //create a new byte array of size 64 bits (8 bytes)

    //goes through IPMinusOne table and initializing the new output array with correct index
    for (size_t i = 0; i < 64; i++) {
        int bitInx = IPMinusOne[i] - 1;  //represents the bit index of IPMinusOne table
        int byteInx = bitInx / 8; //calculates the byte index in array by simply dividing by 8 because all bytes are size of 8

        int bitOffset = 7 - (bitInx % 8); //bitOffset is the bit position inside the byte, we know that it starts from LSB 0 to 7 MSB, we subtract from it the bitInx % 8 for the reminder
        //we know that bitInx represents the index in text array that the desired bit is located at, 
        //so we can calculate the position with the remainder of its position when divided by 8

        int bitValue = (text[byteInx] >> bitOffset) & 0x1; //gets the desired bit from text array, 
        //and shifting the bit with offset to right to get it in the LSB index and then we & with 00000001 = 0x1 so we get only our desired bit
        output[i / 8] |= (unsigned char)(bitValue << (7 - (i % 8))); //sets current bit val in the output vector by doing OR between the current value of the byte and the shifted bitValue
    }
    return output; //return the permuted array
}


vector<unsigned char> DES::PCMinusOnePermutation(const vector<unsigned char>& text) {
    vector<unsigned char> output(7, 0); //create a new byte array of size 56 bits (7 bytes)

    //goes through PCMinusOne table and initializing the new output array with correct index
    for (size_t i = 0; i < 56; i++) {
        int bitInx = PCMinusOne[i] - 1;  //represents the bit index of PCMinusOne table
        int byteInx = bitInx / 8; //calculates the byte index in array by simply dividing by 8 because all bytes are size of 8

        int bitOffset = 7 - (bitInx % 8); //bitOffset is the bit position inside the byte, we know that it starts from LSB 0 to 7 MSB, we subtract from it the bitInx % 8 for the reminder
        //we know that bitInx represents the index in text array that the desired bit is located at, 
        //so we can calculate the position with the remainder of its position when divided by 8

        int bitValue = (text[byteInx] >> bitOffset) & 0x1; //gets the desired bit from text array, 
        //and shifting the bit with offset to right to get it in the LSB index and then we & with 00000001 = 0x1 so we get only our desired bit
        output[i / 8] |= (unsigned char)(bitValue << (7 - (i % 8))); //sets current bit val in the output vector by doing OR between the current value of the byte and the shifted bitValue
    }
    return output; //return the permuted array
}


vector<unsigned char> DES::PCMinusTwoPermutation(const vector<unsigned char>& text) {
    vector<unsigned char> output(6, 0); //create a new byte array of size 48 bits (6 bytes)

    //goes through PCMinusTwo table and initializing the new output array with correct index
    for (size_t i = 0; i < 48; i++) {
        int bitInx = PCMinusTwo[i] - 1;  //represents the bit index of IPMinusOne table
        int byteInx = bitInx / 8; //calculates the byte index in array by simply dividing by 8 because all bytes are size of 8

        int bitOffset = 7 - (bitInx % 8); //bitOffset is the bit position inside the byte, we know that it starts from LSB 0 to 7 MSB, we subtract from it the bitInx % 8 for the reminder
        //we know that bitInx represents the index in text array that the desired bit is located at, 
        //so we can calculate the position with the remainder of its position when divided by 8

        int bitValue = (text[byteInx] >> bitOffset) & 0x1; //gets the desired bit from text array, 
        //and shifting the bit with offset to right to get it in the LSB index and then we & with 00000001 = 0x1 so we get only our desired bit
        output[i / 8] |= (unsigned char)(bitValue << (7 - (i % 8))); //sets current bit val in the output vector by doing OR between the current value of the byte and the shifted bitValue
    }
    return output; //return the permuted array
}


vector<unsigned char> DES::ExpansionPermutation(const vector<unsigned char>& text) {
    vector<unsigned char> output(6, 0); //create a new byte array of size 48 bits (6 bytes)

    //goes through E table and initializing the new output array with correct index
    for (size_t i = 0; i < 48; i++) {
        int bitInx = E[i] - 1;  //represents the bit index of E table
        int byteInx = bitInx / 8; //calculates the byte index in array by simply dividing by 8 because all bytes are size of 8

        int bitOffset = 7 - (bitInx % 8); //bitOffset is the bit position inside the byte, we know that it starts from LSB 0 to 7 MSB, we subtract from it the bitInx % 8 for the reminder
        //we know that bitInx represents the index in text array that the desired bit is located at, 
        //so we can calculate the position with the remainder of its position when divided by 8

        int bitValue = (text[byteInx] >> bitOffset) & 0x1; //gets the desired bit from text array, 
        //and shifting the bit with offset to right to get it in the LSB index and then we & with 00000001 = 0x1 so we get only our desired bit
        output[i / 8] |= (unsigned char)(bitValue << (7 - (i % 8))); //sets current bit val in the output vector by doing OR between the current value of the byte and the shifted bitValue
    }
    return output; //return the permuted array
}


vector<unsigned char> DES::pPermutation(const vector<unsigned char>& text) {
    vector<unsigned char> output(4, 0); //create a new byte array of size 40 bits (5 bytes)

    //goes through P table and initializing the new output array with correct index
    for (size_t i = 0; i < 32; i++) {
        int bitInx = P[i] - 1;  //represents the bit index of P table
        int byteInx = bitInx / 8; //calculates the byte index in array by simply dividing by 8 because all bytes are size of 8

        int bitOffset = 7 - (bitInx % 8); //bitOffset is the bit position inside the byte, we know that it starts from LSB 0 to 7 MSB, we subtract from it the bitInx % 8 for the reminder
        //we know that bitInx represents the index in text array that the desired bit is located at, 
        //so we can calculate the position with the remainder of its position when divided by 8

        int bitValue = (text[byteInx] >> bitOffset) & 0x1; //gets the desired bit from text array, 
        //and shifting the bit with offset to right to get it in the LSB index and then we & with 00000001 = 0x1 so we get only our desired bit
        output[i / 8] |= (unsigned char)(bitValue << (7 - (i % 8))); //sets current bit val in the output vector by doing OR between the current value of the byte and the shifted bitValue
    }
    return output; //return the permuted array
}


vector<vector<unsigned char>> DES::KeySchedule(const vector<unsigned char>& key, const bool isDecrypt) {
    vector<vector<unsigned char>> keys(16, vector<unsigned char>(7)); //keys array for our use later, 16 different keys each 48 bit
    vector<unsigned char> newKey = PCMinusOnePermutation(key); //sending key to first permutation

    //split the key byte array to form two 28 bit halfs represented in int
    int left = 0;
    int right = 0;

    //copy first 3 bytes and first 4 bits of 4th byte to left
    for (size_t i = 0; i < 3; i++) {
        left = left << 8; //shift to the left by 8 so we can insert our byte
        left |= newKey[i] & 0xFF; // append byte to left
    }
    left = left << 4; // make space for last 4 bits of 4th byte
    left |= (newKey[3] >> 4) & 0xF; // append first 4 bits of 4th byte to left

    //copy last 4 bits of 4th byte and remaining 3 bytes to right
    right = newKey[3] & 0xF; // append last 4 bits of 4th byte to right
    for (size_t i = 4; i < 7; i++) {
        right = right << 8; //shift to the left by 8 so we can insert our byte
        right |= newKey[i] & 0xFF; // append byte to left
    }

    for (size_t i = 0; i < 16; i++) {
        int leftMSB; //extracts the left's MSB bits
        int rightMSB; //extracts the right's MSB bits

        if (i == 0 || i == 1 || i == 8 || i == 15) { //shift by 1 (rounds 1, 2, 9, 16)
            leftMSB = (left >> 27) & 1; //extracts the left's last MSB bit
            rightMSB = (right >> 27) & 1; //extracts the right's last MSB bit
            //shifting left and right
            left = (left << 1) & 0x0FFFFFFF; //shifts left by 1
            left |= leftMSB; //does OR to add the left's MSB bit to the right side
            right = (right << 1) & 0x0FFFFFFF; //shifts left by 1
            right |= rightMSB; //does OR to add the right's MSB bit to the right side
        }
        else{ //shift by 2
            leftMSB = (left >> 26) & 0b11; //extracts the left's last two MSB bit
            rightMSB = (right >> 26) & 0b11; //extracts the right's last two MSB bit
            //shifting left and right
            left = (left << 2) & 0x0FFFFFFF; //shifts left by 2
            left |= leftMSB; //does OR to add the left's MSB bit to the right side
            right = (right << 2) & 0x0FFFFFFF; //shifts left by 2
            right |= rightMSB; //does OR to add the right's MSB bit to the right side
        }
        
        //merging the left and right int's to byte array
        vector<unsigned char> currentKey(7); //allocation of 7 bytes (56 bits)
        currentKey[0] = (unsigned char)(left >> 20); //inserting first byte of left (most left 8 bits)
        currentKey[1] = (unsigned char)(left >> 12); //inserting next 8 bits of left
        currentKey[2] = (unsigned char)((left >> 4) & 0xFF); //shifting to the right by 4 bits to take the final byte (without 4 LSB bits)
        currentKey[3] = (unsigned char)(((left & 0x0F) << 4) | ((right >> 24) & 0x0F)); //take 4 LSB bits of left and 4 MSB bits of right and merge them to a byte
        currentKey[4] = (unsigned char)(right >> 16); //inserting next 8 bits from right (after the 4 bits we already took for the previous byte)
        currentKey[5] = (unsigned char)(right >> 8); //inserting next 8 bits from right
        currentKey[6] = (unsigned char)right; //inserting last 8 bits from right (last byte)

        currentKey = PCMinusTwoPermutation(currentKey); //sending current key to second premutation in each round
        keys[i] = currentKey; //adds current round k to keys array
    }

    if (isDecrypt) { //if we need to decrypt then we reverse the keys array
        reverse(keys.begin(), keys.end()); //reverse keys for decryption
    }

    return keys; //return encryption keys
}


vector<unsigned char> DES::XOR(const vector<unsigned char>& text1, const vector<unsigned char>& text2) {
    vector<unsigned char> output(text1.size()); //new output vector with size of 48 bits
    for (size_t i = 0; i < text1.size(); i++) {
        output[i] = text1[i] ^ text2[i]; //doing xor between each corresponding elements in vectors
    }
    return output; //returns vector that represents the xor of two arrays
}


vector<unsigned char> DES::F(const vector<unsigned char>& RightText, const vector<unsigned char>& key) {
    vector<unsigned char> output(4); //allocation of final array 
    vector<unsigned char> NewRight = ExpansionPermutation(RightText); //saving the new permutated RightText in new variable
    NewRight = XOR(NewRight, key); //xor between key and NewRight 
    long long SplitNewRight = 0; //allocating new long (64 bits) for calculating the sboxes values
    //going through text array and copy all bits to newText int (48 bits = 6 bytes)
    for (size_t i = 0; i < 6; i++) {
        SplitNewRight = SplitNewRight << 8; //shift to the left by 8 so we can insert our byte
        SplitNewRight |= (unsigned char)(NewRight[i] & 0xFF); // append byte to left (newRight is 48 bits)
    }

    int outputValue = 0; //we use this int to add our 4 bits each iteration
    for (size_t i = 0; i < 8; i++) {
        int SboxIndexes = 0; // we use it to calculate sbox indexes
        SboxIndexes = SboxIndexes << 6; //shift the SboxIndexes to the left by 6 so we can insert our 6 bits
        SboxIndexes |= (SplitNewRight >> (42 - (i * 6))) & 0x3F; // does shifts to right to get the 6 MSB bits
        //then in each iteration we subtract i*6 so we get the correct bits each time, then doing & with 0111111 to get the 6 bits
        //now we calculate the sbox col and row
        int msb = (SboxIndexes >> 5) & 0x01; // we shift right 4 times for MSB (bit 5)
        int lsb = SboxIndexes & 0x01; // we're doing AND with 0x01 for the LSB (bit 0)
        int row = (msb << 1) | lsb; // row of the sbox table
        int col = (SboxIndexes & 0x1E) >> 1;  // col of the sbox table (we're doing & with 011110 to keep middle bits and shift right)
        unsigned char result = (unsigned char)SBoxes[i][row][col]; //goes to the desired Sbox and takes the value (byte)
        //now we need to insert the 4bit num to outputValue:
        outputValue = (outputValue << 4) | (result & 0x0F); //shifting the int to right 4 bits, then insert the result with OR
    }

    //now we convert the outputValue back to byte array
    vector<unsigned char> buffer(4); //allocation of 4 bytes(32 bits)
    buffer[0] = (unsigned char)(outputValue >> 24);
    buffer[1] = (unsigned char)(outputValue >> 16);
    buffer[2] = (unsigned char)(outputValue >> 8);
    buffer[3] = (unsigned char)outputValue;

    output = pPermutation(buffer); //calling P permutation on output
    return output;
}


vector<unsigned char> DES::DESFunction(const vector<unsigned char>& text, const vector<unsigned char>& key, const bool isDecrypt) {
    if (text.size() != 8 || key.size() != 8) //checks if length of text and key valid
        throw invalid_argument("Invalid length of parameters!"); //throw invalid_argument exception 

    //start of operations on text from user....
    vector<unsigned char> output(8); //our output array 
    vector<unsigned char> newText = InitialPermutation(text); //calling initial permutation
    vector<vector<unsigned char>> keys = KeySchedule(key, isDecrypt); //calling KeySchedule to generate keys
    //split newText to left and right arrays, each 32 bits (4 bytes)
    vector<unsigned char> left(newText.begin(), newText.begin() + 4); //splits first 4 bytes 
    vector<unsigned char> right(newText.begin() + 4, newText.end()); //splits last 4 bytes 

    //goes through encryption algorithm 16 times
    for (size_t i = 0; i < 16; i++) {
        vector<unsigned char> tempRight = right; //save old right  
        vector<unsigned char> fResult = F(right, keys[i]); //calls F function with old right and key and saves it in fResult
        right = XOR(left, fResult); //xor operation between old left and fResult
        left = tempRight; //giving new left the old right
    }
    //combine both right and left together after final round
    copy(right.begin(), right.end(), output.begin()); //copy right output
    copy(left.begin(), left.end(), output.begin() + 4); //copy left output

    output = FinalPermutation(output); //sending new output to finalPermutation
    ClearVector(keys); //clear keys vector for added security
    return output; //return new output
}


vector<unsigned char> DES::Encrypt(const vector<unsigned char>& text, const vector<unsigned char>& key) {
    vector<unsigned char> cipherText = DESFunction(text, key, false); //encrypt the text using key
    return cipherText; //return cipherText
}


vector<unsigned char> DES::Decrypt(const vector<unsigned char>& text, const vector<unsigned char>& key) {
    vector<unsigned char> decipheredText = DESFunction(text, key, true); //decrypt the text using key
    return decipheredText; //return decipheredText
}