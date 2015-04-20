#include "GlutFunctions.h"

Vector2i BezierGlutFunctions::screenSize;
Vector3f BezierGlutFunctions::screenPan = Vector3f(0.0f, 0.0f, -80.0f);
bool BezierGlutFunctions::verticesVisible;

void BezierGlutFunctions::init(int *argc, char **argv, Vector2i argScreenSize)
{
	screenSize = argScreenSize;
	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(screenSize.x, screenSize.y);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Bezier Surface Project");
	glDepthMask(true);
	glEnable(GL_DEPTH_TEST | GL_TEXTURE_2D);
	glClearColor(0.15f, 0.15f, 0.15f, 1.0f);
	glClearDepth(1.0f);

	verticesVisible = true;
	BezierPatch patch;
	patch.setPoint(0, Vector3f(0.0f, 0.0f, 10.0f));
	patch.setPoint(1, Vector3f(10.0f, 0.0f, 40.0f));
	patch.setPoint(2, Vector3f(20.0f, 0.0f, 0.0f));
	patch.setPoint(3, Vector3f(0.0f, 20.0f, 20.0f));
	patch.setPoint(4, Vector3f(10.0f, 20.0f, 15.0f));
	patch.setPoint(5, Vector3f(20.0f, 20.0f, 10.0f));
	patch.setPoint(6, Vector3f(0.0f, 30.0f, 40.0f));
	patch.setPoint(7, Vector3f(10.0f, 30.0f, 50.0f));
	patch.setPoint(8, Vector3f(20.0f, 30.0f, 30.0f));
	BezierPatchContainer::getInstance()->appendPatch(patch);

	BezierPatch patch2;
	patch2.setPoint(0, Vector3f(20.0f, 0.0f, 0.0f));
	patch2.setPoint(1, Vector3f(30.0f, 0.0f, -40.0f));
	patch2.setPoint(2, Vector3f(40.0f, 0.0f, 10.0f));
	patch2.setPoint(3, Vector3f(20.0f, 20.0f, 10.0f));
	patch2.setPoint(4, Vector3f(30.0f, 20.0f, -15.0f));
	patch2.setPoint(5, Vector3f(40.0f, 20.0f, 5.0f));
	patch2.setPoint(6, Vector3f(20.0f, 30.0f, 30.0f));
	patch2.setPoint(7, Vector3f(30.0f, 30.0f, -50.0f));
	patch2.setPoint(8, Vector3f(40.0f, 30.0f, 10.0f));
	BezierPatchContainer::getInstance()->appendPatch(patch2);

	glutIdleFunc(&idle);
	glutDisplayFunc(&display);
	glutKeyboardFunc(&keyboard);
	glutMouseFunc(&mouseClick);
}

void BezierGlutFunctions::idle()
{
	glutPostRedisplay();
}

void BezierGlutFunctions::display()
{
	static float angle = 0.0f;
	angle += TIMESTEP;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(110.0, 1.0, 10.0f, 170.0f);
	//glOrtho(-(float)screenSize.x / 2.0f, (float)screenSize.x / 2.0f, -(float)screenSize.y / 2.0f, (float)screenSize.y / 2.0f, 10.0f, 200.0f);

	glPushMatrix();
	glTranslatef(screenPan.x, screenPan.y, screenPan.z);
	glRotatef(-45.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(angle, 0.0f, 0.0f, 1.0f);

	BezierGlutFunctions::displayGrid();
	BezierPatchContainer::getInstance()->renderAll();
	if (verticesVisible)
		BezierPatchContainer::getInstance()->renderVertices();

	glPopMatrix();
	glutSwapBuffers();
}

void BezierGlutFunctions::keyboard(unsigned char argKey, int argX, int argY)
{
	if (argKey == 'v')
		verticesVisible = !verticesVisible;
	if (argKey == 'w')
		screenPan.z += 1.0f;
	if (argKey == 's')
		screenPan.z -= 1.0f;
}

void BezierGlutFunctions::mouseClick(int argButton, int argState, int argX, int argY)
{
	static bool clicked = false;
	if (argState == GLUT_DOWN && clicked == false)
	{
		clicked = true;
		gluUnProjectTest(Vector2i(argX, argY));
	}
	else if (argState == GLUT_UP && clicked == true)
	{
		clicked = false;
	}
}

void BezierGlutFunctions::displayGrid()
{
	for (float i = 0.0f; i < 100.0f; i+=5.0f)
	{
		for (float j = 0.0f; j < 100.0f; j+=5.0f)
		{
			glColor3f(0.2f, 0.2f, ((int((i/5.0f) + int(j/5.0f)) % 2 == 0 ? 0.5f : 0.2f)));
			glBegin(GL_QUADS);
			glVertex3f(i - 50.0f, j - 50.0f, minZ);
			glVertex3f(i - 50.0f + 5.0f, j - 50.0f, minZ);
			glVertex3f(i - 50.0f + 5.0f, j - 50.0f + 5.0f, minZ);
			glVertex3f(i - 50.0f, j - 50.0f + 5.0f, minZ);
			glEnd();
		}
	}
}

void BezierGlutFunctions::displayVertices(GLfloat *argPoints, int argNumVertices, float *argColor4f)
{
	float color[4];
	for (int i = 0; i < 4; i++)
		color[i] = argColor4f == 0 ? 1.0f : argColor4f[i];

	const int cursorSize = 1.0f;
	for (int i = 0; i < argNumVertices / 3; i++)
	{
		glColor4f(color[0], color[1], color[2], color[3]);
		glBegin(GL_LINES);
		glVertex3f(argPoints[3 * i] - cursorSize, argPoints[3 * i + 1], argPoints[3 * i + 2]);
		glVertex3f(argPoints[3 * i] + cursorSize, argPoints[3 * i + 1], argPoints[3 * i + 2]);
		glVertex3f(argPoints[3 * i], argPoints[3 * i + 1] - cursorSize, argPoints[3 * i + 2]);
		glVertex3f(argPoints[3 * i], argPoints[3 * i + 1] + cursorSize, argPoints[3 * i + 2]);
		glVertex3f(argPoints[3 * i], argPoints[3 * i + 1], argPoints[3 * i + 2] - cursorSize);
		glVertex3f(argPoints[3 * i], argPoints[3 * i + 1], argPoints[3 * i + 2] + cursorSize);
		glEnd();
	}
}

void BezierGlutFunctions::gluUnProjectTest(Vector2i argClick)
{
	float *depthBuffer = new float/*[screenSize.x * screenSize.y]*/;
	glReadPixels(argClick.x, argClick.y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, depthBuffer);
	//std::cout << "pixel depth data: " << *depthBuffer/*[argClick.y + screenSize.x - argClick.x]*/ << std::endl;
	GLdouble *model = new GLdouble[16];	glGetDoublev(GL_MODELVIEW_MATRIX, model);
	GLdouble *proj = new GLdouble[16];	glGetDoublev(GL_PROJECTION_MATRIX, proj);
	GLdouble *objX = new GLdouble, *objY = new GLdouble, *objZ = new GLdouble;
	GLint *view = new GLint(GL_VIEWPORT);
	gluUnProject(argClick.x, argClick.y, 0.0, model, proj, view, objX, objY, objZ);
	std::cout << "clicked coordinates: " << *objX << " : " << *objY << " : " << *objZ << std::endl;

	delete[] depthBuffer;
}
