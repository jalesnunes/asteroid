#ifndef rocks_h
#define rocks_h

#include "flyingObject.h"

#define BIG_ROCK_SIZE 16
#define MEDIUM_ROCK_SIZE 8
#define SMALL_ROCK_SIZE 4

#define BIG_ROCK_SPIN 10
#define MEDIUM_ROCK_SPIN 15
#define SMALL_ROCK_SPIN 20



// Define the following classes here:
//   Rock
class Rock : public FlyingObjects
{
protected:
	int spin;
	int radius;
	int bonus;
	

public:
	Rock();
	virtual int getRadius() const { return radius; }
	virtual int hit();
	virtual void brokenRock();
	void rotate90();
	void rotate270();

};

//   BigRock
class BigRock : public Rock
{
protected:
	

public:
	BigRock(Point point, Velocity velocity);
	virtual void draw();
	virtual void advance();
	virtual void brokenRock();

};



//   MediumRock
class MediumRock : public Rock
{
protected:
	
	
public:
	MediumRock(Point point, Velocity velocity);

	virtual void draw();
	virtual void advance();
	virtual void brokenRock();

};

//   SmallRock
class SmallRock : public Rock
{
protected:
	
	

public:
	SmallRock(Point point, Velocity velocity);
	virtual void draw();
	virtual void advance();
	virtual void brokenRock();

};

#endif /* rocks_h */
