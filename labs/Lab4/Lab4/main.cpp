#include "SFML/Graphics.hpp"
#include "SFML/OpenGL.hpp"
#include <gl/glut.h>
#include <iostream>

enum Rotation {
	X,
	Y,
	Z,
	NX,
	NY,
	NZ,
	NO
};

const float ANGLE = 1;
const int AXIS_LENGTH = 150;

////////////////////////////////////////////////////////////
/// Entry point of application
////////////////////////////////////////////////////////////
int main()
{
	sf::ContextSettings Settings;
	Settings.depthBits = 24; // Request a 24 bits depth buffer
	Settings.stencilBits = 8;  // Request a 8 bits stencil buffer
	Settings.antialiasingLevel = 2;  // Request 2 levels of antialiasing
									 // Create the main window
	sf::Window App(sf::VideoMode(800, 600, 32), "SFML OpenGL", sf::Style::Close, Settings);

	// Create a clock for measuring time elapsed
	sf::Clock Clock;

	//prepare OpenGL surface for HSR
	glClearDepth(1.f);
	glClearColor(0.509f, 0.925f, 0.952f, 0.f);
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);

	//// Setup a perspective projection & Camera position
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.f, 1.f, 1.f, 300.0f);//fov, aspect, zNear, zFar

	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	GLfloat material_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_diffuse);

	// Lighting

	GLfloat light1_diffuse[] = { 1.0, 1.0, 1.0 };

	GLfloat light1_position[] = { 0.0, 1.0, 1.0, 1.0 };

	glEnable(GL_LIGHT1);

	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);

	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);

	glColorMaterial(GL_FRONT, GL_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	Rotation rotation = NO;
	float angleX = 30, angleY = 60, angleZ = 0;
	bool axis = true;
	// Start game loop
	while (App.isOpen())
	{
		// Process events
		sf::Event Event;
		while (App.pollEvent(Event))
		{
			// Close window : exit
			if (Event.type == sf::Event::Closed)
				App.close();

			// Escape key : exit
			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape))
				App.close();

			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::F1)) {
				rotation = X;
			}

			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::F2)) {
				rotation = NX;
			}

			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::F3)) {
				rotation = Y;
			}

			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::F4)) {
				rotation = NY;
			}

			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::F5)) {
				rotation = Z;
			}

			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::F6)) {
				rotation = NZ;
			}

			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::F10)) {
				axis = !axis;
			}

		}

		//Prepare for drawing
		// Clear color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Apply some transformations for the cube
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(0.f, 0.f, -200.f);

		switch (rotation) {
		case X: angleX += ANGLE; break;
		case Y: angleY += ANGLE; break;
		case Z: angleZ += ANGLE; break;
		case NX: angleX -= ANGLE; break;
		case NY: angleY -= ANGLE; break;
		case NZ: angleZ -= ANGLE; break;
		case NO: break;
		}
		rotation = NO;
		glRotatef(angleX, 1.f, 0.f, 0.f);
		glRotatef(angleY, 0.f, 1.f, 0.f);
		glRotatef(angleZ, 0.f, 0.f, 1.f);

		//Draw a dumbbell
		GLUquadricObj *quadObj = gluNewQuadric();

		//gluQuadricNormals(quadObj, GLU_SMOOTH);   // Create Smooth Normals ( NEW )
		//gluQuadricTexture(quadObj, GL_TRUE);

		glPushMatrix();
		glColor3f(0.133f, 0.145f, 0.145f);
		gluQuadricDrawStyle(quadObj, GLU_FILL);
		glTranslated(0, 0, -50);
		gluCylinder(quadObj, 5, 5, 100, 10, 10);
		glPopMatrix();

		glPushMatrix();
		glColor3f(0.505f, 0.627f, 0.635f);
		gluQuadricDrawStyle(quadObj, GLU_FILL);
		glTranslated(0, 0, 50);
		gluCylinder(quadObj, 25, 25, 50, 10, 10);
		glPopMatrix();

		glPushMatrix();
		glColor3f(0.505f, 0.627f, 0.635f);
		gluQuadricDrawStyle(quadObj, GLU_FILL);
		glTranslated(0, 0, -100);
		gluCylinder(quadObj, 25, 25, 50, 10, 10);
		glPopMatrix();

		glPushMatrix();
		glColor3f(1.f, 1.f, 1.f);
		gluQuadricDrawStyle(quadObj, GLU_FILL);
		glTranslated(0, 0, -100);
		gluDisk(quadObj, 0, 25, 10, 10);
		glPopMatrix();

		glPushMatrix();
		glColor3f(1.f, 1.f, 1.f);
		gluQuadricDrawStyle(quadObj, GLU_FILL);
		glTranslated(0, 0, 50);
		gluDisk(quadObj, 0, 25, 10, 10);
		glPopMatrix();

		glPushMatrix();
		glColor3f(1.f, 1.f, 1.f);
		gluQuadricDrawStyle(quadObj, GLU_FILL);
		glTranslated(0, 0, -50);
		gluDisk(quadObj, 0, 25, 10, 10);
		glPopMatrix();

		glPushMatrix();
		glColor3f(1.f, 1.f, 1.f);
		gluQuadricDrawStyle(quadObj, GLU_FILL);
		glTranslated(0, 0, 100);
		gluDisk(quadObj, 0, 25, 10, 10);
		glPopMatrix();

		if (axis) {
			glLineWidth(3);
			glBegin(GL_LINES);

			glColor3f(1, 0, 0);
			glVertex3f(-AXIS_LENGTH, 0.f, 0);
			glVertex3f(AXIS_LENGTH, 0.f, 0);

			glColor3f(0, 1, 0);
			glVertex3f(0.f, -AXIS_LENGTH, 0);
			glVertex3f(0.f, AXIS_LENGTH, 0);

			glColor3f(0, 0, 1);
			glVertex3f(0.f, 0.f, -AXIS_LENGTH);
			glVertex3f(0.f, 0.f, AXIS_LENGTH);

			glEnd();
		}

		// Finally, display rendered frame on screen
		App.display();
	}

	return EXIT_SUCCESS;
}
