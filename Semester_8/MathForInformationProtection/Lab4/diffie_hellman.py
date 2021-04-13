import random

class DiffieHellman:

    def __init__(self, g, p):
        self.p = p
        self.g = g

    def generate_key(self):
        return random.randint(1, self.p - 2)

    def get_public(self, key):
        return pow(self.g, key, self.p)

    def get_result(self, private_key, public_key):
        return pow(public_key, private_key, self.p)


def main() -> None:
    print("---------------------------- DIFFIE HELLMAN ALGO 1 ----------------------------")
    diffie_hellman = DiffieHellman(46, 5387)
    private_key =  1488 # generate_rand(p)
    private_key_fr = 1337
    public_key = diffie_hellman.get_public(private_key)
    public_key_fr = diffie_hellman.get_public(private_key_fr)
    print("My = ", diffie_hellman.get_result(private_key, public_key_fr), ", pr_key = ", private_key,
          ", pub_key = ", public_key)
    print("Fr = ", diffie_hellman.get_result(private_key_fr, public_key), ", pr_key_fr = ", private_key_fr,
          ", pub_key_fr = ", public_key_fr)

    print("---------------------------- DIFFIE HELLMAN ALGO ----------------------------")
    diffie_hellman = DiffieHellman(31, 3947)
    private_key = 1912  # generate_rand(p)
    private_key_fr = 1911
    public_key = diffie_hellman.get_public(private_key)
    public_key_fr = diffie_hellman.get_public(private_key_fr)
    print("My = ", diffie_hellman.get_result(private_key, public_key_fr), ", pr_key = ", private_key,
          ", pub_key = ", public_key)
    print("Fr = ", diffie_hellman.get_result(private_key_fr, public_key), ", pr_key_fr = ", private_key_fr,
          ", pub_key_fr = ", public_key_fr)


if __name__ == '__main__':
    main()
