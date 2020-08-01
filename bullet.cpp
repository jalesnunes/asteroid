#include "bullet.h"


// Put your bullet methods here

Bullet::Bullet()
{
	
	angle = 90.0;
	bulletTime = 0;
}

void Bullet::draw()
{
	drawDot(getPoint());
}

void Bullet::fire(Point point, float angle)
{
	this->point = point;

	float x = BULLET_SPEED * -sin(M_PI / 180.0 * (angle));
	float y = BULLET_SPEED * cos(M_PI / 180.0 * (angle));
	

	velocity.setDx(x);
	velocity.setDy(y);
}

void Bullet::advance()
{
	FlyingObjects::advance();
	bulletTime++;
}
