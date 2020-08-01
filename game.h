/*********************************************************************
 * File: game.h
 * Description: Defines the game class for Asteroids
 *
 *********************************************************************/

#ifndef GAME_H
#define GAME_H


#include <vector>

#include "uiDraw.h"
#include "uiInteract.h"
#include "point.h"
#include "velocity.h"
#include "bullet.h"
#include "rocks.h"
#include "flyingObject.h"
#include "ship.h"

using namespace std;


#define CLOSE_ENOUGH 30
#define LARGE_ASTEROID_BEGINS 10


/*****************************************
 * GAME
 * The main game class containing all the state
 *****************************************/
class Game
{
public:
	/*********************************************
	 * Constructor
	 * Initializes the game
	 *********************************************/
	Game(Point tl, Point br);
	~Game();

	/*********************************************
	 * Function: handleInput
	 * Description: Takes actions according to whatever
	 *  keys the user has pressed.
	 *********************************************/
	void handleInput(const Interface& ui);

	/*********************************************
	 * Function: advance
	 * Description: Move everything forward one
	 *  step in time.
	 *********************************************/
	void advance();

	/*********************************************
	 * Function: draw
	 * Description: draws everything for the game.
	 *********************************************/
	void draw(const Interface& ui);

	

private:
	// The coordinates of the screen
	Point topLeft;
	Point bottomRight;

	int score;

	Ship* pShip;
	vector<Rock*> asteroids;
	vector<Bullet> bullets;

	/*************************************************
	 * Private methods to help with the game logic.
	 *************************************************/
	bool isOnScreen(const Point& point);
	void advanceBullets();
	void advanceAsteroid();
	void wrap();
	

	void handleCollisions();
	void cleanUpZombies();
	float getClosestDistance(const FlyingObjects& obj1, const FlyingObjects& obj2) const;
};

#endif /* GAME_H */
