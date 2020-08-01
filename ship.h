#ifndef ship_h
#define ship_h

#include "flyingObject.h"

#define SHIP_SIZE 10

#define SHIP_ROTATE_AMOUNT 6
#define SHIP_THRUST_AMOUNT 1
#define SHIP_KEEP_MOVING 0.01



// Put your Ship class here
class Ship : public FlyingObjects
{
protected:
	int angle;
	bool thurst;
	
public:
	Ship();

	/*****************
	* Getters
	*****************/
	int getAngle() const { return angle; }

	/*****************
	* Setters
	*****************/
	void setAngle(int angle);
	void setThurst(bool thurst);

	/*****************
	* Movement
	*****************/
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();

	virtual void draw();
	virtual void advance();

};


#endif /* ship_h */
