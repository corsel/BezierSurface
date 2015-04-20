#include "BezierPatch.h"

int activePatch = 0;
int activeVertex = 0;
float minZ = 0.0f;

Renderable::Renderable() {}

//BezierPatch Class
BezierPatch::BezierPatch()
	:Renderable()
{
	points = new float[27];
}
BezierPatch::BezierPatch(float *argPoints)
	:points(argPoints), Renderable() {}
void BezierPatch::render(bool isActive) //virtual implementation
{

	glEnable(GL_MAP2_VERTEX_3);
	glMap2f(GL_MAP2_VERTEX_3, 0.0f, 1.0f, 3, 3, 0.0f, 1.0f, 9, 3, points);
	glMapGrid2f(20, 0.0f, 1.0f, 20, 0.0f, 1.0f);
	if (isActive)
		glColor4f(1.0f, 0.5f, 0.5f, 1.0f);
	else
		glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
	glEvalMesh2(GL_LINE, 0, 20, 0, 20); //GL_LINE, GL_POINT, GL_FILL
}
void BezierPatch::renderVertices(bool argActive)
{
	glBegin(GL_LINES);
	for (int i = 0; i < 9; i++)
	{
		float activeMultiplier = (argActive && activeVertex == i) ? 3.0f : 1.0f;
		glColor4f(0.5f * activeMultiplier, 0.5f * activeMultiplier, 0.5f * activeMultiplier, 1.0f);
		glVertex3f(points[i * 3]-1.0f * activeMultiplier, points[i * 3+1], points[i * 3+2]);
		glVertex3f(points[i * 3]+1.0f * activeMultiplier, points[i * 3+1], points[i * 3+2]);
		glVertex3f(points[i * 3], points[i * 3+1]-1.0f * activeMultiplier, points[i * 3+2]);
		glVertex3f(points[i * 3], points[i * 3+1]+1.0f * activeMultiplier, points[i * 3+2]);
		glVertex3f(points[i * 3], points[i * 3+1], points[i * 3+2]-1.0f * activeMultiplier);
		glVertex3f(points[i * 3], points[i * 3+1], points[i * 3+2]+1.0f * activeMultiplier);
	}
	glEnd();
}
float *BezierPatch::getPoints()
{
	return points;
}
void BezierPatch::setPoint(int argIndex, Vector3f argCoordinate)
{
	if (argIndex >= 9) return;
   this->points[argIndex*3] = argCoordinate.x;
   points[argIndex*3+1] = argCoordinate.y;
   points[argIndex*3+2] = argCoordinate.z;
   if (argCoordinate.z <= minZ) minZ = argCoordinate.z;
}

//BezierPatchContainer Class
BezierPatchContainer *BezierPatchContainer::instance = 0;
BezierPatchContainer::BezierPatchContainer() {}
BezierPatchContainer *BezierPatchContainer::getInstance()
{
   if (instance == 0)
		instance = new BezierPatchContainer();
	return instance;
}
void BezierPatchContainer::appendPatch(BezierPatch argPatch)
{
	patchVector.push_back(argPatch);
}
void BezierPatchContainer::renderAll()
{
	for (int i = 0; i < patchVector.size(); i++)
	{
		patchVector[i].render(activePatch == i);
	}
}
void BezierPatchContainer::renderVertices()
{
	for (int i = 0; i < patchVector.size(); i++)
	{
		patchVector[i].renderVertices(activePatch == i);
	}
}
