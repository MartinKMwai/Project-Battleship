#include <iostream>
#include <limits>
using namespace std;

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
	    string playerName;	//name of the player
	    string** playerboard;	// this is the player's board
	    string** enemyboard;	// this is the player's view of the enemy board
	    bool battleshipSunk[5] = {false};	//true if battleship has sunk, false otherwise
		string battleshipName[5] = {"Carrier", "Battleship", "Cruiser", "Submarine", "Destroyer"};	//name of each battleship
		int battleshipSize[5] = {5, 4, 3, 3, 2};	//size of each battleship
		string** battleboardstatus;	//a view of the board, with each location occupied by ship replaced with ship name otherwise o
		
	    //initial player board and player's view of enemy board setup
	    //if there is nothing then print o, if there is ship then print *, if there is sunk/hit ship then print x, if there is hit place and no ship print +
	    void set_initial_board(){
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
	    
  	public:
	  	//constructor for player
	    Player(){
	      set_initial_board();
	    }
	    
	    //set player name
	    void setPlayerName(string playerName){
	      this->playerName = playerName;
	    }
	    
	    //retrieve player name
	    string getPlayerName(){
	      return playerName;
	    }
	    
	    //retrieve player board
	    string** getPlayerBoard(){
	      return playerboard;
	    }
	    
	    //get the player's view of the enemy's board, i.e. the spots the player has attacked
	    string** getEnemyBoard(){
	    	return enemyboard;
		}
		
		//retrieve the battle board status, this is used for checking which ships have sunk
		string** getBattleBoardStatus(){
			return battleboardstatus;
		}
		
	    //retrieve battleship names
	    string* getBattleshipName(){
	    	return battleshipName;
		}
		
		//retrieve battleship sizes
		int* getBattleshipSize(){
			return battleshipSize;
		}
		
		//retrive battleship status
		bool* getBattleshipSunk(){
			return battleshipSunk;
		}
};


void initial_setup(Player player1, Player player2);
bool place_battleship_legal(Player player, int battleshipsize, int place_x, int place_y, string alignment);
void place_battleship(Player player);
void print_board(Player player);
void take_turn(Player player1, Player player2);
bool hit_enemy(Player player1, Player player2, int &hit_x, int &hit_y);
void battle_ship_sunk(Player player, int hit_x, int hit_y);
bool win(Player player1, Player player2);
void name_setup(Player *player1, Player *player2);



void name_setup(Player *player1, Player *player2){
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
}

void initial_setup(Player player1, Player player2){
	//place battleships on the player board
	//player 1 places battleships
  	cout << player1.getPlayerName() << " please place your battleships\n" << endl;
  	place_battleship(player1);
  	
  	//player 2 places battleships
  	cout << player2.getPlayerName() << " please place your battleships\n" << endl;
  	place_battleship(player2);
}


//check if the placing of the new battleship is a legal move
bool place_battleship_legal(Player player, int battleshipsize, int place_x, int place_y, string alignment){
	bool checkShip = true;
	if (alignment == "horizontal"){
		if (place_x < 0 || place_x + battleshipsize - 1 >= 10 || place_y < 0 || place_y >= 10){
			return false;
		}
		else{
			for (int i=0; i<battleshipsize; i++){
				if (player.getPlayerBoard()[place_x+i][place_y] == "*"){
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
	else if(alignment == "vertical"){
		if (place_x < 0 || place_x >= 10 || place_y < 0 || place_y + battleshipsize - 1 >= 10){
			return false;
		}
		else{
			for (int i=0; i<battleshipsize; i++){
				if (player.getPlayerBoard()[place_x][place_y+i] == "*"){
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
void place_battleship(Player player){
  	string alignment; //alignment of ship i.e. horizontal or vertical
  	int place_x, place_y; //coordinates to place the ships at
    
	/**
	1	Carrier	5
	2	Battleship	4
	3	Cruiser	3
	4	Submarine	3
	5	Destroyer	2
	**/
	
  	for (int i=0; i<5; i++){
	  	//prompt player to place battle ships
	  	//check alignment, if invalid input ask again
		cout << "Placing " << player.getBattleshipName()[i] << " battleship (size: " << player.getBattleshipSize()[i] << ")" << endl;
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
			cout << "Please enter coordinates to put " << player.getBattleshipName()[i] << " battleship (size: " << player.getBattleshipSize()[i] << ")"<< endl;
			while (!(cin >> place_x >> place_y)) {
			    cin.clear(); //clear bad input flag
			    cin.ignore(numeric_limits<streamsize>::max(), '\n'); //discard input
			    cout << "Invalid input; please re-enter.\n";
			}
			cout << endl;
			
			
			if (place_battleship_legal(player, player.getBattleshipSize()[i], place_x, place_y, alignment)){
				for (int j=0; j<player.getBattleshipSize()[i]; j++){
					//add the ship to the board if the placement is legal
					if (alignment == "vertical"){
						player.getPlayerBoard()[place_x][place_y+j] = '*'; 
						player.getBattleBoardStatus()[place_x][place_y+j] = player.getBattleshipName()[i];
					}
					else if (alignment == "horizontal"){
						player.getPlayerBoard()[place_x+j][place_y] = '*'; 
						player.getBattleBoardStatus()[place_x+j][place_y] = player.getBattleshipName()[i];
					}
				}
				break;
			}
		  	else{
		    	cout << "invalid battlship location retry\n" << endl;
			}
			
		}
		print_board(player);
  	}
}

void print_board(Player player){
	cout << player.getPlayerName() << " Board: \n"<< endl;
	//output the axis
	cout << "  ";
	for (int i=0; i<10; i++){
		cout << i << " ";
	}
	cout << endl;
	//output the enemy board
	for (int j=0; j<10; j++){
		cout << j << " ";
		for (int i=0; i<10; i++){
			cout << player.getEnemyBoard()[i][j] << " ";
		}
		cout << endl;
	}
	
	cout << "----------------------" << endl;
	
	//output the axis 
	cout << "  ";
	for (int i=0; i<10; i++){
		cout << i << " ";
	}
	cout << endl;
	//output the player board
	for (int j=0; j<10; j++){
		cout << j << " ";
		for (int i=0; i<10; i++){
			cout << player.getPlayerBoard()[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}
void take_turn(Player player1, Player player2){
	print_board(player1);
	int hit_x = 0, hit_y = 0;
	bool hit_enemy_ship;
	
	//hit the enemy and update both player boards
	hit_enemy_ship = hit_enemy(player1, player2, hit_x, hit_y);
	
	//if enemy was hit, check and report if any battleship sunk
	if (hit_enemy_ship){
		battle_ship_sunk(player2, hit_x, hit_y);
	}
}

bool hit_enemy(Player player1, Player player2, int &hit_x, int &hit_y){
	// x and + means that spot was hit before, x = hit ship, + = hit nothing
	while (true){
		cout << player1.getPlayerName() << " Enter the coordinates that you would like to hit on the enemy board" << endl;
		while (!(cin >> hit_x >> hit_y)) {
			    cin.clear(); //clear bad input flag
			    cin.ignore(numeric_limits<streamsize>::max(), '\n'); //discard input
			    cout << "Invalid input; please re-enter.\n";
		}
		if (player1.getEnemyBoard()[hit_x][hit_y] == "o"){	//if the place has not been hit before
			if (player2.getPlayerBoard()[hit_x][hit_y] == "*"){
				player1.getEnemyBoard()[hit_x][hit_y] = "x";
				player2.getPlayerBoard()[hit_x][hit_y] = "x";
				return true;
			}
			else if (player2.getPlayerBoard()[hit_x][hit_y] == "o"){
				player1.getEnemyBoard()[hit_x][hit_y] = "+";
				player2.getPlayerBoard()[hit_x][hit_y] = "+";
				return false;
			}
			break;
		}
	}
}

void battle_ship_sunk(Player player, int hit_x, int hit_y){
	string shipname = player.getBattleBoardStatus()[hit_x][hit_y];
	player.getBattleBoardStatus()[hit_x][hit_y] = 'x';
  	bool containsShip = false;
  	for (int i=0; i<10; i++){
	  	for (int j=0; j<10; j++){
	  		if (player.getBattleBoardStatus()[i][j] == shipname){
	  			containsShip = true;	//ship still on the board, not sunk
			}
		}
	}
	if (!containsShip){
		//ship is sunk
		cout << player.getPlayerName() << " " << shipname << " has sank";
		for (int i=0; i<5; i++){
			if (player.getBattleshipName()[i] == shipname){
				player.getBattleshipSunk()[i] == true;
			}
		}
	}
}
//return true if all battle ships are sunk for the player
bool win(Player player1, Player player2){
  	bool checkWin = true;
  	for (int i=0; i<5; i++){
    	if (!player2.getBattleshipSunk()[i]){
      		checkWin = false;
      		break;
    	}
  	}
  	if (checkWin){
  		cout << player1.getPlayerName() << " has won the game!!!" << endl;
	}
	return checkWin;
}


//vertical 1 1 vertical 2 2 vertical 3 3 vertical 4 4 vertical 5 5

int main(int argc, char** argv){
  Player player1;
  Player player2;
  Player* player1_ptr = &player1;
  Player* player2_ptr = &player2;
  
  name_setup(player1_ptr, player2_ptr);
  initial_setup(player1, player2);
  while (!win(player1, player2) || !win(player2, player1)){
  	take_turn(player1, player2);
  	take_turn(player2, player1);
  }
}









