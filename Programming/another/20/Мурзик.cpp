#include <iostream>
#include <cmath>
//#include <cstdlib>
//#include <conio.h>

using namespace std;

#define ll long long
#define BASE 10000000
#define step_BASE 7
#define Min_Length_for_Karatsuba 1000000

struct longnumber {
       int length;
       ll digits[150000];
};

longnumber Number[20][100000];
int N, K, Pow[20];
longnumber P[20];

void Print(longnumber X){
     int i,j,copy,d,k_zero;
     if (X.sign == false)
        cout << '-';
     cout << X.digits[X.length - 1];
     for (i = X.length - 2; i >= 0; i --){
         d = 0;
         copy = X.digits[i];
         do {
            copy /= 10;
            d ++;
         } while (copy != 0);
         k_zero = step_BASE - d;
         for (j = 0; j < k_zero; j ++)
             cout << 0;
         cout << X.digits[i];
     }
     cout << endl;
}

void   Convert(string S, longnumber *X){
       int k_zero,i,j;
       string zeroes = "";
       k_zero = (step_BASE - S.size() % step_BASE) % step_BASE;
       for (i = 0; i < k_zero; i ++)
           zeroes += "0";
       S = zeroes + S;

       X->length = S.size() / step_BASE;
       for (i = 0; i < X->length; i ++){
           X->digits[i] = 0;
           for (j = 0; j < step_BASE; j ++){
               X->digits[i] *= 10;
               X->digits[i] += (int) S[S.size() - (i + 1) * step_BASE + j] - 48;
           }
       }
}

void Find_Pow(){
     Pow[0] = 1;
     for (int i = 1; i < 20; i ++)
         Pow[i] = Pow[i - 1] * 2;
}

bool First_bigger_or_equals_Second(longnumber A, longnumber B){
     if (A.sign == true && B.sign == false)
        return true;
     else if (A.sign == false && B.sign == true)
             return false;
     else if (A.sign == true){
              if (A.length > B.length)
                 return true;
              else if (A.length < B.length)
                      return false;
              else {
                      int i;
                      for (i = A.length - 1; i >= 0; i --)
                          if (A.digits[i] != B.digits[i])
                             break;
                      if (i == -1)
                         return true;
                      else return A.digits[i] > B.digits[i];
              }
     }
     else {
           if (A.length < B.length)
              return true;
           else if (A.length > B.length)
                   return false;
           else {
                  int i;
                  for (i = A.length - 1; i >= 0; i --)
                      if (A.digits[i] != B.digits[i])
                         break;
                  if (i == -1)
                     return true;
                  else return A.digits[i] < B.digits[i];
           }
     }
}

longnumber Sum(longnumber A, longnumber B){
           longnumber C;
           if (A.length < B.length){
              C = A;
              A = B;
              B = C;
           }
           for (int i = B.length; i < A.length; i ++)
               B.digits[i] = 0;
           C.length = A.length + 1;
           C.digits[C.length - 1] = 0;

           for (int i = 0; i < A.length; i ++)
               C.digits[i] = A.digits[i] + B.digits[i];

           for (int i = 0; i < A.length; i ++){
               C.digits[i + 1] += C.digits[i] / BASE;
               C.digits[i] %= BASE;
           }
           while (C.length > 1 && C.digits[C.length - 1] == 0)
                 C.length --;

           return C;
}

longnumber Different(longnumber A, longnumber B){
           longnumber C;
           C.length = A.length;
           for (int i = B.length; i < A.length; i ++)
               B.digits[i] = 0;

           for (int i = 0; i < C.length; i ++)
               C.digits[i] = A.digits[i] - B.digits[i];
           for (int i = 0; i < C.length - 1; i ++)
               if (C.digits[i] < 0){
                  C.digits[i] += BASE;
                  C.digits[i + 1] --;
               }
           while (C.length > 1 && C.digits[C.length - 1] == 0)
                 C.length --;

           return C;
}

longnumber Product(longnumber A, longnumber B){
           longnumber C;
           int i,j;
           C.length = A.length + B.length;
           for (i = 0; i < C.length; i ++)
               C.digits[i] = 0;

           for (i = 0; i < A.length; i ++)
               for (j = 0; j < B.length; j ++)
                   C.digits[i + j] += A.digits[i] * B.digits[j];
           for (i = 0; i < C.length - 1; i ++){
               C.digits[i + 1] += C.digits[i] / BASE;
               C.digits[i] %= BASE;
           }
           while (C.length > 1 && C.digits[C.length - 1] == 0)
                 C.length --;

           return C;
}

longnumber Karatsuba(longnumber A, longnumber B){
           if (max(A.length,B.length) >= Min_Length_for_Karatsuba){
               if (A.length > B.length){
                  for (int i = B.length; i < A.length; i ++)
                      B.digits[i] = 0;
                  B.length = A.length;
               }
               else if (B.length > A.length){
                       for (int i = A.length; i < B.length; i ++)
                           A.digits[i] = 0;
                       A.length = B.length;
               }
               int N = A.length, M = N / 2;
               longnumber A0,A1,B0,B1;
               A0.length = M;
               A1.length = N - M;
               B0.length = M;
               B1.length = N - M;
               for (int i = 0; i < M; i ++)
                   A0.digits[i] = A.digits[i];
               for (int i = M; i < N; i ++)
                   A1.digits[i - M] = A.digits[i];
               for (int i = 0; i < M; i ++)
                   B0.digits[i] = B.digits[i];
               for (int i = M; i < N; i ++)
                   B1.digits[i - M] = B.digits[i];
               longnumber Prod_A0_B0, Prod_A1_B1, under_BASE_M;
               Prod_A0_B0 = Karatsuba(A0,B0);
               Prod_A1_B1 = Karatsuba(A1,B1);
               under_BASE_M = Different(Different(Karatsuba(Sum(A0,A1),Sum(B0,B1)),Prod_A0_B0),Prod_A1_B1);
               for (int i = under_BASE_M.length - 1; i >= 0; i --)
                   under_BASE_M.digits[i + M] = under_BASE_M.digits[i];
               under_BASE_M.length += M;
               for (int i = 0; i < M; i ++)
                   under_BASE_M.digits[i] = 0;
               for (int i = Prod_A1_B1.length - 1; i >= 0; i --)
                   Prod_A1_B1.digits[i + 2 * M] = Prod_A1_B1.digits[i];
               for (int i = 0; i < 2 * M; i ++)
                   Prod_A1_B1.digits[i] = 0;
               Prod_A1_B1.length += 2 * M;
               return Sum(Sum(Prod_A0_B0,under_BASE_M),Prod_A1_B1);
           }
           else return Product(A,B);
}

longnumber Find_Command_Product(int Command){
           longnumber P;
           int i = 0, j, next, Step_2;
           bool sign;
           while (K > Pow[i])
                 i ++; //cout << Pow[i] << endl; getch();
           Step_2 = i;
           //cout << i << endl;
           for (i = K; i < Pow[Step_2]; i ++){
               Number[Command][i].sign = true;
               Number[Command][i].length = 1;
               Number[Command][i].digits[0] = 1;
           }
           for (i = 1; i <= Step_2; i ++){
               for (j = 0; j < Pow[Step_2]; j += Pow[i]){
                   next = j + Pow[i - 1];
                   //cout << j << ' ' << next << endl; getch();
                   //Print(Number[Command][j]); Print(Number[Command][next]);
                   if (Number[Command][j].sign == true && Number[Command][next].sign == true)
                      sign = true;
                   else if (Number[Command][j].sign == false && Number[Command][next].sign == false)
                           sign = true;
                   else if (Number[Command][j].sign == true && Number[Command][next].sign == false)
                           sign = false;
                   else sign = false;
                   Number[Command][j] = Karatsuba(Number[Command][j],Number[Command][next]);
                   Number[Command][j].sign = sign;
                   //Print(Number[Command][j]); getch();
               }
           }
           P = Number[Command][0];
               
           return P;
}

int main(){
    //freopen("Ìóðçèê.txt","r",stdin);
    //ios::sync_with_stdio(0);
    int i,j;
    string S;
    cin >> N >> K;
    for (i = 0; i < K; i ++)
        for (j = 0; j < N; j ++){
            cin >> S;
            if (S[0] == '-'){
               S.erase(0,1);
               Number[j][i].sign = false;
               //cout << i << ' ' << j << endl;
            }
            else Number[j][i].sign = true;
            Convert(S,&Number[j][i]);
            //Print(Number[j][i]); getch();
        }
    //freopen("CON","r",stdin);
    
    Find_Pow();
    for (i = 0; i < N; i ++){
        P[i] = Find_Command_Product(i);
        //Print(P[i]); getch();
        //cout << P[i].digits[0] << endl;
    }

    int Max = 0;
    for (i = 1; i < N; i ++){
        if (First_bigger_or_equals_Second(P[i],P[Max]))
           Max = i;
    }
    
    cout << Max + 1 << endl;
    
    //getch();
    return 0;
}
