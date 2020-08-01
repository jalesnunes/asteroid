#ifndef FLYINGOBJECTS_H
#define FLYINGOBJECTS_H

#include "point.h"
#include "velocity.h"
#include "uiDraw.h"
#include <cmath>
#include <vector>

# define M_PI 3.14159265358979323846


class FlyingObjects
{
protected:
	Point point;
	Velocity velocity;
	bool alive;
	bool wrappable;

public:
	/*CONSTRUCTOR*/
	FlyingObjects();

	/*GETTERS*/
	Point getPoint() const { return point; }
	Velocity getVelocity() const { return velocity; }
	bool isAlive() const { return alive; }
	bool canWrappable() const { return wrappable; }
	void kill() { alive = false; }

	/*SETTERS*/
	void setPoint(Point point);
	void setVelocity(Velocity velocity);

	virtual void advance();
	virtual void wrap(Point tl, Point br);
	virtual void draw() = 0;
};

#endif // !FLYINGOBJECTS_H
