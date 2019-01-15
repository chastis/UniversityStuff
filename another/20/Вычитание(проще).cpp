#include <iostream>
//#include <conio.h>

using namespace std;

#define ll long long
#define BASE 10000000000000000
#define step_BASE 16

struct longnumber {
       int length;
       ll *digits;
};

void Print_longnumber(longnumber A);

longnumber Read_longnumber(){
           longnumber A;
           string S;
           int i,j;
           cin >> S;

           int k_zero = (step_BASE - S.size() % step_BASE) % step_BASE;
           string zeroes = "";
           for (i = 0; i < k_zero; i++)
               zeroes += "0";
           S = zeroes + S;

           A.length = S.size() / step_BASE;
           A.digits = new ll[A.length];
           for (i = 0; i < A.length; i++)
               A.digits[i] = 0;
           for (i = 0; i < A.length; i++)
               for (j = 0; j < step_BASE; j++){
                   A.digits[i] *= 10;
                   A.digits[i] += (int) S[S.size() - step_BASE * (i + 1) + j] - 48;
               }

           return A;
}

longnumber Difference(longnumber A, longnumber B){
           longnumber C, B_copy;
           int i;
           C.length = A.length;
           C.digits = new ll[C.length];
           B_copy.digits = new ll[A.length];
           for (i = 0; i < B.length; i++)
               B_copy.digits[i] = B.digits[i];
           for (i = B.length; i < C.length; i++)
               B_copy.digits[i] = 0;

           for (i = 0; i < A.length; i++)
               C.digits[i] = A.digits[i] - B_copy.digits[i];
           for (i = 0; i < A.length; i++){
               if (C.digits[i] < 0){
                  C.digits[i] += BASE;
                  C.digits[i+1] -= 1;
               }
           }
           while (C.length > 0 && C.digits[C.length-1] == 0)
                 C.length--;
           if (C.length == 0) C.length = 1;

           return C;
}

void Print_longnumber(longnumber A){
     int i,j,d,k_zero;
     ll cur;
     cout << A.digits[A.length-1];
     for (i = A.length - 2; i >= 0; i--){
         d = 0;
         cur = A.digits[i];
         while (cur != 0){
               d++;
               cur /= 10;
         }
         k_zero = step_BASE - d;
         for (j = 0; j < k_zero; j++)
             cout << 0;
         cout << A.digits[i];
     }
     cout << endl;
}

int main(){
    longnumber A,B;
    A = Read_longnumber();
    B = Read_longnumber();

    Print_longnumber(Difference(A,B));

    //getch();
}
