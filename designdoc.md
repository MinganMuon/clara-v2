# Designing Clara

UIs:
----
Game UI: allows the user to play against a selected group of AI's
AI testing UI: allows the user to pit AIs against each other and analyze the results
AI statistics/info UI: allows the user to get info about the AIs and statistics from previous AI-AI matches
AI training UI: allows the user to train trainable AI types

Game logic:
-----------
Game state class: Holds a game state:
		  - board
		  - who's turn it is
		  - a list of previous moves
		  - possibly other things like how many moves since the last capture and similar stuff
		  Also contains functions to determine:
		  - if the board represents a winning situation
		  - other things like that
Board class: Holds a board state; see the board representation section for details
             Also contains functions to do things like count the pieces on the board and similar stuff
Move generation subsystem: Generates the possible moves/jumps that a particular piece can take on a particular board

Board representation:
---------------------

Checkers boards are represented via a padded array inside the checkers subsystem.
The padded array is an int array of length 46, and maps to a checkerboard as follows:
Note: is using an array idiomatic C++? Is there a better/more efficient way to represent the board?
 
   37  38  39  40
 32  33  34  35
   28  29  30  31
 23  24  25  26
   19  20  21  22
 14  15  16  17
   10  11  12  13
 05  06  07  08  

This way, incrementing the array by +5/+4/-4/-5 moves to the space up right/up left/down left/down right or a space that isn't on the board if the move is invalid.

Roadmap:
--------

- Get the game UI, all the game logic, and a simple AI that moves randomly set up and tested
- Plan out all the AI stuff

