#ifndef bullet_h
#define bullet_h

#include "flyingObject.h"
#include <cmath>
#include <vector>

#define BULLET_SPEED 10
#define BULLET_LIFE 40



// Put your Bullet class here


class Bullet : public FlyingObjects
{
protected:
	float angle;
	int bulletTime;

public:
	Bullet();

	float getAngle() const { return angle; }

	void setAngle(float angle) { this->angle = angle; }

	int bulletLife() { return bulletTime; }

	void fire(Point point, float angle);

	virtual void draw();
	virtual void advance();

};



#endif /* bullet_h */
