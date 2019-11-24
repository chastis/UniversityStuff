#include "expression.h"
#include <cmath>

float Expression :: unary_plus(float a) {
	return a;
} 
float Expression :: unary_minus(float a) {
	return -a;
} 
float Expression :: binary_plus(float a, float b) {
	return a + b;
} 
float Expression :: binary_minus(float a, float b) {
	return a - b;
} 
float Expression :: multiplication(float a, float b) {
	return a * b;
} 
float Expression :: division(float a, float b) {
	return a / b;
} 
float Expression :: exponent(float a) {
	return exp(a);
} 
