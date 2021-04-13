import random


def is_prime(r, s):
    n = r*s + 1
    for i in range(1000):
        a = random.randint(2, n-1)
        if pow(a, n-1, n) != 1 or pow(a, r, n) == 1:
            return False
    return True


def get_prime(length):
    if length % 2 == 1:
        s = 10 ** (length // 2) + 1
    else:
        s = 10 ** (length // 2) // 2 + 1

    for r in range(s+1, 4*s + 2, 2):
        if is_prime(r, s):
            ans = s*r + 1
            print(len(str(ans)))
            return s*r + 1


print(get_prime(40))
