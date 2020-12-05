//Author: Van Abbott
//
//
#include "game.h"

void displayMenu(vector<User> highscores, User user){ //displays menu screen and highscores to the screen
		gfx_clear();
		gfx_text(xSize*5/16,ySize/4,"Press any key to play Bit Blaster! (or q to quit)");
		gfx_text(xSize*5/16,ySize/4 + BOARDER, user.name.c_str());
		gfx_text(xSize*5/16,ySize/4 + 2*BOARDER, "Score:");
		gfx_text(xSize*5/16+40,ySize/4 + 2*BOARDER, (to_string(user.score)).c_str());
		gfx_text(xSize*5/16,ySize/4 + 3*BOARDER, "Difficulty Level:");
		gfx_text(xSize*5/16+ 110, ySize/4+3*BOARDER, (to_string(abs(user.difficulty-5))).c_str());
		gfx_text(xSize*3/8,ySize/2, "Highscores:");
		for(int i = 0; i < highscores.size(); i++){
				gfx_text(xSize*3/8,ySize/2+(i+1)*BOARDER, highscores[i].name.c_str());
				gfx_text(xSize*3/8+100,ySize/2+(i+1)*BOARDER, (to_string(highscores[i].score)).c_str());
		}
}
void sortScores(vector<User>& highscores){ //bubble sort algorithm to sort highscores
		User t;
		for(auto it=highscores.begin();it!=highscores.end(); it++){
		}
		for(int it = 1; it < highscores.size(); it++){
				t = highscores[it];
				
				for(int n = it-1; n >=0;n--){
						if(highscores[n].score<t.score){
								highscores[n+1]=highscores[n];
								highscores[n] = t;
						}
				}
				
				
		}
		highscores.pop_back(); // delete lowest score so only top ten scores are recorded
		
}

Object::Object(){ // default constructor for objects
		x = 0;
		y = 0;
		type = 0;
		dx = 0; 
		dy = 0;
}
Object::Object(int a,int b,int t,int vx,int vy){ //constructor 
		setX(a);
		setY(b);
		setType(t);
		setDx(vx);
		setDy(vy);
}
Object::~Object(){}

int Object::getX(){return x;}    
int Object::getY(){return y;}
int Object::getType(){return type;}
int Object::getDx(){return dx;}
int Object::getDy(){return dy;}

void Object::setX(int a){ 
		if(a>xSize)a = 0+1; // if object goes past screen to the right bring it back onto the screen from the left side
		if(a<0)a = xSize-1; // if object goes off screen to the left bring it back onto the screen from the right side
		x = a;
}
void Object::setY(int b){y = b;}
void Object::setType(int t){type = t;}
void Object::setDx(int vx){dx = vx;}
void Object::setDy(int vy){dy = vy;}

void Object::printPlayer(float s){ // recursive player spaceship
		if(s<0.5)return;;
		gfx_line(x,y-(8*s),x,y-(16*s));
		gfx_line(x-(4*s),y-(8*s),x+(4*s),y-(8*s));
		gfx_line(x-(4*s),y-(8*s),x-(4*s),y-(4*s));
		gfx_line(x+(4*s),y-(8*s),x+(4*s),y-(4*s));
		gfx_line(x-(4*s),y-(4*s),x-(10*s),y+(4*s));
		gfx_line(x+(4*s),y-(4*s),x+(10*s),y+(4*s));
		gfx_line(x-(10*s),y+(4*s),x+(10*s),y+(4*s));
		gfx_line(x-(10*s),y+(4*s),x-(10*s),y-(6*s));
		gfx_line(x+(10*s),y+(4*s),x+(10*s),y-(6*s));
		s=s-1;
		printPlayer(s);
		
}

void Object::printRock(float s){ // recursive rock
		if(s<0.5)return;
		gfx_circle(x,y,SIZE*s);
		s--;
		printRock(s);
		
}

void Object::printEnemy(float s){ // recursive enemy spaceship
		if(s<0.5)return;
		gfx_line(x-(11*s),y-(6*s),x+(11*s),y-(6*s));
		gfx_line(x-(11*s),y-(6*s),x-(11*s),y-(2*s));
		gfx_line(x+(11*s),y-(6*s),x+(11*s),y-(2*s));
		gfx_line(x-(11*s),y-(2*s),x-(6*s),y+(2*s));
		gfx_line(x-(6*s),y+(2*s),x-(4*s),y-(2*s));
		gfx_line(x+(11*s),y-(2*s),x+(6*s),y+(2*s));
		gfx_line(x+(6*s),y+(2*s),x+(4*s),y-(2*s));
		gfx_line(x-(4*s),y-(2*s),x,y+(6*s));
		gfx_line(x+(4*s),y-(2*s),x,y+(6*s));
		s--;
		printEnemy(s);
		
}
void Object::printShot(float s){ // player bullet
		gfx_line(x,y-(4*s),x,y+(2*s));
		gfx_line(x-1,y-(4*s),x-1, y+(2*s));
		gfx_line(x+1,y-(4*s),x+1, y+(2*s));
		return;
}
void Object::printEnemyshot(float s){ // enemy bullet
		gfx_line(x,y-(4*s),x,y+(2*s));
		return;
}

void Object::printExplosion(float s){ // print explosion
		//gfx_color(255,100,100);
		for(int i = 1; i<=8; i++){
				gfx_line(x+cos((M_PI/4)*i)*10*s,y+sin((M_PI/4)*i)*10*s,x+cos((M_PI/4)*i)*4*s,y+sin((M_PI/4)*i)*4*s);
		}
		//gfx_color(255,255,255);
		return;
}
void Object::printPowerup(float s){ // print tripleshot powerup as five horizontal lines
		for(int i = -2; i <= 2; i++){
				gfx_line(x-s*SIZE,y+SIZE*s*i/5,x+s*SIZE,y+SIZE*s*i/5);
		}
		return;
}

void Object::printBoost(float s){ // print boost powerup as two arrow heads point to either side
		for(int i = 1; i < 3; i++){
				gfx_line(x+SIZE*s*i, y, x+SIZE*i*s/4,y+SIZE*s);
				gfx_line(x+SIZE*s*i, y, x+SIZE*i*s/4,y-SIZE*s);
				gfx_line(x-SIZE*s*i, y, x-SIZE*i*s/4,y+SIZE*s);
				gfx_line(x-SIZE*s*i, y, x-SIZE*i*s/4,y-SIZE*s);
		}
}

Board::Board(){}
Board::Board(Object o){setObj(o);}
Board::~Board(){}

void Board::setObj(Object o){
		currentObjects.push_back(o); // add new object to currentObjects
}
void Board::printScreen(int score,int s,int nuke,bool triple, bool boost){
		string snuke = to_string(nuke);
		string sc = to_string(score);
		for(auto it = currentObjects.begin(); it != currentObjects.end(); it++){ // iterate through every object in currentObjects
				switch(it->getType()){ 							// print object depending on what type of object it is and adjust its position according to its velocities
						case PLAYER:
								it->printPlayer((float)s);
								it->setX(it->getX()+it->getDx());
								break;
						case ENEMY:
								it->printEnemy((float)s);
								it->setY(it->getY()+it->getDy());
								break;
						case ROCK:
								it->printRock((float)s);
								it->setY(it->getY()+it->getDy());
								break;
						case SHOT:
								it->printShot((float)s);
								it->setY(it->getY()+it->getDy());
								break;
						case EXPLOSION:
								it->printExplosion((float)s);
								it->setY(it->getY()+it->getDy());
								break;
						case POWERUP:
								it->printPowerup((float)s);
								it->setY(it->getY()+it->getDy());
								break;
						case ENEMYSHOT:
								it->printEnemyshot((float)s);
								it->setY(it->getY()+it->getDy());
								break;
						case BOOST: 
								it->printBoost((float)s);
								it->setY(it->getY()+it->getDy());
								break;
				}
		}
		gfx_text(xSize-75,BOARDER, "Score: "); // print current score to top right corner
		gfx_text(xSize-30,BOARDER, sc.c_str()); 
		gfx_text(xSize-105, 2*BOARDER, "Nukes Left: "); // print how many nukes the player has remaining in top right corner
		gfx_text(xSize-30, 2*BOARDER,snuke.c_str());
		if(triple)gfx_text(10, BOARDER, "MULTISHOT"); //display multishot in top left corner if player has that powerup
		if(boost)gfx_text(10,2*BOARDER, "BOOST"); // display boost in top left corner if player has that powerup
}
void Board::newObst(){ // create new objects either rock enemy or either of the powerups randomly and add them to current objects
		Object newEn;
		newEn.setX(rand()%(xSize-BOARDER)+10);
		newEn.setY(-BOARDER);
		newEn.setType(rand()%2+2);
		newEn.setDx(0);
		newEn.setDy(1);
		currentObjects.push_back(newEn);
		if((rand()%10+1)%5==0){
				newEn.setX(rand()%(xSize-BOARDER)+10);
				newEn.setY(-BOARDER);
				if(rand()%2==0){
						newEn.setType(POWERUP);
				}else{
						newEn.setType(BOOST);
				}
				newEn.setDx(0);
				newEn.setDy(1);
				currentObjects.push_back(newEn);
		}
}
void Board::enemyShoot(int s){ // create new enemy bullet for the closest enemy only and add them to the current objects
		Object bullet;
		bullet.setType(ENEMYSHOT);
		for(auto it = currentObjects.begin(); it!=currentObjects.end(); it++){
				if(it->getType()==ENEMY){
						bullet.setX(it->getX());
						bullet.setY(it->getY()+6*s);
						bullet.setDy(3);
						currentObjects.push_back(bullet);
						break;	
				}
		}
}
void Board::playerVelocity(int vx){ //update player's velocity (player is always the zeroth element of current objects)
		currentObjects[0].setDx(vx);
}
void Board::playerPos(int x){ //set players position
		if(currentObjects[0].getX()>0-BOARDER &&currentObjects[0].getX()<xSize+BOARDER){
				currentObjects[0].setX(currentObjects[0].getX()+x);
		}else{
				currentObjects[0].setX(abs(currentObjects[0].getX()-xSize+BOARDER));
		}
}
int Board::getPlayerPos(){ // get players position
		return currentObjects[0].getX();
}
void Board::shoot(bool TRIPLESHOT,int s){ // create players bullets depending on whether they have tripleshot or not
		Object bullet;
		bullet.setType(SHOT);
		if(TRIPLESHOT){
				for(int i = -1; i<2; i++){
						bullet.setX(currentObjects[0].getX()+s*10*i);
						bullet.setY(700-BOARDER+abs(i*6*s));
						bullet.setDx(0);
						bullet.setDy(-3);
						currentObjects.push_back(bullet);
				}
		}else{
				bullet.setX(currentObjects[0].getX());
				bullet.setY(700-BOARDER);
				bullet.setDx(0);
				bullet.setDy(-3);
				currentObjects.push_back(bullet);
		}
}

int Board::clearObj(long double &timeOf, long double &powerTime ,long double &boostTime, int s,bool &TRIPLESHOT, bool &SPEED, int score, int &nuke){
		Object boom(0,0,EXPLOSION,0,0);
		int kill=0;
		int del = 0;
		double dist;
		for(auto it = currentObjects.begin(); it != currentObjects.end(); it++){ //iterate through every current object
				if(it->getY()<-BOARDER||it->getY()>ySize+BOARDER){ // if the object is past the screen in either + or - y directions delete it
						del = 1;
				}else if(it->getType()<SHOT&&it->getType()>PLAYER){ // if object is an enemy or rock
						for(int ij = 0; ij<currentObjects.size(); ij++){ //iterate through every object on th escreen 
								if(currentObjects[ij].getType()==SHOT){ // if that object is a player bullet
										dist =sqrt(pow((it->getY())-(currentObjects[ij].getY()),2)+pow((it->getX())-(currentObjects[ij].getX()),2));
										if(dist<=s*SIZE){ // and that bullet is closer than the radius of the enemy or rock then delete object
												del = 2;
										}
								}
						}
				}else if(it->getType()==SHOT|| it->getType()==ENEMYSHOT){ // if the current object is either player bullet or enemy bullet
						for(auto iw = currentObjects.begin();iw!=currentObjects.end(); iw++){ // iterate through every object on the screen 
								if(it->getType()==SHOT){ // if the current object is player bullet 
										if(iw->getType()==ENEMY||iw->getType()==ROCK){ // and new object is enemy or rock 
												dist =sqrt(pow((it->getY())-(iw->getY()),2)+pow((it->getX())-(iw->getX()),2));
												if(dist<=s*SIZE){ // and the bullet hits the object delete the bullet
														del=1;
														if(iw->getType()==ENEMY){ //count as a kill and increase if it hits an enemy
																kill++;
																if((score+1)%10==0)nuke++;//give the player another nuke to use every ten points
																
														}
												}
										}else if(iw->getType()==ENEMYSHOT){ 
												dist =sqrt(pow((it->getY())-(iw->getY()),2)+pow((it->getX())-(iw->getX()),2));
												if(dist<=3){ // delete the player bullet if it collides with an enemy bullet
														del=1;
												}
										}
								}else if(it->getType() == ENEMYSHOT){ // if the current object is an enemy bullet
										if(iw->getType()<POWERUP&&iw->getType()!=ENEMY){ // delete the enemy bullet if it hits anything other than a power up or boost 
												dist =sqrt(pow((it->getY())-(iw->getY()),2)+pow((it->getX())-(iw->getX()),2));
												if(iw->getType()==SHOT&& dist<=3){
														del = 1;
												}else if(dist <s*SIZE&&iw->getType()!=SHOT){ 
														del = 1;
												}
										}
								}
								
						}
				}else if(it->getType()==EXPLOSION&&(time(0)-timeOf)>0.25){ // if the current object is an explosion and it has been longer than a quarter of a second since it "blew up" than delete it
						del = 1;
				}else if(it->getType()==POWERUP||it->getType()==BOOST){ // if the object is either of the powerups and collides with the player object than turn the bools for the powerups to be true and record the time the powerup started and remove the powerup from the screen
						dist =sqrt(pow((it->getY())-(currentObjects[0].getY()),2)+pow((it->getX())-(currentObjects[0].getX()),2));
						if(dist<2*s*SIZE&&it->getType()==POWERUP){
								del = 1;
								TRIPLESHOT = true;
								powerTime = time(0);
						}else if(dist<2*s*SIZE){
								del = 1;
								SPEED = true;
								boostTime = time(0);
						}
				}
				if(del==0){ 
						tempObjects.push_back(*it); // if the object's del value was unchanged add it to the temporary objects
				}else if(del == 2){ //if object was destroyed from a bullet replace with explosion
						boom.setX(it->getX());
						boom.setY(it->getY());
						tempObjects.push_back(boom);
						timeOf = time(0);
				}
				del= 0; // reset del value for every object
		}
		currentObjects.clear(); // clear the old objects
		currentObjects = tempObjects; // update the current objects
		tempObjects.clear(); // clear the temp objects
		return score+kill; // return the new score
		
}
void Board::wipeBoard(){
		currentObjects.clear(); // delete all objects on the screen
}	
bool Board::endGame(int s){ // returns true if the game needs to end
		double dist;
		for(auto it = currentObjects.begin();it!=currentObjects.end();it++){
				if(it->getType()==ENEMY&&it->getY()>ySize){ // if any enemy object gets past the bottom of the screen game over
						return true;
				}else if(it->getType()==ENEMY||it->getType()==ROCK||it->getType()==ENEMYSHOT){
						dist =sqrt(pow((it->getY())-(currentObjects[0].getY()),2)+pow((it->getX())-(currentObjects[0].getX()),2));
						if(dist<2*s*SIZE&&it->getType()!=ENEMYSHOT){
								return true; // if any rock or enemy collides with player game over
						}else if(dist<s*SIZE&&it->getType()==ENEMYSHOT){
								return true; // if any enemy bullet collides with the player game over
						}
				}
		}
		return false; // else the game can keep going
}

void Board::nuke(long double &timeOf){ // replace all rocks and enemies on the screen with explosion
		for(auto it=currentObjects.begin(); it!=currentObjects.end(); it++){
				if(it->getType()==ENEMY||it->getType()==ROCK||it->getType()==ENEMYSHOT){
						it->setType(EXPLOSION);
						timeOf=time(0);
				}
		}
		
}



