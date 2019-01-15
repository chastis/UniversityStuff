#ifndef TURTLE_H
#define TURTLE_H

class Turtle {
	
	private:
		float x, y, a;
	
	public:
		Turtle(float, float, float);
		void forward(float);
		void rotate(float);	
		float getX();
		float getY();
		void setX(float);
		void setY(float);
};

#endif // TURTLE_H
