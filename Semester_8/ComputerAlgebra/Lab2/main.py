
class Monomial:

    parameter_names = 'xyzabcde'

    def __init__(self, coef: float, parameters_power: list) -> None:
        self.coef = coef
        self.powers = parameters_power

    def __str__(self) -> str:
        if self.coef < 0:
            value = "- "
        else:
            value = ""

        if self.is_empty():
            return value + str('%.4f'%abs(self.coef))

        if abs(self.coef) == 1:
            value += ""
        else:
            value += str('%.4f'%abs(self.coef))+ ""

        for i in range(len(self.powers)):
            if self.powers[i] == 1:
                value += Monomial.parameter_names[i] + ""
            elif self.powers[i] != 0:
                value += Monomial.parameter_names[i] + "^" + str(self.powers[i]) + " "
        return value

    @staticmethod
    def gcd(a, b):
        new_monomial = Monomial(1, [])
        for i in range(min(len(a.powers), len(b.powers))):
            new_monomial.powers.append(min(a.powers[i], b.powers[i]))
        return new_monomial


    def is_empty(self):
        for power in self.powers:
            if power != 0:
                return False
        return True

    def __eq__(self, other):
        return not self.__lt__(other) and not self.__gt__(other)

    def __lt__(self, other):
        for i in range(min(len(self.powers), len(other.powers))):
            if self.powers[i] > other.powers[i]:
                return True
            if self.powers[i] < other.powers[i]:
                return False
        return len(self.powers) < len(other.powers)

    def __le__(self, other):
        for i in range(min(len(self.powers), len(other.powers))):
            if self.powers[i] > other.powers[i]:
                return True
            if self.powers[i] < other.powers[i]:
                return False
        return len(self.powers) <= len(other.powers)

    def __ge__(self, other):
        return not self.__lt__(other)

    def __gt__(self, other):
        return not self.__le__(other)

    def __len__(self):
        return len(self.powers)

    def __mul__(self, other):
        while len(self) < len(other):
            self.powers.append(0)
        while len(self) > len(other):
            other.powers.append(0)

        new_monomial = Monomial(self.coef*other.coef, [])
        for i in range(len(self)):
            new_monomial.powers.append(self.powers[i]+other.powers[i])
        return new_monomial

    def __truediv__(self, other):
        while len(self) < len(other):
            self.powers.append(0)
        while len(self) > len(other):
            other.powers.append(0)

        new_monomial = Monomial(self.coef/other.coef, [])
        for i in range(len(other)):
            new_monomial.powers.append(self.powers[i] - other.powers[i])
        return new_monomial

    def sub(self, coef):
        return Monomial(self.coef-coef, self.powers)

    def is_good(self):
        if self.is_empty():
            return False
        for power in self.powers:
            if power < 0:
                return True
        return False

    def is_almost_good(self):
        if self.is_empty():
            return True
        for power in self.powers:
            if power < 0:
                return True
        return False

    def evaluate(self, vals):
        ans = self.coef
        for i in range(len(self)):
            ans *= vals[i]**self.powers[i]
        return ans


class Polynomial:

    def __init__(self, monomials: list) -> None:
        self.monomials = monomials

    def __str__(self):
        value = ""
        for i in range(len(self.monomials)):
            if self.monomials[i].coef < 0:
                value += " " + str(self.monomials[i])
            elif i != 0:
                value += " + " + str(self.monomials[i])
            else:
                value += str(self.monomials[i])
        return value

    def multiply_monomial(self, monom):
        new_poly = Polynomial([])
        for i in range(len(self)):
            new_poly.monomials.append(self.monomials[i] * monom)
        return new_poly

    def head(self):
        return self.monomials[0]

    @staticmethod
    def gcd_head(a, b):
        return Monomial.gcd(a.head(), b.head())

    @staticmethod
    def div_head(a, b):
        return a.head() / b.head()

    def __len__(self):
        return len(self.monomials)

    def __sub__(self, other):
        new_poly = Polynomial(self.monomials.copy())
        for i in range(len(other)):
            was = False
            for j in range(len(new_poly)):
                if other.monomials[i] == new_poly.monomials[j]:
                    new_poly.monomials[j] = new_poly.monomials[j].sub(other.monomials[i].coef)
                    was = True
            if not was:
                new_poly.monomials.append(other.monomials[i])
                new_poly.monomials[-1].coef *= -1

        i = 0
        while i < len(new_poly):
            if abs(new_poly.monomials[i].coef) < 0.0000001:
                new_poly.monomials.pop(i)
            else:
                i += 1

        new_poly.monomials.sort()
        return new_poly

    def evaluate(self, vals):
        ans = 0
        for i in range(len(self)):
            ans += self.monomials[i].evaluate(vals)
        return ans


class Buchberger:

    def __init__(self, system: list) -> None:
        self.system = system
        self.connected = {}

    def _find_connected(self) -> ():
        for i in range(len(self.system)):
            for j in range(i+1, len(self.system)):
                if not Polynomial.gcd_head(self.system[i], self.system[j]).is_empty() and not (i, j) in self.connected:
                    self.connected[(i, j)] = 1
                    return i, j
        return -1, -1

    def _simplify(self, new_poly: list) -> list:
        simplified = False
        if len(self.connected) < 5 or len(self.connected) > 18: 
            
            print("--------------------------simplification start " + str(len(self.connected)) + "--------------------------")
        while not simplified and len(new_poly) > 0:
            simplified = True
            for i in range(len(self.system)):
                div = new_poly.head() / self.system[i].head()
                if not div.is_good():
                    simplified = False
                    dob = self.system[i].multiply_monomial(div)
                    # print("\tdob = ", dob)
                    new_poly = new_poly - dob
                    if len(self.connected) < 5 or len(self.connected) > 18: 
            
                        print("\tdiv = ", div)
                        print("\tf = ", self.system[i], "; i =  ", str(i))
                        print("\tnew_poly = ", new_poly, "\n")
                    break
        if len(self.connected) < 5 or len(self.connected) > 18: 
            
            print("--------------------------simplification end--------------------------\n\n")
        return new_poly

    def get_basis(self) -> list:
        counter = 0
        while True:
            connected = self._find_connected()
            if connected == (-1, -1):
                break
            a, b = connected
            gcd = Polynomial.gcd_head(self.system[a], self.system[b])
            if len(self.connected) < 5 or len(self.connected) > 18: 
                print(a, ' ', b)
                print("a = " + str(self.system[a]), "$$$  b = " + str(self.system[b]), "$$$ " + str(gcd))

            qa = self.system[a].head() / gcd
            qb = self.system[b].head() / gcd
            if len(self.connected) < 5 or len(self.connected) > 18: 
                print("qa = " + str(qa))
                print("qb = " + str(qb))

            multy_a_qb = self.system[a].multiply_monomial(qb)
            multy_b_qa = self.system[b].multiply_monomial(qa)
            if len(self.connected) < 5 or len(self.connected) > 18: 
                print("a * qb = ", multy_a_qb)
                print("b * qa = ", multy_b_qa)

            new_poly = multy_a_qb - multy_b_qa
            new_poly.monomials.sort()
            if len(self.connected) < 5 or len(self.connected) > 18: 
                print(" new_poly: ", new_poly)
            new_poly = self._simplify(new_poly)
            if len(new_poly) > 0:
                self.system.append(new_poly)
                if len(self.connected) < 5 or len(self.connected) > 18: 
                    print(len(self.system))
            else:
                counter += 1

        print(counter)
        print(len(self.connected))
        print(self.connected)

        return self.system

    def reduce(self):
        answer = self.system.copy()
        i = 0
        while i < len(answer):
            for j in range(len(answer)):
                if i != j and not (answer[i].head() / answer[j].head()).is_good():
                    answer.pop(i)
                    i -= 1
                    break
            i += 1
        return answer


def main() -> None:
    f = [Polynomial([Monomial(1, [1, 1, 0]), Monomial(1, [0, 0, 1]), Monomial(-1, [0, 0, 0])]),
         Polynomial([Monomial(1, [1, 0, 0]), Monomial(-1, [0, 1, 0]), Monomial(-1, [0, 0, 2])]),
         Polynomial([Monomial(1, [2, 0, 0]), Monomial(-2, [0, 1, 0]), Monomial(1, [0, 0, 0])])]

    print("| " + str(f[0]))
    print("| " + str(f[1]))
    print("| " + str(f[2]))

    f[0].monomials.sort()
    f[1].monomials.sort()
    f[2].monomials.sort()

    print("sorted")
    print("| " + str(f[0]))
    print("| " + str(f[1]))
    print("| " + str(f[2]))

    print(Monomial.gcd(f[0].monomials[0], f[2].monomials[1]))
    print(Polynomial.gcd_head(f[0], f[0]))

    print(f[0].head().is_empty())
    buch = Buchberger(f)
    basis = buch.get_basis()

    vals = [0.5, -0.5, -0.5]
    for i in basis:
        print(i, " #### ", i.evaluate(vals))

    reduced = buch.reduce()
    print("----------------------------------- reduced -----------------------------------")
    for i in reduced:
        print(i, " #### ", i.evaluate(vals))


if __name__ == "__main__":
    main()
