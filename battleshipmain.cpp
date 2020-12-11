#include <iostream>
#include <limits>
#include "player.h"
using namespace std;

void initial_setup(Player *player1, Player *player2);
bool place_battleship_legal(Player *player, int battleshipsize, int place_x, int place_y, string alignment);
void place_battleship(Player *player);
void print_board(Player *player);
void take_turn(Player *player1, Player *player2);
bool hit_enemy(Player *player1, Player *player2, int &hit_x, int &hit_y);
void battle_ship_sunk(Player *player, int hit_x, int hit_y);
bool win(Player *player1, Player *player2);

void initial_setup(Player *player1, Player *player2){
	//enter and set player names
	string name;
	//player 1 name setup
	cout << "Enter player 1 name" << endl;
	getline(cin, name);
	cout << endl;
	player1->setPlayerName(name);
	
	//player2 name setup
	cout << "Enter player 2 name" << endl;
	getline(cin, name);
	cout << endl;
	player2->setPlayerName(name);
	
	//place battleships on the player board
	//player 1 places battleships
  	cout << player1->getPlayerName() << " please place your battleships\n" << endl;
  	place_battleship(player1);
  	
  	//player 2 places battleships
  	cout << player2->getPlayerName() << " please place your battleships\n" << endl;
  	place_battleship(player2);
}


//check if the placing of the new battleship is a legal move
bool place_battleship_legal(Player *player, int battleshipsize, int place_x, int place_y, string alignment){
	bool checkShip = true;
	//check if the placement is legal for horizontal placement
	if (alignment == "horizontal"){
		if (place_x < 0 || place_x + battleshipsize - 1 >= 10 || place_y < 0 || place_y >= 10){
			return false;
		}
		else{
			for (int i=0; i<battleshipsize; i++){
				if (player->getPlayerBoard()[place_x+i][place_y] == "*"){
					checkShip = false;
				}
			}
			if (checkShip){
				return true;
			}
			else{
				return false;
			}
		}
	}
	//check if the placement is legal for vertical placement
	else if(alignment == "vertical"){
		if (place_x < 0 || place_x >= 10 || place_y < 0 || place_y + battleshipsize - 1 >= 10){
			return false;
		}
		else{
			for (int i=0; i<battleshipsize; i++){
				if (player->getPlayerBoard()[place_x][place_y+i] == "*"){
					checkShip = false;
				}
			}
			if (checkShip){
				return true;
			}
			else{
				return false;
			}
		}
	}
}

//place the battleships on the board
void place_battleship(Player *player){
  	string alignment; //alignment of ship i.e. horizontal or vertical
  	int place_x, place_y; //coordinates to place the ships at
    
	/**
	battleship index, name and sizes
	1	Carrier	5
	2	Battleship	4
	3	Cruiser	3
	4	Submarine	3
	5	Destroyer	2
	**/
	
  	for (int i=0; i<5; i++){
	  	//prompt player to place battle ships
	  	//check alignment, if invalid input ask again
		cout << "Placing " << player->getBattleshipName()[i] << " battleship (size: " << player->getBattleshipSize()[i] << ")" << endl;
	  	while (true){
	  		//get alignment of ship from the player
	  		cout << "Please enter alignment vertical or horizontal?" << endl;
	    	cin >> alignment;
	    	cout << endl;
	    	//convert the player input to lowercase for checking correct input i.e. ignore case sensivity
			for (int j=0; j<alignment.length(); j++){
		      	if (alignment[j] > 'A' && alignment[j] < 'Z'){
		        	alignment[j] -= 'A' - 'a';
		     	}
	    	}
	    	if (alignment == "vertical" || alignment == "horizontal"){
	      		break;
	    	}
	    	else{
	    		cout << "invalid input, please enter again" << endl;
			}
	 	}
 	
 		while (true){
 			//check placed position of battleship, if invalid placement ask for input again
			cout << "Please enter coordinates to put " << player->getBattleshipName()[i] << " battleship (size: " << player->getBattleshipSize()[i] << ")"<< endl;
			while (!(cin >> place_x >> place_y)) {
			    cin.clear(); //clear bad input flag
			    cin.ignore(numeric_limits<streamsize>::max(), '\n'); //discard input
			    cout << "Invalid input; please re-enter.\n";
			}
			cout << endl;
			
			//check if the position is legal, if not print error message and retry
			if (place_battleship_legal(player, player->getBattleshipSize()[i], place_x, place_y, alignment)){
				for (int j=0; j<player->getBattleshipSize()[i]; j++){
					//add the ship to the board if the placement is legal
					if (alignment == "vertical"){
						player->getPlayerBoard()[place_x][place_y+j] = '*'; 
						player->getBattleBoardStatus()[place_x][place_y+j] = player->getBattleshipName()[i];
					}
					else if (alignment == "horizontal"){
						player->getPlayerBoard()[place_x+j][place_y] = '*'; 
						player->getBattleBoardStatus()[place_x+j][place_y] = player->getBattleshipName()[i];
					}
				}
				break;
			}
		  	else{
		    	cout << "invalid battlship location retry\n" << endl;
			}
			
		}
		//print the board for visualization
		print_board(player);
  	}
}

void print_board(Player *player){
	cout << player->getPlayerName() << " Board: \n"<< endl;
	//output the top/horizontal axis
	cout << "  ";
	for (int i=0; i<10; i++){
		cout << i << " ";
	}
	cout << endl;
	//output the enemy board
	for (int j=0; j<10; j++){
		cout << j << " ";	//for printing vertical axis
		for (int i=0; i<10; i++){
			cout << player->getEnemyBoard()[i][j] << " ";	//print the board
		}
		cout << endl;
	}
	
	cout << "----------------------" << endl;
	
	//output the top/horizontal axis 
	cout << "  ";
	for (int i=0; i<10; i++){
		cout << i << " ";
	}
	cout << endl;
	//output the player board
	for (int j=0; j<10; j++){
		cout << j << " ";	//for printing vertical axis
		for (int i=0; i<10; i++){
			cout << player->getPlayerBoard()[i][j] << " ";	//print the board
		}
		cout << endl;
	}
	cout << endl;
}

//player 1 takes turn to attack player 2
//check if enemy was hit, if it was hit check if a battle ship has sunk
void take_turn(Player *player1, Player *player2){
	//print board for visualization before taking turn
	print_board(player1);
	//declare variables
	int hit_x = 0, hit_y = 0;
	bool hit_enemy_ship;
	
	//hit the enemy and update both player boards
	hit_enemy_ship = hit_enemy(player1, player2, hit_x, hit_y);
	
	//if enemy was hit, check and report if any battleship sunk
	if (hit_enemy_ship){
		battle_ship_sunk(player2, hit_x, hit_y);
	}
}

//update the board on the attack for both players
//check if the enemy has been hit
bool hit_enemy(Player *player1, Player *player2, int &hit_x, int &hit_y){
	// x and + means that spot was hit before, x = hit ship, + = hit nothing
	while (true){
		cout << player1->getPlayerName() << " Enter the coordinates that you would like to hit on the enemy board" << endl;
		while (!(cin >> hit_x >> hit_y) || (hit_x < 0 || hit_x >= 10 || hit_y < 0 || hit_y >= 10)) {
			    cin.clear(); //clear bad input flag
			    cin.ignore(numeric_limits<streamsize>::max(), '\n'); //discard input
			    cout << "Invalid input; please re-enter.\n";
		}
		if (player1->getEnemyBoard()[hit_x][hit_y] == "o"){	//if the place has not been hit before
			if (player2->getPlayerBoard()[hit_x][hit_y] == "*"){
				player1->getEnemyBoard()[hit_x][hit_y] = "x";
				player2->getPlayerBoard()[hit_x][hit_y] = "x";
				return true;
			}
			else if (player2->getPlayerBoard()[hit_x][hit_y] == "o"){
				player1->getEnemyBoard()[hit_x][hit_y] = "+";
				player2->getPlayerBoard()[hit_x][hit_y] = "+";
				return false;
			}
			break;
		}
	}
}

//this function is only called if a ship has been hit
//if it has check if the ship sunk, flag the ship as sunk
//declare winner if all ships have sunk
void battle_ship_sunk(Player *player, int hit_x, int hit_y){
	//check if a ship has sunk from the hit
	string shipname = player->getBattleBoardStatus()[hit_x][hit_y];
	player->getBattleBoardStatus()[hit_x][hit_y] = 'x';
  	bool containsShip = false;
  	for (int i=0; i<10; i++){
	  	for (int j=0; j<10; j++){
	  		if (player->getBattleBoardStatus()[i][j] == shipname){
	  			containsShip = true;	//ship still on the board, not sunk
			}
		}
	}
	//if the ship has sunk for the player, announce it and flag it as sunk
	if (!containsShip){
		//announce ship is sunk
		cout << player->getPlayerName() << " " << shipname << " has sank!/n" << endl;
		
		//flag the correct ship as sunk
		for (int i=0; i<5; i++){
			if (player->getBattleshipName()[i] == shipname){
				player->getBattleshipSunk()[i] = true;
			}
		}
	}
}
//return true if all battle ships are sunk for the player
bool win(Player *player1, Player *player2){
  	bool checkWin = true;
  	//check if all of the battleship have sunk for opponent player, if so declare victory
  	for (int i=0; i<5; i++){
    	if (!player2->getBattleshipSunk()[i]){
      		checkWin = false;
      		break;
    	}
  	}
  	//if victory is declared output winner message
  	if (checkWin){
  		cout << player1->getPlayerName() << " has won the game!!!" << endl;
	}
	//return true if game is over
	return checkWin;
}

//sample case for testing
//vertical 1 1 vertical 2 2 vertical 3 3 vertical 4 4 vertical 5 5 vertical 1 1 vertical 2 2 vertical 3 3 vertical 4 4 vertical 5 5
//1 1 1 1 1 2 1 2 1 3 1 3 1 4 1 4 1 5 1 5 2 2 2 2 2 3 2 3 2 4 2 4 2 5 2 5 3 3 3 3 3 4 3 4 3 5 3 5 4 4 4 4 4 5 4 5 4 6 4 6
//5 5 5 5 5 6 5 6

int main(int argc, char** argv){
	//declare the players
  	Player* player1 = new Player();
  	Player* player2 = new Player();
  	
  	//setup the name and board of the players
  	initial_setup(player1, player2);
  	
  	//take turns until game is won
  	while (!win(player1, player2) && !win(player2, player1)){
		take_turn(player1, player2);
		//if player 1 wins, end game early no need player 2 input.
  		if(win(player1, player2)){
  			break;
		}
  		take_turn(player2, player1);
  	}
}












