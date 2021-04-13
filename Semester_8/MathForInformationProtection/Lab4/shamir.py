import random


def gcd(a, b):
    while a > 0 and b > 0:
        a, b = b, a % b
    return a + b


def gcd_global(a, b):
    if a == 0:
        return b, 0, 1

    d, x1, y1 = gcd_global(b % a, a)
    # print(x1, '*', b%a, ' + ', y1, '*', a, ' = ', d)
    return d, y1 - b // a * x1, x1


class Shamir:

    chr_to_ord = {}
    ord_to_chr = {}

    def fill_chr_to_ord(self):
        if len(Shamir.chr_to_ord) == 0:
            for i in range(27):
                if i != 26:
                    Shamir.chr_to_ord[chr(ord('a') + i)] = i + 10
                    Shamir.ord_to_chr[i + 10] = chr(ord('a') + i)
                else:
                    Shamir.chr_to_ord[' '] = i + 10
                    Shamir.ord_to_chr[i + 10] = ' '

    def __init__(self, p):
        self.p = p
        self.fill_chr_to_ord()

    def check_cd(self, c, d):
        return c*d % (self.p - 1) == 1

    def get_d(self, c):
        return (gcd_global(c, self.p - 1)[1] + (self.p - 1)) % (self.p - 1)

    def get_random_c(self):
        c, d = 0, 0
        while not self.check_cd(c, d):
            c = random.randint(2, self.p - 2)
            if gcd(c, self.p - 1) == 1:
                d = self.get_d(c)
            else:
                c = 0
        return c

    def to_number(self, text):
        answer = ''
        for letter in text:
            answer += str(Shamir.chr_to_ord[letter])
        return answer

    def cipher_step_A(self, text):
        message = self.to_number(text)
        print("Message to number: ", message)
        i = 0
        parts = []
        mes = []
        c = []
        while i < len(message):
            new_part = message[i]
            i += 1
            while int(new_part) < self.p and i < len(message):
                new_part += message[i]
                i += 1
            if int(new_part) >= self.p:
                i -= 1
                new_part = new_part[:-1]
            new_part = int(new_part)
            new_c = self.get_random_c()
            mes.append(new_part)
            parts.append(pow(new_part, new_c, self.p))
            c.append(new_c)

        print("Splitted message number: ", mes)
        return parts, c

    def cipher_step_B(self, ciphered):
        parts = []
        all_c = []
        i = 0
        while i < len(ciphered):
            new_c = self.get_random_c()
            parts.append(pow(ciphered[i], new_c, self.p))
            all_c.append(new_c)
            i += 1
        return parts, all_c

    def decipher_step_A(self, ciphered, all_c):
        parts = []
        all_d = []
        i = 0
        while i < len(ciphered):
            new_d = self.get_d(all_c[i])
            parts.append(pow(ciphered[i], new_d, self.p))
            all_d.append(new_d)
            i += 1
        return parts, all_d

    def decipher_step_B(self, deciphered, all_c):
        prts = []
        parts = ''
        i = 0
        while i < len(deciphered):
            new_d = self.get_d(all_c[i])
            res = pow(deciphered[i], new_d, self.p)
            parts += str(res)
            prts.append(res)
            i += 1
        print("Deciphered by B: ", prts)
        print("Array to number: ", parts)
        answer = ''
        for i in range(0, len(parts), 2):
            answer += Shamir.ord_to_chr[int(parts[i] + parts[i+1])]
        return answer


def main() -> None:
    print("---------------------------- SHAMIR ALGO ----------------------------")
    shamir = Shamir(5387)
    # shamir = Shamir(4919)
    text = "you read too loud read much more slowly and with expression"
    # text = "follow the directions given in the previous exercise"
    print("Message: ", text)

    ciphered_A, all_c_A = shamir.cipher_step_A(text)
    print("All C A: ", all_c_A)
    print("All D A: ", list(map(shamir.get_d, all_c_A)))
    print("All C-D A", list(zip(all_c_A, list(map(shamir.get_d, all_c_A)))))
    print("Ciphered by A: ", ciphered_A)

    ciphered_B, all_c_B = shamir.cipher_step_B(ciphered_A)
    print("All C B: ", all_c_B)
    print("All D B: ", list(map(shamir.get_d, all_c_B)))
    print("All C-D A", list(zip(all_c_B, list(map(shamir.get_d, all_c_B)))))
    print("Ciphered by B: ", ciphered_B)

    decipher_A, all_d_A = shamir.decipher_step_A(ciphered_B, all_c_A)
    print("Deciphered by A: ", decipher_A)

    answer = shamir.decipher_step_B(decipher_A, all_c_B)
    print("Answer message: ", answer)


if __name__ == '__main__':
    main()


'''
Message:  if you have any question you can safely interrupt me
Message to number:  18153634243036171031143610233436263014282918242336342430361210233628101514213436182329142727302529362214
Splitted message number:  [1815, 3634, 2430, 3617, 1031, 1436, 1023, 3436, 2630, 1428, 2918, 2423, 3634, 2430, 3612, 1023, 3628, 1015, 1421, 3436, 1823, 2914, 2727, 3025, 2936, 2214]
Ciphered by A:  [318, 929, 1674, 1811, 4459, 1485, 1417, 1382, 358, 4468, 851, 3169, 542, 4412, 3999, 1268, 152, 657, 3965, 3403, 4631, 3994, 169, 2760, 2854, 3357]
All C:  [1473, 2801, 2749, 861, 1193, 2741, 3277, 1845, 1473, 3291, 435, 1569, 3543, 4283, 1689, 1603, 1165, 997, 1567, 3393, 1781, 3261, 1945, 191, 141, 149]
All D:  [4389, 1129, 2687, 3173, 647, 2275, 975, 857, 4389, 1683, 2667, 3065, 3017, 2037, 3271, 1357, 1819, 3139, 3051, 2501, 2033, 1479, 2713, 3135, 2057, 3171]
All (C, D):  [(1473, 4389), (2801, 1129), (2749, 2687), (861, 3173), (1193, 647), (2741, 2275), (3277, 975), (1845, 857), (1473, 4389), (3291, 1683), (435, 2667), (1569, 3065), (3543, 3017), (4283, 2037), (1689, 3271), (1603, 1357), (1165, 1819), (997, 3139), (1567, 3051), (3393, 2501), (1781, 2033), (3261, 1479), (1945, 2713), (191, 3135), (141, 2057), (149, 3171)]
Ciphered by B:  [4165, 508, 2636, 2599, 960, 3383, 4094, 2798, 581, 3019, 2934, 2053, 996, 3516, 3738, 2463, 1232, 1317, 1018, 3440, 2068, 2407, 3365, 4363, 2094, 80]
All C:  [1325, 1523, 2861, 2579, 4503, 2801, 2551, 1255, 207, 3671, 1785, 4429, 3933, 43, 2755, 2531, 4113, 451, 2287, 1199, 4651, 937, 657, 187, 3811, 2517]
All D:  [1617, 1545, 1053, 4103, 1791, 1129, 1335, 3105, 113, 3289, 2301, 3795, 1237, 2611, 2637, 2205, 3701, 529, 4633, 1229, 693, 669, 1125, 1551, 491, 3929]
All (C, D):  [(1325, 1617), (1523, 1545), (2861, 1053), (2579, 4103), (4503, 1791), (2801, 1129), (2551, 1335), (1255, 3105), (207, 113), (3671, 3289), (1785, 2301), (4429, 3795), (3933, 1237), (43, 2611), (2755, 2637), (2531, 2205), (4113, 3701), (451, 529), (2287, 4633), (1199, 1229), (4651, 693), (937, 669), (657, 1125), (187, 1551), (3811, 491), (2517, 3929)]
Deciphered by A:  [2100, 681, 2937, 754, 3568, 971, 4020, 1351, 2431, 4046, 198, 1582, 1727, 2658, 4103, 326, 29, 4377, 4436, 1211, 438, 2257, 294, 4582, 3328, 521]
Deciphered by B:  [1815, 3634, 2430, 3617, 1031, 1436, 1023, 3436, 2630, 1428, 2918, 2423, 3634, 2430, 3612, 1023, 3628, 1015, 1421, 3436, 1823, 2914, 2727, 3025, 2936, 2214]
Array to number:  18153634243036171031143610233436263014282918242336342430361210233628101514213436182329142727302529362214
Answer message:  if you have any question you can safely interrupt me
'''