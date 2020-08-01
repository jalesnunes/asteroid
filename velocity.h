#ifndef VELOCITY_H
#define VELOCITY_H

#include "point.h"
#include <math.h>

# define M_PI 3.14159265358979323846

class Velocity
{
private:
	float dX;
	float dY;

public:
	Velocity();
	Velocity(float dX, float dY);

	float getDx() const { return dX; }
	float getDy() const { return dY; }

	void setDx(float dX);
	void setDy(float dY);


};

#endif

