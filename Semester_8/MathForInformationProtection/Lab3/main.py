
def block_cipher(letter: str, key: str) -> str:
    k = 0
    letter = [ord(value) - ord('a') for value in letter if value != ' ']
    key = [ord(value) - ord('a') for value in key]
    answer = ""
    for i in range(len(letter)):
        if letter[i] != ' ':
            answer += chr((letter[i] + key[k]) % 26 + ord('a'))
            k = (k + 1) % len(key)
    return answer


def block_decipher(ciphered: str, key: str) -> str:
    k = 0
    ciphered = [ord(value) - ord('a') for value in ciphered]
    key = [ord(value) - ord('a') for value in key]
    answer = ""
    for i in range(len(ciphered)):
        if ciphered[i] != ' ':
            answer += chr((ciphered[i] - key[k] + 26) % 26 + ord('a'))
            k = (k + 1) % len(key)
    return answer


s = "in this lecture i am going to address the following questions"
cur_key = "agreement"
ans = block_cipher(s, cur_key)
print(ans)
print(s)
print(block_decipher(ans, cur_key))
