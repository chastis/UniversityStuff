import math


def get_value_by_poly(poly: list, x: int) -> int:
    c = 0
    for i in range(len(poly)):
        x_pow = 1
        for j in range(i):
            x_pow *= x
        c += poly[i] * x_pow

    return c


def multiply_poly(a: list, b: list) -> list:
    c = [0 for _ in range(len(a) + len(b) - 1)]
    for i in range(len(a)):
        for j in range(len(b)):
            c[i + j] += a[i]*b[j]
    return c


def add_poly(a: list, b: list) -> list:
    if len(a) > len(b):
        c = a.copy()
        less_poly = b
    else:
        c = b.copy()
        less_poly = a
    for i in range(len(less_poly)):
        c[i] += less_poly[i]
    return c


def difference_poly(a: list, b: list) -> list:
    c = [0 for _ in range(max(len(a), len(b)))]

    for i in range(max(len(a), len(b))):
        if i >= len(a):
            c[i] = -b[i]
        elif i >= len(b):
            c[i] = a[i]
        else:
            c[i] = a[i] - b[i]
    return c


def get_max_pow(poly: list) -> int or None:
    for i in reversed(range(len(poly))):
        if abs(poly[i]) > 0.001:
            return i
    return None


def simplify(poly: list) -> list:
    c = poly.copy()
    for i in reversed(range(len(poly))):
        if round(c[i]) == 0:
            c.pop()
        else:
            return c

    return c


def is_int(poly: list) -> bool:
    for i in range(len(poly)):
        if abs(round(poly[i]) - poly[i]) > 0.001:
            return False
    return True


def to_int(poly: list) -> list:
    return [round(poly[x]) for x in range(len(poly))]


def divide(a: list, b: list, flag: bool = False) -> list or None:
    c = [0 for _ in range(len(a))]

    current = a.copy()

    b_max_pow = get_max_pow(b)

    while True:
        current_max_pow = get_max_pow(current)

        if current_max_pow is None:
            if flag:
                print("Div result ", end="")
                print_all_polies([c, current])

            if not is_int(c):
                print("Not integer")
                return None

            # return simplify(c)
            return to_int(simplify(c))

        if b_max_pow > current_max_pow:
            if flag:
                print("Div result ", end="")
                print_all_polies([c, current], True)

            return None

        current_x_coefficient = current_max_pow - b_max_pow
        current_coefficient = current[current_max_pow] / b[b_max_pow]

        divider_value = [0 for _ in range(current_x_coefficient + 1)]
        divider_value[-1] = current_coefficient

        c[current_x_coefficient] = current_coefficient

        divider = multiply_poly(b, divider_value)

        current = difference_poly(current, divider)


def get_base_x_values(n: int) -> list:
    return [i for i in range((n-1) // 2 + 1)]


def get_base_f_values(poly: list, x_values: list) -> list:
    return [get_value_by_poly(poly, x) for x in x_values]


def add_rat_poly(a_numerator: list, a_denominator: list, b_numerator: list, b_denominator: list) -> (list, list):
    if len(a_numerator) > len(b_numerator):
        c_numerator = a_numerator.copy()
        c_denominator = a_denominator.copy()

        less_numerator = b_numerator
        less_denominator = b_denominator
    else:
        c_numerator = b_numerator.copy()
        c_denominator = b_denominator.copy()

        less_numerator = a_numerator
        less_denominator = a_denominator

    for i in range(len(less_numerator)):
        c_numerator[i] = c_numerator[i]*less_denominator[i] + less_numerator[i]*c_denominator[i]
        c_denominator[i] *= less_denominator[i]
    return c_numerator, c_denominator


def gcd(a: int, b:int) -> int:
    if b < 0:
        k = -1
    else:
        k = 1
    a, b = abs(a), abs(b)
    while a > 0 and b > 0:
        a, b = b, a % b
    return (a + b) * k


def get_divisors(a: int) -> list:
    ans = []
    a = abs(a)
    for i in range(1, int(math.sqrt(a)) + 1):
        if a % i == 0:
            ans.append(i)
            ans.append(-i)
            if a != i*i:
                ans.append(a // i)
                ans.append(-a // i)
    return ans


def to_list_of_lists(a: list) -> list:
    for i in range(len(a)):
        a[i] = [a[i]]
    return a


def get_cartesian(a: list, b: list) -> list:
    ans = []
    for i in range(len(a)):
        for j in range(len(b)):
            ans.append(a[i] + b[j])
    return ans


def get_cartesian_all(f_values: list) -> list:
    divisors = []
    for value in f_values:
        if not divisors:
            divisors = [get_divisors(value)]
        else:
            divisors.append(get_divisors(value))
    ans = to_list_of_lists(divisors[0])
    for i in range(1, len(divisors)):
        ans = get_cartesian(ans, to_list_of_lists(divisors[i]))
    return ans


def lagrange(x: list, y: list, flag: bool = False) -> list or None:
    if len(x) != len(y):
        return None
    m = len(x)
    ans_numerator = [0]
    ans_denominator = [1]
    for i in range(m):
        temp_numerator = [y[i]]
        temp_denominator = [1]
        for j in range(m):
            if x[i] != x[j]:
                temp_numerator = multiply_poly(temp_numerator, [-x[j], 1])
                temp_denominator = multiply_poly(temp_denominator, [0, (x[i]-x[j])])
                temp_denominator = add_poly(temp_denominator, [temp_denominator[1]])
        ans_numerator, ans_denominator = add_rat_poly(ans_numerator, ans_denominator, temp_numerator, temp_denominator)

    for i in range(len(ans_numerator)):
        g = gcd(ans_numerator[i], ans_denominator[i])
        ans_numerator[i] //= g
        ans_denominator[i] //= g

    while len(ans_numerator) > 0 and ans_numerator[-1] == 0:
        ans_numerator.pop()
        ans_denominator.pop()

    if flag:
        print(end="Lagrange: ")
        print_rational_poly(ans_numerator, ans_denominator)

    for i in range(len(ans_denominator)):
        if ans_denominator[i] != 1:
            return None

    return ans_numerator


def print_cartesian_10fl(a: list) -> None:
    print(len(a))
    print(end="{")
    for i in range(10):
        if i < len(a):
            print(tuple(a[i]), end="; ")
        else:
            break
    print(end=" ...; ")
    for i in reversed(range(10)):
        if len(a)-i-1 >= 10:
            print(tuple(a[-i-1]), end="; ")
    print("}")


def get_two_dividers(poly: list) -> list or None:
    x_values = get_base_x_values(len(poly))
    f_values = get_base_f_values(poly, x_values)

    print("f_values")
    print(x_values)
    print(f_values)
    print("---divisors---")
    for i in range(len(f_values)):
        if f_values[i] == 0:
            first_poly = [-i, 1]

            second_poly = divide(poly, first_poly)
            print_all_polies([first_poly, second_poly])
            print("---end divisors---")
            return [first_poly, second_poly]
        print(get_divisors(f_values[i]))
    print("---end divisors---")

    cartesian_all = get_cartesian_all(f_values)
    print(print_cartesian_10fl(cartesian_all))

    edge = 10
    first_edge = []
    last_edge = []
    counter = 0
    for cartesian in cartesian_all:
        counter += 1
        if len(first_edge) < edge:
            first_edge.append(cartesian)
        elif len(last_edge) < edge:
            last_edge.append(cartesian)
        else:
            last_edge.pop(0)
            last_edge.append(cartesian)

        lagrange_poly = lagrange(x_values, cartesian)
        if lagrange_poly is None or len(lagrange_poly) <= 1:
            continue

        divider = divide(poly, lagrange_poly)
        if divider is None:
            continue
        print_all_polies([lagrange_poly, divider])
        print(counter)
        print('---------- first edge ------------')
        for i in range(edge):
            print("#### " + str(i))
            print("Cartesian: " + str(first_edge[i]))
            temp_lagrange = lagrange(x_values, first_edge[i], True)
            if temp_lagrange is None or len(temp_lagrange) <= 1:
                continue
            divide(poly, temp_lagrange, True)
        print('---------- end first edge ------------')
        print('---------- last edge ------------')
        for i in range(edge):
            print("#### " + str(i))
            print("Cartesian: " + str(last_edge[i]))
            temp_lagrange = lagrange(x_values, last_edge[i], True)
            if temp_lagrange is None or len(temp_lagrange) <= 1:
                continue
            divide(poly, temp_lagrange, True)
        print('---------- end last edge ------------')
        return [lagrange_poly, divider]

    print(counter)
    print('---------- first edge ------------')
    for i in range(edge):
        print("#### " + str(i))
        print("Cartesian: " + str(first_edge[i]))
        temp_lagrange = lagrange(x_values, first_edge[i], True)
        if temp_lagrange is None or len(temp_lagrange) <= 1:
            continue
        divide(poly, temp_lagrange, True)
    print('---------- end first edge ------------')
    print('---------- last edge ------------')
    for i in range(edge):
        print("#### " + str(i))
        print("Cartesian: " + str(last_edge[i]))
        temp_lagrange = lagrange(x_values, last_edge[i], True)
        if temp_lagrange is None or len(temp_lagrange) <= 1:
            continue
        divide(poly, temp_lagrange, True)
    print('---------- end last edge ------------')

    return None


def get_all_dividers(poly: list) -> list:
    if get_max_pow(poly) <= 1:
        return [poly]

    two_dividers = get_two_dividers(poly)
    if two_dividers is None:
        return [poly]
    if two_dividers[0][-1] < 0:
        two_dividers[0] = multiply_poly(two_dividers[0], [-1])
        two_dividers[1] = multiply_poly(two_dividers[1], [-1])
    first_dividers = get_all_dividers(two_dividers[0])
    second_dividers = get_all_dividers(two_dividers[1])

    return first_dividers + second_dividers


def print_rational(flag: bool, k: int, a: int, b: int = 1, is_doub: bool = False) -> bool:
    if a != 0:
        if flag:
            if a > 0:
                print(" + ", end="")
            else:
                print(" - ", end="")
        else:
            if a < 0:
                print("- ", end="")
            flag = True
        if abs(a) != 1 or k == 0:
            if is_doub:
                print('%.4f'%abs(a), end="")
            else:
                print(abs(a), end="")
        if k != 0:
            print("x", end="")
        if k != 0 and k != 1:
            print("^" + str(k), end="")
        if b != 1:
            print("/" + str(b), end="")
    return flag


def print_poly(a: list, is_doub: bool = False) -> None:
    k = len(a)-1
    flag = False
    for val in reversed(a):
        flag = print_rational(flag, k, val, 1, is_doub)
        k -= 1


def print_all_polies(a: list, is_doub: bool = False) -> None:
    for poly in a:
        print(end="(")
        print_poly(poly, is_doub)
        print(end=")")
    print()


def print_rational_poly(a_numerator: list, a_denominator: list) -> None:
    if len(a_numerator) != len(a_denominator):
        print("LENGTH NOT EQUAL")
        return None
    print(end="(")
    k = len(a_numerator) - 1
    flag = False
    for val in reversed(a_numerator):
        flag = print_rational(flag, k, val, a_denominator[k])
        k -= 1
    print(")")


def main() -> None:
    # polynomial_1 = [-4, 0, 1, -4, 0, 1, 212, 0, 2, -4, 0, 1, -4, 0, 1, -4, 0, 1]
    # polynomial_2 = [5, 0, 1, 32, 323, 3, 42, 12, 43, 134, 23]
    # polynomial_1 = [-4, 0, 1]
    # polynomial_2 = [5, 0, 1]
    # polynomial_1 = [-1, 0, 1, -1, 0, 1]
    # polynomial_2 = [1, 0, 1, 0, 1]

    # polynomial_3 = multiply_poly(polynomial_1, polynomial_2)
    # polynomial_3 = [-324, -81, 0, 0, 4, 1]
    polynomial_3 = [90, 129, 55, 6]
    # polynomial_3 = [-20, 0, 1, 0, 1]
    # polynomial_3 = [120, 138, -82, -46, 14]

    print_all_polies([polynomial_3])

    all_dividers = get_all_dividers(polynomial_3)

    print_all_polies(all_dividers)

    c = [1]
    for dividers in all_dividers:
        c = multiply_poly(c, dividers)

    print_all_polies([c])


if __name__ == '__main__':
    main()
