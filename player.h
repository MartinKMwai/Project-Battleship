#ifndef PLAYER_H
#define PLAYER_H
#include <string>
/**
	battleship index, name and sizes
	1	Carrier	5
	2	Battleship	4
	3	Cruiser	3
	4	Submarine	3
	5	Destroyer	2
**/

class Player{
  	private:
	    std::string playerName;	//name of the player
	    std::string** playerboard;	// this is the player's board
	    std::string** enemyboard;	// this is the player's view of the enemy board
	    bool battleshipSunk[5] = {false};	//true if battleship has sunk, false otherwise
		std::string battleshipName[5] = {"Carrier", "Battleship", "Cruiser", "Submarine", "Destroyer"};	//name of each battleship
		int battleshipSize[5] = {5, 4, 3, 3, 2};	//size of each battleship
		std::string** battleboardstatus;	//a view of the board, with each location occupied by ship replaced with ship name otherwise o
		
	    //initial player board and player's view of enemy board setup
	    //if there is nothing then print o, if there is ship then print *, if there is sunk/hit ship then print x, if there is hit place and no ship print +
	    void set_initial_board();
	    
  	public:
	  	//constructor for player
	    Player();
	    
	    //set player name
	    void setPlayerName(std::string playerName);
	    
	    //retrieve player name
	    std::string getPlayerName();
	    
	    //retrieve player board
	    std::string** getPlayerBoard();
	    
	    //get the player's view of the enemy's board, i.e. the spots the player has attacked
	    std::string** getEnemyBoard();
		
		//retrieve the battle board status, this is used for checking which ships have sunk
		std::string** getBattleBoardStatus();
		
	    //retrieve battleship names
	    std::string* getBattleshipName();
		
		//retrieve battleship sizes
		int* getBattleshipSize();
		
		//retrive battleship status
		bool* getBattleshipSunk();
};

#endif // PLAYER_H
