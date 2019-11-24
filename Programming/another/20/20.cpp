#include <iostream>

using namespace std;

const int MAX_DIGITS = 1000, MINUS_CONST = 120;

class BinaryNumber {
	
	private:
		int length;
		char bytes[MAX_DIGITS];
		
		void normalize() {
			for (int i = length + 1; i < MAX_DIGITS; i++) {
				bytes[i] = 0;
			}
		}
	
	public:
		BinaryNumber() {
			length = 1;
			bytes[0] = 0;
			bytes[1] = 0;
		}
		
		BinaryNumber(string s) {
			*this = createFromString(s);
		}
		
		BinaryNumber(int n) {
			*this = createFromInt(n);
		}
		
		static BinaryNumber createFromInt(int n) {
			BinaryNumber bin;
			if (n < 0) {
				bin.bytes[0] = MINUS_CONST;
				n *= -1;
			} else {
				bin.bytes[0] = 0;
			}
			bin.length = 0;
			do {
				bin.bytes[++bin.length] = n % 2;
				n /= 2;
			} while (n);
			return bin;
		}
		
		int toInt() {
			int pow = 1, n = 0;
			for (int i = 1; i <= length; i++) {
				n += pow * bytes[i];
				pow *= 2;
			}
			return n * (bytes[0] == 0 ? 1 : -1);
		}
		
		static BinaryNumber createFromString(string s) {
			BinaryNumber bin;
			bin.length = s.size() - 1;
			bin.bytes[0] = (s[0] == '+' ? 0 : MINUS_CONST);
			for (int i = 1; i < s.size(); i++) {
				bin.bytes[i] = (s[s.size() - i] == '0' ? 0 : 1);
			}
			return bin;
		}
		
		string toString() {
			string s(length + 1, ' ');
			s[0] = (bytes[0] == 0 ? '+' : '-');
			for (int i = 1; i <= length; i++) {
				s[i] = (bytes[length - i + 1] == 0 ? '0' : '1');
			}
			return s;
		}
		
		BinaryNumber operator + (BinaryNumber x) {
			if (bytes[0] == 0 && x.bytes[0] == MINUS_CONST) {
				return *this - x;
			} else if (bytes[0] == MINUS_CONST && x.bytes[0] == 0) {
				return x - *this;
			}
			BinaryNumber a, b;
			if (*this > x) {
				a = *this;
				b = x;
			} else {
				a = x;
				b = *this;
			}
			b.normalize();
			BinaryNumber c;
			c.bytes[0] = (bytes[0] == 0 ? 0 : MINUS_CONST);
			c.length = a.length + 1;
			c.bytes[c.length] = 0;
			for (int i = 1; i <= a.length; i++) {
				c.bytes[i] = a.bytes[i] + b.bytes[i];
			}
			for (int i = 1; i <= a.length; i++) {
			   c.bytes[i + 1] += c.bytes[i] / 2;
			   c.bytes[i] %= 2;
			}
			if (c.bytes[c.length] == 0) {
			   c.length --;
			}
			return c;
		}
		
		BinaryNumber operator - (BinaryNumber x) {
			if (bytes[0] == 0 && x.bytes[0] == MINUS_CONST) {
				x.bytes[0] = 0;
				return *this + x;
			} else if (bytes[0] == MINUS_CONST && x.bytes[0] == 0) {
				x.bytes[0] = MINUS_CONST;
				return *this + x;
			}
			BinaryNumber c;
			BinaryNumber a, b;
			if (*this > x) {
				c.bytes[0] = (bytes[0] == 0 ? 0 : MINUS_CONST);
				a = *this;
				b = x;
			} else {
				c.bytes[0] = (bytes[0] == 0 ? MINUS_CONST : 0);
				a = x;
				b = *this;
			}
			c.length = a.length;
			b.normalize();
			for (int i = 1; i <= a.length; i++) {
				c.bytes[i] = a.bytes[i] - b.bytes[i];	
			}
			for (int i = 1; i <= a.length - 1; i++) {
				if (c.bytes[i] < 0) {
					c.bytes[i] += 2;
				  	c.bytes[i + 1] -= 1;
				}	
			}
			while (c.length > 0 && c.bytes[c.length] == 0) {
				c.length --;	
			}
			return c;
		}
		
		BinaryNumber operator * (BinaryNumber x) {
			BinaryNumber a, b;
			if (*this > x) {
				a = *this;
				b = x;
			} else {
				a = x;
				b = *this;
			}
			BinaryNumber c;
			if (bytes[0] == 0 && x.bytes[0] == MINUS_CONST || 
				bytes[0] == MINUS_CONST && x.bytes[0] == 0) {
				c.bytes[0] = MINUS_CONST;
			} else {
				c.bytes[0] = 0;
			}
			c.normalize();
			c.length = a.length + b.length;
			for (int i = 1; i <= a.length; i++) {
				for (int j = 1; j <= b.length; j++) {
					c.bytes[i + j - 1] += a.bytes[i] * b.bytes[j];	
				}
			}
			for (int i = 1; i < c.length; i++){
			   c.bytes[i + 1] += c.bytes[i] / 2;
			   c.bytes[i] %= 2;
			}
			while (c.length > 1 && c.bytes[c.length] == 0) {
				c.length --;
			}
			return c;
		}
		
		BinaryNumber operator / (int x) {
			BinaryNumber c;
			if (bytes[0] == 0 && x >= 0 ||
				bytes[0] == MINUS_CONST && x < 0) {
				c.bytes[0] = 0;		
			} else {
				c.bytes[0] = MINUS_CONST;
			}
			x *= (x < 0 ? -1 : 1);
			c.length = length;
			char cur, carry = 0;
			for (int i = length; i >= 1; i--){
				cur = bytes[i] + carry * 2;
				carry = cur % x;
				c.bytes[i] = cur / x;
			}
			while (c.length > 0 && c.bytes[c.length] == 0) {
				c.length --;	
			}
			return c;
		}
		
		bool operator > (BinaryNumber x) {
			if (length > x.length) {
				return true;
			}
			if (length < x.length) {
				return false;
			}
			for (int i = length; i >= 1; i--) {
				if (bytes[i] > x.bytes[i]) {
					return true;
				}
				if (bytes[i] < x.bytes[i]) {
					return false;
				}
			}
			return false;
		}
		
		BinaryNumber operator = (BinaryNumber x) {
			length = x.length;
			for (int i = 0; i <= length; i++) {
				bytes[i] = x.bytes[i];
			}
			return *this;
		}
};

int main() {
}
