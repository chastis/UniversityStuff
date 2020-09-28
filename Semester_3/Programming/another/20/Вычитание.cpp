#include<iostream>
#include <cstring>
using namespace std;

string sa,sb;
int *a,*b,*c,lsa,lsb,maxl;

void make_a_b()
     {
      int i;
      for(i=0; i<lsa; i++) a[i] = (int)sa[lsa-i-1]-48;
      for(i=0; i<lsb; i++) b[i] = (int)sb[lsb-i-1]-48;
      for(i=lsa; i<maxl; i++) a[i] = 0;
      for(i=lsb; i<maxl; i++) b[i] = 0;
      for(i=0; i<maxl; i++) c[i] = 0;
     }

void difference(int sign)
{
     int i;
     if (sign==1)
        for(i=0; i<lsa; i++){
           if (i<lsa-1) {
              a[i+1]--;
              c[i]+=10+a[i];}
           else c[i]+=a[i];
           c[i]-=b[i];
           if (c[i] / 10 > 0){
              c[i+1]++;
              c[i]%=10;} 
           }
     else
        for(i=0; i<lsb; i++){
           if (i<lsb) {
              b[i+1]--;
              c[i]+=10+b[i];}
           else c[i]+=b[i];
           c[i]-=a[i];
           if (c[i] / 10 > 0){
              c[i+1]++;
              c[i]%=10;}
              } 
}

void write_number(int sign)
{
 int i=maxl-1,j;
 if (sign==0) cout << "-";
 while ((i>=0) && (c[i]==0)) i--;
 if (i==-1)
    cout << 0;
 else
    for(j=i; j>=0; j--) cout << c[j];
}

int main()
{
    int sign;
    cin >> sa;
    cin >> sb;
    lsa=sa.length();
    lsb=sb.length();
    maxl = max(lsa,lsb);
    a = new int[maxl];
    b = new int[maxl];
    c = new int[maxl];
    make_a_b();
    sign = 1;
    difference(sign);
    write_number(sign);
}
