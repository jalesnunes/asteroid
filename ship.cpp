#include "ship.h"

// Put your ship methods here

Ship::Ship()
{
	angle = 90;
	thurst = false;

}

void Ship::setAngle(int angle)
{
	this->angle = angle;
}

void Ship::setThurst(bool thurst)
{
	this->thurst = thurst;
}

void Ship::moveLeft()
{
	angle += SHIP_ROTATE_AMOUNT;
}


void Ship::moveRight()
{
	angle -= SHIP_ROTATE_AMOUNT;
}

void Ship::moveUp()
{
	velocity.setDx(SHIP_THRUST_AMOUNT * (-cos(M_PI / 180.0 * angle)));
	velocity.setDy(SHIP_THRUST_AMOUNT * (sin(M_PI / 180.0 * angle)));
}

void Ship::moveDown()
{
	velocity.setDx(SHIP_THRUST_AMOUNT * (cos(M_PI / 180.0 * angle)));
	velocity.setDy(SHIP_THRUST_AMOUNT * (-sin(M_PI / 180.0 * angle)));
}

void Ship::draw()
{
	drawShip(point, angle, thurst);
}

void Ship::advance()
{
	FlyingObjects::advance();
}
