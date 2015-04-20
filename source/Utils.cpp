#include "Utils.h"

Vector2i::Vector2i()
:x(0), y(0) {}
Vector2i::Vector2i(int argX, int argY)
:x(argX), y(argY) {}
Vector2f::Vector2f()
: x(0.0f), y(0.0f) {}
Vector2f::Vector2f(float argX, float argY)
: x(argX), y(argY) {}
Vector3i::Vector3i()
: x(0), y(0), z(0) {}
Vector3i::Vector3i(int argX, int argY, int argZ)
: x(argX), y(argY), z(argZ) {}
Vector3f::Vector3f()
: x(0.0f), y(0.0f), z(0.0f) {}
Vector3f::Vector3f(float argX, float argY, float argZ)
: x(argX), y(argY), z(argZ) {}
