#include "flyingObject.h"


// Put your FlyingObject method bodies here

FlyingObjects::FlyingObjects()
{
	alive = true;
	wrappable = true;
	this->point = point;
	this->velocity = velocity;
}

void FlyingObjects::setPoint(Point point)
{
	this->point = point;
}

void FlyingObjects::setVelocity(Velocity velocity)
{
	this->velocity = velocity;
}

void FlyingObjects::advance()
{
	point.setX(point.getX() + velocity.getDx());
	point.setY(point.getY() + velocity.getDy());
}

void FlyingObjects::wrap(Point tl, Point br)
{
	if (canWrappable())
	{
		if (point.getX() > br.getX() || point.getX() < br.getX())
		{
			point.setX(point.getX() * -1);
		}
	
		if (point.getY() > tl.getY() || point.getY() < tl.getY())
		{
			point.setY(point.getY() * -1);
		}
		
	}

}
