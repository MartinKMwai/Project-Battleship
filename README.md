# Project-Battleship
Team members: Mwai Martin Kibiru, Computer Engineering Major, Yr. 2
              Khan, Sikander Bakht, Computer Engineering Major, Yr. 2
              
              Game Description and Rules 
              (Reference: The Spruce Crafts: https://www.thesprucecrafts.com/the-basic-rules-of-battleship-411069#:~:text=Each%20ship%20must%20be%20placed,ships%20after%20the%20game%20begins.)
              
              
Battleship is a war-themed board game for two players in which the opponents try to guess the location of their opponent's warships and sink them.
 
* Setting-up Game:
Each player will be allocated an empty grid (printed), a hidden grid, and five ships.

Before the game starts, each player inputs the coordinates and direction  of their own five ships into an input file. For each player, the program will read input from the input file and generate the hidden grid by laying out the ships and postitioning them onto the grid. Each ship must be placed horizontally or vertically across grid spaces —not diagonally— and the ships can't hang off the grid. Ships can't occupy the same grid space. You cannot change the position of the ships after the game begins. Also, neither player can see his opponent's grid or ship locations.

The 'printed' grid is used to record the shots fired toward the opponent and to document whether those shots were hits (H) or misses (X).

* GamePlay:
Players take turns calling out row and column coordinates in an attempt to identify a square on the other player's grid that contains a ship. 

On your turn, call out a colum and row. The program then checks that coordinate against the oponent's 'hidden' grid and reports "miss" if there is no ship there, or "hit" if you have correctly guessed a space that is occupied by a ship. The program then updates the 'printed' grid marking each of your shots by using 'H' to document the misses and 'X' to register the hits.

The first player to sink all five of their opponent's ships wins the game.




# Code Requirments:
* Generation of random game sets or events: We intend to use the function "Begin_Attack()"
* Data structure for storing game status: Ship Details, Players (using nested data structures).
* Dynamic memory management: Two Linked Lists to store each players moves.  
* File input/output: 

1- File input for loading each player's input. 

2- File output for printing a player's record of moves and his record grid. 

We anticipatye that as we hit the ground running in earnest on ther project, that we may tweak a few things to accomodate our expertise on C++ as we progress with the coursework.
