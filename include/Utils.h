#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

struct Vector2i
{
	int x, y;

	Vector2i(void);
	Vector2i(int argX, int argY);
};
struct Vector2f
{
	int x, y;

	Vector2f(void);
	Vector2f(float argX, float argY);
};
struct Vector3i
{
	int x, y, z;

	Vector3i(void);
	Vector3i(int argX, int argY, int argZ);
};
struct Vector3f
{
	float x, y, z;

	Vector3f(void);
	Vector3f(float argX, float argY, float argZ);
};

#endif
