package algorithm;

import java.security.SecureRandom;
import java.util.*;
import java.math.BigInteger;

/**
 *
 * El Gamal algorithm
 *
 * Generating of key
 *  1. generate random simple number p
 *  2. choose integer number g, g is antiderivative root of p
 *  3. choose number x , 1 < x < p-1
 *  4. y = g^x mod p - public key
 *  5. x - private key
 *
 * Encryption
 *  1. choose session key k, 1 < k < p-1
 *  2. Pair (a,b) is a encryption text
 *     a = g^k mod p
 *     b = (y^k * M) mod p
 *
 * Decryption
 *  M = (b*a^(p-1-x)) mod p
 *
 */

public class ElGamal {

    static BigInteger p, g, y;
    static BigInteger a, b, k, EC, M;
    static BigInteger secretKey = new BigInteger("1234");;
    static Random sc = new SecureRandom();

    public static BigInteger run (BigInteger num){
        publicKeyCalculation();
        encryption(num);
        return decryption();
    }

    private static void publicKeyCalculation(){
        p = BigInteger.probablePrime(64, sc);
        g = new BigInteger("3");
        y = g.modPow(secretKey, p);
    }

    private static void encryption(BigInteger X){
        k = new BigInteger(64, sc);
        EC = X.multiply(y.modPow(k, p)).mod(p);

        a = g.modPow(k, p);
        b = a.modPow(secretKey, p);
    }

    private static BigInteger decryption(){
        BigInteger d = b.modInverse(p);
        M = d.multiply(EC).mod(p);
        return M;
    }


}


