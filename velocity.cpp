#include "velocity.h"

Velocity::Velocity()
{
	dX = 0;
	dY = 0;
}

Velocity::Velocity(float dX, float dY)
{
	this->dX = dX;
	this->dY = dY;
}

void Velocity::setDx(float dX)
{
	this->dX = dX;
}

void Velocity::setDy(float dY)
{
	this->dY = dY;
}
