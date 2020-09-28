package tests;

import algorithms.Euclidean;
import org.junit.Assert;
import org.junit.jupiter.api.Test;

import java.math.BigInteger;
import java.util.Random;

import static org.junit.jupiter.api.Assertions.assertEquals;

class EuclideanTest {
    public static final int NUMBER_OF_TESTS = 1000;
    public static final int NUMBER_OF_BITS = 512;
    @Test
    public void gcdExtendedTest(){
        Random rand = new Random();
        for(int i = 0; i < NUMBER_OF_TESTS; i++){
            BigInteger a = new BigInteger(NUMBER_OF_BITS, rand);
            BigInteger b = new BigInteger(NUMBER_OF_BITS, rand);
            BigInteger[] res = Euclidean.gcdExtended(a, b);
            Assert.assertEquals(a.gcd(b), res[0]);
            Assert.assertEquals(a.multiply(res[1]).add(b.multiply(res[2])), res[0]);
        }
    }
}