#include "turtle.h"
#include <iostream>
#include <cmath>
#include <graphics.h>

using namespace std;

Turtle :: Turtle(float x, float y, float a) {
	this->x = x;
	this->y = y;
	this->a = a;
}

void Turtle :: forward(float d) {
	float x = this->x - d * cos(a);
	float y = this->y - d * sin(a);
	line(this->x, this->y, x, y);
	this->x = x;
	this->y = y;
}

void Turtle :: rotate(float a) {
	a *= M_PI / 180;
	this->a -=  a;
}

float Turtle :: getX() {
	return x;
}

float Turtle :: getY() {
	return y;
}

void Turtle :: setX(float x) {
	this->x = x;
}

void Turtle :: setY(float y) {
	this->y = y;
}
