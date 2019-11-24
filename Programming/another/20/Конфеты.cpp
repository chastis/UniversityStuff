#include <iostream>
#include <cstdio>
#include <conio.h>

using namespace std;

#define ll long long
#define BASE 1000000000000000
#define step_BASE 15

struct longnumber {
       ll digits[1000];
       int length;
};

void print_longnumber(longnumber A){
     int i, j, d, k_zero;
     ll copy;
     //cout << A.digits[0] << endl;
     cout << A.digits[A.length - 1];
     for (i = A.length - 2; i >= 0; i--){
         copy = A.digits[i];
         d = 0;
         if (copy == 0)
            d = 1;
         else
             while (copy != 0){
                   d ++;
                   copy /= 10;
             }
         k_zero = step_BASE - d;
         for (j = 0; j < k_zero; j++)
             cout << 0;
         cout << A.digits[i];
     }
     cout << endl;
}

longnumber sum_b_b(longnumber A, longnumber B){
           longnumber C;
           if (B.length > A.length){
              C = A;
              A = B;
              B = C;
           }
           C.length = A.length + 1;
           C.digits[C.length - 1] = 0;

           //print_longnumber(A); print_longnumber(B); getch();
           for (int i = 0; i < A.length; i++)
               C.digits[i] = A.digits[i] + B.digits[i];
           for (int i = 0; i < A.length; i++){
               C.digits[i + 1] += C.digits[i] / BASE;
               C.digits[i] %= BASE;
           }
           if (C.digits[C.length - 1] == 0)
              C.length --;
           //print_longnumber(C); getch();

           return C;
}

longnumber difference_b_b(longnumber A, longnumber B){
           longnumber C;
           C.length = A.length;
           for (int i = B.length; i < A.length; i++)
               B.digits[i] = 0;

           for (int i = 0; i < A.length; i++)
               C.digits[i] = A.digits[i] - B.digits[i];
           for (int i = 0; i < A.length - 1; i++)
               if (C.digits[i] < 0){
                  C.digits[i] += BASE;
                  C.digits[i + 1] -= 1;
               }
           while (C.length > 0 && C.digits[C.length - 1] == 0)
                 C.length --;

           return C;
}

longnumber product_b_sm(longnumber A, int X){
           longnumber C;
           C.length = A.length + 1;
           C.digits[C.length - 1] = 0;

           for (int i = 0; i < A.length; i++)
               C.digits[i] = A.digits[i] * X;
           for (int i = 0; i < A.length; i++){
               C.digits[i + 1] += C.digits[i] / BASE;
               C.digits[i] %= BASE;
           }
           if (C.digits[C.length - 1] == 0)
              C.length --;

           return C;
}

longnumber division_b_sm(longnumber A, int X){
           longnumber C;
           C.length = A.length;
           ll cur, carry = 0;

           //cout << X << ' '; print_longnumber(C); getch();
           for (int i = A.length - 1; i >= 0; i--){
               cur = A.digits[i] + carry * BASE;
               carry = cur % X;
               C.digits[i] = cur / X;
           }
           while (C.length > 0 && C.digits[C.length - 1] == 0)
                 C.length --;
           //print_longnumber(C); getch();

           return C;
}

longnumber factorial_div(longnumber A,int X){
           for (int i = 1; i <= X; i++){
                //cout << A.length << endl;
               //print_longnumber(A); getch();
               A = division_b_sm(A, i);
           }

           return A;
}

longnumber factorial_prod(int start, int X){
           longnumber P;
           P.length = 1;
           P.digits[0] = 1;
           for (int i = start; i <= X; i++){
               P = product_b_sm(P, i);
               //print_longnumber(P); getch();
           }

           return P;
}

longnumber Permutation_with_replay(int N, int M){
           longnumber ans;
           //print_longnumber(ans); getch();
           if (M > N){
              ans = factorial_prod(M + 1, M + N);
              ans = factorial_div(ans, N);
           }
           else {
                ans = factorial_prod(N + 1, M + N);
                ans = factorial_div(ans, M);
           }
           /*ans = factorial_div(ans, N);
           //print_longnumber(ans); getch();
           ans = factorial_div(ans, M);
           //print_longnumber(ans); getch();*/

           return ans;
}

int main(){
    //freopen("Eiioaou.txt","r",stdin);

    int N, S;
    cin >> N >> S;

    //freopen("CON","r",stdin);

    longnumber Answer, Sum, Add;
    Answer = Permutation_with_replay(N, S - 1);
    //print_longnumber(Answer); getch();
    Sum.length = 1;
    Sum.digits[0] = 0;
    for (int i = N / 2 + 1; i <= N; i++){
        //cout << N - i << ' ' << S - 2 << endl;
        if (i == N / 2 + 1){
           Add =  Permutation_with_replay(N - i, S - 2); 
           Sum = sum_b_b(Sum, Add);
        }
        else {
             //cout << N - i + 1 << ' ' << N - i + 1 + S - 2 << endl; getch();
             Add = product_b_sm(Add, N - i + 1);
             Add = division_b_sm(Add, N - i + 1 + S - 2);
             Sum = sum_b_b(Sum, Add);
        }
        //Sum = sum_b_b(Sum, Permutation_with_replay(N - i, S - 2));
    }
    Answer = difference_b_b(Answer, product_b_sm(Sum, S));

    print_longnumber(Answer);

    //getch();
    return 0;
}
