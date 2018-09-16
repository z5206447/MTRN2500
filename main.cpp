
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <sstream>
#include <map>

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


#include "Camera.hpp"
#include "Ground.hpp"
#include "KeyManager.hpp"

#include "Shape.hpp"
#include "Vehicle.hpp"

#include "RemoteDataManager.hpp"
#include "Messages.hpp"
#include "HUD.hpp"
#include "ObstacleManager.hpp"

#include "RectangularPrism.h"
#include "TriangularPrism.h"
#include "TrapezoidalPrism.h"
#include "Cylinder.h"
#include "CustomVehicle.h"

#include <Windows.h>
#include <Xinput.h>

void display();
void reshape(int width, int height);
void idle();

void keydown(unsigned char key, int x, int y);
void keyup(unsigned char key, int x, int y);
void special_keydown(int keycode, int x, int y);
void special_keyup(int keycode, int x, int y);

void mouse(int button, int state, int x, int y);
void dragged(int x, int y);
void motion(int x, int y);

using namespace std;
using namespace scos;

// Used to store the previous mouse location so we
//   can calculate relative mouse movement.
int prev_mouse_x = -1;
int prev_mouse_y = -1;

// vehicle control related variables
Vehicle * vehicle = NULL;
double speed = 0;
double steering = 0;

// default goal location
std::deque<GoalState> goals;

std::map<int, Vehicle *> otherVehicles;

int frameCounter = 0;

//int _tmain(int argc, _TCHAR* argv[]) {
int main(int argc, char ** argv) {

	const int WINDOW_WIDTH = 800;
	const int WINDOW_HEIGHT = 600;

	glutInit(&argc, (char**)(argv));
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("MTRN3500 - GL");

	Camera::get()->setWindowDimensions(WINDOW_WIDTH, WINDOW_HEIGHT);

	glEnable(GL_DEPTH_TEST);

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);

	glutKeyboardFunc(keydown);
	glutKeyboardUpFunc(keyup);
	glutSpecialFunc(special_keydown);
	glutSpecialUpFunc(special_keyup);

	glutMouseFunc(mouse);
	glutMotionFunc(dragged);
	glutPassiveMotionFunc(motion);

	// -------------------------------------------------------------------------
	// Please uncomment the following line of code and replace 'MyVehicle'
	//   with the name of the class you want to show as the current 
	//   custom vehicle.
	// -------------------------------------------------------------------------

	//vehicle = new MyVehicle();
	vehicle = new CustomVehicle();

	// add test obstacles
	ObstacleManager::get()->addObstacle(Obstacle(10,10, 1));
	ObstacleManager::get()->addObstacle(Obstacle(10,-10, 1));
	ObstacleManager::get()->addObstacle(Obstacle(-10,10, 1));
	ObstacleManager::get()->addObstacle(Obstacle(-10,-10, 1));

	// add test goal
	GoalState g;
	g.x = 25;
	g.z = 0;
	goals.push_back(g);


	glutMainLoop();

	if (vehicle != NULL) {
		delete vehicle;
	}

	return 0;
}

void drawGoals()
{
	for (int i = 0; i < goals.size(); ++i) {
		GoalState goal = goals[i];

		glPushMatrix();
		glTranslatef(goal.x, 0, goal.z);
		glRotated(90, -1, 0, 0);
		static GLUquadric * quad = gluNewQuadric();

		// make first goal purple
		if (i == 0)
			glColor3f(1, .3, 1);
		else
			glColor3f(1, 1, 1);

		gluCylinder(quad, .5, .5, 10, 5, 1);
		glPopMatrix();
	}
}


void drawtest() {

	//RectangularPrism Rectangle(2, 3, 4, 1, 0, 0);
	//Rectangle.draw();

	//TriangularPrism Triangle(2, 3, 5, 90, 1, 0, 0);
	//Triangle.draw();

	//TrapezoidalPrism Trapezoid(10, 3, 6, 3, 1, 0, 0);
	//Trapezoid.draw();

	//Cylinder Cylinder(10, 10, 1, 0, 0);
	//Cylinder.draw();
}

void display() {
	frameCounter++;
	// -------------------------------------------------------------------------
	//  This method is the main draw routine. 
	// -------------------------------------------------------------------------

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if(Camera::get()->isPursuitMode() && vehicle != NULL) {
		double x = vehicle->getX(), y = vehicle->getY(), z = vehicle->getZ();
		double dx = cos(vehicle->getRotation() * 3.141592765 / 180.0);
		double dy = sin(vehicle->getRotation() * 3.141592765 / 180.0);
		Camera::get()->setDestPos(x + (-20 * dx), y + 15, z + (-20 * dy));
		Camera::get()->setDestDir(dx, -0.25, dy);
	}
	Camera::get()->updateLocation();
	Camera::get()->setLookAt();

	Ground::draw();
	
	// draw other vehicles
	for(std::map<int, Vehicle *>::iterator iter = otherVehicles.begin(); iter != otherVehicles.end(); ++iter) 
		iter->second->draw();

	// draw my vehicle
	if (vehicle != NULL) {
		vehicle->draw();

	}

	// draw obstacles
	ObstacleManager::get()->drawAll();

	// draw goals
	drawGoals();

	// draw HUD
	HUD::Draw();

	// Draw My Shapes
	drawtest();
	glutSwapBuffers();
};

void reshape(int width, int height) {

	Camera::get()->setWindowDimensions(width, height);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
};

void remoteDriver(Vehicle * vehicle, double x, double z, double r, double speed_, double steering_)
{
	// filter 
	const double kSmoothingFactor = 0.5;
	vehicle->setX(vehicle->getX() * kSmoothingFactor + x * (1 - kSmoothingFactor));
	vehicle->setZ(vehicle->getZ() * kSmoothingFactor + z * (1 - kSmoothingFactor));

	vehicle->setRotation(r);
	vehicle->steering = steering_;
	vehicle->speed = speed_;
}

double getTime()
{
#if defined(WIN32)
	LARGE_INTEGER freqli;
	LARGE_INTEGER li;
	if(QueryPerformanceCounter(&li) && QueryPerformanceFrequency(&freqli)) {
		return double(li.QuadPart) / double(freqli.QuadPart);
	}
	else {
		static ULONGLONG start = GetTickCount64();
		return (GetTickCount64() - start) / 1000.0;
	}
#else
	struct timeval t;
	gettimeofday(&t, NULL);
	return t.tv_sec + (t.tv_usec / 1000000.0);
#endif
}

void idle() {
	XINPUT_STATE state;
	if (KeyManager::get()->isAsciiKeyPressed('a')) {
		Camera::get()->strafeLeft();
	}

	if (KeyManager::get()->isAsciiKeyPressed('c')) {
		Camera::get()->strafeDown();
	}

	if (KeyManager::get()->isAsciiKeyPressed('d')) {
		Camera::get()->strafeRight();
	}

	if (KeyManager::get()->isAsciiKeyPressed('s')) {
		Camera::get()->moveBackward();
	}

	if (KeyManager::get()->isAsciiKeyPressed('w')) {
		Camera::get()->moveForward();
	}

	if (KeyManager::get()->isAsciiKeyPressed(' ')) {
		Camera::get()->strafeUp();
	}

	speed = 0;
	steering = 0;

	if (KeyManager::get()->isSpecialKeyPressed(GLUT_KEY_LEFT) || ((state.Gamepad.wButtons) && (XINPUT_GAMEPAD_DPAD_LEFT) == 1)) {
		steering = Vehicle::MAX_LEFT_STEERING_DEGS * -1;   
	}

	if (KeyManager::get()->isSpecialKeyPressed(GLUT_KEY_RIGHT) || ((state.Gamepad.wButtons) && (XINPUT_GAMEPAD_DPAD_RIGHT) == 1)) {
		steering = Vehicle::MAX_RIGHT_STEERING_DEGS * -1;
	}

	if (KeyManager::get()->isSpecialKeyPressed(GLUT_KEY_UP) || ((state.Gamepad.wButtons) && (XINPUT_GAMEPAD_DPAD_UP) == 1)) {
		speed = Vehicle::MAX_FORWARD_SPEED_MPS;
	}

	if (KeyManager::get()->isSpecialKeyPressed(GLUT_KEY_DOWN) || ((state.Gamepad.wButtons) && (XINPUT_GAMEPAD_DPAD_DOWN) == 1)) {
		speed = Vehicle::MAX_BACKWARD_SPEED_MPS;
	}

	// attempt to do data communications every 4 frames if we've created a local vehicle
	if(frameCounter % 4 == 0 && vehicle != NULL) {

		// if not connected, attempt to connect every 2 seconds
		if(!RemoteDataManager::IsConnected()) {
			if(frameCounter % 120 == 0) {
		
				// erase other vehicles
				for(std::map<int, Vehicle*>::iterator iter = otherVehicles.begin(); iter  != otherVehicles.end(); ++iter) {
					delete iter->second;
				}
				otherVehicles.clear();

				// uncomment this line to connect to the robotics server.
				RemoteDataManager::Connect("www.robotics.unsw.edu.au","18081");

				// on connect, let's tell the server what we look like
				if (RemoteDataManager::IsConnected()) {
					ObstacleManager::get()->removeAll();

					VehicleModel vm;
					vm.remoteID = 0;
					

					//
					// student code goes here
					//
					CustomVehicle *Car = new CustomVehicle();
					for (std::vector<Shape *>::iterator it = Car->getBegin(); it != Car->getEnd(); ++it) {
						RectangularPrism *RectPrism = dynamic_cast<RectangularPrism*>(*it);
						if (RectPrism) {
							ShapeInit RectInit;
							RectInit.type = RECTANGULAR_PRISM;
							RectInit.params.rect.xlen = RectPrism->getXLength();
							RectInit.params.rect.ylen = RectPrism->getYLength();
							RectInit.params.rect.zlen = RectPrism->getZLength();
							RectInit.xyz[0] = static_cast<float> (RectPrism->getX());
							RectInit.xyz[1] = static_cast<float> (RectPrism->getY());
							RectInit.xyz[2] = static_cast<float> (RectPrism->getZ());
							RectInit.rotation = static_cast<float> (RectPrism->getRotation());
							RectInit.rgb[0] = static_cast<float> (RectPrism->getRed());
							RectInit.rgb[1] = static_cast<float> (RectPrism->getGreen());
							RectInit.rgb[2] = static_cast<float> (RectPrism->getBlue());

							vm.shapes.push_back(RectInit);
							continue;
						}
						TriangularPrism *TriPrism = dynamic_cast<TriangularPrism*>(*it);
						if (TriPrism) {
							ShapeInit TriInit;
							TriInit.type = TRIANGULAR_PRISM;
							TriInit.params.tri.alen = TriPrism->getALength();
							TriInit.params.tri.angle = TriPrism->getAngle();
							TriInit.params.tri.blen = TriPrism->getBLength();
							TriInit.params.tri.depth = TriPrism->getDepth();
							TriInit.xyz[0] = static_cast<float> (TriPrism->getX());
							TriInit.xyz[1] = static_cast<float> (TriPrism->getY());
							TriInit.xyz[2] = static_cast<float> (TriPrism->getZ());
							TriInit.rotation = static_cast<float> (TriPrism->getRotation());
							TriInit.rgb[0] = static_cast<float> (TriPrism->getRed());
							TriInit.rgb[1] = static_cast<float> (TriPrism->getGreen());
							TriInit.rgb[2] = static_cast<float> (TriPrism->getBlue());

							vm.shapes.push_back(TriInit);
							continue;
						}
						TrapezoidalPrism *TrapPrism = dynamic_cast<TrapezoidalPrism*>(*it);
						if (TrapPrism) {
							ShapeInit TrapInit;
							TrapInit.type = TRAPEZOIDAL_PRISM;
							TrapInit.params.trap.alen = TrapPrism->getXLengthBottom();
							TrapInit.params.trap.blen = TrapPrism->getXLengthTop();
							TrapInit.params.trap.aoff = TrapPrism->getOffset();
							TrapInit.params.trap.height = TrapPrism->getYLength();
							TrapInit.params.trap.depth = TrapPrism->getZLength();
							TrapInit.xyz[0] = static_cast<float> (TrapPrism->getX());
							TrapInit.xyz[1] = static_cast<float> (TrapPrism->getY());
							TrapInit.xyz[2] = static_cast<float> (TrapPrism->getZ());
							TrapInit.rotation = static_cast<float> (TrapPrism->getRotation());
							TrapInit.rgb[0] = static_cast<float> (TrapPrism->getRed());
							TrapInit.rgb[1] = static_cast<float> (TrapPrism->getGreen());
							TrapInit.rgb[2] = static_cast<float> (TrapPrism->getBlue());

							vm.shapes.push_back(TrapInit);
							continue;
						}
						Cylinder *Cyl = dynamic_cast<Cylinder*>(*it);
						if (Cyl) {
							ShapeInit CylInit;
							CylInit.type = CYLINDER;
							CylInit.params.cyl.radius = Cyl->getRadius();
							CylInit.params.cyl.depth = Cyl->getLength();
							CylInit.params.cyl.isRolling = Cyl->getRolling();
							CylInit.params.cyl.isSteering = Cyl->getSteering();
							CylInit.xyz[0] = static_cast<float> (Cyl->getX());
							CylInit.xyz[1] = static_cast<float> (Cyl->getY());
							CylInit.xyz[2] = static_cast<float> (Cyl->getZ());
							CylInit.rotation = static_cast<float> (Cyl->getRotation());
							CylInit.rgb[0] = static_cast<float> (Cyl->getRed());
							CylInit.rgb[1] = static_cast<float> (Cyl->getGreen());
							CylInit.rgb[2] = static_cast<float> (Cyl->getBlue());

							vm.shapes.push_back(CylInit);
							continue;
						}
					}
					/*ShapeInit RectPrism;
					RectPrism.type = RECTANGULAR_PRISM;
					RectPrism.params.rect.xlen = 10;
					RectPrism.params.rect.ylen = 4;
					RectPrism.params.rect.zlen = 12;
					RectPrism.xyz[0] = 0.0;
					RectPrism.xyz[1] = 2.0;
					RectPrism.xyz[2] = 0.0;
					RectPrism.rotation = 0.0;
					RectPrism.rgb[0] = 1.0;
					RectPrism.rgb[1] = 0.0;
					RectPrism.rgb[2] = 0.0;

					ShapeInit TriPrism;
					TriPrism.type = TRIANGULAR_PRISM;
					TriPrism.params.tri.alen = 5;
					TriPrism.params.tri.blen = 4;
					TriPrism.params.tri.depth = 12;
					TriPrism.params.tri.angle = 90;
					TriPrism.xyz[0] = 5.0;
					TriPrism.xyz[1] = 2.0;
					TriPrism.xyz[2] = 0.0;
					TriPrism.rotation = 0.0;
					TriPrism.rgb[0] = 0.0;
					TriPrism.rgb[1] = 1.0;
					TriPrism.rgb[2] = 0.0;

					ShapeInit TrapPrism;
					TrapPrism.type = TRAPEZOIDAL_PRISM;
					TrapPrism.params.trap.alen = 10.0;
					TrapPrism.params.trap.blen = 8.0;
					TrapPrism.params.trap.height = 2.0;
					TrapPrism.params.trap.aoff = 1.0;
					TrapPrism.params.trap.depth = 12.0;
					TrapPrism.xyz[0] = -5.0;
					TrapPrism.xyz[1] = 4.0;
					TrapPrism.xyz[2] = 0.0;
					TrapPrism.rotation = 0.0;
					TrapPrism.rgb[0] = 1.0;
					TrapPrism.rgb[1] = 1.0;
					TrapPrism.rgb[2] = 1.0;

					//Add models for wheels
					ShapeInit FrontLeft;
					FrontLeft.type = CYLINDER;
					FrontLeft.params.cyl.radius = 2.0;
					FrontLeft.params.cyl.depth = 1.0;
					FrontLeft.params.cyl.isRolling = 1.0;
					FrontLeft.params.cyl.isSteering = 1.0;
					FrontLeft.xyz[0] = 5.0;
					FrontLeft.xyz[1] = 0.0;
					FrontLeft.xyz[2] = -6.0;
					FrontLeft.rotation = 0.0;
					FrontLeft.rgb[0] = 0.0;
					FrontLeft.rgb[1] = 0.0;
					FrontLeft.rgb[2] = 1.0;

					ShapeInit FrontRight;
					FrontRight.type = CYLINDER;
					FrontRight.params.cyl.radius = 2.0;
					FrontRight.params.cyl.depth = 1.0;
					FrontRight.params.cyl.isRolling = 1.0;
					FrontRight.params.cyl.isSteering = 0.0;
					FrontRight.xyz[0] = -5.0;
					FrontRight.xyz[1] = 0.0;
					FrontRight.xyz[2] = -6.0;
					FrontRight.rotation = 0.0;
					FrontRight.rgb[0] = 0.0;
					FrontRight.rgb[1] = 0.0;
					FrontRight.rgb[2] = 1.0;

					ShapeInit BackLeft;
					BackLeft.type = CYLINDER;
					BackLeft.params.cyl.radius = 2.0;
					BackLeft.params.cyl.depth = 1.0;
					BackLeft.params.cyl.isRolling = 1.0;
					BackLeft.params.cyl.isSteering = 0.0;
					BackLeft.xyz[0] = -5.0;
					BackLeft.xyz[1] = 0.0;
					BackLeft.xyz[2] = 6.0;
					BackLeft.rotation = 0.0;
					BackLeft.rgb[0] = 0.0;
					BackLeft.rgb[1] = 0.0;
					BackLeft.rgb[2] = 1.0;

					ShapeInit BackRight;
					BackRight.type = CYLINDER;
					BackRight.params.cyl.radius = 2.0;
					BackRight.params.cyl.depth = 1.0;
					BackRight.params.cyl.isRolling = 1.0;
					BackRight.params.cyl.isSteering = 1.0;
					BackRight.xyz[0] = 5.0;
					BackRight.xyz[1] = 0.0;
					BackRight.xyz[2] = 6.0;
					BackRight.rotation = 0.0;
					BackRight.rgb[0] = 0.0;
					BackRight.rgb[1] = 0.0;
					BackRight.rgb[2] = 1.0;

					//Add all ShapeInit into vector

					vm.shapes.push_back(RectPrism);
					vm.shapes.push_back(TriPrism);
					vm.shapes.push_back(TrapPrism);
					vm.shapes.push_back(FrontLeft);
					vm.shapes.push_back(FrontRight);
					vm.shapes.push_back(BackLeft);
					vm.shapes.push_back(BackRight);
					//vm.
					*/

					RemoteDataManager::Write(GetVehicleModelStr(vm));
				}
			}
		}

		// if we're connected, send our vehicle state to the server
		if (RemoteDataManager::IsConnected()) {
			VehicleState vs;
			vs.remoteID = 0;
			vs.x = vehicle->getX();
			vs.z = vehicle->getZ();
			vs.rotation = vehicle->getRotation();
			vs.speed = vehicle->getSpeed();
			vs.steering = vehicle->getSteering();
			RemoteDataManager::Write(GetVehicleStateStr(vs));
		}

		// if we're still connected, receive and handle response messages from the server
		if (RemoteDataManager::IsConnected()) {
			std::vector<RemoteMessage> msgs = RemoteDataManager::Read();
			for(unsigned int i = 0; i < msgs.size(); i++ ) {

				RemoteMessage msg = msgs[i];
				cout << msg.payload << endl;

				switch(msg.type) {
					// new models
					case 'M':
						{
							std::vector<VehicleModel> models = GetVehicleModels(msg.payload);
							for(unsigned int i = 0; i < models.size(); i++) {
								VehicleModel vm = models[i];
								
								// uncomment the line below to create remote vehicles
								//otherVehicles[vm.remoteID] = new MyVehicle();
								otherVehicles[vm.remoteID] = new CustomVehicle(vm);
								//otherVehicles[vm.remoteID] = new CustomVehicle(vm);
								//
								// more student code goes here
								//

							}
							break;
						}

					// vehicle states
					case 'S': 
						{
							std::vector<VehicleState> states = GetVehicleStates(msg.payload);
							for(unsigned int i = 0; i < states.size(); i++) {
								VehicleState vs = states[i];

								std::map<int, Vehicle*>::iterator iter = otherVehicles.find(vs.remoteID);
								if(iter != otherVehicles.end()) {
									Vehicle * veh = iter->second;
									remoteDriver(veh, vs.x, vs.z, vs.rotation, vs.speed, vs.steering);
								}
							}
							break;
						}

					// goal state
					case 'G':
						{
							goals = GetGoals(msg.payload);
							break;
						}

					// obstacle state
					case 'O':
						{
							std::vector<ObstacleState> obs = GetObstacles(msg.payload);
							for(unsigned int i = 0; i < obs.size(); i++) {
								Obstacle o(obs[i].x, obs[i].z, obs[i].radius);
								ObstacleManager::get()->addObstacle(o);
							}
							break;
						}

					// disconnect list
					case 'D':
						{
							std::vector<int> disconnectedIDs = GetVehicleDisconnects(msg.payload);
							for(unsigned int i = 0; i < disconnectedIDs.size(); i++) {
								int id = disconnectedIDs[i];
								std::map<int, Vehicle*>::iterator iter = otherVehicles.find(id);
								if(iter != otherVehicles.end()) {
									delete iter->second;
									otherVehicles.erase(iter);
								}
							}
							break;
						}

					// error message
					case 'E':
						{
							cerr << "Server error: " << msg.payload << endl;
							break;
						}

				}
			} 
		}
	}


	const float sleep_time_between_frames_in_seconds = 0.025;

	static double previousTime = getTime();
	const double currTime = getTime();
	const double elapsedTime = currTime - previousTime;
	previousTime = currTime;

	// do a simulation step
	if (vehicle != NULL) {
		vehicle->update(speed, steering, elapsedTime);
	}
	for(std::map<int, Vehicle*>::iterator iter = otherVehicles.begin(); iter  != otherVehicles.end(); ++iter) {
		iter->second->update(elapsedTime);
	}

	display();

#ifdef _WIN32 
	Sleep(sleep_time_between_frames_in_seconds * 1000);
#else
	usleep(sleep_time_between_frames_in_seconds * 1e6);
#endif
};

void keydown(unsigned char key, int x, int y) {

	// keys that will be held down for extended periods of time will be handled
	//   in the idle function
	KeyManager::get()->asciiKeyPressed(key);

	// keys that react ocne when pressed rather than need to be held down
	//   can be handles normally, like this...
	switch (key) {
	case 27: // ESC key
		exit(0);
		break;      
	case '0':
		Camera::get()->jumpToOrigin();
		break;
	case 'p':
		Camera::get()->togglePursuitMode();
		break;
	}

};

void keyup(unsigned char key, int x, int y) {
	KeyManager::get()->asciiKeyReleased(key);
};

void special_keydown(int keycode, int x, int y) {

	KeyManager::get()->specialKeyPressed(keycode);

};

void special_keyup(int keycode, int x, int y) {  
	KeyManager::get()->specialKeyReleased(keycode);  
};

void mouse(int button, int state, int x, int y) {

};

void dragged(int x, int y) {

	if (prev_mouse_x >= 0) {

		int dx = x - prev_mouse_x;
		int dy = y - prev_mouse_y;

		Camera::get()->mouseRotateCamera(dx, dy);
	}

	prev_mouse_x = x;
	prev_mouse_y = y;
};

void motion(int x, int y) {

	prev_mouse_x = x;
	prev_mouse_y = y;
};


