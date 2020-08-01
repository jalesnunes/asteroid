/*********************************************************************
 * File: game.cpp
 * Description: Contains the implementaiton of the game class
 *  methods.
 *
 *********************************************************************/

#include "game.h"

// These are needed for the getClosestDistance function...
#include <limits>
#include <algorithm>

#define OFF_SCREEN_BORDER_AMOUNT 5

/***************************************
 * GAME CONSTRUCTOR
 ***************************************/
Game::Game(Point tl, Point br)
	: topLeft(tl), bottomRight(br)
{
	Velocity velocity;
	Point point;

	for (int i = 0; i < LARGE_ASTEROID_BEGINS; i++)
	{
		point.setX(random(tl.getX(), br.getX()));
		point.setY(random(br.getY(), tl.getY()));
		if (random(0, 10000) % 2 == 0)
			velocity.setDx(1);
		else
			velocity.setDx(-1);
		if (random(0, 100000) % 2 == 0)
			velocity.setDy(1);
		else
			velocity.setDy(-1);
		asteroids.push_back(new BigRock(point, velocity));
	}

	// Set up the initial conditions of the game
	score = 0;

	Ship* ship = new Ship;
	pShip = ship;

}

/****************************************
 * GAME DESTRUCTOR
 ****************************************/
Game :: ~Game()
{
	// TODO: Check to see if there is currently a ship allocated
	//       and if so, delete it.
	if (pShip != NULL)
	{
		delete pShip;
		pShip = NULL;
	}

	for (vector<Bullet>::iterator it = bullets.begin(); it != bullets.end(); it++)
	{
		if (!it->isAlive())
		{
			it = bullets.erase(it);
		}
	}

	for (vector<Rock*>::iterator it = asteroids.begin(); it != asteroids.end(); it++)
	{
		if (!(*it)->isAlive())
		{
			delete (*it);
			(*it) = NULL;
			it = asteroids.erase(it);
		}
	}



}


// You may find this function helpful...

/**********************************************************
 * Function: getClosestDistance
 * Description: Determine how close these two objects will
 *   get in between the frames.
 **********************************************************/

float Game :: getClosestDistance(const FlyingObjects &obj1, const FlyingObjects &obj2) const
{
   // find the maximum distance traveled
   float dMax = max(abs(obj1.getVelocity().getDx()), abs(obj1.getVelocity().getDy()));
   dMax = max(dMax, abs(obj2.getVelocity().getDx()));
   dMax = max(dMax, abs(obj2.getVelocity().getDy()));
   dMax = max(dMax, 0.1f); // when dx and dy are 0.0. Go through the loop once.
   
   float distMin = std::numeric_limits<float>::max();
   for (float i = 0.0; i <= dMax; i++)
   {
      Point point1(obj1.getPoint().getX() + (obj1.getVelocity().getDx() * i / dMax),
                     obj1.getPoint().getY() + (obj1.getVelocity().getDy() * i / dMax));
      Point point2(obj2.getPoint().getX() + (obj2.getVelocity().getDx() * i / dMax),
                     obj2.getPoint().getY() + (obj2.getVelocity().getDy() * i / dMax));
      
      float xDiff = point1.getX() - point2.getX();
      float yDiff = point1.getY() - point2.getY();
      
      float distSquared = (xDiff * xDiff) +(yDiff * yDiff);
      
      distMin = min(distMin, distSquared);
   }
   
   return sqrt(distMin);
}

/***************************************
 * GAME :: ADVANCE
 * advance the game one unit of time
 ***************************************/
void Game::advance()
{
	pShip->advance();
	advanceBullets();
	advanceAsteroid();
	wrap();

	handleCollisions();
	cleanUpZombies();
}

/***************************************
 * GAME :: ADVANCE BULLETS
 * Go through each bullet and advance it.
 ***************************************/
void Game::advanceBullets()
{
	// Move each of the bullets forward if it is alive
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i].isAlive())
		{
			// this bullet is alive, so tell it to move forward
			bullets[i].advance();

		}
	}
}

/**************************************************************************
 * GAME :: ADVANCE BIRD
 *
 * 1. If there is no bird, create one with some probability
 * 2. If there is a bird, and it's alive, advance it
 * 3. Check if the bird has gone of the screen, and if so, "kill" it
 **************************************************************************/
void Game::advanceAsteroid()
{
	for (vector<Rock*>::iterator it = asteroids.begin(); it != asteroids.end(); it++)
	{
		if ((*it)->isAlive())
		{
			(*it)->advance();
		}
	}

}

/**************************************************************************
 * GAME :: IS ON SCREEN
 * Determines if a given point is on the screen.
 **************************************************************************/
bool Game::isOnScreen(const Point& point)
{
	return (point.getX() >= topLeft.getX() - OFF_SCREEN_BORDER_AMOUNT
		&& point.getX() <= bottomRight.getX() + OFF_SCREEN_BORDER_AMOUNT
		&& point.getY() >= bottomRight.getY() - OFF_SCREEN_BORDER_AMOUNT
		&& point.getY() <= topLeft.getY() + OFF_SCREEN_BORDER_AMOUNT);
}

/**************************************************************************
 * GAME :: HANDLE COLLISIONS
 * Check for a collision between a bird and a bullet.
 **************************************************************************/
 void Game::handleCollisions()
{
	 for (vector<Rock*>::iterator it = asteroids.begin(); it != asteroids.end(); it++)
	 {
		 if((*it)->isAlive())
		 if (getClosestDistance(*pShip, *(*it)) <= (*it)->getRadius())
		 {
			 pShip->kill();
		 }
	 }

	 vector<Rock*> newAsteroid;
	 Rock* rock;

	 for (vector<Rock*>::iterator it = asteroids.begin(); it != asteroids.end(); it++)
	 {
		 for (int i = 0; i < bullets.size(); i++)
		 {
			 if ((*it)->isAlive())
			 {
				 if (getClosestDistance(*(*it), bullets[i]) < (*it)->getRadius())
				 {
					 if ((*it)->getRadius() == BIG_ROCK_SIZE)
					 {
						 if (fabs(bullets[i].getPoint().getX() - (*it)->getPoint().getX()) < CLOSE_ENOUGH
							 && fabs(bullets[i].getPoint().getY() - (*it)->getPoint().getY()) < CLOSE_ENOUGH)
						 {
							 int points = (*it)->hit();
							 score += points;
						 }

						 bullets[i].kill();
						 (*it)->brokenRock();

						 Point p1 = (*it)->getPoint();
						 Point p2 = (*it)->getPoint();
						 Point p3 = (*it)->getPoint();

						 Velocity v1 = (*it)->getVelocity();
						 Velocity v2 = (*it)->getVelocity();
						 Velocity v3 = (*it)->getVelocity();

						 p1.setY(p1.getY() + MEDIUM_ROCK_SIZE * 3);
						 p2.setY(p2.getY() - MEDIUM_ROCK_SIZE * 3);
						 p3.setX(p3.getX() - SMALL_ROCK_SIZE * 3);
						 
						 v1.setDx(v1.getDx() + 1);
						 v1.setDy(v1.getDy() + 1);
						 v2.setDx(v2.getDx() + 1);
						 v2.setDy(v2.getDy() + 1);
						 v3.setDx(v3.getDx() + 3);
						 v3.setDy(v3.getDy() + 3);

						 rock = new MediumRock(p1, v1);
						 rock->rotate90();
						 rock->draw();
						 newAsteroid.push_back(rock);

						 rock = new MediumRock(p2, v2);
						 rock->rotate270();
						 rock->draw();
						 newAsteroid.push_back(rock);

						 rock = new SmallRock(p3, v3);
						 rock->draw();
						 newAsteroid.push_back(rock);

					 }
					 else if ((*it)->getRadius() == MEDIUM_ROCK_SIZE)
					 {
						 if (fabs(bullets[i].getPoint().getX() - (*it)->getPoint().getX()) < CLOSE_ENOUGH
							 && fabs(bullets[i].getPoint().getY() - (*it)->getPoint().getY()) < CLOSE_ENOUGH)
						 {
							 int points = (*it)->hit();
							 score += points;
						 }

						 bullets[i].kill();
						 (*it)->brokenRock();

						 Point p1 = (*it)->getPoint();
						 Point p2 = (*it)->getPoint();

						 Velocity v1 = (*it)->getVelocity();
						 Velocity v2 = (*it)->getVelocity();

						 p1.setY(p1.getY() + SMALL_ROCK_SIZE * 3);
						 p2.setY(p2.getY() - SMALL_ROCK_SIZE * 3);
						 
						 v1.setDx(v1.getDx() + 3);
						 v1.setDy(v1.getDy() + 3);
						 v2.setDx((v2.getDx() + 3) * -1);
						 v2.setDy(v2.getDy() + 3);

						 rock = new SmallRock(p1, v1);
						 rock->draw();
						 newAsteroid.push_back(rock);

						 rock = new SmallRock(p2, v2);
						 rock->draw();
						 newAsteroid.push_back(rock);
					 }
					 else
					 {
						 if (fabs(bullets[i].getPoint().getX() - (*it)->getPoint().getX()) < CLOSE_ENOUGH
							 && fabs(bullets[i].getPoint().getY() - (*it)->getPoint().getY()) < CLOSE_ENOUGH)
						 {
							 int points = (*it)->hit();
							 score += points;
						 }

						 bullets[i].kill();
						 (*it)->getPoint();
						 
						 (*it)->kill();
					 }
				 }
			 }
		 }
	 }


	 while (!newAsteroid.empty())
	 {
		 asteroids.push_back(newAsteroid.at(newAsteroid.size() - 1));
		 newAsteroid.pop_back();
	 }
}

/**************************************************************************
 * GAME :: CLEAN UP ZOMBIES
 * Remove any dead objects (take bullets out of the list, deallocate bird)
 **************************************************************************/
void Game::cleanUpZombies()
{
	// Look for dead bullets
	vector<Bullet>::iterator bulletIt = bullets.begin();

	while (bulletIt != bullets.end())
	{
		// Asteroids Hint:
		// If we had a list of pointers, we would need this line instead:
		//Bullet* pBullet = *bulletIt;

		if (bulletIt->isAlive())
		{
			if (bulletIt->bulletLife() > BULLET_LIFE)
			{
				bulletIt = bullets.erase(bulletIt);
			}
			else
			{
				bulletIt++; // advance
			}
			
		}

		else if (!bulletIt->isAlive())
		{
			bulletIt = bullets.erase(bulletIt);
		}
	}

}

/***************************************
 * GAME :: HANDLE INPUT
 * accept input from the user
 ***************************************/
void Game::handleInput(const Interface& ui)
{

	// Change the direction of the ship
	if (ui.isLeft() && pShip->isAlive())
	{
		pShip->moveLeft();
	}

	if (ui.isRight() && pShip->isAlive())
	{
		pShip->moveRight();
		
	}
	if (ui.isUp() && pShip->isAlive())
	{
		pShip->moveUp();
		pShip->setThurst(true);
		pShip->advance();
		
		
	}
	if (ui.isDown() && pShip->isAlive())
	{
		pShip->moveDown();
		pShip->setThurst(true);
		pShip->advance();
		
		
	}

	// Check for "Spacebar
	if (ui.isSpace() && pShip->isAlive())
	{
		Bullet newBullet;
		newBullet.fire(pShip->getPoint(), pShip->getAngle());

		bullets.push_back(newBullet);
	}
}

/*********************************************
 * GAME :: DRAW
 * Draw everything on the screen
 *********************************************/
void Game::draw(const Interface& ui)
{
	for (vector<Rock*>::iterator it = asteroids.begin(); it != asteroids.end(); it++)
	{
		if (!pShip->isAlive())
		{
			 (*it)->kill();
		}
		else if ((*it)->isAlive())
		{
			(*it)->draw();
		}
		/*if ((*it)->isAlive())
		{
			(*it)->draw();
		}
		else if (!pShip->isAlive())
		{
			(*it)->kill();
		}*/
	}

	if (pShip->isAlive())
	{
		pShip->draw();
	}
	else
	{
		for (int i = 0; i < bullets.size(); i++)
		{
			bullets[i].kill();
		}
		char gameOver[256] = { "Game Over" };
		Point gameOverLocation;
		gameOverLocation.setX(topLeft.getX() + 390);
		gameOverLocation.setY(topLeft.getY() - 390);
		drawText2(gameOverLocation, gameOver);
	}

	// draw the bullets, if they are alive
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i].isAlive())
		{
			bullets[i].draw();
		}
	}

	char gameName[256] = { "Asteroid Game" };
	Point gameNameLocation;
	gameNameLocation.setX(topLeft.getX() + 15);
	gameNameLocation.setY(topLeft.getY() - 15);
	drawText1(gameNameLocation, gameName);

	for (int i = 0; i < 100; i++)
	{
		drawStars(Point(random(-400, 400), random(-400, 400)));
	}


	// Put the score on the screen
	Point scoreLocation1;
	Point scoreLocation2;
	char scoreName[256] = { "Score: " };
	scoreLocation1.setX(topLeft.getX() + 15);
	scoreLocation1.setY(topLeft.getY() - 35);
	scoreLocation2.setX(topLeft.getX() + 80);
	scoreLocation2.setY(topLeft.getY() - 25);
	drawText(scoreLocation1, scoreName);
	drawNumber(scoreLocation2, score);

}

void Game::wrap()
{

	if (!isOnScreen(pShip->getPoint()))
	{
		pShip->wrap(topLeft, bottomRight);
	}

	for (vector<Bullet>::iterator it = bullets.begin(); it != bullets.end(); it++)
	{
		if (!isOnScreen(it->getPoint()))
			{
				it->wrap(topLeft, bottomRight);
			}
	}

	for (vector<Rock*>::iterator it = asteroids.begin(); it != asteroids.end(); it++)
	{
		if (!isOnScreen((*it)->getPoint()))
		{
			(*it)->wrap(topLeft, bottomRight);
		}
	}
}

