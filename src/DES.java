import java.nio.ByteBuffer;
import java.util.Arrays;

public class DES {
    //default tables for DES
    public static final int[] IP = {
        58, 50, 42, 34, 26, 18, 10, 2,
        60, 52, 44, 36, 28, 20, 12, 4,
        62, 54, 46, 38, 30, 22, 14, 6,
        64, 56, 48, 40, 32, 24, 16, 8,
        57, 49, 41, 33, 25, 17,  9, 1,
        59, 51, 43, 35, 27, 19, 11, 3,
        61, 53, 45, 37, 29, 21, 13, 5,
        63, 55, 47, 39, 31, 23, 15, 7
     };                         
    
    public static final int[] IPMinusOne = {
        40, 8, 48, 16, 56, 24, 64, 32,
        39, 7, 47, 15, 55, 23, 63, 31,
        38, 6, 46, 14, 54, 22, 62, 30,
        37, 5, 45, 13, 53, 21, 61, 29,
        36, 4, 44, 12, 52, 20, 60, 28,
        35, 3, 43, 11, 51, 19, 59, 27,
        34, 2, 42, 10, 50, 18, 58, 26,
        33, 1, 41, 9, 49, 17, 57,  25 
    };
                
    public static final int[] E = {
        32, 1,  2,  3,  4,   5,
        4,  5,  6,  7,  8,   9,
        8,  9,  10, 11, 12, 13,
        12, 13, 14, 15, 16, 17,
        16, 17, 18, 19, 20, 21,
        20, 21, 22, 23, 24, 25,
        24, 25, 26, 27, 28, 29,
        28, 29, 30, 31, 32,  1 
    };
                   
    //SBox tables
    public static final int[][][] SBoxes = {
       {{ 14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7 },
        { 0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8 },
        { 4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0 },
        { 15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13 }},

      {{ 15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10 },
       { 3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5 },
       { 0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15 },
       { 13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9 }},

      {{ 10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8 },
       { 13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1 },
       { 13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7 },
       { 1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12 }},

      {{ 7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15 },
       { 13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9 },
       { 10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4 },
       { 3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14 }},

      {{ 2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9 },
       { 14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6 },
       { 4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14 },
       { 11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3 }},

      {{ 12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11 },
       { 10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8 },
       { 9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6 },
       { 4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13 }},

      {{ 4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1 },
       { 13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6 },
       { 1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2 },
       { 6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12 }},

      {{ 13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7 },
       { 1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2 },
       { 7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8 },
       { 2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11 }}
};
    
    public static final int[] P ={
        16,	7,	20,	21,	29,	12,	28,	17,
        1,	15,	23,	26,	5,	18,	31,	10,
        2,	8,	24,	14,	32,	27,	3,	9,
        19,	13,	30,	6,	22,	11,	4,	25,
    };

    public static final int[] PCMInusOne = {
        57, 49, 41, 33, 25, 17, 9,
        1, 58, 50, 42, 34, 26, 18,
        10, 2, 59, 51, 43, 35, 27,
        19, 11, 3, 60, 52, 44, 36,
        63, 55, 47, 39, 31, 23, 15,
        7, 62, 54, 46, 38, 30, 22,
        14, 6, 61, 53, 45, 37, 29,
        21,  13, 5, 28, 20, 12, 4
    };

    public static final int[] PCMinusTwo = {
        14, 17, 11, 24, 1, 5, 3, 28,
        15, 6, 21, 10, 23, 19, 12, 4,
        26, 8, 16, 7, 27, 20, 13, 2,
        41, 52, 31, 37, 47, 55, 30, 40,
        51, 45, 33, 48, 44, 49, 39, 56,
        34, 53, 46, 42, 50, 36, 29, 32
    };
//=========================================================Permutations=======================================================================//

    public static byte[] InitialPermutation(byte[] text){ //initial permutation func 1001 1001 1111 0011 -> 0000 0000 0000 0001
        byte[] output = new byte[8]; //create new byte array of size 64 bit

        for (int i = 0; i < IP.length; i++) { //goes through IP table and initializing the new output array with currect index
            int bitInx = IP[i] - 1; // represents the bit index of IP table
            int byteInx = bitInx / 8; //calculates the byte index in array by simpley dividing by 8 beacsue all bytes are size of 8

            
            int bitOffset = 7 - (bitInx % 8); //bitOffset is the bit position inside the byte, we know that it starts from LSB 0 to 7 MSB, we substract from it the bitInx % 8 for the reminder
            //we know that bitInx represents the index in text array that the desired bit is located at, 
            //so we can calculate the position with the remainder of its position when divided by 8

            int bitValue = (text[byteInx] >> bitOffset) & 0x1; //gets the desired bit from text array, 
            //and shifting the bit with offset to left to get it in the LSB index and then we & with 00000001 = 0x1 so we get only our desired bit
            output[i / 8] |= (bitValue << (7 - (i % 8)));//sets current bit val in the output byte[] by doing OR between the current value of the byte and the shifted bitValue
        }
        return output; //return the premuted array
    }

    public static byte[] FinalPermutation(byte[] text){
        byte[] output = new byte[8]; //create new byte array of size 64 bit

        for (int i = 0; i < IPMinusOne.length; i++) { //goes through IP-1 table and initializing the new output array with currect index
            int bitInx = IPMinusOne[i] - 1; // represents the bit index of IP-1 table
            int byteInx = bitInx / 8; //calculates the byte index in array by simpley dividing by 8 beacsue we know all bytes are size of 8

            
            int bitOffset = 7 - (bitInx % 8); //bitOffset is the bit position inside the byte, we know that it starts from LSB 0 to 7 MSB, we substract from it the bitInx % 8 for the reminder
            //we know that bitInx represents the index in text array that the desired bit is located at, 
            //so we can calculate the position with the remainder of its position when divided by 8

            int bitValue = (text[byteInx] >> bitOffset) & 0x1; //gets the desired bit from text array, 
            //and shifting the bit with offset to left to get it in the LSB index and then we & with 00000001 = 0x1 so we get only our desired bit
            output[i / 8] |= (bitValue << (7 - (i % 8)));//sets current bit val in the output byte[] by doing OR between the current value of the byte and the shifted bitValue
        }
        return output; //return the premuted array
    }

    public static byte[] PCMinusOnePermutation(byte[] text){
        byte[] output = new byte[7];

        for (int i = 0; i < PCMInusOne.length; i++) { //goes through PCMInusOne table and initializing the new output array with currect index
            int bitInx = PCMInusOne[i] - 1; // represents the bit index of PCMInusOne table
            int byteInx = bitInx / 8; //calculates the byte index in array by simpley dividing by 8 beacsue we know all bytes are size of 8

            
            int bitOffset = 7 - (bitInx % 8); //bitOffset is the bit position inside the byte, we know that it starts from LSB 0 to 7 MSB, we substract from it the bitInx % 8 for the reminder
            //we know that bitInx represents the index in text array that the desired bit is located at, 
            //so we can calculate the position with the remainder of its position when divided by 8

            int bitValue = (text[byteInx] >> bitOffset) & 0x1; //gets the desired bit from text array, 
            //and shifting the bit with offset to left to get it in the LSB index and then we & with 00000001 = 0x1 so we get only our desired bit
            output[i / 8] |= (bitValue << (7 - (i % 8)));//sets current bit val in the output byte[] by doing OR between the current value of the byte and the shifted bitValue
        }
        return output; //return the premuted array
    }
    
    public static byte[] PCMinusTwoPermutation(byte[] text){
        byte[] output = new byte[6];

        for (int i = 0; i < PCMinusTwo.length; i++) { //goes through PCMinusTwo table and initializing the new output array with currect index
            int bitInx = PCMinusTwo[i] - 1; // represents the bit index of PCMInusTwo table
            int byteInx = bitInx / 8; //calculates the byte index in array by simpley dividing by 8 beacsue we know all bytes are size of 8

            
            int bitOffset = 7 - (bitInx % 8); //bitOffset is the bit position inside the byte, we know that it starts from LSB 0 to 7 MSB, we substract from it the bitInx % 8 for the reminder
            //we know that bitInx represents the index in text array that the desired bit is located at, 
            //so we can calculate the position with the remainder of its position when divided by 8

            int bitValue = (text[byteInx] >> bitOffset) & 0x1; //gets the desired bit from text array, 
            //and shifting the bit with offset to left to get it in the LSB index and then we & with 00000001 = 0x1 so we get only our desired bit
            output[i / 8] |= (bitValue << (7 - (i % 8)));//sets current bit val in the output byte[] by doing OR between the current value of the byte and the shifted bitValue
        }
        return output; //return the premuted array
    }

    public static byte[] ExpantionPermutation(byte[] text){
        byte[] output = new byte[6]; //allocating new byte array with updated size

        for (int i = 0; i < E.length; i++) { //goes through E table and initializing the new output array with currect index
            int bitInx = E[i] - 1; // represents the bit index of E table
            int byteInx = bitInx / 8; //calculates the byte index in array by simpley dividing by 8 beacsue we know all bytes are size of 8

            
            int bitOffset = 7 - (bitInx % 8); //bitOffset is the bit position inside the byte, we know that it starts from LSB 0 to 7 MSB, we substract from it the bitInx % 8 for the reminder
            //we know that bitInx represents the index in text array that the desired bit is located at, 
            //so we can calculate the position with the remainder of its position when divided by 8

            int bitValue = (text[byteInx] >> bitOffset) & 0x1; //gets the desired bit from text array, 
            //and shifting the bit with offset to left to get it in the LSB index and then we & with 00000001 = 0x1 so we get only our desired bit
            output[i / 8] |= (bitValue << (7 - (i % 8)));//sets current bit val in the output byte[] by doing OR between the current value of the byte and the shifted bitValue
        }
        return output; //return the premuted array
    }

    public static byte[] pPermutation(byte[] text){
        byte[] output = new byte[4]; //allocating new byte array with updated size

        for (int i = 0; i < P.length; i++) { //goes through P table and initializing the new output array with currect index
            int bitInx = P[i] - 1; // represents the bit index of P table
            int byteInx = bitInx / 8; //calculates the byte index in array by simpley dividing by 8 beacsue we know all bytes are size of 8

            
            int bitOffset = 7 - (bitInx % 8); //bitOffset is the bit position inside the byte, we know that it starts from LSB 0 to 7 MSB, we substract from it the bitInx % 8 for the reminder
            //we know that bitInx represents the index in text array that the desired bit is located at, 
            //so we can calculate the position with the remainder of its position when divided by 8

            int bitValue = (text[byteInx] >> bitOffset) & 0x1; //gets the desired bit from text array, 
            //and shifting the bit with offset to left to get it in the LSB index and then we & with 00000001 = 0x1 so we get only our desired bit
            output[i / 8] |= (bitValue << (7 - (i % 8))); //sets current bit val in the output byte[] by doing OR between the current value of the byte and the shifted bitValue
        }
        return output; //return the premuted array
    }
//============================================================================================================================================//

    public static byte[][] KeySchedule(byte[] key, String mode){
        byte[][] keys = new byte[16][6]; //keys array for our use later, 16 different keys each 48 bit
        key = PCMinusOnePermutation(key); //sending key to first permutation
        //splite the key byte array to form two 28 bit halfs represented in int
        int left = 0;
        int right = 0;

        //copy first 3 bytes and first 4 bits of 4th byte to left
        for (int i = 0; i < 3; i++) {
            left = left << 8; //shift to the left by 8 so we can insert our byte
            left |= key[i] & 0xFF; // append byte to left
        }
        left = left << 4; // make space for last 4 bits of 4th byte
        left |= (key[3] >> 4) & 0xF; // append first 4 bits of 4th byte to left

        //copy last 4 bits of 4th byte and remaining 3 bytes to right
        right = key[3] & 0xF; // append last 4 bits of 4th byte to right
        for (int i = 4; i < 7; i++) {
            right = right << 8; //shift to the left by 8 so we can insert our byte
            right |= key[i] & 0xFF; // append byte to left
        }

        //loops the key 16 times to initialize the keys array
        for(int i = 0; i < keys.length; i++) { 
            int leftMSB; //extracts the left's MSB bits
            int rightMSB; //extracts the right's MSB bits
            if (i == 0 || i == 1 || i == 8 || i == 15) { //shift by 1 (rounds 1, 2, 9, 16)
                leftMSB = (left >> 27) & 1; //extracts the left's last MSB bit
                rightMSB =  (right >> 27) & 1; //extracts the right's last MSB bit
                //shifting left and right
                left = (left << 1) & 0x0FFFFFFF; //shifts left by 1
                left |= leftMSB; //does OR to add the left's MSB bit to the right side
                right = (right << 1) & 0x0FFFFFFF; //shifts left by 1
                right |= rightMSB; //does OR to add the right's MSB bit to the right side
            }
            else { //shift by 2
                leftMSB = (left >> 26) & 0b11; //extracts the left's last two MSB bit
                rightMSB =  (right >> 26) & 0b11; //extracts the right's last two MSB bit
                //shifting left and right
                left = (left << 2) & 0x0FFFFFFF; //shifts left by 2
                left |= leftMSB; //does OR to add the left's MSB bit to the right side
                right = (right << 2) & 0x0FFFFFFF; //shifts left by 2
                right |= rightMSB; //does OR to add the right's MSB bit to the right side
            }
            // merging the left and right int's to byte array
             ByteBuffer buffer = ByteBuffer.allocate(7); //alloation of 7 bytes (56 bits)
             buffer.put((byte) (left >>> 20)); //inserting first byte of left (most left 8 bits)
             buffer.put((byte) (left >>> 12)); //inserting next 8bits of left (remember that cast to byte takes least significant bits)
             buffer.put((byte) ((left >>> 4) & 0xFF)); //shifting to the right by 4 bits to take final byte (without 4 LSB bits)
             buffer.put((byte) (((left & 0x0F) << 4) | ((right >>> 24) & 0x0F))); //take 4 LSB bits of left and 4 MSB bits of right and merge them to byte
             buffer.put((byte) (right >>> 16)); //inserting next 8 bits from right (after 4 bits we already took for previous bit)
             buffer.put((byte) (right >>> 8)); //inserting next 8 bits from right
             buffer.put((byte) right); //inserting last 8 bits from right (last byte) remember that cast to byte takes LSB bits!
             byte[] currentkey = buffer.array(); //giving currentKey its correct output

            currentkey = PCMinusTwoPermutation(currentkey); //sending current key to second premutation in each round
            keys[i] = currentkey; //adds current round key to keys array
        }

        if(mode.equals("decrypt")){ //if we need to decrypt then we reverse the keys array
            byte[][] reversedKeys = new byte[16][6];
            for(int i = 0; i < 16; i++)
                reversedKeys[15-i] = keys[i];
            return reversedKeys; //return reversedKeys
        }
        return keys; //else we return original (encrypt)
    }

   
    public static byte[] XOR(byte[] text1, byte[] text2){ //xor function for use in DES 
        byte[] output = new byte[text1.length]; // new output array with size of 48 bits
        for(int i = 0; i < output.length; i++){ 
            output[i] = (byte) (text1[i] ^ text2[i]); //doing xor between each corresponding elements in arrays
        } 
        return output; //returns new array that represents the xor of two arrays
    }

//==============================================================================================================//

    public static byte[] F(byte[] RightText, byte[] key){
        byte[] output = new byte[4];//allocation of final array 
        byte[] NewRight = ExpantionPermutation(RightText); //saving the new permutated RightText in new variable
        NewRight = XOR(NewRight, key); // xor between key and NewRight 
        long SplitNewRight = 0; //allocating new int for calculating the sboxes values
        for (int i = 0; i < 6; i++) { //going through text array and copy all bits to newText int (48 bits = 6 bytes)
            SplitNewRight = SplitNewRight << 8; //shift to the left by 8 so we can insert our byte
            SplitNewRight |= NewRight[i] & 0xFF; // append byte to left (newRignt is 48 bits)
        }
        int outputValue = 0; //we use this int to add our 4 bits each iteration
        for(int i = 0; i < 8; i++){
            int SboxIndexes = 0; // we use it to calculate sbox indexs
            SboxIndexes = SboxIndexes << 6; //shift the SboxIndexes to the left by 6 so we can insert our 6 bits
            SboxIndexes |= (SplitNewRight >> 42 - (i * 6)) & 0x3F; // does shifts to right to get the 6 MSB bits
            //then in each iteration we substract i*6 so we get the correct bits each time, then doing & with 0111111 to get the 6 bits
            //now we calculate the sbox col and row
            int msb = (SboxIndexes >> 5) & 0x01; // we shift right 4 times for MSB (bit 5)
            int lsb = SboxIndexes & 0x01; // we're doing AND with 0x01 for the LSB (bit 0)
            int row = (msb << 1) | lsb; // row of the sbox table
            int col = (SboxIndexes & 0x1E) >> 1;  // col of the sbox table (we're doing & with 011110 to keep middle bits and shift right)
            byte result = (byte)SBoxes[i][row][col]; //goes to the desired Sbox and takes the value (byte)
            //now we need to insert the 4bit num to outputValue:
            outputValue = (outputValue << 4) | (result & 0x0F); //shifting the int to right 4 bits, then insert the result with OR
        }
        //now we convert the outputValue back to byte array
        ByteBuffer buffer = ByteBuffer.allocate(4); //allocation of 4 bytes(32 bits)
        buffer.putInt(outputValue); //inserting the outputValue
        output = buffer.array(); //giving output array its correct values 
        output = pPermutation(output); // calling P permutation on output
        return output;
    }


    public static String DESFunction(String text, String key, String mode){ // mode can be only "encrypt" or "decrypt" 
        if(text.length() != 8 || key.length() != 8)//checks if length of text and key valid
            return "Invalid length of parameters!";
        if(mode != "encrypt" && mode != "decrypt")//checks if mode type is valid
            return "Invalid mode!";
        byte[] output = new byte[8]; //our output array
        byte[] newText = text.getBytes(); //converting from String to byte array
        newText = InitialPermutation(newText); //calling initial permutation
        byte[][] keys = KeySchedule(key.getBytes(), mode); //calling KeySchedule to generate keys
        //splite newText to left and right arrays, each 32 bits (4 bytes)
        byte[] left = Arrays.copyOfRange(newText, 0, newText.length / 2); //splits first 4 bytes 
        byte[] right = Arrays.copyOfRange(newText, newText.length / 2, newText.length); //splits the other 4 bytes
        for(int i = 0; i < 16; i++){ //goes through loop 16 times
            byte[] tempRight = right; //save old right 
            byte[] fResult = F(right, keys[i]); //calls F function with old right and key and saves it in fResult
            right = XOR(left, fResult); //xor operation between old left and fResult
            left = tempRight; //giving new left the old right
        }
        //combine both right and left together after final round
        System.arraycopy(right, 0, output, 0, right.length); //copy right output
        System.arraycopy(left, 0, output, right.length, left.length); //copy left to output
        output = FinalPermutation(output); //sending new output to finalPermutation
        String finalOutput = new String(output); //converting the byte array output to String
        return finalOutput; //return new ciphered text
    }

//==============================================================================================================//

    public static void main(String[] args) { //main
        String output = DESFunction("thoughts", "nonsense", "encrypt"); //encryption
        System.out.println(output);
        System.out.println(DESFunction(output, "nonsense", "decrypt")); //decryption
    }
}
