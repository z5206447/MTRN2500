#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <unistd.h>
#include <sys/time.h>
#elif defined(WIN32)
#include <Windows.h>
#include <tchar.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <unistd.h>
#include <sys/time.h>
#endif


#include "CustomVehicle.h"
#include "RectangularPrism.h"
#include "TriangularPrism.h"
#include "TrapezoidalPrism.h"
#include "Cylinder.h"

CustomVehicle::CustomVehicle()
{
}

void CustomVehicle::draw()
{	
	int x = 5;
	int y = 2;
	int z = 6;

	glPushMatrix();
	positionInGL();
	glTranslatef(0.0, y, 0.0);
	RectangularPrism Rectangle(x, y, z, 1, 0, 0);
	Rectangle.draw();

	glPushMatrix();
	glTranslatef(x, -y, -z);
	TriangularPrism Triangle(x, 2 * y, z * 2, 90, 0, 1, 0);
	Triangle.draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0, (1 + y), 0.0);
	TrapezoidalPrism Trapezoid(x, 1.0, z, 1.0, 1, 1, 1);
	Trapezoid.draw();
	glPopMatrix();
	
	glTranslatef(0, -y, 0);
	distance += speed;

	glPushMatrix();
	glTranslatef(-x, 0, -z);
	glRotatef(-distance, 0, 0, 0.1);
	Cylinder Cylinder1(2, 1, 0, 0, 1);
	Cylinder1.draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-x, 0, z);
	glRotatef(-distance, 0, 0, 0.1);
	Cylinder Cylinder2(2, 1, 0, 0, 1);
	Cylinder2.draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(x, 0, z);
	glRotatef(-steering, 0, 0.1, 0);
	glRotatef(-distance, 0, 0, 0.1);
	Cylinder Cylinder3(2, 1, 0, 0, 1);
	Cylinder3.draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(x, 0.0, -z);
	glRotatef(-steering, 0, 0.1, 0);
	glRotatef(-distance, 0, 0, 0.1);
	Cylinder Cylinder4(2, 1, 0, 0, 1);
	Cylinder4.draw();
	glPopMatrix();
	
	glPopMatrix();



	glPopMatrix();

}
