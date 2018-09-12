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

#include "Messages.hpp"

CustomVehicle::CustomVehicle()
{
}

CustomVehicle::CustomVehicle(VehicleModel vm)
{

	for (std::vector<ShapeInit>::iterator it = vm.shapes.begin; it != vm.shapes.end(); ++it) {


		// check the shape type
		if (it->type == RECTANGULAR_PRISM) {
			RectangularPrism *ret = new RectangularPrism();
			ret->setXLength(it->params.rect.xlen);
			ret->setYLength(it->params.rect.ylen);
			ret->setZLength(it->params.rect.zlen);

			ret->setX(it->xyz[0]);
			ret->setY(it->xyz[1]);
			ret->setZ(it->xyz[2]);
			ret->setColor(it->rgb[0], it->rgb[1], it->rgb[2]);
			ret->setRotation(it->rotation);

			addShape(ret);
			

		}
		else if (it->type == TRIANGULAR_PRISM) {
			TriangularPrism *tri = new TriangularPrism();
			tri->setALength(it->params.tri.alen);
			tri->setBLength(it->params.tri.blen);
			tri->setAngle(it->params.tri.angle);


			tri->setX(it->xyz[0]);
			tri->setY(it->xyz[1]);
			tri->setZ(it->xyz[2]);
			tri->setColor(it->rgb[0], it->rgb[1], it->rgb[2]);
			tri->setRotation(it->rotation);

			addShape(tri);
		}
		else if (it->type == TRAPEZOIDAL_PRISM) {

		}
		else if (it->type == CYLINDER) {
			Cylinder *cyl = new Cylinder();
			cyl->setRadius(it->params.cyl.radius);
			cyl->setLength(it->params.cyl.depth);



			cyl->setX(it->xyz[0]);
			cyl->setY(it->xyz[1]);
			cyl->setZ(it->xyz[2]);
			cyl->setColor(it->rgb[0], it->rgb[1], it->rgb[2]);
			cyl->setRotation(it->rotation);


		}
		else {

		}

		// Add shape
	}
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
