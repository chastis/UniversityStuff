package algorithm;

import java.util.Scanner;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

/**
 *
 * https://uk.wikipedia.org/wiki/RC6
 *
 * Details of RC6
 *  W is the length of the machine word in bits.
 *  R is the number of rounds.
 *  B is the length of the key in bytes.
 *
 * Key extension
 *  Input: the user-specified B-bit key is pre-converted to an array of words L[0,...,c-1].
 *         R is a quantity of rounds.
 *  Output: W-bit key table S[0,...,2*r+3].
 *
 * Encryption
 *  Input: R is a quantity of rounds.
 *         W-bit key for each rounds S[0,...,2*r+3].
 *  Output: encrypted text is stored in A, B, C, D.
 *
 * Decryption
 *  Input: encrypted text which stored in A, B, C, D.
 *         R is a quantity of rounds.
 *         W-bit key for each rounds S[0,...,2*r+3].
 *  Output: output text saved in A, B, C, D.
 *
 */

public class RC6 {

    public static String text = "";
    public static String encrypted_text = "";
    public static String decrypted_text = "";

    public static void run() {
        runEncryption();
        runDecryption();
    }

    private static int w = 32, r = 20;
    private static int[] S;
    private static int Pw = 0xb7e15163, Qw = 0x9e3779b9;

    // INT --> BYTE
    private static byte[] convertIntToByte(int[] integerArray, int length) {
        byte[] int_to_byte = new byte[length];
        for (int i = 0; i < length; i++) {
            int_to_byte[i] = (byte) ((integerArray[i / 4] >>> (i % 4) * 8) & 0xff);
        }

        return int_to_byte;
    }
    // BYTE --> INT
    private static int[] convertBytetoInt(byte[] arr, int length) {
        int[] byte_to_int = new int[length];
        for (int j = 0; j < byte_to_int.length; j++) {
            byte_to_int[j] = 0;
        }

        int counter = 0;
        for (int i = 0; i < byte_to_int.length; i++) {
            byte_to_int[i] = ((arr[counter++] & 0xff)) |
                    ((arr[counter++] & 0xff) << 8) |
                    ((arr[counter++] & 0xff) << 16) |
                    ((arr[counter++] & 0xff) << 24);
        }
        return byte_to_int;

    }
    // HEX --> BYTE
    private static byte[] hexStringToByteArray(String s) {
        int string_len = s.length();
        byte[] data = new byte[string_len / 2];
        for (int i = 0; i < string_len; i += 2) {
            data[i / 2] = (byte) ((Character.digit(s.charAt(i), 16) << 4) + Character
                    .digit(s.charAt(i + 1), 16));
        }
        return data;
    }
    // BYTE --> HEX
    private static String byteArrayToHex(byte[] a) {
        StringBuilder sb = new StringBuilder(a.length * 2);
        for (byte b : a)
            sb.append(String.format("%02x", b & 0xff));
        return sb.toString();
    }
    // BYTE --> WORDS
    private static int[] bytestoWords(byte[] userkey, int c) {
        int[] bytes_to_words = new int[c];
        for (int i = 0; i < bytes_to_words.length; i++)
            bytes_to_words[i] = 0;

        for (int i = 0, off = 0; i < c; i++)
            bytes_to_words[i] = ((userkey[off++] & 0xFF)) | ((userkey[off++] & 0xFF) << 8)
                    | ((userkey[off++] & 0xFF) << 16) | ((userkey[off++] & 0xFF) << 24);

        return bytes_to_words;
    }

    // ROTATE LEFT METHOD
    private static int rotateLeft(int val, int pas) {
        return (val << pas) | (val >>> (32 - pas));
    }
    //ROTATE RIGHT METHOD
    private static int rotateRight(int val, int pas) {
        return (val >>> pas) | (val << (32 - pas));
    }

    // KEY EXTENSION
    private static int[] keySchedule(byte[] key) {
        int[] S = new int[2 * r + 4];
        S[0] = Pw;

        int c = key.length / (w / 8);
        int[] L = bytestoWords(key, c);

        for (int i = 1; i < (2 * r + 4); i++) {
            S[i] = S[i - 1] + Qw;
        }

        int A, B, i, j;

        A = B = i = j = 0;

        int v = 3 * Math.max(c, (2 * r + 4));

        for (int s = 0; s < v; s++) {
            A = S[i] = rotateLeft((S[i] + A + B), 3);
            B = L[j] = rotateLeft(L[j] + A + B, A + B);
            i = (i + 1) % (2 * r + 4);
            j = (j + 1) % c;

        }
        return S;
    }
    // ENCRYPTION
    private static byte[] encryption(byte[] keySchArray) {
        int temp, t, u;
        int[] temp_data = new int[keySchArray.length / 4];

        for (int i = 0; i < temp_data.length; i++) temp_data[i] = 0;

        temp_data = convertBytetoInt(keySchArray, temp_data.length);
        int A, B, C, D;
        A = B = C = D = 0;

        A = temp_data[0];
        B = temp_data[1];
        C = temp_data[2];
        D = temp_data[3];

        B = B + S[0];
        D = D + S[1];

        int lgw = 5;

        byte[] outputArr;
        for (int i = 1; i <= r; i++) {
            t = rotateLeft(B * (2 * B + 1), lgw);
            u = rotateLeft(D * (2 * D + 1), lgw);
            A = rotateLeft(A ^ t, u) + S[2 * i];
            C = rotateLeft(C ^ u, t) + S[2 * i + 1];

            temp = A;
            A = B;
            B = C;
            C = D;
            D = temp;
        }

        A = A + S[2 * r + 2];
        C = C + S[2 * r + 3];

        temp_data[0] = A;
        temp_data[1] = B;
        temp_data[2] = C;
        temp_data[3] = D;

        outputArr = convertIntToByte(temp_data, keySchArray.length);
        return outputArr;
    }
    //DECRYPTION
    private static byte[] decryption(byte[] keySchArray) {


        int temp, t, u;
        int A, B, C, D;

        A = B = C = D = 0;
        int[] temp_data_decryption = new int[keySchArray.length / 4];

        for (int i = 0; i < temp_data_decryption.length; i++)
            temp_data_decryption[i] = 0;


        temp_data_decryption = convertBytetoInt(keySchArray, temp_data_decryption.length);


        A = temp_data_decryption[0];
        B = temp_data_decryption[1];
        C = temp_data_decryption[2];
        D = temp_data_decryption[3];


        C = C - S[2 * r + 3];
        A = A - S[2 * r + 2];

        int lgw = 5;

        byte[] outputArr = new byte[keySchArray.length];
        for (int i = r; i >= 1; i--) {
            temp = D;
            D = C;
            C = B;
            B = A;
            A = temp;

            u = rotateLeft(D * (2 * D + 1), lgw);
            t = rotateLeft(B * (2 * B + 1), lgw);
            C = rotateRight(C - S[2 * i + 1], t) ^ u;
            A = rotateRight(A - S[2 * i], u) ^ t;

        }
        D = D - S[1];
        B = B - S[0];


        temp_data_decryption[0] = A;
        temp_data_decryption[1] = B;
        temp_data_decryption[2] = C;
        temp_data_decryption[3] = D;


        outputArr = convertIntToByte(temp_data_decryption, keySchArray.length);


        return outputArr;
    }
    
    private static String runEncryption(){
        String tempString;
        String given_text;
        String key_value;
        String[] input_text_val;
        BufferedWriter output_to_text_file = null;
        Scanner sc = new Scanner(System.in);

        try {

            FileReader input_file = new FileReader("inputEncryption.txt");
            FileWriter output_file = new FileWriter("outputEncription.txt", false);
            BufferedReader bf = new BufferedReader(input_file);
            String choice = bf.readLine();

            given_text = bf.readLine();
            input_text_val = given_text.split(":");
            String text_data = input_text_val[1];
            text = text_data.replace(" ", "");
            key_value = bf.readLine();
            String[] input_key_val = key_value.split(":");
            tempString = input_key_val[1];
            tempString = tempString.replace(" ", "");
            text_data = text_data.replace(" ", "");

            byte[] key = hexStringToByteArray(tempString);
            byte[] W = hexStringToByteArray(text_data);
            S = new RC6().keySchedule(key);

            byte[] encrypt = new RC6().encryption(W);
            encrypted_text = byteArrayToHex(encrypt);
            encrypted_text = encrypted_text.replaceAll("..", "$0 ");
            output_to_text_file = new BufferedWriter(output_file);
            output_to_text_file.write("ciphertext: " + encrypted_text);
        } catch (FileNotFoundException e) {
            System.out.println("File not found exception");
            e.printStackTrace();
        } catch (IOException e) {
            System.out.println("IO exception");
            e.printStackTrace();

        } finally {
            if (output_to_text_file != null) {
                try {
                    output_to_text_file.close();
                } catch (IOException e) {
                    System.out.println("File cannot be closed");
                    e.printStackTrace();
                }
            }
        }

        encrypted_text = encrypted_text.replace(" ", "");
        return encrypted_text;
    }
    private static String runDecryption(){
        String tempString;
        String given_text;
        String text_data;
        String key_value;
        String[] input_text_val;
        BufferedWriter output_to_text_file = null;
        Scanner sc = new Scanner(System.in);

        try {

            FileReader input_file = new FileReader("inputDecryption.txt");
            FileWriter output_file = new FileWriter("outputDecryption.txt", false);
            BufferedReader bf = new BufferedReader(input_file);
            String choice = bf.readLine();

            given_text = bf.readLine();
            input_text_val = given_text.split(":");
            text_data = input_text_val[1];
            key_value = bf.readLine();
            String[] input_key_val = key_value.split(":");
            tempString = input_key_val[1];


            tempString = tempString.replace(" ", "");
            text_data = text_data.replace(" ", "");

            byte[] key2 = hexStringToByteArray(tempString);
            byte[] X = hexStringToByteArray(text_data);
            S = new RC6().keySchedule(key2);
            byte[] decrypt = new RC6().decryption(X);
            decrypted_text = byteArrayToHex(decrypt);
            decrypted_text = decrypted_text.replaceAll("..", "$0 ");
            output_to_text_file = new BufferedWriter(output_file);
            output_to_text_file.write("plaintext: " + decrypted_text);

        } catch (FileNotFoundException e) {
            System.out.println("File not found exception");
            e.printStackTrace();
        } catch (IOException e) {
            System.out.println("IO exception");
            e.printStackTrace();

        } finally {
            if (output_to_text_file != null) {
                try {
                    output_to_text_file.close();
                } catch (IOException e) {
                    System.out.println("File cannot be closed");
                    e.printStackTrace();
                }
            }
        }

        decrypted_text = decrypted_text.replace(" ", "");
        return decrypted_text;
    }

}
