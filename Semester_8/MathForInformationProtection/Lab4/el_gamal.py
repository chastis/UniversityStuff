import random


class ElGamal:
    chr_to_ord = {}
    ord_to_chr = {}

    def fill_chr_to_ord(self):
        if len(ElGamal.chr_to_ord) == 0:
            for i in range(27):
                if i != 26:
                    ElGamal.chr_to_ord[chr(ord('a') + i)] = i + 10
                    ElGamal.ord_to_chr[i + 10] = chr(ord('a') + i)
                else:
                    ElGamal.chr_to_ord[' '] = i + 10
                    ElGamal.ord_to_chr[i + 10] = ' '

    def __init__(self, g, p):
        self.p = p
        self.g = g
        self.fill_chr_to_ord()

    def generate_key(self):
        return random.randint(1, self.p - 2)

    def get_public(self, key):
        return pow(self.g, key, self.p)

    def cipher(self, message, public_key):
        k = random.randint(1, self.p - 3)
        r = pow(self.g, k, self.p)
        e = message*pow(public_key, k, self.p) % self.p
        return r, e

    def decipher(self, r, e, private_key):
        return e*pow(r, self.p - 1 - private_key, self.p) % self.p

    def to_number(self, text):
        answer = ''
        for letter in text:
            answer += str(ElGamal.chr_to_ord[letter])
        return answer

    def to_splitted_number(self, text, show=False):
        message = self.to_number(text)
        if show:
            print("Message to number: ", message)
        i = 0
        parts = []
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
            parts.append(new_part)
        return parts

    def generate_n_keys(self, n):
        private_keys = []
        public_keys = []
        for i in range(n):
            key = self.generate_key()
            private_keys.append(key)
            public_keys.append(self.get_public(key))
        return private_keys, public_keys

    def cipher_text(self, text, public_keys):
        parts = self.to_splitted_number(text, True)
        print("Splitted message number: ", parts)
        ciphered = []
        for i in range(len(parts)):
            ciphered.append(self.cipher(parts[i], public_keys[i]))
        return ciphered

    def decipher_text(self, ciphered, private_keys):
        deciphered = ""
        blck = []
        for i in range(len(ciphered)):
            deciphered += str(self.decipher(ciphered[i][0], ciphered[i][1], private_keys[i]))
            blck.append(self.decipher(ciphered[i][0], ciphered[i][1], private_keys[i]))
        answer = ''
        print("Deciphered: ", blck)
        print("Array to number: ", deciphered)
        for i in range(0, len(deciphered), 2):
            answer += ElGamal.ord_to_chr[int(deciphered[i] + deciphered[i + 1])]
        return answer


def main():

    print("---------------------------- EL GAMAL ALGO ----------------------------")
    elgamal = ElGamal(31 , 3947)
    # elgamal = ElGamal(43, 4919)
    # text = "if you have any question you can safely interrupt me"
    text = "you read too loud read much more slowly and with expression"
    print("Message: ", text)
    numbers_of_keys_needed = len(elgamal.to_splitted_number(text))
    print("NEED: ", numbers_of_keys_needed)
    private_keys, public_keys = elgamal.generate_n_keys(numbers_of_keys_needed)
    print("Private keys: ", private_keys)
    print("Public keys: ", public_keys)

    ciphered = elgamal.cipher_text(text, public_keys)
    print("Ciphered: ", ciphered)

    deciphered = elgamal.decipher_text(ciphered, private_keys)
    print("Deciphered message: ", deciphered)


    """
    elgamal = ElGamal(39, 4679)
    key_b = 1234 # elgamal.generate_key()
    public_b = elgamal.get_public(key_b)

    message = 1001
    print("Message :", message)
    ciphered = elgamal.cipher(message, public_b)
    print("r = ", ciphered[0], ", e = ", ciphered[1])

    deciphered = elgamal.decipher(ciphered[0], ciphered[1], key_b)
    print("Deciphered message:", deciphered)
    """

if __name__ == '__main__':
    main()
