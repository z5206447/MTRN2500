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
#include <iostream>

CustomVehicle::CustomVehicle()
{
	RectangularPrism *ret = new RectangularPrism();
	ret->setXLength(3.0);
	ret->setYLength(1.0);
	ret->setZLength(2.0);

	ret->setX(0.0);
	ret->setY(0.4);
	ret->setZ(0.0);
	ret->setColor(0.0, 0.6, 0.0);
	ret->setRotation(0.0);

	addShape(ret);

	TriangularPrism *Tri = new TriangularPrism();
	Tri->setALength(1.5);
	Tri->setAngle(30);
	Tri->setBLength(1.0);
	Tri->setDepth(2.0);

	Tri->setX(0.75);
	Tri->setY(1.4);
	Tri->setZ(0.0);
	Tri->setColor(1.0, 0.0, 1.0);
	Tri->setRotation(0.0);

	addShape(Tri);

	TrapezoidalPrism *Trap = new TrapezoidalPrism();
	Trap->setXLengthBottom(1.5);
	Trap->setXLengthTop(1.0);
	Trap->setOffset(0.2);
	Trap->setYLength(0.5);
	Trap->setZLength(2.0);
	
	Trap->setX(-0.75);
	Trap->setY(1.4);
	Trap->setZ(0.0);
	Trap->setColor(1.0, 1.0, 1.0);
	Trap->setRotation(0.0);

	addShape(Trap);

	Cylinder *FrontRight = new Cylinder();
	FrontRight->setRadius(0.8);
	FrontRight->setLength(0.1);

	FrontRight->setX(1.1);
	FrontRight->setY(0.0);
	FrontRight->setZ(1.1);
	FrontRight->setColor(1.0, 0.0, 0.0);
	FrontRight->setRotation(0.0);

	addShape(FrontRight);

	Cylinder *FrontLeft = new Cylinder();
	FrontLeft->setRadius(0.8);
	FrontLeft->setLength(0.1);

	FrontLeft->setX(1.1);
	FrontLeft->setY(0.0);
	FrontLeft->setZ(-1.1);
	FrontLeft->setColor(1.0, 0.0, 0.0);
	FrontLeft->setRotation(0.0);

	addShape(FrontLeft);

	Cylinder *BackRight = new Cylinder();
	BackRight->setRadius(0.4);
	BackRight->setLength(0.1);

	BackRight->setX(-1.1);
	BackRight->setY(0.0);
	BackRight->setZ(1.1);
	BackRight->setColor(0.0, 0.0, 1.0);
	BackRight->setRotation(0.0);

	addShape(BackRight);

	Cylinder *BackLeft = new Cylinder();
	BackLeft->setRadius(0.4);
	BackLeft->setLength(0.1);

	BackLeft->setX(-1.1);
	BackLeft->setY(0.0);
	BackLeft->setZ(-1.1);
	BackLeft->setColor(0.0, 0.0, 1.0);
	BackLeft->setRotation(0.0);

	addShape(BackLeft);
}

CustomVehicle::CustomVehicle(VehicleModel vm)
{

	for (std::vector<ShapeInit>::iterator it = vm.shapes.begin(); it != vm.shapes.end(); ++it) {


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
		if (it->type == TRIANGULAR_PRISM) {
			TriangularPrism *tri = new TriangularPrism();
			tri->setALength(it->params.tri.alen);
			tri->setBLength(it->params.tri.blen);
			tri->setAngle(it->params.tri.angle);
			tri->setDepth(it->params.tri.depth);


			tri->setX(it->xyz[0]);
			tri->setY(it->xyz[1]);
			tri->setZ(it->xyz[2]);
			tri->setColor(it->rgb[0], it->rgb[1], it->rgb[2]);
			tri->setRotation(it->rotation);

			addShape(tri);
		}
		if (it->type == TRAPEZOIDAL_PRISM) {
			TrapezoidalPrism *trap = new TrapezoidalPrism();
			trap->setXLengthBottom(it->params.trap.alen);
			trap->setXLengthTop(it->params.trap.blen);
			trap->setYLength(it->params.trap.height);
			trap->setZLength(it->params.trap.depth);
			trap->setOffset(it->params.trap.aoff);



			trap->setX(it->xyz[0]);
			trap->setY(it->xyz[1]);
			trap->setZ(it->xyz[2]);
			trap->setColor(it->rgb[0], it->rgb[1], it->rgb[2]);
			trap->setRotation(it->rotation);

			addShape(trap);


		}
		if (it->type == CYLINDER) {
			Cylinder *cyl = new Cylinder();
			cyl->setRadius(it->params.cyl.radius);
			cyl->setLength(it->params.cyl.depth);

			//need is rolling/ steering
			cyl->setRolling(it->params.cyl.isRolling);
			cyl->setSteering(it->params.cyl.isSteering);

			cyl->setX(it->xyz[0]);
			cyl->setY(it->xyz[1]);
			cyl->setZ(it->xyz[2]);
			cyl->setColor(it->rgb[0], it->rgb[1], it->rgb[2]);
			cyl->setRotation(it->rotation);

			addShape(cyl);


		}

	}
}


void CustomVehicle::draw()
{	
	glPushMatrix();
	positionInGL();
	for (std::vector<Shape *>::iterator it = shapes.begin(); it != shapes.end(); ++it) {
		//if (dynamic_cast<RectangularPrism*>(it*) != 0)
		
		(*it)->draw();
		//std::cout << "Its working";
	}
	glPopMatrix();



	/*
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
	*/
}
