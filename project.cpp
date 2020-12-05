//Author: Van Abbott
//
//
#include "gfx.h"
#include "game.h"

int main(int argc, char *argv[]){	
		ifstream ifs;
		User user; 
		vector<User> highscores;

		ifs.open(filename); // opens "highscores.txt" which contains the highscores and who achieved that score
		ifs>>user.name >>user.difficulty>>user.score; // populate temporary user structure with name of player difficulty level they played on and score achieved
		
		while(user.name != "STOP"){
				highscores.push_back(user); // populate vectore with each of the user information for each player that has gotten a top ten score
				ifs>>user.name >>user.difficulty>>user.score;
		}



		int s = 2;	// default difficulty setting for game is 2
		long double timeOf, powerTime,boostTime; //timeOF: keeps track of time something was destroyed, powerTime: keeps track of time that last POWERUP object was picked up, boostTime: keeps track of last time a BOOST object was picked up
		bool gameover = true, TRIPLESHOT = false, SPEED = false; 
		int NUKE = 2; // player starts out with 2 nukes to use
		int score = 0;
		srand(time(NULL));
		int count = 0;
		


		if(argc == 3){ // create user struct with current players info that they enter as arguments
				user.name = argv[1];
				user.difficulty = stoi(argv[2]);
				s = stoi(argv[2]);
		}else{
				cout <<"ERROR: Enter name followed by difficulty level after executable" << endl;
				cout <<"Ex: ./play Name 2 \n(difficulty level 1-5, 1 being the hardest)"<<endl;
				return 1;
		}

		gfx_open(xSize,ySize, "Blaster");
		gfx_clear_color(169,169,169); // gray screen
		gfx_color(126,25,27); // dark red writing and objects
		Object player(400,700,PLAYER,0,0); 
		Board screen(player); //initialize screen object with a player as first element in currentObjects within screen

		char c;
		while(c!='q'){
				while(!gameover){ // while the game is being played
						if(count%(75*s+150) == 0){ // create a random new obst either enemy or rock at spaced out times
								screen.newObst();
						}
						if(count%(150*s+100) == 0){ // have the closest enemy shoot at set interval
								screen.enemyShoot(s);
						}

						gfx_clear(); // clear the screen
						score = screen.clearObj(timeOf,powerTime,boostTime, s,TRIPLESHOT,SPEED,score,NUKE); // check all the objects in screen for collision and destroy or activate power up or boost depending on which objects collide
						screen.printScreen(score,s,NUKE,TRIPLESHOT,SPEED); //display all remaining objects in their updated positions on screen with updated score, nuke and powerup values.

						usleep(15000-60*sqrt(count));//game speeds up with every iteration through game loop

						if(gfx_event_waiting()){ // if user presses anything
								c=gfx_wait();
								if(time(0)-boostTime>10){ // if its been ten seconds since the player picked up last boost take away the boost
										SPEED = false;
								}
								if(c=='w'){ //press w
										if(time(0)-powerTime>15){ // if its been 15 seconds since the player last picked up a tripleshot take away the powerup
												TRIPLESHOT = false;
										}
										screen.shoot(TRIPLESHOT,s); // create bullet objects 1 or 3 depending on whether they have the power up.
										screen.playerVelocity(0); // stop the players movement whenever they shoot
								}else if(c=='a'){// press a
										if(SPEED){
												screen.playerVelocity(-4);//player moves to the left fast
										}else{
												screen.playerVelocity(-2);//player moves to the left normally
										}
								}else if(c=='d'){//press d 
										if(SPEED){
												screen.playerVelocity(4);//player moves to the right fast
										}else{
												screen.playerVelocity(2);//player moves to the right normally
										}
								}else if(c==32&&NUKE>0){ //press space bar
										screen.nuke(timeOf); // destroy all rocks and enemies and turn them into an explosion
										NUKE--;
										;
								}else{ 
										screen.playerVelocity(0); // if user presses any not used key then stop the players movement
								}

						}
						count++;
						if(screen.endGame(s))gameover=true; // if the player collides with a rock enemy or bullet or if an enemy gets past the player end the game
						if(c=='q')break; // quit game if user presses q
				}
				user.score = score;//record users score to user struct
				score = 0; // reset score
				powerTime = 0; // reset time of last powerup
				count = 0; // reset count
				NUKE = 2; // reset number of nukes

				screen.wipeBoard(); // delete all objects on the board
				screen.setObj(player); //add the original player object to the game

				highscores.push_back(user); // add the users score to vector of highscores to be compared
				sortScores(highscores); // sort the scores and delete the lowest one
				ofstream ofs;
				ofs.open(filename); 
				for (auto it = highscores.begin(); it != highscores.end(); it++){ // write the updated highscores to the "highscores.txt" file
						ofs << it->name << " " << it->difficulty << " " <<it->score <<endl;
				}
				ofs << "STOP 0 0"<<endl;

				displayMenu(highscores,user); // display the menu and highscores to screen
				while(1==1){ 
						if(gfx_event_waiting()){ // wait for the user to press a key to start the game
								c = gfx_wait();
								gfx_clear();
								gameover=false;
								break;	
						}
				}	
		}
		return 0;
}
