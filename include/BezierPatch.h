#ifndef BEZIER_PATCH_H_INCLUDED
#define BEZIER_PATCH_H_INCLUDED

#include <vector>
#include <freeglut.h>
#include "Utils.h"

extern int activePatch;
extern int activeVertex;
extern float minZ;

class Renderable
{
public:
	virtual void render(bool isActive) = 0; //virtual
	Renderable(void);
};

class BezierPatch : public Renderable
{
private:
	float *points;

public:
	BezierPatch();
	BezierPatch(float *argPoints);
	void render(bool isActive = false); //virtual implementation
	void renderVertices(bool argActive = false);
	void setPoint(int argIndex, Vector3f argCoordinate);
	float *getPoints(void);
	void movePoint(Vector3f argCoordinate);
};

class BezierPatchContainer //Singleton
{
private:
	static BezierPatchContainer *instance;
	std::vector<BezierPatch> patchVector;
	BezierPatchContainer(void);

public:
	static BezierPatchContainer *getInstance(void);
	void appendPatch(BezierPatch argPatch);
	void switchActivePatch(void);
	void renderAll(void);
	void renderVertices(void);
	void movePatchPoint(Vector3f argCoordinate);
};

#endif //BEZIER_H_INCLUDED
