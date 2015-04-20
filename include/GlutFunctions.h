#ifndef GLUTFUNCTIONS_H_INCLUDED
#define GLUTFUNCTIONS_H_INCLUDED

#ifdef __linux__
#define TIMESTEP 0.5f
#else
#define TIMESTEP 0.005f
#endif

#include "Utils.h"
#include "BezierPatch.h"
#include <iostream> //debug
#include <freeglut.h>
#include <vector>

namespace BezierGlutFunctions
{
	extern Vector2i screenSize;
	extern Vector3f screenPan;
	extern Vector3i screenRotate;

	void init(int *argc, char **argv, Vector2i argScreenSize = Vector2i(800, 600));
	void idle();
	void display();
	void keyboard(unsigned char argKey, int argX, int argY);
	void mouseClick(int argButton, int argState, int argX, int argY);

	void displayGrid(void);
	void displayVertices(GLfloat *argPoints, int argNumVertices, float *argColor4f = 0);
	void gluUnProjectTest(Vector2i argClick);
	void evaluator(void);
}

#endif //GLUTFUNCTIONS_H_INCLUDED
