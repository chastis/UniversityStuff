package test;

import algorithm.RC6;
import org.junit.Assert;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class RC6Test {

    @Test
    void run() {
        RC6 a = new RC6();
        a.run();
        Assert.assertEquals(a.text, a.decrypted_text);
    }
}