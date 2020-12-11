#include "player.h"
#include <iostream>

using namespace std;

//initial player board and player's view of enemy board setup
//if there is nothing then print o, if there is ship then print *, if there is sunk/hit ship then print x, if there is hit place and no ship print +
void Player::set_initial_board(){
	//set up the player's own board
	playerboard = new string*[10];
	for(int i=0; i<10; i++){
		playerboard[i] = new string[10];
		for (int j=0; j<10; j++){
		    playerboard[i][j] = 'o';
		}
	}
		    
	//set up the player's view of the enemy board
	enemyboard = new string*[10];
	for(int i=0; i<10; i++){
		enemyboard[i] = new string[10];
		for (int j=0; j<10; j++){
		enemyboard[i][j] = 'o';
		}
	}
	
	//set up the battle board status, this is used for checking which ships have sunk
	battleboardstatus = new string*[10];
	for(int i=0; i<10; i++){
		battleboardstatus[i] = new string[10];
		for (int j=0; j<10; j++){
		    battleboardstatus[i][j] = 'o';
		}
	}
}

//constructor for player
Player::Player(){
	set_initial_board();
}
	    
//set player name
void Player::setPlayerName(string playerName){
	this->playerName = playerName;
}
	    
//retrieve player name
string Player::getPlayerName(){
	return playerName;
}
	    
//retrieve player board
string** Player::getPlayerBoard(){
	return playerboard;
}
	    
//get the player's view of the enemy's board, i.e. the spots the player has attacked
string** Player::getEnemyBoard(){
	return enemyboard;
}
		
//retrieve the battle board status, this is used for checking which ships have sunk
string** Player::getBattleBoardStatus(){
	return battleboardstatus;
}
		
//retrieve battleship names
string* Player::getBattleshipName(){
	return battleshipName;
}
		
//retrieve battleship sizes
int* Player::getBattleshipSize(){
	return battleshipSize;
}
		
//retrive battleship status
bool* Player::getBattleshipSunk(){
	return battleshipSunk;
}
		
		
		
		
		
		
