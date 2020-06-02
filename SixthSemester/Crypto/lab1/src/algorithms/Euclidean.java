package algorithms;

import java.math.BigInteger;

/**
 *
 * What we need:  a*x + b*y = gcd(a,b)
 * How I get it:
 * 1. BigInteger[] res = gcdExtended(a, b);
 * 2. res[0] = gcd(a,b);
 * 3. res[1] = x;
 * 4. res[2] = y;
 *
 */

public class Euclidean {

    public Euclidean(){}

    public static BigInteger[] gcdExtended(BigInteger a, BigInteger b) {
        BigInteger[] qRem;
        BigInteger[] result = new BigInteger[3];
        BigInteger x = a;
        BigInteger y = b;

        BigInteger x0 = BigInteger.ONE;
        BigInteger x1 = BigInteger.ZERO;
        BigInteger y0 = BigInteger.ZERO;
        BigInteger y1 = BigInteger.ONE;

        while (true){
            qRem = x.divideAndRemainder(y);
            x = qRem[1];
            x0 = x0.subtract(y0.multiply(qRem[0]));
            x1 = x1.subtract(y1.multiply(qRem[0]));

            if (x.equals(BigInteger.ZERO)) {
                result[0]=y;
                result[1]=y0;
                result[2]=y1;
                return result;
            }

            qRem = y.divideAndRemainder(x);
            y = qRem[1];
            y0 = y0.subtract(x0.multiply(qRem[0]));
            y1 = y1.subtract(x1.multiply(qRem[0]));
            if (y.equals(BigInteger.ZERO)) {
                result[0]=x;
                result[1]=x0;
                result[2]=x1;
                return result;
            }
        }
    }

}