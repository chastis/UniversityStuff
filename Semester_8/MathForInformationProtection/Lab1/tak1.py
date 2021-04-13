def gcd(a, b, x, y, prev1_x, prev1_y, prev2_x, prev2_y):
    if a == 0:
        print('a = ' + str(a) + ', b = ' + str(b))
        return b, 0, 1
    
    print(str(b) + ' = ' + str(b//a) + '*' + str(a) + ' + '+ str(b%a))
    new_x = prev2_x - b//a * prev1_x
    new_y = prev2_y - b//a * prev1_y
    #print(str(b%a) + ' = ' + str(new_x) + '*a + (' + str(new_y)+ ')*b')
    d, x1, y1 = gcd(b%a, a, 0, 0, new_x, new_y, prev1_x, prev1_y)
    x = y1 - (b//a) * x1
    y = x1
    return d, x, y

def get_s_t(a, b, c, ans_gcd):
    return c//ans_gcd[0]*ans_gcd[1], c//ans_gcd[0]*ans_gcd[2]
    
in_a, in_b, in_c = 247678868885655 , 230200504829220 , 35175
ans = gcd(in_a, in_b, 0, 0, 1, 0, 0, 1)
print(ans)
print(get_s_t(in_a, in_b, in_c, ans))