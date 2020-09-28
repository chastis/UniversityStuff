#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
#include <map>
#include <set>
#include <type_traits>
#include <variant>
#include <functional>
#include <bitset>
#include <thread>

using namespace std;

class Vector {
    
    vector<double> els;
    
    bool column;
    
public:
    
    Vector(int size, bool column = true) : column(column) {
        els.resize(size);
    }
    
    Vector() : Vector(0) {}
    
    void transpose() {
        column = !column;
    }
    
    bool isColumn() const {
        return column;
    }

    double get(int pos) const {
        return els[pos];
    }
    
    void set(int pos, double val) {
        els[pos] = val;
    }
    
    int getSize() const {
        return els.size();
    }
    
    Vector multiplication(double a) {
        Vector v(els.size());
        for (int i = 0; i < els.size(); i++) {
            v.set(i, els[i] * a);
        }
        return v;
    }
    
    Vector plus(const Vector& v) {
        int size = this->getSize();
        Vector sum(size);
        for (int i = 0; i < size; i++) {
            sum.set(i, this->get(i) + v.get(i));
        }
        return sum;
    }
    
    Vector& operator = (const Vector& v) {
        this->els = v.els;
        return *this;
    }
    
    void resize(int size) {
        els.resize(size);
    }
    
    double scalarMult(Vector v) {
        double sum = 0;
        for (int i = 0; i < this->getSize(); i++) {
            sum += this->get(i) * v.get(i);
        }
        return sum;
    }
    
    double euclideanDistance(Vector v) const {
        double sum = 0;
        for (int i = 0; i < this->getSize(); i++) {
            function<double(double)> sqr =
                [] (double a) -> double { return a * a; };
            sum += sqr(this->els[i] - v.get(i));
        }
        return sqrt(sum);
    }
    
    void erase(int pos) {
        els.erase(els.begin() + pos);
    }
    
    void print() {
        for (auto it: els) cout << it << " ";
        cout << endl;
    }
        
};

class Matrix {

    vector<Vector> rows;
    
    static double goodness(double a) {
        return fabs(a);
    }
    
    static int findBestUp(const Matrix& c, int pos) {
        int bestPos = pos;
        double goods = goodness(c.get(pos, pos));
        for (int i = pos; i < c.getRowsCount();  i++) {
            double curGoods = goodness(c.get(i, pos));
            if (curGoods > goods) {
                goods = curGoods;
                bestPos = i;
            }
        }
        return bestPos;
    }
    
    static void forthGauss(Matrix& c) {
        int n = c.getRowsCount();
        for (int i = 0; i < n; i++) {
            int k = findBestUp(c, i);
            if (k != i) c.swap(i, k);
            double x = 1 / c.get(i, i);
            c.setRow(i, c.getRow(i).multiplication(x));
            for (int j = i + 1; j < n; j++) {
                Vector v = c.getRow(i).multiplication(-c.get(j, i));
                c.setRow(j, c.getRow(j).plus(v));
            }
        }
    }
    
    static void backGauss(Matrix& c) {
        int n = c.getRowsCount();
        for (int i = n - 1; i > 0; i--) {
            for (int j = i - 1; j >= 0; j--) {
                Vector v = c.getRow(i).multiplication(-c.get(j, i));
                c.setRow(j, c.getRow(j).plus(v));
            }
        }
    }
    
    static Matrix plusIdentityMatrixAtRight(const Matrix& m) {
        int n = m.getRowsCount();
        Matrix c(n, 2 * n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                c.set(i, j, m.get(i, j));
            }
            c.set(i, n + i, 1);
        }
        return c;
    }
    
    static Matrix cutMatrixFromRight(const Matrix& m) {
        int n = m.getRowsCount();
        Matrix r(n, n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                r.set(i, j, m.get(i, n + j));
            }
        }
        return r;
    }
    
public:
    
    Matrix(int n, int m) {
        rows.resize(n);
        for (auto& row: rows) {
            row.resize(m);
            for (int i = 0; i < m; i++) {
                row.set(i, 0);
            }
        }
    }
    
    Matrix(int n) : Matrix(n, n) {}
    
    Matrix() : Matrix(0) {}
    
    double get(int i, int j) const {
        return rows[i].get(j);
    }
    
    void set(int i, int j, double val) {
        rows[i].set(j, val);
    }

    Vector getRow(int pos) const {
        return rows[pos];
    }
    
    void setRow(int pos, const Vector& row) {
        rows[pos] = row;
    }
    
    void swap(int i, int j) {
        Vector mid = rows[i];
        rows[i] = rows[j];
        rows[j] = mid;
    }
    
    int getRowsCount() const {
        return rows.size();
    }
    
    int getColumnsCount() const {
        return rows[0].getSize();
    }
    
    Vector multiplication(const Vector& v) {
        int n = v.getSize();
        Vector m(n);
        if (!v.isColumn()) {
            m.transpose();
        }
        for (int i = 0; i < n; i++) {
            double sum = 0;
            for (int j = 0; j < n; j++) {
                if (v.isColumn()) {
                    sum += v.get(j) * this->get(i, j);
                } else {
                    sum += v.get(j) * this->get(j, i);
                }
            }
            m.set(i, sum);
        }
        return m;
    }
    
    Matrix multiplication(const Matrix& x) {
        int n = this->getRowsCount();
        int m = this->getColumnsCount();
        int p = x.getColumnsCount();
        Matrix c(n, p);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < p; j++) {
                double sum = 0;
                for (int k = 0; k < m; k++) {
                    sum += this->get(i, k) * x.get(k, j);
                }
                c.set(i, j, sum);
            }
        }
        return c;
    }
    
    Matrix plus(const Matrix& x) {
        int n = this->getRowsCount();
        int m = this->getColumnsCount();
        Matrix s(n, m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                s.set(i, j, this->get(i, j) + x.get(i, j));
            }
        }
        return s;
    }
    
    Matrix inversedMatrix() {
        Matrix c = plusIdentityMatrixAtRight(*this);
        forthGauss(c);
        backGauss(c);
        return cutMatrixFromRight(c);
    }
    
    Matrix& operator = (const Matrix& m) {
        int n = m.getRowsCount();
        rows.resize(n);
        for (int i = 0; i < n; i++) {
            rows[i] = m.getRow(i);
        }
        return *this;
    }
    
    void print() {
        int n = rows.size(), m = rows[0].getSize();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) cout << rows[i].get(j) << " ";
            cout << endl;
        }
    }
    
};

struct SLE {
    Matrix a;
    Vector b;
    Vector x;
    
    SLE(const Matrix& a, const Vector& b, const Vector& x) : a(a), b(b), x(x) {}
    
    SLE() {}
    
    int getSize() {
        return b.getSize();
    }
};

class SleGenerator {
    
    static double randDouble() {
        double a = (double)rand() / RAND_MAX;
        return MIN_DVAL + a * (MAX_DVAL - MIN_DVAL);
    }
    
    static int randInt() {
        return MIN_IVAL + rand() % (MAX_IVAL - MIN_IVAL);
    }
    
    static Vector randAnsVector(int size) {
        Vector v(size);
        for (int i = 0; i < size; i++) {
            v.set(i, randInt());
        }
        return v;
    }
    
    static Matrix randMatrix(int n) {
        Matrix a(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                a.set(i, j, randDouble());
            }
        }
        return a;
    }
    
    static SLE generateSle(Matrix a) {
        int n = a.getRowsCount();
        Vector ans = randAnsVector(n);
        Vector b(n);
        for (int i = 0; i < n; i++) {
            b.set(i, ans.scalarMult(a.getRow(i)));
        }
        return SLE(a, b, ans);
    }
    
    static void makeDiagonallyDominant(Matrix& a) {
        int n = a.getRowsCount();
        for (int i = 0; i < n; i++) {
            int sum = 0;
            for (int j = 0; j < n; j++) {
                if (i == j) continue;
                sum += fabs(a.get(i, j));
            }
            double d = sum + fabs(randDouble());
            d *= rand() % 2 ? -1 : 1;
            a.set(i, i, d);
        }
    }
    
public:
    
    static const double MIN_DVAL, MAX_DVAL;
    static const int MIN_IVAL, MAX_IVAL;
    
    static SLE random(int n) {
        Matrix a = randMatrix(n);
        return generateSle(a);
    }
    
    static SLE diagonallyDominant(int n) {
        Matrix a = randMatrix(n);
        makeDiagonallyDominant(a);
        return generateSle(a);
    }
    
    static SLE gilberts(int n) {
        Matrix a(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                a.set(i, j, (double)1 / (i + j + 1));
            }
        }
        return generateSle(a);
    }
    
};

const double SleGenerator::MIN_DVAL = -9.99, SleGenerator::MAX_DVAL = 9.99;
const int SleGenerator::MIN_IVAL = -9, SleGenerator::MAX_IVAL = 9;

class SleSolver {
    
    static Vector generateInitialGuess(int size) {
        Vector ans(size);
        for (int i = 0; i < size; i++) {
            ans.set(i, 1);
        }
        return ans;
    }
    
    static Matrix createExtendedMatrix(SLE sle) {
        int n = sle.getSize();
        Matrix c(n, n + 1);
        for (int i = 0; i < n; i++) {
            Vector row = sle.a.getRow(i);
            row.resize(n + 1);
            row.set(n, sle.b.get(i));
            c.setRow(i, row);
        }
        return c;
    }
    
    static Matrix findEliminationMatrix(int k, const Matrix& c) {
        int n = c.getRowsCount();
        Matrix m(n);
        for (int i = 0; i < n; i++) {
            m.set(i, i, 1);
        }
        for (int i = k + 1; i < n; i++) {
            m.set(i, k, -c.get(i, k) / c.get(k, k));
        }
        return m;
    }
    
    static double goodness(double a) {
        return fabs(a);
    }
    
    static int findBestDown(int k, const Matrix& c) {
        int bestPos = k;
        double goods = goodness(c.get(k, k));
        for (int i = k; i < c.getRowsCount();  i++) {
            double curGoods = goodness(c.get(i, k));
            if (curGoods > goods) {
                goods = curGoods;
                bestPos = i;
            }
        }
        return bestPos;
    }
    
    static void fixPivot(int k, Matrix& c) {
        int i = findBestDown(k, c);
        if (i != k) c.swap(i, k);
    }
    
    static Vector getUpperDiagonalAnswer(const Matrix& c) {
        int n = c.getRowsCount();
        Vector ans(n);
        for (int i = n - 1; i >= 0; i--) {
            double sum = 0;
            for (int j = i + 1; j < n; j++) {
                sum += c.get(i, j) * ans.get(j);
            }
            ans.set(i, (c.get(i, n) - sum) / c.get(i, i));
        }
        return ans;
    }
    
    static Matrix getDiagonalMatrix(const Matrix& a) {
        int n = a.getRowsCount();
        Matrix d(n);
        for (int i = 0; i < n; i++) {
            d.set(i, i, a.get(i, i));
        }
        return d;
    }
    
    static Matrix getStrictUpperTriangularMatrix(const Matrix& a) {
        int n = a.getRowsCount();
        Matrix u(n);
        for (int i = 0; i < n - 1; i++) {
            for (int j = i + 1; j < n; j++) {
                u.set(i, j, a.get(i, j));
            }
        }
        return u;
    }
    
    static Matrix getStrictLowerTriangularMatrix(const Matrix& a) {
        int n = a.getRowsCount();
        Matrix l(n);
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < i; j++) {
                l.set(i, j, a.get(i, j));
            }
        }
        return l;
    }
    
    static Matrix inverseOfDiagonalMatrix(const Matrix& d) {
        int n = d.getRowsCount();
        Matrix inv(n);
        for (int i = 0; i < n; i++) {
            inv.set(i, i, 1 / d.get(i, i));
        }
        return inv;
    }
    
public:
    
    static const int MAX_ITS;

    static Vector gauss(SLE sle) {
        Matrix c = createExtendedMatrix(sle);
        int n = c.getRowsCount();
        for (int i = 0; i < n - 1; i++) {
            fixPivot(i, c);
            Matrix m = findEliminationMatrix(i, c);
            c = m.multiplication(c);
        }
        return getUpperDiagonalAnswer(c);
    }
    
    static pair<Vector, int> jacobi(SLE sle, double e) {
        int n = sle.getSize();
        Matrix d = getDiagonalMatrix(sle.a);
        Matrix dInv = inverseOfDiagonalMatrix(d);
        Matrix u = getStrictUpperTriangularMatrix(sle.a);
        Matrix l = getStrictLowerTriangularMatrix(sle.a);
        Matrix lPlusU = l.plus(u);
        Vector x = generateInitialGuess(n), xNext(n);
        int its = 0;
        do {
            x = xNext;
            xNext = dInv.multiplication(sle.b.plus((lPlusU.multiplication(x)).multiplication(-1)));
            its++;
        } while (xNext.euclideanDistance(x) > e && its < MAX_ITS);
        return {xNext, its};
    }
    
    static pair<Vector, int> seidel(SLE sle, double e) {
        int n = sle.getSize();
        Matrix d = getDiagonalMatrix(sle.a);
        Matrix u = getStrictUpperTriangularMatrix(sle.a);
        Matrix l = getStrictLowerTriangularMatrix(sle.a);
        Matrix dPlusL = d.plus(l);
        Matrix dPlusLInv = dPlusL.inversedMatrix();
        Vector xPrev, x =  generateInitialGuess(n);
        int its = 0;
        do {
            xPrev = x;
            x = dPlusLInv.multiplication(sle.b.plus((u.multiplication(xPrev)).multiplication(-1)));
            its++;
        } while (x.euclideanDistance(xPrev) > e && its < MAX_ITS);
        return {x, its};
    }
        
};

const int SleSolver::MAX_ITS = 100000;

class DeviationCalculator {
    
public:
    
    static double absoluteDeviation(const Vector& expected, const Vector& actual) {
        return expected.euclideanDistance(actual);
    }
    
    static double relativeDeviation(const Vector& expected, const Vector& actual) {
        Vector z(expected.getSize());
        for (int i = 0; i < expected.getSize(); i++) z.set(i, 0);
        return absoluteDeviation(expected, actual) / actual.euclideanDistance(z);
    }
    
};

class Interface {
    
public:
    
    void run() {
        srand(time(nullptr));
        while (true) {
            int size;
            cout << "Matrix size = "; cin >> size;
            int type;
            cout << "Matrix type (1 - random, 2 - diagonally dominant, 3 - gilbert) = "; cin >> type;
            SLE sle;
            switch (type) {
                case 1 : { sle = SleGenerator::random(size); break; }
                case 2 : { sle = SleGenerator::diagonallyDominant(size); break; }
                case 3 : { sle = SleGenerator::gilberts(size); break; }
                default: break;
            }
            int algo;
            cout << "Solving algorithm (1 - gauss, 2 - jacobi, 3 - seidel) = "; cin >> algo;
            double e;
            if (algo == 2 || algo == 3) {
                cout << "Epsilon = "; cin >> e;
            }
            Vector answer;
            if (algo == 1) {
                answer = SleSolver::gauss(sle);
            } else if (algo == 2 || algo == 3) {
                pair<Vector, int> ansP;
                if (algo == 2) ansP = SleSolver::jacobi(sle, e);
                else ansP = SleSolver::seidel(sle, e);
                cout << "Number of iterations = " << ansP.second << endl;
                answer = ansP.first;
            } else {
                break;
            }
            cout << "Absolute deviation = " << DeviationCalculator::absoluteDeviation(sle.x, answer) << endl;
            cout << "Relative deviation = " << DeviationCalculator::relativeDeviation(sle.x, answer) << endl;
            bool flag;
            cout << "More information (0 - no, 1 - yes) = "; cin >> flag;
            if (!flag) {
                cout << endl;
                continue;
            }
            cout << "A:" << endl; sle.a.print();
            cout << "b: "; sle.b.print();
            cout << "real x: "; sle.x.print();
            cout << "found x: "; answer.print();
            cout << endl;
        }
    }
    
};

int main() {
    Interface().run();
}

