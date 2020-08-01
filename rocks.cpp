#include "rocks.h"

// Put your Rock methods here

/*********************************************
* Rock Class nethods
*********************************************/
Rock::Rock()
{
	radius = 0;
	spin = 0;
	bonus = 1;
}

int Rock::hit()
{
	return bonus;
	
}

void Rock::brokenRock()
{

}

void Rock::rotate90()
{
	Velocity velocity = getVelocity();
	float x = velocity.getDx();
	velocity.setDx(velocity.getDy() * -1);
	velocity.setDy(x);
	setVelocity(velocity);
}

void Rock::rotate270()
{
	Velocity velocity = getVelocity();
	float x = velocity.getDx();
	velocity.setDx(velocity.getDy());
	velocity.setDy(x * -1);
	setVelocity(velocity);
}

/*********************************************
* BigRock Class nethods
*********************************************/
BigRock::BigRock(Point point, Velocity velocity)
{
	radius = BIG_ROCK_SIZE;
	alive = true;
	spin = BIG_ROCK_SPIN;
	this->point = point;
	this->velocity = velocity;
	bonus = 1;
}

void BigRock::advance()
{
	FlyingObjects::advance();
	spin = spin + BIG_ROCK_SPIN % 360;

}

void BigRock::draw()
{
	drawLargeAsteroid(point, spin);
}
void BigRock::brokenRock()
{
	
	FlyingObjects::kill();
	
}

/*********************************************
* MediumRock Class nethods
*********************************************/
MediumRock::MediumRock(Point point, Velocity velocity)
{
	radius = MEDIUM_ROCK_SIZE;
	alive = true;
	spin = MEDIUM_ROCK_SPIN;
	this->point = point;
	this->velocity = velocity;
	bonus = 5;

}

void MediumRock::advance()
{
	FlyingObjects::advance();
	spin = spin + BIG_ROCK_SPIN % 360;
}

void MediumRock::draw()
{
	drawMediumAsteroid(point, spin);
}

void MediumRock::brokenRock()
{

	FlyingObjects::kill();

}

/*********************************************
* SmallRock Class nethods
*********************************************/
SmallRock::SmallRock(Point point, Velocity velocity)
{
	radius = SMALL_ROCK_SIZE;
	alive = true;
	spin = SMALL_ROCK_SPIN;
	this->point = point;
	this->velocity = velocity;
	bonus = 10;

}

void SmallRock::advance()
{
	FlyingObjects::advance();
	spin = spin + BIG_ROCK_SPIN % 360;
}

void SmallRock::draw()
{
	drawSmallAsteroid(point, spin);
}

void SmallRock::brokenRock()
{

	FlyingObjects::kill();

}