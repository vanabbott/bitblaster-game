//Author: Van Abbott
//
//
#include <vector>
#include "gfx.h"
#include <ctime>
#include <unistd.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

using namespace std;

const int PLAYER = 1;					//these ints are all the values representing what type of object every object is
const int ROCK = 2;
const int ENEMY = 3;
const int SHOT = 4;
const int	EXPLOSION = 5;
const int POWERUP = 6;
const int ENEMYSHOT = 7;
const int BOOST = 8;


const int SIZE = 10;    //various global variables to be used throughout the implementation and driver
const int xSize = 750;
const int ySize = 750;
const int BOARDER = 25;
const string filename = "highscores.txt";




struct User{    // user struct storing the users name previous score and difficulty they are playing at 
		string name;
		int difficulty;
		int score;
};
void displayMenu(vector<User>,User); // function to display main menu to screen in driver
void sortScores(vector<User>&);  // function to sort and delete lowest of highscores and users score



class Object{ // class for every object that gets displayed to the screen during gameplay
		public:
				//constructor methods
				Object();
				Object(int,int,int,int,int);
				//deconstructor method
				~Object();

				//access methods
				int getX();
				int getY();
				int getType();
				int getDx();
				int getDy();

				//modify methods
				void setX(int);
				void setY(int);
				void setType(int);
				void setDx(int);
				void setDy(int);

				//utility methods
				void printPlayer(float); // recursive function to print player spaceship to screen
				void printEnemy(float); // recursive function to print enemy spaceship to screen
				void printRock(float); // recursive function to print rock to screen
				void printShot(float); // prints player bullet to the screen
				void printEnemyshot(float); //print enemy bullet to the screen
				void printExplosion(float); //prints explosion to the screen
				void printPowerup(float);  //prints tripleshot powerup to screen
				void printBoost(float);		// prints boost powerup to screen

		private:
				int x,y; // center of object
				int type; // (1-8) types of objects player rock enemy shot explosion powerup or boost
				int dx, dy; // change in objects position over time
				

};

class Board{
		public:
				//constructor methods
				Board(); 
				Board(Object);
				//deconstructor method
				~Board();

				//utility methods
				void setObj(Object);  // add object to currentObjects vector
				void printScreen(int, int,int, bool, bool); //print all the elements of currentObjects to the screen
				void newObst(); // create a new object randomly between an enemy and a rock
				void enemyShoot(int); // create the enemy bullets and add them to currentObjects
				void playerVelocity(int); //set the player (first element of currentObjects) velocity to given value
				void playerPos(int); //set the player (first element of currentObjects) position to given value
				int getPlayerPos(); // get the player position
				void shoot(bool,int); // bullet objects and add them to currentObjects
				int clearObj(long double &, long double &,long double &,int, bool&, bool&,int,int&); // check all the objects for collisions and delete or modify those objects depending on which objects collide
				void wipeBoard(); //clear all the objects from currentObjects
				bool endGame(int); // return true or false depending on whether the user lost the game or not
				void nuke(long double&); // destroy all enemies and rocks in currentObjects

				


		private:
				vector<Object> currentObjects; // vector of Objects that stores all the objects in the game
				vector<Object> tempObjects; // temp vector used to advance the objects in clearObj()
};

